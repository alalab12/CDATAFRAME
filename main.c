#include "fonctions.h"
#include "fonctionnalites.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
    COLUMN *mycol = create_column("colonne 1");
    insert_value(mycol, 1);
    insert_value(mycol, 2);
    insert_value(mycol, 3);

    print_column(mycol);

    int x = 3;
    printf("Le nombre d'occurence de %d: %d\n", x, nb_occurence(mycol, x));

    free_column(mycol);





    return 0;
}

