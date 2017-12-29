/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCitiesZBST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:46:00 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/29 01:08:24 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zscore.h"
#include "City.h"
#include "findCities.h"
#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int comparison_fn_t (const void *a, const void *b);
int comparison_double_t(double a, double b);

typedef struct u_unionCity {
  const City  *city;
  uint64_t    coded;
}             s_unionCity_t;
/* ------------------------------------------------------------------------- *
 * Find all the cities in a box.
 *
 * PARAMETERS
 * cities           A valid pointer to a linked list containing all the cities
 * latitudeMin      The minimum latitude defining the box
 * latitudeMax      The maximum latitude defining the box
 * longitudeMin     The minimum logitude defining the box
 * longitudeMax     The maximum logitude defining the box
 *
 * RETURN
 * filtered         A linked list containing the cities within the box,
 *                  or NULL in case of error.
 *                  Note that if no cities are within the box, this function
 *                  will return an empty linked list (not NULL).
 * ------------------------------------------------------------------------- */

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax) {

  const City          *city;
  LinkedList          *filtered;
  s_unionCity_t       *unionCity;
  BinarySearchTree    *bst     = newBST(&comparison_fn_t);
  LinkedList          *res     = newLinkedList();
  LLNode              *curr    = cities->head;
  bool                error    = false;
  uint64_t            min      = zEncode(latitudeMin, longitudeMin);
  uint64_t            max      = zEncode(latitudeMax, longitudeMax);
  uint64_t            *ptr_min = &min;
  uint64_t            *ptr_max = &max;
  int                 i        = 0;

  unionCity = malloc(sizeof(s_unionCity_t)* cities->size);
  city = (const City*)curr->value;

  assert(-90 <= latitudeMin && latitudeMax <= 90);
  assert(-180 <= longitudeMin && longitudeMax <= 180);

  while (!error && curr != NULL) {
    assert(i < (int) cities->size);
    unionCity[i].city = city = (const City *) curr->value;
    unionCity[i].coded = zEncode(city->latitude, city->longitude);
    error = error || !insertInBST(bst, &unionCity[i].coded, unionCity[i].city);
    curr = curr->next;
    i++;
  }


  if (error) {
    puts("Error while inserting");
    freeBST(bst, false);
    return NULL;
  }

  filtered = getInRange(bst, ptr_min, ptr_max);

  curr = filtered->head;

  while (curr) {
    city = (const City *) curr->value;
    if (city == NULL) {
      curr = curr->next;
      continue;
    }
    if ((comparison_double_t(city->longitude, longitudeMax) <= 0)
          && (comparison_double_t(city->latitude, latitudeMax) <= 0)
          && (comparison_double_t(latitudeMin, city->latitude) <= 0)
          && (comparison_double_t(longitudeMin, city->longitude) <= 0)) {
            error = error || !insertInLinkedList(res, city);
    }
    curr = curr->next;
  }

  if (error) {
    puts("Error while inserting");
    freeLinkedList(filtered, false);
    freeLinkedList(res, false);
    freeBST(bst, false);
    return NULL;
  }

  freeBST(bst, false);
  free(unionCity);
  freeLinkedList(filtered, false);
  return res;
}

/**
 * Compare two Const void*
 *
 * a < b    <=>   foo(a,b) < 0
 * a > b    <=>   foo(a,b) > 0
 * a = b    <=>   foo(a,b) == 0
 *
 * @param a 1st void *
 * @param b 2nd void *
 * @return Boolean calculus.
 */
int comparison_fn_t(const void* a, const void* b) {
  const uint64_t *a_ = a;
  const uint64_t *b_ = b;
  return  (*a_ > *b_) - (*a_ < *b_);
}

/**
 * Compare two Unit64 types
 *
 * a < b    <=>   foo(a,b) < 0
 * a > b    <=>   foo(a,b) > 0
 * a = b    <=>   foo(a,b) == 0
 *
 * @param a 1st uint64_t
 * @param b 2nd uint64_t
 * @return Boolean calculus.
 */
inline int comparison_double_t(double a, double b) {
  return  (a > b) - (a < b);
}
