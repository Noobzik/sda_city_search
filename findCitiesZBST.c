/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCitiesZBST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:46:00 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/17 21:32:35 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zscore.h"
#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <stdio.h>

int comparison_fn_t (const void *a, const void *b);
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

  BinarySearchTree    *bst = newBST(&comparison_fn_t);
  LinkedList          *filtered;
  const City          *city;
  uint64_t            coded;
  bool                error = false;
  LLNode              *curr = cities->head;
  uint64_t            max   = zEncode(latitudeMax, longitudeMax);
  uint64_t            min   = zEncode(latitudeMin, longitudeMin);

  printf("Minimum morton code : %d\n", (int) min);
  printf("Maximum morton code : %d\n", (int) max);

  while (!error && curr != NULL) {
    city = (const City *) curr->value;
    coded = zEncode(city->latitude, city->longitude);
    printf("Coded = %d\n", (int) coded);
    error = error || !insertInBST(bst, &coded, curr->value);
    curr = curr->next;
  }

  if (error) {
    puts("Error while inserting");
    freeBST(bst, true);
    freeLinkedList(cities, true);
    return NULL;
  }

  freeBST(bst, true);
  filtered = getInRange(bst, &min, &max);

  return filtered;
}

int comparison_fn_t (const void *a, const void *b) {
  const uint64_t* a_ = a;
  const uint64_t* b_ = b;

  return  (*a_ > *b_) - (*a_ < *b_);
}
