/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dryska <emeric.bayard@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:07:10 by Dryska            #+#    #+#             */
/*   Updated: 2018/01/13 23:23:57 by NoobZik          ###   ########.fr       */
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

void MergeSort(LLNode **L, int cmp(const void*, const void*)) {

  LLNode* head = *L;
  LLNode* a;
  LLNode* b;

  /* Base case -- length 0 or 1 */
  if (!head || !head->next)
    return;


  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);

  /* Recursively sort the sublists */
  MergeSort(&a, cmp);
  MergeSort(&b, cmp);


  /* answer = merge the two sorted lists together */
  *L = SortedMerge(a, b, cmp);
}


void FrontBackSplit(LLNode* source,
          LLNode** frontRef, LLNode** backRef) {

  LLNode* fast;
  LLNode* slow;
  if (!source || !source->next) {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else {
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast) {
      fast = fast->next;
      if (fast) {
        slow = slow->next;
        fast = fast->next;
      }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}

LLNode* SortedMerge(LLNode* a, LLNode* b, int cmp(const void*, const void*)) {
  LLNode* result = NULL;

  /* Base cases */
  if (!a)
     return(b);
  else if (!b)
     return(a);

  /* Pick either a or b, and recur */
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
