/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities2BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 20:39:53 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/15 22:34:15 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include "intersect.h"
#include <stdio.h>
#include <string.h>

int comparison_fn_t(const void *a, const void *b);
int comparison_city_t(const void* a, const void* b);
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
  BinarySearchTree     *bst_lat = newBST(&comparison_fn_t);
  BinarySearchTree     *bst_lon = newBST(&comparison_fn_t);
  LinkedList           *res;
  LinkedList       *filtered_lat;
  LinkedList       *filtered_lon;
  const City       *city;

  /** Latitude **/

  LLNode* curr = cities->head;
  bool error = false;
  while (!error && curr != NULL) {
    city = (const City*)curr->value;
    error = error || !insertInBST(bst_lat, &city->latitude, curr->value);
    curr = curr->next;
  }

  filtered_lat = getInRange(bst_lat, &latitudeMin, &latitudeMax);
  printf("Size of filtered_lat%d\n", (int)filtered_lat->size);
  /** Longitude **/

  curr = cities->head;
  error = false;
  while (!error && curr != NULL) {
    city = (const City*)curr->value;
    error = error || !insertInBST(bst_lon, &city->longitude, curr->value);
    curr = curr->next;
  }
  filtered_lon = getInRange(bst_lon, &longitudeMin, &longitudeMax);

  res = intersect(filtered_lat, filtered_lon, &comparison_fn_t);

  freeLinkedList(filtered_lat, false);
  freeLinkedList(filtered_lon, false);
  freeBST(bst_lat, true);
  freeBST(bst_lon, true);
  return res;
}

int comparison_fn_t(const void* a, const void* b) {
  const double *a_ = a;
  const double *b_ = b;
  return  (*a_ > *b_) - (*a_ < *b_);
}

int comparison_city_t(const void* a, const void* b) {
  const City *a_ = a;
  const City *b_ = b;

  if (strcmp(a_->name, b_->name) == 0) {
    if (a_->latitude == b_->latitude) {
      if (a_->longitude == b_->longitude)
        return 1;
    }
  }
  return  0;
}
