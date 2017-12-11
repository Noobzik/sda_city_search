#include "BinarySearchTree.h"
#include "Pile.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct pile_t {
    BinarySearchTree *elem;
    struct pile_t *suiv;
} Pile;

/* initialise la pile */
Pile * pile_init (void)
{
    return NULL;
}


/* empile un noeud du BinarySearchTree */
void pile_empiler (Pile **self, BinarySearchTree *a)
{
    if (self != NULL && a != NULL)
    {
        Pile* res = malloc(sizeof(struct pile_t));
        if (res != NULL)
        {
            static Pile tmp = {0};
            *res = tmp;

            res->elem = a;
            res->suiv = *self;
            *self = res;
        }
    }
}

/* depile un noeud de l'BinarySearchTree */
BinarySearchTree * pile_depiler (Pile **self)
{
    BinarySearchTree *return_val = NULL;

    if (self != NULL && *self != NULL)
    {
        Pile *cur = *self;
        return_val = cur->elem;
        *self = cur->suiv;
        free(cur), cur = NULL;
    }

    return return_val;
}

/* teste si la pile est vide */
int pile_estVide (Pile *self)
{
    return self == NULL;
}
