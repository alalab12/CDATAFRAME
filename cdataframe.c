#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cdataframe.h"


//création dataframe vide
CDATAFRAME* creation_dataframe_vide() {
    CDATAFRAME* dataframe = (CDATAFRAME *)malloc(sizeof(CDATAFRAME));
    dataframe->columns = NULL;
    dataframe->number_columns = 0;
    dataframe->number_rows = 0;
    return dataframe;
}

//remplissage avec saisie utilisateur
void remplissage_utilisateur(CDATAFRAME* dataframe){
    for (int i=0; i < dataframe->number_columns; i++){
        int val;
        printf("Entrez des valeurs pour la colonne %s\n",dataframe->columns[i]->title);
        while (scanf("%d", &val)==1){
            insert_value(dataframe->columns[i], val);
            dataframe->number_rows++;
        }

    }
}

//remplissage en dur
void remplissage_dur(CDATAFRAME* dataframe, int** data, int number_rows, int number_columns){
    for (int i = 0; i < number_columns; i++) {
        COLUMN* column = create_column("Titre");
        for (int j = 0; j < number_rows; j++) {
            insert_value(column, data[j][i]);
        }

    }
}

//Afficher tous le dataframe
void afficher_dataframe(CDATAFRAME* dataframe){
    for (int i = 0; i < dataframe->number_columns; i++) {
        printf("%s:\n", dataframe->columns[i]->title);
        print_column(dataframe->columns[i]);
    }
}

//Afficher une partie des colonnes du dataframe
void afficher_certaines_colonne(CDATAFRAME* dataframe,int limite){
    for (int i = 0; i < dataframe->number_columns && i < limite; i++) {
        printf("%s:\n", dataframe->columns[i]->title);
        print_column(dataframe->columns[i]);
    }
}

//Afficher une partie des lignes du dataframe
void afficher_certaines_ligne(CDATAFRAME* dataframe,int limite){
    for (int i = 0; i < dataframe->number_columns; i++) {
        for (int j = 0; j < limite && j < dataframe->columns[i]->logical_size; j++) {
            printf("[%d] %d\n", j, dataframe->columns[i]->data[j]);
        }
    }
}

//ajouter une ligne de valeur
void ajouter_ligne_valeur(CDATAFRAME * dataframe, int* val){
    for (int i=0;i < dataframe->number_columns; i++){
        insert_value(dataframe->columns[i], val[i]);
    }
    dataframe->number_rows++;
}

//supprimer une ligne de valeurs


//ajouter une colonne
void ajouter_colonne(CDATAFRAME * dataframe, COLUMN* column) {
    dataframe->columns = realloc(dataframe->columns, (dataframe->number_columns + 1) * sizeof(COLUMN*));
    dataframe->columns[dataframe->number_columns] = column;
    dataframe->number_columns++;
}


//suprimer colonne
void supprimer_colonne(CDATAFRAME * dataframe, int index) {
    if (index < 0 || index >= dataframe->number_columns) {
        printf("Colonne inexistante\n");
    }
    free_column(&(dataframe->columns[index]));
    for (int i = index; i < dataframe->number_columns - 1; i++) {
        dataframe->columns[i] = dataframe->columns[i + 1];
    }

    dataframe->number_columns--;
}

//renomer la colonne
void renomer_colonne(CDATAFRAME * dataframe, int index, char* nouveau_titre) {

    if (index < 0 || index >= dataframe->number_columns) {
        printf("Colonne inexistante\n");
    }
    int nouveau_titre_longueur= strlen(nouveau_titre);

    // Reallocate memory for the title of the specified column
    char* temp = realloc(dataframe->columns[index]->title, (nouveau_titre_longueur + 1) * sizeof(char));
    dataframe->columns[index]->title = temp;

    for (int i = 0; i < nouveau_titre_longueur; i++) {
        dataframe->columns[index]->title[i] =nouveau_titre[i];
    }

    dataframe->columns[index]->title[nouveau_titre_longueur] = '\0';
}

//accéder à une valeur
int acceder_valeur(CDATAFRAME * dataframe, int ligne, int colonne) {
    if (ligne < 0 || ligne >= dataframe->number_rows || colonne < 0 || colonne >= dataframe->number_columns) {
        printf("Colonne ou ligne inexistante\n");
    }
    return dataframe->columns[colonne]->data[colonne];
}


//remplacer une valeur
void remplacer_valeur(CDATAFRAME * dataframe, int row, int col, int value) {
    // Check if the provided row and column indices are valid
    if (row < 0 || row >= dataframe->number_rows || col < 0 || col >= dataframe->number_columns) {
        printf("Invalid row or column index\n");
    }

    dataframe->columns[col]->data[row] = value;
}

//afficher titre colonne

void afficher_titre_colonne(CDATAFRAME* dataframe){
    printf("Noms des colonnes :\n");
    for (int i=0; i < dataframe->number_columns; i++){
        printf("%s\n",dataframe->columns[i]->title);
    }
}

//afficher le nombre de ligne
int nb_lignes(CDATAFRAME* dataframe){
    return dataframe->number_rows;
}

//afficher le nombre de colonne
int nb_colonnes(CDATAFRAME* dataframe){
    return dataframe->number_columns;
}

//Nombre de cellules avec une valeur égale à x
int nb_valeur_egale(CDATAFRAME* dataframe, int val){
    int cpt = 0;
    for (int i =0; i < dataframe->number_columns;i++){
        cpt+= val_egal(dataframe->columns[i], val);
        return cpt;
    }
}

//Nombre de cellules avec une valeur supérieur à x
int nb_valeur_sup(CDATAFRAME* dataframe, int val){
    int cpt = 0;
    for (int i =0; i < dataframe->number_columns;i++){
        cpt+= val_sup(dataframe->columns[i], val);
    }
        return cpt;
}

//Nombre de cellules avec une valeur inférieur à x
int nb_valeur_inf(CDATAFRAME* dataframe, int val){
    int cpt = 0;
    for (int i =0; i < dataframe->number_columns;i++){
        cpt+= val_inf(dataframe->columns[i], val);
    }
    return cpt;
}
