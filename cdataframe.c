
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include <stdio.h>


CDataframe* creation_dataframe() {
    //Allocation de la mémoire
    CDataframe* cdf= (CDataframe*)malloc(sizeof(CDataframe));
    if (!cdf) {
        return NULL;
    }
    //Iniatialisation
    cdf->columns = NULL;
    cdf->num_columns = 0;
    cdf->num_rows = 0;
    return cdf;
}

void liberer_dataframe(CDataframe* cdf) {
    //Libérer la mémoire pour chaque colonne
    for (int i = 0; i < cdf->num_columns; i++) {
        free(cdf->columns[i]->data);
        free(cdf->columns[i]->title);
        free(cdf->columns[i]);
    }
    //Libérer le data frame
    free(cdf->columns);
    free(cdf);
}

void dataframe_remplissage_utilisateur(CDataframe* cdf) {
    //Remplissage du data frame par l'utilisateur
    int logical_s, nb, val, i, j, nb_max=0;
    char title[25];
    printf("Veuillez saisir la taille de votre Dataframe: ");
    scanf(" %d",&logical_s);
    //Allocation de la mémoire pour les colonnes
    cdf->columns = (COLUMN**)realloc(cdf->columns, logical_s*sizeof(COLUMN*));
    for (i=0; i<logical_s; i++){
        //Changer le nombre de colonne dans le data frame
        cdf->num_columns ++;
        //Choix du titre
        printf("\nVeuillez saisir un titre pour votre colonne numero %d: ",i+1);
        scanf(" %s", title);
        //Création d'une nouvelle colonne
        COLUMN *col = create_column(title);
        printf("\nVeuillez saisir le nombre de ligne souhaité dans votre colonne numero %d:", i+1);
        scanf(" %d",&nb);
        //Remplissage des valeurs de la colonne par l'utilisateur
        for(j=0; j<nb; j++){
            printf("\nVeuillez saisir la valeur numero %d: ", j+1);
            scanf(" %d", &val);
            insert_value(col, val);
        }
        //Mettre la colonne dans le data frame
        cdf->columns[i] = col;
        //Teste si c'est la colonne avec le plus de ligne
        if(nb>nb_max)
            nb_max = nb;
    }
    //Changement du nombre de ligne du data frame en prenant celle de la plus grande colonne
    cdf->num_rows = nb_max;
}

void dataframe_remplissage_dur(CDataframe* df) {
    //Ajout des trois colonne en dur
    add_column(df, "Column1");
    add_column(df, "Column2");
    add_column(df, "Column3");

    //Remplissage avec des valeurs
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
    int values3[] = {7, 8, 9};

    add_row(df, values1);
    add_row(df, values2);
    add_row(df, values3);
}

//Affichage
void afficher_dataframe( CDataframe* cdf) {
    //Affichage du data frame  A CHANGER POUR POUVOIR AFFICHER DES COLONNES DE TAILLES DIFFERENTES!!
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");

    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            printf("%d\t", cdf->columns[j]->data[i]);
        }
        printf("\n");
    }
}

void afficher_dataframe_rows( CDataframe* cdf, int row_limit) {
    //Affichage de certaines lignes
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
    for (int i = 0; i < row_limit && i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            printf("%d\t", cdf->columns[j]->data[i]);
        }
        printf("\n");
    }
}

void afficher_dataframe_colonnes(CDataframe* cdf, int col_limit) {
    for (int i = 0; i < col_limit && i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < col_limit && j < cdf->num_columns; j++) {
            printf("%d\t", cdf->columns[j]->data[i]);
        }
        printf("\n");
    }
}

//Fonctionnalités
int add_row(CDataframe* cdf, int* values) {
    //Ajout d'une ligne dans chaque colonne
    if ( cdf->num_columns == 0) {
        return 0;
    }
    //Pour chaque colonne, teste si de la taille physique égale à la taille logique, si oui changement de la taille de la mémoire
    for (int i = 0; i < cdf->num_columns; i++) {
        if (cdf->columns[i]->logical_size == cdf->columns[i]->physical_size) {
            int new_size = cdf->columns[i]->physical_size + REALLOC_SIZE;
            int* new_data = realloc(cdf->columns[i]->data, new_size * sizeof(int));
            if (!new_data) return 0;
            cdf->columns[i]->data = new_data;
            cdf->columns[i]->physical_size = new_size;
        }
        //Sinon ajout directement de la valeur dans la ligne
        cdf->columns[i]->data[cdf->num_rows] = values[i];
        cdf->columns[i]->logical_size++;
    }
    //Changement du nombre de ligne dans le data frame
    cdf->num_rows++;
    return 1;
}

int delete_row(CDataframe* cdf, int row_index) {
    //Supprime une ligne si elle existe dans le data frame
    if (row_index >= cdf->num_rows || row_index < 0) {
        return 0;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = row_index; j < cdf->num_rows - 1; j++) {
            cdf->columns[i]->data[j] = cdf->columns[i]->data[j + 1];
        }
        //Changement de la taille logique des colonnes
        cdf->columns[i]->logical_size--;
    }
    //Changement du nombre de ligne dans le data frame
    cdf->num_rows--;
    return 1;
}

int add_column(CDataframe* cdf, char* title) {
    //Ajout d'une colonne
    //Création d'une nouvelle colonne
    COLUMN* col = (COLUMN*)malloc(sizeof(COLUMN));
    col->title = strdup(title);
    col->data = (int*)malloc(cdf->num_rows * sizeof(int));
    if (!col->data) {
        free(col->title);
        free(col);
        return 0;
    }
    col->logical_size = cdf->num_rows;
    col->physical_size = cdf->num_rows;
    for (int i = 0; i < cdf->num_rows; i++) {
        col->data[i] = 0; // Initialisation à 0
    }
    cdf->columns = realloc(cdf->columns, (cdf->num_columns + 1) * sizeof(COLUMN*));
    if (!cdf->columns) {
        free(col->data);
        free(col->title);
        free(col);
        return 0;
    }
    cdf->columns[cdf->num_columns] = col;
    cdf->num_columns++;
    return 1;
}

int delete_column(CDataframe* cdf, int col_index) {
    //Suppression d'une colonne du data frame si elle existe
    if ( col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    //Libérer la mémoire de la colonne
    free(cdf->columns[col_index]->data);
    free(cdf->columns[col_index]->title);
    free(cdf->columns[col_index]);
    //Changement de place des colonnes suivantes s'il y en a
    for (int i = col_index; i < cdf->num_columns - 1; i++) {
        cdf->columns[i] = cdf->columns[i + 1];
    }
    //Changement du nombre de colonne dans le data frame
    cdf->num_columns--;
    return 1;
}

int rename_column(CDataframe* cdf, int col_index,char* new_title) {
    //Nouveau nom pour une colonne si elle existe
    if (col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    //Enlever l'ancien nom
    free(cdf->columns[col_index]->title);
    //Iniatialisation du nouveau nom
    cdf->columns[col_index]->title = strdup(new_title);
    return cdf->columns[col_index]->title != NULL;
}

int value_exists(CDataframe* cdf, int value) {
    //Test si la valeur existe dans le data frame
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            //Test si la valeur est présente
            if (cdf->columns[i]->data[j] == value){
                printf("La valeur %d existe dans le data frame", value);
                return 1;}
        }
    }
    printf("La valeur n'est pas présente.");
    return 0;
}

int access_value(CDataframe* cdf, int row, int col, int* value) {
    //Accéder à une valeur dans le data frame si la position existe
    if (row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    *value = cdf->columns[col]->data[row];
    return 1;
}

int replace_value(CDataframe* cdf, int row, int col, int value) {
    //Changement d'une valeur si la position est possible
    if ( row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    cdf->columns[col]->data[row] = value;
    return 1;
}

void print_column_titles(CDataframe* cdf) {
    //Affichage du nom de toute les colonnes séparé par une tabulation
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
}

//Analyse et statistiques
int num_rows(CDataframe* cdf) {
    //Nombre de lignes dans le data frame 
    return cdf->num_rows;
}

int num_columns(CDataframe* cdf) {
    //Nombre de colonne
    return cdf->num_columns;
}

int count_equal(CDataframe* cdf, int x) {
    //Nombre valeur égale à x dans le data frame
    //Iniatialisation du compteur
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            //Test d'égalité
            if (cdf->columns[i]->data[j] == x)
                count++;
        }
    }
    return count;
}

int count_greater(CDataframe* cdf, int x) {
    //Nombre de valeur dans le data frame supérieure à x
    int count = 0;
    //Parcours du data frame
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            //Test si la valeur à la position i,j est supérieure à x
            if (cdf->columns[i]->data[j] > x) 
                count++;
        }
    }
    return count;
}

int count_less(CDataframe* cdf, int x) {
    //Nombre de valeur inférieure à x
    int count = 0;
    //Parcours du data frame
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            //Test si la valeur à la position i,j est inférieure à x
            if (cdf->columns[i]->data[j] < x)
                count++;
        }
    }
    return count;
}
