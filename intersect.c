/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dryska <Emeric.Bayard@Outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:07:10 by Dryska            #+#    #+#             */
/*   Updated: 2017/12/04 09:50:02 by Dryska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LinkedList.h"
#include "intersect.h"

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

  while (tmpA != listA->last) {
    while (tmpB != listB->last) {
      if (comparison_fn_t(tmpA->value, tmpB->value)) {
        insertInLinkedList(listC, tmpA->value);
      }
      tmpB = tmpB->next;
    }
    tmpA = tmpA->next;
    tmpB = listB->head;
  }
  return listC;
}