/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:28:18 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/15 19:11:08 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinarySearchTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct                tree_t {
  struct tree_t       *root;
  struct tree_t       *left;
  const void*          key;
  const void*          value;
  int (*compare)      (const void*, const void*);
  struct tree_t       *right;
};

void *extractFile(LinkedList *file);
// int comparison_fn_t(const void* , const void* );

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
BinarySearchTree* newBST (int comparison_fn_t(const void*, const void*)) {
  BinarySearchTree *res = malloc(sizeof(BinarySearchTree));
  assert(res != NULL);
  res->value = NULL;
  res->key = NULL;
  res->right  = 0;
  res->left   = 0;
  res->root   = 0;
  res->compare = comparison_fn_t;
  return res;
}

/**
 * Frees the allocated memory of the given BinarySearchTree.
 *
 * First Case : Left and right are not nulled
 * Look for the successor of the right side
 *
 * Second case : Right is null, the current bst take the bst->left
 * Third case : Left is null, the current bst take the bst->right
 *
 * NOTE
 * The const qualifier will be exceptionally discarded if freeContent == true
 * to allow the deletion of the content.
 * @param bst         A valid pointer to a BinarySearchTree object
 * @param freeContent Whether to free the content as well.
 */

void freeBST (BinarySearchTree* bst, bool freeContent){
  BinarySearchTree *y;
  BinarySearchTree *tmp;

  if (sizeOfBST(bst) == 0) {
    puts("Je suis la dans size = 0");
    free(bst);
    return;
  }

  if (freeContent == false) {


    if (!(bst->left) && !(bst->right)) {
      bst = bst->right;
      return;
    }

    if (bst->left && !(bst->right)) {
      bst = bst->left;
      return;
    }

    if (bst->left && bst->right) {
      if (!(bst->right->left)) {
        bst->right->left = bst->left;
        bst = bst->right;
      }
      else {
        y = bst;
        while (y->left)
          y = y->left;
        tmp = y;
        y = tmp->right;
        tmp->left = bst->left;
        tmp->right = bst->right;
        bst = tmp;
      }
      return;
    }
  }

  else {
    if (bst) {
      freeBST(bst->left, true);
      freeBST(bst->right, true);
      free(bst);
    }
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
size_t sizeOfBST (const BinarySearchTree* bst) {
  return (bst == 0) ? 0 : 1 + sizeOfBST(bst->left) + sizeOfBST(bst->right);
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

bool insertInBST (BinarySearchTree* bst, const void* key, const void* value) {
  if (!bst->key) {
    bst->key = key;
    bst->value = value;
    return true;
  }
  if (key > bst->key) {
    if (bst->right) {
      return insertInBST (bst->right, key, value);
    }
    else {
      BinarySearchTree *tmp = newBST(bst->compare);
      tmp->key   = key;
      tmp->value = value;
      tmp->root  = bst;
      bst->right = tmp;
      return true;
    }
  }
  if (key < bst->key) {
    if (bst->left) {
      return insertInBST(bst->left, key, value);
    }
    else {
      BinarySearchTree *tmp = newBST(bst->compare);
      tmp->key = key;
      tmp->value = value;
      tmp->root  = bst;
      bst->left = tmp;
      return true;
    }
  }
  return false;
}


/* ------------------------------------------------------------------------- *
 * Return the value associated to that key, if any
 *
 * PARAMETERS
 * bst          A valid pointer to a BinarySearchTree object
 * key          The key to look for
 *
 * RETURN
 * res          One of the value corresping to that key. Or NULL if the key
 *              is not present in the BST
 * ------------------------------------------------------------------------- */

const void* searchBST (BinarySearchTree* bst, const void* key) {
  if (sizeOfBST(bst) == 0)
    return NULL;
  if (key == bst->key) return bst->value;
  return (key < bst->key) ? searchBST(bst->left, key) :
                            searchBST(bst->right, key);
}


/* ------------------------------------------------------------------------- *
 * Finds a set of elements in the provided BinarySearchTree whose the keys
 * are included in a range [key1, key2] and returns their values. The values
 * are sorted in the increasing order of the keys.
 *
 * PARAMETERS
 * bst          A valid pointer to a BinarySearchTree object
 * keyMin       Lower bound of the range (inclusive)
 * keyMax       Upper bound of the range (inclusive)
 *
 * RETURN
 * ll           A linkedList containing the element in the given range, or
 *              NULL in case of allocation error.
 *
 * NOTES
 * The linkedList must be freed but not its content
 * If no elements are in the range, the function returns an empty linked-list
 * ------------------------------------------------------------------------- */

LinkedList *getInRange(const BinarySearchTree *bst, void *keyMin, void *keyMax){
  LinkedList* file = newLinkedList();
  LinkedList* res = newLinkedList();
  BinarySearchTree *temp = (BinarySearchTree *) bst;

  if (temp->compare(keyMin, keyMin) == 0)

  while (temp) {

    if (temp->compare(keyMin, temp->key) < 0
        && temp->compare(temp->key, keyMax) < 0)
      if (!insertInLinkedList(res, temp->value)) return NULL;

    if (temp->left)
      if (!insertInLinkedList(file, temp->left)) return NULL;
    if (temp->right)
      if (!insertInLinkedList(file, temp->right)) return NULL;
    temp = extractFile(file);
  }
  freeLinkedList(file,false);
  return res;
}

/**
 * Extract a node at the end of the queue
 * @param file A LinkedList
 * @return A generic pointer to the data.
 */
void *extractFile(LinkedList *file) {
  void *res = 0;
  LLNode* node = 0;

  if (!(file->size == 0)) {
    node = file->head;
    file->head = node->next;
    file->size--;
    if (!(file->size == 0)) {
      node->next = 0;
    }
    else {
      file->head = 0;
      file->last = 0;
    }
  }

  if (node) res = (void *) node->value;

  free(node);
  return res;
}
