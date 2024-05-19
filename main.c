#include "column.h"
#include "cdataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
  CDataframe* df = create_dataframe();
    
    add_column(df, "Column1");
    add_column(df, "Column2");

    
    int values1[] = {1, 2};
    int values2[] = {3, 4};
    add_row(df, values1);
    add_row(df, values2);
    // Display dataframe
    print_dataframe(df);
    
    free_dataframe(df);

    return 0;

}
