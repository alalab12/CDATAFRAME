

#ifndef CDATAFRAME_COLUMN_H
#define CDATAFRAME_COLUMN_H



// Structure de la colonne
typedef struct {
    char* title;        // Titre de la colonne
    int* data;          // Données de la colonne
    int physical_size;  // Taille physique
    int logical_size;   // Taille logique
}COLUMN;


//prototypes fonctions 

COLUMN *create_column(char* title);

int insert_value(COLUMN* column, int value);

void free_column(COLUMN** column);

void print_column(COLUMN* col);

int nb_occurence(COLUMN* col, int x);

int x_pos(COLUMN* col, int x);

int val_sup(COLUMN* col, int x);

int val_inf(COLUMN* col, int x);

int val_egal(COLUMN* column, int x);

#endif //CDATAFRAME_COLUMN_H
