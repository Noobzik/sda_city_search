# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/28 12:22:35 by NoobZik           #+#    #+#              #
#    Updated: 2017/12/09 10:00:37 by NoobZik          ###   ########.fr        #
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

#Liste des fichiers *.o à rassembler en un executable
FICHIER = findCitiesList.o LinkedList.o zscore.o main.o BinarySearchTree.o

#Programme après la compilation
OUT = boxsearch

#Compilation séparé
CCSEP = $(CC) -c $(CFLAGS)

all:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -o $(OUT)

# Ici les dépendances de compilation de chaque ficher
# La commande à utiliser est $(CCSEP) ficher.c
# Exemple
#cercle.o : cercle.c
#	$(CCSEP) cercle.c

findCitiesList.o:findCitiesList.c
	$(CCSEP) findCitiesList.c

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
