/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:28:18 by NoobZik           #+#    #+#             */
/*   Updated: 2017/11/30 21:42:46 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinarySearchTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
  * Creates an empty BinarySearchTree (or BST).
  *
  * The BST must later be deleted by calling freeBinarySearchTree().
  *
  * @oaram comparison_fn_t   A comparison function
  * @return A pointer to the BinarySearchTree, or NULL in case of
  *         error
  *
  * COMPARISON FUNCTION
  * comparison_fn_t(a, b) < 0    <=> a < b
  * comparison_fn_t(a, b) = 0    <=> a == b
  * comparison_fn_t(a, b) > 0    <=> a > b
  *
  * USAGE (example for doubles: http://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html)
  * int compare_doubles(const void* a, const void* b)
  * {
  *     const double* a_ = (const double*)a;
  *     const double* b_ = (const double*)b;
  *     return (*a_ > *b_) - (*a_ < *b_)
  * }
  * ...
  * BinarySearchTree bst = newBST(&compare_doubles);
  *
  */
BinarySearchTree* newBST(int comparison_fn_t(const void *a, const void *b)) {

	BinarySearchTree *res = NULL;
	res = malloc(sizeof(BinarySearchTree));
    
    if (res == NULL) {
        fprintf("Impossible d'allouer le noeud !\n");
        return NULL;
        
    }
	res->right = NULL;
	res->left  = NULL;

	return res;
}

/**
 * Frees the allocated memory of the given BinarySearchTree.
 *
 * NOTE
 * The const qualifier will be exceptionally discarded if freeContent == true
 * to allow the deletion of the content.
 * @param bst         A valid pointer to a BinarySearchTree object
 * @param freeContent Whether to free the content as well.
 */
void freeBST(BinarySearchTree* bst, bool freeContent) {
	if (bst == NULL) return;

	if (freeContent == true) {
		freeBST(bst->left, true);
		freeBST(bst->right, true);
		free(bst->keys);
	}

/**
 * Return the number of cityes contained in the tree.
 *
 * NOTE
 *
 * Recursiv course of the tree.
 * @param bst         A valid pointer to a BinarySearchTree object
 * @param n           A integer that represent number of element in bst
 * PURE
 */
 
 int sizeOfBST(BinarySearchTree* bst, int n) {
     if (bst == NULL) {
         return n;
     }
     else {
         n = n + 1;
         return (sizeOfBST(bst->left, n) + sizeOfBST(bst->right, n));
 }
 
 
 /**
 * 
 *
 * NOTE
 *
 * insert a node in a BST-longitude 
 * @param bst         A valid pointer to a BinarySearchTree object
 * @param long        A integer that represent longitude of a city
 * @param lat         A integer that represent latitude of a city
 */
 
 void insertInBST(BinarySearchTree* bst, float longitude, float latitude) {
     if (bst == NULL) {
         printf("Impossible d'insérer un noeud dans un arbre vide ! Meme pour Mr.Hernandez !\n");
     }
     else {
     
     }
 }