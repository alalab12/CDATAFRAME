
#include "column.h"
#include "cdataframe.h"
#include <stdio.h>


// Definition des fonctions du menu
void menu_creation(CDataframe* cdf);
void menu_remplissage(CDataframe* cdf);
void menu_supression(CDataframe* cdf);
void menu_affichage(CDataframe* cdf);
void menu_operation(CDataframe* cdf);
void menu_fonctionnalite(CDataframe* cdf);

int main() {
    CDataframe* cdf = creation_dataframe();//création du DATAFRAME

    int choix, verif = 1;
    while(verif) {
        //Affichage du menu
        printf("Menu :\n");
        printf("1. Creation\n");
        printf("2. Remplissage\n");
        printf("3. Suppression\n");
        printf("4. Affichage\n");
        printf("5. Gestion\n");
        printf("6. Fonctionnalites\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) { //choix du menu souhaité
            case 1:
                menu_creation(cdf);
                break;
            case 2:
                menu_remplissage(cdf);
                break;
            case 3:
                menu_supression(cdf);
                break;
            case 4:
                menu_affichage(cdf);
                break;
            case 5:
                menu_operation(cdf);
                break;
            case 6:
                menu_fonctionnalite(cdf);
                break;
            case 7:
                liberer_dataframe(cdf);
                printf("Merci d'avoir teste notre programme ! Aude Labat et Julie Brouet\n");
                verif=0;
                break;
            default:
                printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
        }
    }

    return 0;
}
//Fonction pour les differents menu
void menu_creation(CDataframe* cdf) {
    printf("Creation de dataframe :\n");
    printf("1. Creer un dataframe vide\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        // Creer un dataframe vide
        printf("Dataframe cree !\n");
    } else {
        printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
    }
}

void menu_remplissage(CDataframe* cdf) {
    printf("Remplissage de dataframe :\n");
    printf("1. Remplir le dataframe a partir de l'utilisateur\n");
    printf("2. Remplir le dataframe end dur\n");
    printf("Entrez votre choix : ");//choix tu mode de remplissage
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        dataframe_remplissage_utilisateur(cdf);
        printf("Dataframe rempli a partir de l'utilisateur !\n");
    }
    else if (choix == 2) {
        dataframe_remplissage_dur(cdf);
        printf("Dataframe rempli en dur !\n");
    }
    else {
        printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
    }
}

void menu_supression(CDataframe* cdf) {
    printf("Suppression de dataframe :\n");
    printf("1. Liberer le dataframe\n");
    printf("Entrez votre choix : ");//choix entre 1 seul possiblité (supression)
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        liberer_dataframe(cdf);
        printf("Dataframe libere !\n");
    } else {
        printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
    }
}

void menu_affichage(CDataframe* cdf) {
    printf("Affichage de dataframe :\n");
    printf("1. Afficher tout le dataframe\n");
    printf("2. Afficher les lignes du dataframe\n");
    printf("3. Afficher les colonnes du dataframe\n");
    printf("Entrez votre choix : ");// choix du mode d'affichage
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        afficher_dataframe(cdf);
        
    } else if (choix == 2) {
        int ligne_limite;
        printf("Entrez le nombre de lignes a afficher : ");
        scanf("%d", &ligne_limite);
        afficher_dataframe_lignes(cdf, ligne_limite);
        
    } else if (choix == 3) {
        int col_limite;
        printf("Entrez le nombre de colonnes a afficher : ");
        scanf("%d", &col_limite);
        afficher_dataframe_colonnes(cdf, col_limite);
        
    } else {
        printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
    }
}

void menu_operation(CDataframe* cdf) {
    printf("Gestion de dataframe :\n");
    printf("1. Ajouter une ligne\n");
    printf("2. Supprimer une ligne\n");
    printf("3. Ajouter une colonne\n");
    printf("4. Supprimer une colonne\n");
    printf("5. Renommer une colonne\n");
    printf("6. Verifier si une valeur existe\n");
    printf("7. Acceder a une valeur\n");
    printf("8. Remplacer une valeur\n");
    printf("9. Afficher les titres\n");
    printf("Entrez votre choix : ");// choix du type d'opération
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        //Stocker les nouvelles valeurs a ajouter dans un tableau
        int val[cdf->num_columns];
        for (int i = 0; i < cdf->num_columns; i++) {
            printf("Entrez la valeur pour la colonne %d : ", i);
            scanf("%d", &val[i]);
        }
        int res = ajouter_ligne(cdf, val);
        if (res == 1) {
            printf("Ligne ajoutee avec succes !\n");
            
        } else {
            printf("Erreur lors de l'ajout de la ligne.\n");//gestion cas d'erreur
            
        }
    } else if (choix == 2) {
        int lig_ind;
        printf("Entrez l'index de la ligne a supprimer : ");
        scanf("%d", &lig_ind);
        int result = supprimer_ligne(cdf, lig_ind);
        
        if (result == 1) {
            printf("Ligne supprimee avec succes !\n");
            
        } else {
            printf("Erreur lors de la suppression de la ligne.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 3) {
        char titre[100];
        printf("Entrez le titre de la colonne a ajouter : ");
        scanf("%s", titre);
        int result = ajouter_colonne(cdf, titre);
        
        if (result == 1) {
            printf("Colonne ajoutee avec succes !\n");
            
        } else {
            printf("Erreur lors de l'ajout de la colonne.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 4) {
        int col_ind;
        printf("Entrez l'indice de la colonne a supprimer : ");
        scanf("%d", &col_ind);
        int result = supprimer_colonne(cdf, col_ind);
        
        if (result == 1) {
            printf("Colonne supprimee avec succes !\n");
            
        } else {
            printf("Erreur lors de la suppression de la colonne.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 5) {
        int col_ind;
        char nv_titre[100];
        printf("Entrez l'indice de la colonne a renommer : ");
        scanf("%d", &col_ind);
        printf("Entrez le nouveau titre de la colonne : ");
        scanf("%s", nv_titre);
        int result = renomer_colonne(cdf, col_ind, nv_titre);
        
        if (result == 1) {
            printf("Colonne renommee avec succes !\n");
            
        } else {
            printf("Erreur lors du renommage de la colonne.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 6) {
        int val;
        printf("Entrez la valeur a verifier : ");
        scanf("%d", &val);
        int result = valeur_exists(cdf, val);
        
        if (result == 1) {
            printf("La valeur existe dans le dataframe.\n");
            
        } else {
            printf("La valeur n'existe pas dans le dataframe.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 7) {
        int lig, col;
        int valeur;
        printf("Entrez l'indice de la ligne : ");
        scanf("%d", &lig);
        printf("Entrez l'indice de la colonne : ");
        scanf("%d", &col);
        int result = acceder_valeur(cdf, lig, col, &valeur);
        
        if (result == 1) {
            printf("La valeur a la ligne %d et a la colonne %d est : %d\n", lig, col, valeur);
            
        } else {
            printf("Erreur lors de l'acces a la valeur.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 8) {
        int lig, col;
        int valeur;
        printf("Entrez l'index de la ligne : ");
        scanf("%d", &lig);
        printf("Entrez l'index de la colonne : ");
        scanf("%d", &col);
        printf("Entrez la nouvelle valeur : ");
        scanf("%d", &valeur);
        int result = remplacer_valeur(cdf, lig, col, valeur);
        
        if (result == 1) {
            printf("Valeur remplacee !\n");
            
        } else {
            printf("Erreur lors du remplacement de la valeur.\n");//gestion cas d'erreur
        }
        
    } else if (choix == 9) {
        afficher_titres(cdf);
    }
}

void menu_fonctionnalite(CDataframe* cdf) {
    printf("Fonctionnalites de dataframe :\n");
    printf("1. Nombre de lignes\n");
    printf("2. Nombre de colonnes\n");
    printf("3. Compter les valeurs egales a un entier\n");
    printf("4. Compter les valeurs superieures a un entier\n");
    printf("5. Compter les valeurs inferieures a un entier\n");
    printf("Entrez votre choix : ");//choix du type de fonctionnalitées
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        int result = nombre_ligne(cdf);
        printf("Nombre de lignes : %d\n", result);
        
    } else if (choix == 2) {
        int result = nombre_colonne(cdf);
        printf("Nombre de colonnes : %d\n", result);
        
    } else if (choix == 3) {
        int x;
        printf("Entrez la valeur a compter : ");
        scanf("%d", &x);
        int res = count_egal(cdf, x);
        printf("Nombre de valeurs egales a %d : %d\n", x, res);
        
    } else if (choix == 4) {
        int x;
        printf("Entrez la valeur a compter : ");
        scanf("%d", &x);
        int result = count_sup(cdf, x);
        printf("Nombre de valeurs superieures a %d : %d\n", x, result);
        
    } else if (choix == 5) {
        int x;
        printf("Entrez la valeur a compter : ");
        scanf("%d", &x);
        int result = count_inf(cdf, x);
        printf("Nombre de valeurs inferieures a %d : %d\n", x, result);
        
    } else {
        printf("Choix invalide. Reessayer.\n");//gestion cas d'erreur
    }
}
