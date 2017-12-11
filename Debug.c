/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dryska <Emeric.Bayard@Outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 11:46:50 by Dryska            #+#    #+#             */
/*   Updated: 2017/12/11 12:47:54 by Dryska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "intersect.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {

  BinarySearchTree *bst = 0;

  int a = 1;
  int b = 2;
  int c = 3;

  const int *var1;
  const int *var2;
  const int *var3;

  var1 = &a;
  var2 = &b;
  var3 = &c;

  insertInBST(bst, var1, var1);
  insertInBST(bst, var2, var2);
  insertInBST(bst, var3, var3);
  printf("%lu\n", sizeOfBST(bst));


  freeBST(bst, true); //demolition


  return 0;
}
