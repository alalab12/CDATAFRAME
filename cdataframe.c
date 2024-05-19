
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include <stdio.h>


CDataframe* create_dataframe() {
    CDataframe* cdf= (CDataframe*)malloc(sizeof(CDataframe));
    if (!cdf) {
        return NULL;
    }
    cdf->columns = NULL;
    cdf->num_columns = 0;
    cdf->num_rows = 0;
    return cdf;
}

void free_dataframe(CDataframe* cdf) {
    for (int i = 0; i < cdf->num_columns; i++) {
        free(cdf->columns[i]->data);
        free(cdf->columns[i]->title);
        free(cdf->columns[i]);
    }
    free(cdf->columns);
    free(cdf);
}

void dataframe_user_input(CDataframe* cdf) {
    int logical_s, nb, val, i, j, nb_max=0;
    char title[25];
    printf("Veuillez saisir la taille de votre Dataframe: ");
    scanf(" %d",&logical_s);
    cdf->columns = (COLUMN**)realloc(cdf->columns, logical_s*sizeof(COLUMN*));
    for (i=0; i<logical_s; i++){
        cdf->num_columns ++;
        printf("\nVeuillez saisir un titre pour votre colonne numero %d: ",i+1);
        scanf(" %s", title);
        COLUMN *col = create_column(title);
        printf("\nVeuillez saisir le nombre de ligne souhaité dans votre colonne numero %d:", i+1);
        scanf(" %d",&nb);
        for(j=0; j<nb; j++){
            printf("\nVeuillez saisir la valeur numero %d: ", j+1);
            scanf(" %d", &val);
            insert_value(col, val);
        }
        cdf->columns[i] = col;
        if(nb>nb_max)
            nb_max = nb;
    }
    cdf->num_rows = nb_max;
}

void dataframe_hardcoded(CDataframe* df) {
    // Adding columns
    add_column(df, "Column1");
    add_column(df, "Column2");
    add_column(df, "Column3");

    // Adding rows
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
    int values3[] = {7, 8, 9};

    add_row(df, values1);
    add_row(df, values2);
    add_row(df, values3);
}

// Display
void print_dataframe( CDataframe* cdf) {
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

void print_dataframe_rows( CDataframe* cdf, int row_limit) {
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

void print_dataframe_columns(CDataframe* cdf, int col_limit) {
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

// Usual operations
int add_row(CDataframe* cdf, int* values) {
    if ( cdf->num_columns == 0) {
        return 0;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        if (cdf->columns[i]->logical_size == cdf->columns[i]->physical_size) {
            int new_size = cdf->columns[i]->physical_size + REALLOC_SIZE;
            int* new_data = realloc(cdf->columns[i]->data, new_size * sizeof(int));
            if (!new_data) return 0;
            cdf->columns[i]->data = new_data;
            cdf->columns[i]->physical_size = new_size;
        }
        cdf->columns[i]->data[cdf->num_rows] = values[i];
        cdf->columns[i]->logical_size++;
    }
    cdf->num_rows++;
    return 1;
}

int delete_row(CDataframe* cdf, int row_index) {
    if (row_index >= cdf->num_rows || row_index < 0) {
        return 0;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = row_index; j < cdf->num_rows - 1; j++) {
            cdf->columns[i]->data[j] = cdf->columns[i]->data[j + 1];
        }
        cdf->columns[i]->logical_size--;
    }
    cdf->num_rows--;
    return 1;
}

int add_column(CDataframe* cdf, char* title) {
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
        col->data[i] = 0; // Initialize with zero or any default value
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
    if ( col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    free(cdf->columns[col_index]->data);
    free(cdf->columns[col_index]->title);
    free(cdf->columns[col_index]);
    for (int i = col_index; i < cdf->num_columns - 1; i++) {
        cdf->columns[i] = cdf->columns[i + 1];
    }
    cdf->num_columns--;
    return 1;
}

int rename_column(CDataframe* cdf, int col_index,char* new_title) {
    if (col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    free(cdf->columns[col_index]->title);
    cdf->columns[col_index]->title = strdup(new_title);
    return cdf->columns[col_index]->title != NULL;
}

int value_exists(CDataframe* cdf, int value) {
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == value) return 1;
        }
    }
    return 0;
}

int access_value(CDataframe* cdf, int row, int col, int* value) {
    if (row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    *value = cdf->columns[col]->data[row];
    return 1;
}

int replace_value(CDataframe* cdf, int row, int col, int value) {
    if ( row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    cdf->columns[col]->data[row] = value;
    return 1;
}

void print_column_titles(CDataframe* cdf) {
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
}

// Analysis and statistics
int num_rows(CDataframe* cdf) {
    return cdf->num_rows;
}

int num_columns(CDataframe* cdf) {
    return cdf->num_columns;
}

int count_equal(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == x) count++;
        }
    }
    return count;
}

int count_greater(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] > x) count++;
        }
    }
    return count;
}

int count_less(CDataframe* cdf, int x) {
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] < x) count++;
        }
    }
    return count;
}
