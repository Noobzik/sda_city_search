/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dryska <emeric.bayard@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:07:10 by Dryska            #+#    #+#             */
/*   Updated: 2018/01/14 08:46:56 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** Previous algorithm wriiten by Dryska
  * Major speed optimisation by NoobZik
  */

#include "LinkedList.h"
#include "intersect.h"
#include "City.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void    MergeSort     (LLNode **L,           int cmp(const void*, const void*));
LLNode* SortedMerge   (LLNode* a, LLNode* b, int cmp(const void*, const void*));
void    FrontBackSplit(LLNode* source, LLNode** frontRef, LLNode** backRef);

/* ------------------------------------------------------------------------- *
 * Computes the intersection of `listA` and `listB`. Both lists must contain
 * objects comparable by `comparison_fn_t`
 *
 *
 *
 * PARAMETERS
 * listA                A valid pointer to a linked list object
 * listB                A valid pointer to a linked list object
 * comparison_fn_t      A comparison function
 *
 * RETURN
 * intersection     A linked list containing the intersection or NULL in case of
 *                  error. If there are no elements in the intersection, an
 *                  empty list must be returned
 *
 * COMPARISON FUNCTION
 * comparison_fn_t(a, b) < 0    <=> a < b
 * comparison_fn_t(a, b) = 0    <=> a == b
 * comparison_fn_t(a, b) > 0    <=> a > b
 *
 * Note that an element `a` of `listA` must belong to the intersection if
 * and only if there exists an element `b` in `listB` such that
 * comparison_fn_t(a, b) = 0
 * In particular, the element `a` and `b` could have different memory addresses
 * but still represent the same city.
 * ------------------------------------------------------------------------- */

LinkedList* intersect(const LinkedList* listA, const LinkedList* listB,
                      int comparison_fn_t(const void *, const void *)) {

  LLNode *tmpA = listA->head;
  LLNode *tmpB = listB->head;
  LinkedList* listC = newLinkedList();
  int (*cmp) (const void*, const void*) = comparison_fn_t;

  MergeSort(&tmpA, comparison_fn_t);
  MergeSort(&tmpB, comparison_fn_t);

  while (tmpA && tmpB) {
    if (cmp(tmpA->value, tmpB->value) < 0)
      tmpA = tmpA->next;
    else if (cmp(tmpA->value, tmpB->value) > 0)
      tmpB = tmpB->next;
    else if(cmp(tmpA->value, tmpB->value) == 0){
      if(!insertInLinkedList(listC, tmpA->value)) {
        freeLinkedList(listC, false);
        printf("Assertion failed line 73, intersection.c.)"
               " insertInLinkedList(listC, tmp->value)\n");
        return NULL;
      }
      tmpA = tmpA->next;
      tmpB = tmpB->next;
    }
    else {
      puts("Erreur de comparaison");
      break;
    }
  }

  return listC;
}

/**
 * MergeSort()
 * Sort a LinkedList by alphabetical up order. Changes only the pointers.
 * Base case : exit the MergeSort is the lenght is 0 or 1
 * Split head into two sublist.
 * Recursively sort the sublist
 * Merge the two sublist into the source list.
 *
 * Estimated overall complexity is around O(n log n)
 *
 * @param L      LLNode pointer to first Node list
 * @param (*cmp) A generic function pointer to a comparison function
 */
void MergeSort(LLNode **L, int cmp(const void*, const void*)) {
  LLNode* head = *L;
  LLNode* a;
  LLNode* b;

  if (!head || !head->next)
    return;

  FrontBackSplit(head, &a, &b);
  MergeSort(&a, cmp);
  MergeSort(&b, cmp);

  *L = SortedMerge(a, b, cmp);
}

/**
 * FrontBackSplit()
 * Split the nodes of the given list (source) into front and bacj halves.
 * Return the two list using the reference parameters.
 * If the lenght id odd, node + 1 to the front list.
 * Fast / slow pointer stategy
 * Base case : If the lenght of the list is less than 2. the front list will
 * take the source list and the back list will be null.
 *
 * The fast pointer will advance by 2 node for the fast node and advance by 1
 * the slow pointer.
 *
 * The slow pointer is right before the midpoint of the assumed sources list,
 * so split it in two
 * at that point.
 * @param source   (LLNode *) Source list
 * @param frontRef (LLNode *) A pointer to the front list
 * @param backRef  (LLNode *) A pointer to the back list
 */
void FrontBackSplit(LLNode* source, LLNode** frontRef, LLNode** backRef) {
  LLNode* fast;
  LLNode* slow;

  if (!source || !source->next) {
    *frontRef = source;
    *backRef = NULL;
  }
  else {
    slow = source;
    fast = source->next;

    while (fast) {
      fast = fast->next;
      if (fast) {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}

/**
 * SortedMerge()
 * Compare two node and sort accordingly by the given result of the comparison
 * Base case : a is nulled -> return b (respectively b)
 * If a is lower than/equals to , b, the result will be a. and Recursively check
 * the next node of a->next;
 * Else b will the result and Recursively check the next of b->next
 * @param a (LLNode *)
 * @param b (LLNode *)
 * @return The result node of the comparison.
 */
LLNode* SortedMerge(LLNode* a, LLNode* b, int cmp(const void*, const void*)) {
  LLNode* result = NULL;

  if (!a)
     return(b);
  else if (!b)
     return(a);

  if (cmp(a->value, b->value) <= 0) {
     result = a;
     result->next = SortedMerge(a->next, b, cmp);
  }
  else {
     result = b;
     result->next = SortedMerge(a, b->next, cmp);
  }
  return(result);
}
