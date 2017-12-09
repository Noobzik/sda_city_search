/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities1BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:26:53 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/09 11:59:00 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax) {

  BinarySearchTree *bst = NULL;
  (void)           longitudeMax;
  (void)           longitudeMin;
  LinkedList       *filtered;
  const City       *city;

  LLNode* curr = cities->head;
  bool error = false;
  while (!error && curr != NULL) {
    city = (const City*)curr->value;
    error = error || !insertInBST(bst, &city->latitude, &curr->value);
    curr = curr->next;
  }
  if (error) {
    freeBST(bst, false);
    return NULL;
  }
  filtered = getInRange(bst, &latitudeMin, &latitudeMax);
  freeBST(bst, false);
  return filtered;
}
