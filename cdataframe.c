
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include <stdio.h>

//création d'un DATAFRAME
CDataframe* creation_dataframe() {
    CDataframe* cdf = (CDataframe*)malloc(sizeof(CDataframe));//allocation de la mémoire pour le DATAFRAME
    
    cdf->columns = NULL; //initialisation
    cdf->num_columns = 0;
    cdf->num_rows = 0;
    
    if (!cdf) { //gestion cas d'erreur
        return NULL;
    }
    return cdf;
}
// Libérer la mémoire du DATAFRAME
void liberer_dataframe(CDataframe* cdf) {
    //liberer la mémoire de chaque colonne du DATAFRAME
    for (int i = 0; i < cdf->num_columns; i++) {
        free(cdf->columns[i]->data);
        free(cdf->columns[i]->title);
        free(cdf->columns[i]);
    }

    free(cdf->columns);
    free(cdf);
}

// Remplissage du DATAFRAME par l'utilisateur
void dataframe_remplissage_utilisateur(CDataframe* cdf) {
    int num_columns, num_values, val, i, j;
    char title[25];
    
   
    printf("Veuillez saisir le nombre de colonnes de votre Dataframe: ");
    scanf("%d", &num_columns);
    

    printf("Veuillez saisir le nombre de valeurs par colonne: "); // Nous avons décidé que toutes les colonnes du DATAFRAME devait avoir le même nombre de valeur
    scanf("%d", &num_values);
   
    cdf->columns = (COLUMN**)realloc(cdf->columns, num_columns * sizeof(COLUMN*)); // Allocation de la mémoire pour le nombre de colonnes demandées
    cdf->num_columns = num_columns;
    cdf->num_rows = num_values;

    for (i = 0; i < num_columns; i++) {
      
        printf("\nVeuillez saisir un titre pour votre colonne numero %d: ", i + 1);
        scanf("%s", title);
        
        // Création d'une nouvelle colonne
        COLUMN *col = create_column(title);
        
    
        for (j = 0; j < num_values; j++) {
            printf("\nVeuillez saisir la valeur numero %d pour la colonne %s: ", j + 1, title);
            scanf("%d", &val);
            insert_value(col, val);
        }
        
        // Ajouter la colonne dans le DATAFRAME
        cdf->columns[i] = col;
    }
}


//Remplissage en dur( comme exemple nous avons pris le cas d'un DATAFRAME à 3 colonnes)
void dataframe_remplissage_dur(CDataframe* df) {
    ajouter_colonne(df, "Column1");
    ajouter_colonne(df, "Column2");
    ajouter_colonne(df, "Column3");

    // Remplissage avec des valeurs
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
    int values3[] = {7, 8, 9};

    ajouter_ligne(df, values1);
    ajouter_ligne(df, values2);
    ajouter_ligne(df, values3);
}

// Affichage du DATAFRAME
void afficher_dataframe(CDataframe* cdf) {
    // Affichage des titres des colonnes
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");

    // Affichage des données du DATAFRAME
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } 
        }
        printf("\n");
    }
}
//Affichage de certaines lignes
void afficher_dataframe_lignes(CDataframe* cdf, int row_limit) {
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
    for (int i = 0; i < row_limit && i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } 
        }
        printf("\n");
    }
}
//Affichage de certaines colonnes
void afficher_dataframe_colonnes(CDataframe* cdf, int col_limit) {
    for (int i = 0; i < col_limit && i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < col_limit && j < cdf->num_columns; j++) {
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } 
        }
        printf("\n");
    }
}

// Fonctionnalitée permettant d'ajouter une ligne
int ajouter_ligne(CDataframe* cdf, int* values) {
    if (cdf->num_columns == 0) {
        return 0;
    }
   
    for (int i = 0; i < cdf->num_columns; i++) {
        if (cdf->columns[i]->logical_size == cdf->columns[i]->physical_size) { //si  la taille physique égale à la taille logique, on change la taille de la mémoire
            int new_size = cdf->columns[i]->physical_size + REALLOC_SIZE;
            int* new_data = realloc(cdf->columns[i]->data, new_size * sizeof(int));
            if (!new_data){ // gestion cas d'erreur
                return 0;
            }
            cdf->columns[i]->data = new_data;
            cdf->columns[i]->physical_size = new_size;
        }
       
        cdf->columns[i]->data[cdf->num_rows] = values[i];
        cdf->columns[i]->logical_size++;
    }
    // Changement du nombre de ligne dans le data frame
    cdf->num_rows++;
    return 1;
}

int supprimer_ligne(CDataframe* cdf, int row_index) {
    // Supprime une ligne si elle existe dans le data frame
    if (row_index >= cdf->num_rows || row_index < 0) {
        return 0;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = row_index; j < cdf->num_rows - 1; j++) {
            cdf->columns[i]->data[j] = cdf->columns[i]->data[j + 1];
        }
        // Changement de la taille logique des colonnes
        cdf->columns[i]->logical_size--;
    }
    // Changement du nombre de ligne dans le data frame
    cdf->num_rows--;
    return 1;
}
//AJoute une colonne au DATAFRAME
int ajouter_colonne(CDataframe* cdf, char* title) {

    int x;
    //allocation de la mémoire pour la colonne
    COLUMN* col = (COLUMN*)malloc(sizeof(COLUMN));
    col->title = strdup(title);
    col->data = (int*)malloc(cdf->num_rows * sizeof(int));
    if (!col->data) { // gestion cas d'erreur
        free(col->title);
        free(col);
        return 0;
    }
    col->logical_size = cdf->num_rows;
    col->physical_size = cdf->num_rows;
    //Remplissage de cette nouvelle colonne
    for (int i = 0; i < cdf->num_rows; i++) {
        printf("Saisir la valeur numero %d",i+1);
        scanf(" %d",&x);
        col->data[i] = x;
    }
    cdf->columns = realloc(cdf->columns, (cdf->num_columns + 1) * sizeof(COLUMN*));//augentation de la mémoire
    if (!cdf->columns) { // gestion cas d'erreur
        free(col->data);
        free(col->title);
        free(col);
        return 0;
    }
    cdf->columns[cdf->num_columns] = col;
    cdf->num_columns++;
    return 1;
}


//Supprime une colonne du DATAFRAME
int supprimer_colonne(CDataframe* cdf, int col_index) {

    if (col_index >= cdf->num_columns || col_index < 0) {//gestion cas d'erreur
        return 0;
    }
    // Libérer la mémoire de la colonne en question
    free(cdf->columns[col_index]->data);
    free(cdf->columns[col_index]->title);
    free(cdf->columns[col_index]);
    // Mise à jour des indices des colonnes du DATAFRAME
    for (int i = col_index; i < cdf->num_columns - 1; i++) {
        cdf->columns[i] = cdf->columns[i + 1];
    }
    // Change le nombre de colonnes du DATAFRAME
    return 1;
}
//Change le titre d'une colonne du DATAFRAME
int renomer_colonne(CDataframe* cdf, int col_index,char* new_title) {
    if (col_index >= cdf->num_columns || col_index < 0) { //gestion cas d'erreur
        return 0;
    }
    //Supprime l'ancien titre
    free(cdf->columns[col_index]->title);
    //Iniatialisation le nouveau titre
    cdf->columns[col_index]->title = strdup(new_title);
    return cdf->columns[col_index]->title != NULL;
}


//Test si la valeur existe dans le DATAFRAME
int valeur_exists(CDataframe* cdf, int value) {
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == value){ //test de présence
                printf("La valeur %d existe dans le data frame", value);
                return 1;}
        }
    }
    printf("La valeur n'est pas présente.");//gestion cas d'erreur
    return 0;
}

//Permet d'accéder à une valeur du DATAFRAME
int accceder_valeur(CDataframe* cdf, int row, int col, int* value) {
    if (row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) { //gestion cas d'erreur
        return 0;
    }
    *value = cdf->columns[col]->data[row];
    return 1;
}
//Remplace une valeur du DATAFRAME donné (par ses indices) par une autre
int remplacer_valeur(CDataframe* cdf, int row, int col, int value) {
    if ( row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) { //gestion cas d'erreur
        return 0;
    }
    cdf->columns[col]->data[row] = value;
    return 1;
}

//Affichage du nom de toute les colonnes du DATAFRAME séparé par des tabulations
void afficher_titres(CDataframe* cdf) {
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
}

//Retourne le nombre de ligne du DATAFRAME
int nombre_ligne(CDataframe* cdf) {
    return cdf->num_rows;
}

//Retourne le nombre de colonne du DATAFRAME
int nombre_colonne(CDataframe* cdf) {
    return cdf->num_columns;
}


//Compte le nomrbe de valeur égal à x dans le DATAFRAME
int count_egal(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == x) // test d'égalité
                count++;
        }
    }
    return count;
}

//compte le nombre de valeur superieur à x dans le DATAFRAME
int count_sup(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] > x) //test de supériorité
                count++;
        }
    }
    return count;
}


//compte le nombre de valeur inférieur à x dans le DATRAME
int count_inf(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] < x) // test d'infériorité
                count++;
        }
    }
    return count;
}
