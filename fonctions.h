


#ifndef CDATAFRAME_FONCTIONS_H
#define CDATAFRAME_FONCTIONS_H

// Structure de la colonne
typedef struct {
    char* title;        // Titre de la colonne (chaîne de caractères)
    int* data;          // Données de la colonne (tableau d'entiers)
    int logical_size;   // Taille logique (nombre de valeurs insérées)
    int physical_size;  // Taille physique (nombre de cases allouées dynamiquement)
} COLUMN;

COLUMN *create_column(char* title);

int insert_value(COLUMN* column, int value);

void delete_column(COLUMN **column);

void print_col(COLUMN* col);

#endif //CDATAFRAME_FONCTIONS_H
