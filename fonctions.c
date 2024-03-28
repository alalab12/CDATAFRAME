
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"


#define REALOC_SIZE 256

COLUMN *create_column(char* title){
    COLUMN *column;
    //initialisation données
    column->data = NULL;

    //initialisation de la taille physique
    column->physical_size = 0;

    //initialisation de la taille logique
    column->logical_size = 0;

    //allocation de la mémoire pour le titre
    column->title = (char*)malloc((strlen(title) + 1) * sizeof(char));

    //allocation de la mémoire pour la colonne
    column = (COLUMN*)malloc(sizeof(COLUMN));
}

int insert_value(COLUMN* column, int value){
    if



}
