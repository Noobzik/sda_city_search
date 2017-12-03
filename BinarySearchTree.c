/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:28:18 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/03 15:21:48 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinarySearchTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct                tree_t {
  struct tree_t       *left;
  const void*          key;
  const void*          value;
  struct tree_t       *right;
};

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

BinarySearchTree* newBST (/*int comparison_fn_t(const void *, const void *) */) {
  BinarySearchTree *res = 0;
  if (!(res = malloc(sizeof(res)))) return res;
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
void freeBST(BinarySearchTree* bst, bool freeContent){
  if (bst == NULL) return;

  if (freeContent == true) {
    freeBST(bst->left, true);
    freeBST(bst->right, true);
  }
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
size_t sizeOfBST(const BinarySearchTree* bst) {
  return (bst == NULL) ? 0 :
   1 + sizeOfBST(bst->left) + sizeOfBST(bst->right);
}


/**
 * NOTE
 * Inserts a new key-value pair in the provided BinarySearchTree. This
 * specific implementation of the BST must handle duplicate keys.
 *
 * PARAMETERS
 * bst          A valid pointer to a BinarySearchTree object
 * key          The key of the new element or of the element to update
 *              We gonna use the key to sort our tree.
 * value        The value to store
 *
 * RETURN
 * res          A boolean equal to true if the new element was successfully
 *              inserted, false otherwise
 */

bool insertInBST(BinarySearchTree* bst, const void* key, const void* value) {
  if (bst == NULL) {
    bst = newBST();
    bst->key = key;
    bst->value = value;
    return true;
  }
  if (key == bst->key && value == bst->value) {
    return false;
  }
  if (key < bst->key) {
    insertInBST(bst->left, key, value);
    return true;
  }
  else {
    insertInBST(bst->right, key, value);
    return true;
  }
  return false;
}
