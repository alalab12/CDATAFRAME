
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include <stdio.h>


CDataframe* create_dataframe() {
    CDataframe* cdf= (CDataframe*)malloc(sizeof(CDataframe));
    if (!cdf) return NULL;
    cdf->columns = NULL;
    cdf->num_columns = 0;
    cdf->num_rows = 0;
    return cdf;
}

void free_dataframe(CDataframe* cdf) {
    if (!cdf) {
        return;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        free(cdf->columns[i]->data);
        free(cdf->columns[i]->title);
        free(cdf->columns[i]);
    }
    free(cdf->columns);
    free(cdf);
}


void dataframe_user_input(CDataframe* cdf) {
    // à faire
}

void dataframe_hardcoded(CDataframe* cdf) {
    // à faire
}

// Display
void print_dataframe( CDataframe* cdf) {
    if (!cdf) {
        return;
    }
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
    if (!cdf) {
        return;
    }
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
    if (!cdf) {
        return;
    }
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
    if (!cdf || cdf->num_columns == 0) {
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
    if (!cdf || row_index >= cdf->num_rows || row_index < 0) {
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
    if (!cdf) return 0;
    COLUMN* col = (COLUMN*)malloc(sizeof(COLUMN));
    if (!col) return 0;
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
    if (!cdf || col_index >= cdf->num_columns || col_index < 0) {
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
    if (!cdf || col_index >= cdf->num_columns || col_index < 0) {
        return 0;
    }
    free(cdf->columns[col_index]->title);
    cdf->columns[col_index]->title = strdup(new_title);
    return cdf->columns[col_index]->title != NULL;
}

int value_exists(CDataframe* cdf, int value) {
    if (!cdf) {
        return 0;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == value) return 1;
        }
    }
    return 0;
}

int access_value(CDataframe* cdf, int row, int col, int* value) {
    if (!cdf || row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    *value = cdf->columns[col]->data[row];
    return 1;
}

int replace_value(CDataframe* cdf, int row, int col, int value) {
    if (!cdf || row >= cdf->num_rows || col >= cdf->num_columns || row < 0 || col < 0) {
        return 0;
    }
    cdf->columns[col]->data[row] = value;
    return 1;
}

void print_column_titles(CDataframe* cdf) {
    if (!cdf) {
        return;
    }
    for (int i = 0; i < cdf->num_columns; i++) {
        printf("%s\t", cdf->columns[i]->title);
    }
    printf("\n");
}

// Analysis and statistics
int num_rows(CDataframe* cdf) {
    if (!cdf) {
        return 0;
    }
    return cdf->num_rows;
}

int num_columns(CDataframe* cdf) {
    if (!cdf) {
        return 0;
    }
    return cdf->num_columns;
}

int count_equal(CDataframe* cdf, int x) {
    if (!cdf){
        return 0;
    }
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] == x) count++;
        }
    }
    return count;
}

int count_greater(CDataframe* cdf, int x) {
    if (!cdf) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] > x) count++;
        }
    }
    return count;
}

int count_less(CDataframe* cdf, int x) {
    if (!cdf) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < cdf->num_columns; i++) {
        for (int j = 0; j < cdf->num_rows; j++) {
            if (cdf->columns[i]->data[j] < x) count++;
        }
    }
    return count;
}
