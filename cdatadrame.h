#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"

#define REALLOC_SIZE 256


typedef struct {
    COLUMN** columns;
    int num_columns;
    int num_rows;
} CDataframe;

//Creation
CDataframe* creation_dataframe();

//Removal
void liberer_dataframe(CDataframe* cdf);

//Filling
void dataframe_remplissage_utilisateur(CDataframe* cdf);
void dataframe_remplissage_dur(CDataframe* cdf);

// Display
void afficher_dataframe(CDataframe* cdf);
void afficher_dataframe_lignes(CDataframe* cdf, int row_limit);
void afficher_dataframe_colonnes( CDataframe* cdf, int col_limit);

//Handling
int ajouter_ligne(CDataframe* cdf, int* values);
int supprimer_ligne(CDataframe* cdf, int row_index);
int ajouter_colonne(CDataframe* cdf, char* title);
int suprimer_colonne(CDataframe* cdf, int col_index);
int renomer_colonne(CDataframe* cdf, int col_index, char* new_title);
int valeur_exists(CDataframe* cdf, int value);
int acceder_valeur(CDataframe* cdf, int row, int col, int* value);
int remplacer_valeur(CDataframe* cdf, int row, int col, int value);
void afficher_titres( CDataframe* cdf);

//Functionality
int nombre_ligne(CDataframe* cdf);
int nombre_colonne(CDataframe* cdf);
int count_egal(CDataframe* cdf, int x);
int count_sup(CDataframe* cdf, int x);
int count_inf(CDataframe* cdf, int x);
