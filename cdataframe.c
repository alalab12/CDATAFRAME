
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include <stdio.h>


CDataframe* creation_dataframe() {
    // Allocation de la mémoire
    CDataframe* cdf = (CDataframe*)malloc(sizeof(CDataframe));
    if (!cdf) {
        return NULL;
    }
    // Initialisation
    cdf->columns = NULL;
    cdf->num_columns = 0;
    cdf->num_rows = 0;
    return cdf;
}

void liberer_dataframe(CDataframe* cdf) {
    // Libérer la mémoire pour chaque colonne
    for (int i = 0; i < cdf->num_columns; i++) {
        free(cdf->columns[i]->data);
        free(cdf->columns[i]->title);
        free(cdf->columns[i]);
    }
    // Libérer le data frame
    free(cdf->columns);
    free(cdf);
}

void dataframe_remplissage_utilisateur(CDataframe* cdf) {
    // Remplissage du data frame par l'utilisateur
    int num_columns, num_values, val, i, j;
    char title[25];
    
    // Demande du nombre de colonnes
    printf("Veuillez saisir le nombre de colonnes de votre Dataframe: ");
    scanf("%d", &num_columns);
    
    // Demande du nombre de valeurs par colonne
    printf("Veuillez saisir le nombre de valeurs par colonne: ");
    scanf("%d", &num_values);
    
    // Allocation de la mémoire pour les colonnes
    cdf->columns = (COLUMN**)realloc(cdf->columns, num_columns * sizeof(COLUMN*));
    cdf->num_columns = num_columns;
    cdf->num_rows = num_values;

    for (i = 0; i < num_columns; i++) {
      
        printf("\nVeuillez saisir un titre pour votre colonne numero %d: ", i + 1);
        scanf("%s", title);
        
        // Création d'une nouvelle colonne
        COLUMN *col = create_column(title);
        
        // Remplissage des valeurs de la colonne par l'utilisateur
        for (j = 0; j < num_values; j++) {
            printf("\nVeuillez saisir la valeur numero %d pour la colonne %s: ", j + 1, title);
            scanf("%d", &val);
            insert_value(col, val);
        }
        
        // Mettre la colonne dans le data frame
        cdf->columns[i] = col;
    }
}

void dataframe_remplissage_dur(CDataframe* df) {
    // Ajout des trois colonnes en dur
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

// Affichage
void afficher_dataframe(CDataframe* cdf) {
    // Affichage des titres des colonnes
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");

    // Affichage des données du data frame
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } else {
                printf("\t"); // Espace pour colonnes de différentes tailles
            }
        }
        printf("\n");
    }
}

void afficher_dataframe_lignes(CDataframe* cdf, int row_limit) {
    // Affichage de certaines lignes
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
    for (int i = 0; i < row_limit && i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } else {
                printf("\t"); // Espace pour colonnes de différentes tailles
            }
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
            if (i < cdf->columns[j]->logical_size) {
                printf("%d\t", cdf->columns[j]->data[i]);
            } else {
                printf("\t"); // Espace pour colonnes de différentes tailles
            }
        }
        printf("\n");
    }
}

// Fonctionnalités
int ajouter_ligne(CDataframe* cdf, int* values) {
    // Ajout d'une ligne dans chaque colonne
    if (cdf->num_columns == 0) {
        return 0;
    }
    // Pour chaque colonne, teste si de la taille physique égale à la taille logique, si oui changement de la taille de la mémoire
    for (int i = 0; i < cdf->num_columns; i++) {
        if (cdf->columns[i]->logical_size == cdf->columns[i]->physical_size) {
            int new_size = cdf->columns[i]->physical_size + REALLOC_SIZE;
            int* new_data = realloc(cdf->columns[i]->data, new_size * sizeof(int));
            if (!new_data) return 0;
            cdf->columns[i]->data = new_data;
            cdf->columns[i]->physical_size = new_size;
        }
        // Sinon ajout directement de la valeur dans la ligne
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

int ajouter_colonne(CDataframe* cdf, char* title) {
    // Ajout d'une colonne
    // Création d'une nouvelle colonne
    int x;
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
    //Remplissage de cette nouvelle colonne
    for (int i = 0; i < cdf->num_rows; i++) {
        printf("Saisir la valeur numero %d",i+1);
        scanf(" %d",&x);
        col->data[i] = x;
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

int supprimer_colonne(CDataframe* cdf, int col_index) {
    // Suppression d'une colonne du data frame si elle existe
    if (col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    // Libérer la mémoire de la colonne
    free(cdf->columns[col_index]->data);
    free(cdf->columns[col_index]->title);
    free(cdf->columns[col_index]);
    // Changement de place des colonnes suivantes s'il y en a
    for (int i = col_index; i < cdf->num_columns - 1; i++) {
        cdf->columns[i] = cdf->columns[i + 1];
    }
    // Changement du nombre de colonnes dans le data frame
    cdf->num_columns--;
    return 1;
}
int renomer_colonne(CDataframe* cdf, int col_index,char* new_title) {
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

int valeur_exists(CDataframe* cdf, int value) {
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

int accceder_valeur(CDataframe* cdf, int row, int col, int* value) {
    //Accéder à une valeur dans le data frame si la position existe
    if (row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    *value = cdf->columns[col]->data[row];
    return 1;
}

int remplacer_valeur(CDataframe* cdf, int row, int col, int value) {
    //Changement d'une valeur si la position est possible
    if ( row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    cdf->columns[col]->data[row] = value;
    return 1;
}

void afficher_titres(CDataframe* cdf) {
    //Affichage du nom de toute les colonnes séparé par une tabulation
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
}

//Analyse et statistiques
int nombre_ligne(CDataframe* cdf) {
    //Nombre de lignes dans le data frame 
    return cdf->num_rows;
}

int nombre_colonne(CDataframe* cdf) {
    //Nombre de colonne
    return cdf->num_columns;
}

int count_egal(CDataframe* cdf, int x) {
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

int count_sup(CDataframe* cdf, int x) {
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

int count_inf(CDataframe* cdf, int x) {
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
