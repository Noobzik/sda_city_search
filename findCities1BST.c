/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities1BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:26:53 by NoobZik           #+#    #+#             */
/*   Updated: 2018/01/22 17:35:06 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "City.h"
#include "findCities.h"
#include "BinarySearchTree.h"
#include <stdio.h>
#include <assert.h>

int comparison_fn_t(const void* a, const void* b);

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax) {

  BinarySearchTree    *bst = newBST(&comparison_fn_t);
  LinkedList          *filtered;
  const City          *city;
  int                 i     = -1;
  bool                error = false;
  LLNode              *curr = cities->head;
  LinkedList          *res  = newLinkedList();

  assert(-90 <= latitudeMin && latitudeMax <= 90);
  assert(-180 <= longitudeMin && longitudeMax <= 180);

  while (!error && curr != NULL) {
    city = (const City*)curr->value;
    error = error || !insertInBST(bst, &city->latitude, curr->value);
    curr = curr->next;
  }

  if (error) {
    puts("Error while inserting");
    freeBST(bst, true);
    return NULL;
  }


  filtered = getInRange(bst, &latitudeMin, &latitudeMax);

  curr = filtered->head;
  while (++i < (int) filtered->size && !error) {
    city = (const City*)curr->value;
    if (comparison_fn_t(&longitudeMin, &city->longitude) <= 0
        && comparison_fn_t(&city->longitude, &longitudeMax) <= 0)
         error = error || !insertInLinkedList(res, city);
    curr = curr->next;
  }

  if (error) {
    puts("Error while inserting");
    freeLinkedList(res, true);
    return NULL;
  }

  freeBST(bst, false);
  freeLinkedList(filtered, false);
  return res;
}

int comparison_fn_t(const void* a, const void* b) {
  const double *a_ = (const double *) a;
  const double *b_ = (const double *) b;
  return  (*a_ > *b_) - (*a_ < *b_);
}
