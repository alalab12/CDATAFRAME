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
void dataframe_remplissage_utisateur(CDataframe* cdf);
void dataframe_dur(CDataframe* cdf);

// Display
void afficher_dataframe(CDataframe* cdf);
void afficher_dataframe_lignes(CDataframe* cdf, int row_limit);
void print_dataframe_colonnes( CDataframe* cdf, int col_limit);

//Handling
int add_row(CDataframe* cdf, int* values);
int delete_row(CDataframe* cdf, int row_index);
int add_column(CDataframe* cdf, char* title);
int delete_column(CDataframe* cdf, int col_index);
int rename_column(CDataframe* cdf, int col_index, char* new_title);
int value_exists(CDataframe* cdf, int value);
int access_value(CDataframe* cdf, int row, int col, int* value);
int replace_value(CDataframe* cdf, int row, int col, int value);
void print_column_titles( CDataframe* cdf);

//Functionality
int num_rows(CDataframe* cdf);
int num_columns(CDataframe* cdf);
int count_equal(CDataframe* cdf, int x);
int count_greater(CDataframe* cdf, int x);
int count_less(CDataframe* cdf, int x);
