/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities1BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:26:53 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/17 21:26:33 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <stdio.h>

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
    if (comparison_fn_t(&longitudeMin, &city->longitude) < 0
        && comparison_fn_t(&city->longitude, &longitudeMax) < 0)
         error = error || !insertInLinkedList(res, city);
    curr = curr->next;
  }

  freeBST(bst, true);
  freeLinkedList(filtered, false);
  return res;
}

int comparison_fn_t(const void* a, const void* b) {
  const double *a_ = a;
  const double *b_ = b;
  return  (*a_ > *b_) - (*a_ < *b_);
}
