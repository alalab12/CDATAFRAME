//
// Created by audel on 15/04/2024.
//

#ifndef CDATAFRAME_FONCTIONNALITES_H
#define CDATAFRAME_FONCTIONNALITES_H

#include "column.h"


typedef struct {
    COLUMN** columns;
    int number_columns;
    int number_rows;

}CDATAFRAME;


CDATAFRAME* creation_dataframe_vide();

void remplissage_utilisateur(CDATAFRAME* dataframe);
void remplissage_dur(CDATAFRAME* dataframe, int** data, int number_rows, int number_columns);
void afficher_dataframe(CDATAFRAME* dataframe);
void afficher_certaines_colonne(CDATAFRAME* dataframe,int limite);
void afficher_certaines_ligne(CDATAFRAME* dataframe,int limite);
void ajouter_ligne_valeur(CDATAFRAME * dataframe, int* val);
void ajouter_colonne(CDATAFRAME * dataframe, COLUMN* column);
void supprimer_colonne(CDATAFRAME * dataframe, int index);
void renomer_colonne(CDATAFRAME * dataframe, int index, char* nouveau_titre);
int acceder_valeur(CDATAFRAME * dataframe, int ligne, int colonne);
void remplacer_valeur(CDATAFRAME * dataframe, int row, int col, int value);
void afficher_titre_colonne(CDATAFRAME* dataframe);
int nb_lignes(CDATAFRAME* dataframe);
int nb_colonnes(CDATAFRAME* dataframe);
int nb_valeur_egale(CDATAFRAME* dataframe, int val);
int nb_valeur_sup(CDATAFRAME* dataframe, int val);
int nb_valeur_inf(CDATAFRAME* dataframe, int val);


#endif //CDATAFRAME_FONCTIONNALITES_H
