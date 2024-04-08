
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

int insert_value(COLUMN *column, int value){
    int* new_data = NULL;
    // Vérifier qu'il y a assez d'espace disponible
    if (column->logical_size >= column->physical_size) {
        //Alloue un nouveau bloc de mémoire
        new_data = (int*)malloc((column->physical_size + REALLOC_SIZE) * sizeof(int));
    }

    //Cas d'erreur
    if (new_data == NULL){
        return 0;
    }

    //Copie des données dans le nouveau bloc
    for (int i=0; i < column->logical_size;i++){
        new_data[i] = column->data[i];
    }

    //Libérer l'ancien bloc
    free(column->data);

    //Mettre à jour le pointeur de donné
    column->data = new_data;

    //Mettre à jour la taille physique
    column->physical_size += REALLOC_SIZE;

    //Insérer la nouvelle valeur
    column->data[column->logical_size++] = value;

    return 1; //Indique la valeur à bien été insérée

}

//Supprime une colonne
void delete_column(COLUMN **column){

    //libération des données
    free((*column)->data);
    //libération du titre
    free((*column)->title);
    // libération de la colonne
    free(*column);
    *column =NULL;

}

// Affiche le contenu d'une colonne
void print_col(COLUMN* col) {
    for (int i = 0; i < col->logical_size; i++) {
        printf("[%d] %d\n", i, col->data[i]);
    }
}



