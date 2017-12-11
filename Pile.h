#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"


#ifndef _PILE_H_
#define _PILE_H_

/*Opaque structure*/

typedef struct pile_t Pile;


Pile *pile_init (void);
void pile_empiler (Pile **self, BinarySearchTree *a);
BinarySearchTree *pile_depiler (Pile **self);
int pile_estVide (Pile *self);

#endif // !_PILE_H_
