# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/28 12:22:35 by NoobZik           #+#    #+#              #
#    Updated: 2017/12/17 22:39:29 by NoobZik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Projet imcopilable avec C90, n'essayez pas de compiler sur windows... J'en ai fais les frais
# Indication du compilateur
CC=gcc

#Objectif 0 WARNING, donc inclusion de tout les warnings possibles, Wall est trop gentil...
WARNING :=  -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
		-Wuninitialized -Wconversion -Wstrict-prototypes
# Flags du compilateur
CFLAGS = -g -O3 $(WARNING) -std=c99

# On force la derniere norme de compilation qui est C11
FICHIER =
#Liste des fichiers *.o à rassembler en un executable
FICHIER0 = findCitiesList.o LinkedList.o main.o BinarySearchTree.o
#
# Premier alogrithme sur latitude + filtre longitude
FICHIER1 = findCities1BST.o LinkedList.o main.o BinarySearchTree.o

# Deuxieme alogrithme sur intersect de 2 ABR
FICHIER2 = findCities2BST.o LinkedList.o main.o BinarySearchTree.o intersect.o

# Troiseme alogrithme sur le code morton sur ABR
FICHIER3 = findCitiesZBST.o LinkedList.o main.o BinarySearchTree.o intersect.o \
		zscore.o

#Programme après la compilation
OUT = boxsearch

#Compilation séparé
CCSEP = $(CC) -c $(CFLAGS)

0:$(FICHIER0)
	$(CC) $(FICHIER0) $(CFLAGS) -o $(OUT)

1:$(FICHIER1)
	$(CC) $(FICHIER1) $(CFLAGS) -o $(OUT)

2:$(FICHIER2)
	$(CC) $(FICHIER2) $(CFLAGS) -o $(OUT)

3:$(FICHIER3)
	$(CC) $(FICHIER3) $(CFLAGS) -o $(OUT)
# Ici les dépendances de compilation de chaque ficher
# La commande à utiliser est $(CCSEP) ficher.c
# Exemple
#cercle.o : cercle.c
#	$(CCSEP) cercle.c

findCitiesList.o:findCitiesList.c
	$(CCSEP) findCitiesList.c

findCities1BST.o:findCities1BST.c
	$(CCSEP) findCities1BST.c

findCities2BST.o:findCities2BST.c
	$(CCSEP) findCities2BST.c

findCitiesZBST.o:findCitiesZBST.c
	$(CCSEP) findCitiesZBST.c

LinkedList.o:LinkedList.c
	$(CCSEP) LinkedList.c

zscore.o:zscore.c
	$(CCSEP) zscore.c

BinarySearchTree.o:BinarySearchTree.c
	$(CCSEP) BinarySearchTree.c

main.o:main.c
	$(CCSEP) main.c

# NE PAS TOUCHER EN BAS DE CETTE LIGNE
# Nettoie les junk .o et le prog, surement pour recompiler à zéro
clean:
	rm *.o
	rm $(OUT)

# Nettoie les fichier junk généré par Atom linter, en plus du prog, si vous avez touché au .h et .c en meme temps
clean-atom:
	rm src/header/*.gch
	rm *.o
	rm $(OUT)

# Sert a re-compiler à partir de 0
rebuild:clean all

# Sert a recompiler à partir de 0 et de lancer le prog
# Pour les flemmards et pour les big boss des 0 warning + 0 Erreurs
rebuild-run: rebuild
	./$(OUT)

# Compile le programme et execute directement, pour les flemmard du fleche haut
build-run:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -o $(OUT)
	./$(OUT)

debug:
	valgrind ./$(OUT) cities_10.csv 1 1 10 10

debug1000:
	valgrind ./$(OUT) cities_1000.csv 1 1 10 10
