

#include <stdlib.h>
#include <string.h>
#include "column.h"
#include <stdio.h>

#define REALLOC_SIZE 256



//création d'une colonne
COLUMN* create_column(char* title){

    //allocation de la mémoire pour la colonne
    COLUMN* col = (COLUMN*)malloc(sizeof(COLUMN));

    //initialisation données
    col->data = NULL;

    //initialisation de la taille physique
    col->physical_size = 0;

    //initialisation de la taille logique
    col->logical_size = 0;

    //allocation de la mémoire pour le titre
    column->title= (char*) malloc((strlen(title)+1)*sizeof(char));
    strcpy(column->title, title);

    return col;
}


//insertion de valeur
int insert_value(COLUMN* column, int value){
    //si la taille physique = taille logique, il faut ajouter de l'espace
    if (column->logical_size == column->physical_size) {
        int *new_data = malloc((column->physical_size + REALLOC_SIZE) * sizeof(int));

        if (!new_data) { //cas d'erreur
            return 0;
        }
        //Copie des données
        for (int i = 0; i < column->physical_size; i++) {
            new_data[i] = column->data[i];
        }

        free(column->data);
        column->data = new_data;
        column->physical_size += 256;
    }
    //sinon on rajoute seulement la valeur et on change la taille logique 
    column->data[column->logical_size] = value;
    column->logical_size++;

    return 1;

}

//Supprime une colonne
void free_column(COLUMN** column){

    //libération des données
    free((*column)->data);
    //libération du titre
    free((*column)->title);
    // libération de la colonne
    free(*column);
    *column =NULL;

}

// Affiche le contenu d'une colonne
void print_column(COLUMN* col) {
    printf("%s:\n", col->title);
    for (int i = 0; i < col->logical_size; i++) {
        printf("[%d] %d\n", i, col->data[i]);
    }
}

//Retourne le nombre d'occurence de la valeur x
int nb_occurence(COLUMN* col, int x){
    //Initialisation du compteur
    int cpt = 0;
    for(int i=0; i<col->logical_size;i++){
        //Vérifie si la valeur est la même que x
        if(col->data[i]==x){
            cpt++;
        }
    }

    return cpt;
}

//Retourne la valeur à la position x
int x_pos(COLUMN* col, int x){
    return col->data[x];
}

//Retourne le nombre de valeur supérieure à x
int val_sup(COLUMN* col, int x){
    int cpt=0;
    for(int i=0; i<col->logical_size;i++){
        //Vérifie si la valeur est supérieure à x
        if(col->data[i]>x){
            cpt++;
        }
    }
    return cpt;
}

//Retourne le nombre de valeur inférieure à x
int val_inf(COLUMN* col, int x){
    int cpt=0;
    for(int i=0; i<col->logical_size;i++){
        //Vérifie si la valeur est inférieure à x
        if(col->data[i]<x){
            cpt++;
        }
    }
    return cpt;
}

//Retourne le nombre de valeur égal à x
int val_egal(COLUMN* column, int x){
    int cpt=0;
    for(int i=0; i < column->logical_size; i++){
        //vérifie si la valeur est égale à x
        if(column->data[i]==x){
            cpt++;
        }
    }
    return cpt;
}


