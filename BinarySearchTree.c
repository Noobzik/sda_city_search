/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:28:18 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/06 22:39:27 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinarySearchTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct                tree_t {
  struct tree_t       *left;
  const void*          key;
  const void*          value;
  struct tree_t       *right;
};

BinarySearchTree *bstMinimum(BinarySearchTree *b);
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

BinarySearchTree* newBST (/*int comparison_fn_t(const void *, const void *)*/) {
  BinarySearchTree *res = 0;

  if (!(res = (BinarySearchTree*) malloc(sizeof(BinarySearchTree)))) return res;
  /*if (comparison_fn_t(key,value)) {
    res->right = NULL;
    res->left  = NULL;
  }*/
  else {
    res->right  = NULL;
    res->left   = NULL;
  }
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
  if (!freeContent) {
    if (bst->left != NULL && bst->right != NULL) {
      if (bst->right->left == NULL) {
        bst->right->left = bst->left;
        bst = bst->right;
      }
      else {
        y = bstMinimum(bst->right);
        tmp = y;
        y = tmp->right;
        tmp->left = bst->left;
        tmp->right = bst->right;
        bst = tmp;
      }
      return;
    }

    if (bst->left == NULL && bst->right != NULL) {
      bst = bst->right;
      return;
    }

    if (bst->left != NULL && bst->right == NULL) {
      bst = bst->left;
      return;
    }
  }

  else {
    if (bst != NULL) {
      freeBST(bst->left, false);
      freeBST(bst->right, false);
      free(bst);
    }
  }
}

/**
 * Search the Minimum of the given tree
 * @param  b [description]
 * @return   [description]
 */
BinarySearchTree *bstMinimum(BinarySearchTree *b) {
  while (b->left != NULL)
    b = b->left;
  return b;
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
inline size_t sizeOfBST (const BinarySearchTree* bst) {
  return (bst == NULL) ? 0 : 1 + sizeOfBST(bst->left) + sizeOfBST(bst->right);
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
  if (bst == NULL) {
    bst = newBST();
    assert(bst != 0);
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
  assert(bst != NULL);
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
/*
LinkedList* getInRange(const BinarySearchTree* bst, void* keyMin, void* keyMax){
  assert(bst != NULL);

  if (bst->key < keyMin) {
    return getInRange(bst->right, keyMin, keyMax);
  }
  if (bst->key > keyMax) {
    return getInRange(bst->left, keyMin, keyMax);
  }

  LinkedList* tmp = 0;
  LinkedList* res = 0;

  insertInLinkedList(tmp, bst);
  while ((sizeOfLinkedList(tmp) < sizeOfBST(bst)) && (tmp->head != tmp->last)) {
    insertInLinkedList(res, tmp->head->value);
    if (bst->right != NULL) insertInLinkedList(tmp, bst->right);
    if (bst->left != NULL) insertInLinkedList(tmp, bst->left);
    tmp->head = tmp->head->next;
  }
  return res;

}*/
/**
 * Function edited by noobzik thinking in case of major breakdown
 * @param  bst    [description]
 * @param  keyMin [description]
 * @param  keyMax [description]
 * @return        [description]
 */

LinkedList *getInRange(const BinarySearchTree *bst, void *keyMin, void *keyMax){
  assert(bst != NULL);

  while (bst->key != keyMin) {
    (bst->key < keyMin) ?   (bst = bst->left) :
                            (bst = bst->right);
    if (bst->left == NULL && bst->right == NULL)
      return newLinkedList();
    if (bst->key == keyMin) break;
    else                    continue;
  }

  LinkedList *tmp = 0;
  LinkedList *res = 0;

  if(!insertInLinkedList(tmp, bst))
    return NULL;
  while (bst->key < keyMax) {
    if (!insertInLinkedList(res, tmp->head->value))
      return NULL;
    if (bst->right != NULL)
      if(!insertInLinkedList(tmp, bst->right))
        return NULL;
    if (bst->left != NULL)
      if (!insertInLinkedList(tmp, bst->left))
        return NULL;
    tmp->head = tmp->head->next;
  }
  return res;
}
