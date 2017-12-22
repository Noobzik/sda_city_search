/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCitiesZBST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:46:00 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/22 11:00:24 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zscore.h"
#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>

int comparison_fn_t (const void *a, const void *b);

typedef union u_unionCity_u {
  const City *city;
  uint64_t    coded;
}             u_unionCity_t;
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

  BinarySearchTree    *bst   = newBST(&comparison_fn_t);
  LinkedList          *filtered;
  const City          *city;
  bool                error  = false;
  LLNode              *curr  = cities->head;
  uint64_t            *max   = (uint64_t *) zEncode(latitudeMax, longitudeMax);
  uint64_t            *min   = (uint64_t *) zEncode(latitudeMin, longitudeMin);
  u_unionCity_t       *unionCity_u;
  int                 i      = 0;

  unionCity_u = malloc(sizeof(u_unionCity_t)* cities->size);
  city = (const City*)curr->value;

  while (!error && curr != NULL) {
    city = (const City *) curr->value;
    unionCity_u[i].city = city;
    unionCity_u[i].coded = zEncode(city->latitude, city->longitude);
    error = error || !insertInBST(bst, &unionCity_u[i].coded, curr->value);
    curr = curr->next;
    i++;
  }

  if (error) {
    puts("Error while inserting");
    freeBST(bst, true);
    return NULL;
  }

  filtered = getInRange(bst, &min, &max);
  freeBST(bst, false);
  free(unionCity_u);
  return filtered;
}

int comparison_fn_t(const void* a, const void* b) {
  const uint64_t *a_ = a;
  const uint64_t *b_ = b;
  return  (*a_ > *b_) - (*a_ < *b_);
}
