/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities1BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:26:53 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/15 19:07:57 by NoobZik          ###   ########.fr       */
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

  BinarySearchTree *bst = newBST(&comparison_fn_t);
  (void)           longitudeMax;
  (void)           longitudeMin;
  LinkedList       *filtered;
  const City       *city;

  LLNode* curr = cities->head;
  bool error = false;
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
  //freeBST(bst, true);
  return filtered;
}

int comparison_fn_t(const void* a, const void* b) {
  const double *a_ = a;
  const double *b_ = b;
  return  (*a_ > *b_) - (*a_ < *b_);
}
