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

CDataframe* create_dataframe();

void free_dataframe(CDataframe* cdf);


void dataframe_user_input(CDataframe* cdf);
void dataframe_hardcoded(CDataframe* cdf);

// Display
void print_dataframe(const CDataframe* cdf);
void print_dataframe_rows(const CDataframe* cdf, int row_limit);
void print_dataframe_columns(const CDataframe* cdf, int col_limit);


int add_row(CDataframe* cdf, int* values);
int delete_row(CDataframe* cdf, int row_index);
int add_column(CDataframe* cdf, const char* title);
int delete_column(CDataframe* cdf, int col_index);
int rename_column(CDataframe* cdf, int col_index, const char* new_title);
int value_exists(const CDataframe* cdf, int value);
int access_value(CDataframe* cdf, int row, int col, int* value);
int replace_value(CDataframe* cdf, int row, int col, int value);
void print_column_titles(const CDataframe* cdf);


int num_rows(const CDataframe* cdf);
int num_columns(const CDataframe* cdf);
int count_equal(const CDataframe* cdf, int x);
int count_greater(const CDataframe* cdf, int x);
int count_less(const CDataframe* cdf, int x);
