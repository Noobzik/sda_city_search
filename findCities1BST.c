/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findCities1BST.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:26:53 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/10 21:13:18 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "City.h"
#include "findCities.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <stdio.h>

LinkedList* findCities(LinkedList* cities,
                       double latitudeMin,
                       double latitudeMax,
                       double longitudeMin,
                       double longitudeMax) {

  BinarySearchTree *bst = newBST();
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
  print_inorder(bst);
  printf("Taille de l'arbre Avant get in range: %lu\n", sizeOfBST(bst));
  filtered = getInRange(bst, &latitudeMin, &latitudeMax);
  printf("Taille de l'arbre : %lu\n", sizeOfBST(bst));
  freeBST(bst, true);
  return filtered;
}
