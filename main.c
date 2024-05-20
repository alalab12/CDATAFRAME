#include "column.h"
#include "cdataframe.h"
#include <stdio.h>


// Définition des fonctions du menu
void menu_creation(CDataframe* cdf);
void menu_remplissage(CDataframe* cdf);
void menu_supression(CDataframe* cdf);
void menu_affichage(CDataframe* cdf);
void menu_operation(CDataframe* cdf);
void menu_fonctionnalité(CDataframe* cdf);

int main() {
    CDataframe* cdf = creation_dataframe();

    int choix, verif = 1;
    while(verif) {
        //Affichage du menu
        printf("Menu :\n");
        printf("1. Création\n");
        printf("2. Remplissage\n");
        printf("3. Suppression\n");
        printf("4. Affichage\n");
        printf("5. Gestion\n");
        printf("6. Fonctionnalités\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
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
                menu_fonctionnalité(cdf);
                break;
            case 7:
                liberer_dataframe(cdf);
                printf("Merci d'avoir testé notre programme ! Aude Labat et Julie Brouet\n");
                verif=0;
                break;
            default:
                printf("Choix invalide. Réessayer.\n");
        }
    }

    return 0;
}
//Fonction pour les différents menu
void menu_creation(CDataframe* cdf) {
    printf("Création de dataframe :\n");
    printf("1. Créer un dataframe vide\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        // Créer un dataframe vide
        printf("Dataframe créé !\n");
    } else {
        printf("Choix invalide. Réessayer.\n");
    }
}

void menu_remplissage(CDataframe* cdf) {
    printf("Remplissage de dataframe :\n");
    printf("1. Remplir le dataframe à partir de l'utilisateur\n");
    printf("2. Remplir le dataframe aléatoirement\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        dataframe_remplissage_utilisateur(cdf);
        printf("Dataframe rempli à partir de l'utilisateur !\n");
    }
    else if (choix == 2) {
        dataframe_remplissage_dur(cdf);
        printf("Dataframe rempli aléatoirement !\n");
    }
    else {
        printf("Choix invalide. Réessayer.\n");
    }
}

void menu_supression(CDataframe* cdf) {
    printf("Suppression de dataframe :\n");
    printf("1. Libérer le dataframe\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        liberer_dataframe(cdf);
        printf("Dataframe libéré !\n");
    } else {
        printf("Choix invalide. Réessayer.\n");
    }
}

void menu_affichage(CDataframe* cdf) {
    printf("Affichage de dataframe :\n");
    printf("1. Afficher tout le dataframe\n");
    printf("2. Afficher les lignes du dataframe\n");
    printf("3. Afficher les colonnes du dataframe\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        afficher_dataframe(cdf);
    } else if (choix == 2) {
        int ligne_limite;
        printf("Entrez le nombre de lignes à afficher : ");
        scanf("%d", &ligne_limite);
        afficher_dataframe_lignes(cdf, ligne_limite);
    } else if (choix == 3) {
        int col_limite;
        printf("Entrez le nombre de colonnes à afficher : ");
        scanf("%d", &col_limite);
        afficher_dataframe_colonnes(cdf, col_limite);
    } else {
        printf("Choix invalide. Réessayer.\n");
    }
}

void menu_operation(CDataframe* cdf) {
    printf("Gestion de dataframe :\n");
    printf("1. Ajouter une ligne\n");
    printf("2. Supprimer une ligne\n");
    printf("3. Ajouter une colonne\n");
    printf("4. Supprimer une colonne\n");
    printf("5. Renommer une colonne\n");
    printf("6. Vérifier si une valeur existe\n");
    printf("7. Accéder à une valeur\n");
    printf("8. Remplacer une valeur\n");
    printf("9. Afficher les titres\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        //Stocker les nouvelles valeurs à ajouter dans un tableau
        int val[cdf->num_columns];
        for (int i = 0; i < cdf->num_columns; i++) {
            printf("Entrez la valeur pour la colonne %d : ", i);
            scanf("%d", &val[i]);
        }
        int res = ajouter_ligne(cdf, val);
        if (res == 1) {
            printf("Ligne ajoutée avec succès !\n");
        } else {
            printf("Erreur lors de l'ajout de la ligne.\n");
        }
    } else if (choix == 2) {
        int lig_ind;
        printf("Entrez l'index de la ligne à supprimer : ");
        scanf("%d", &lig_ind);
        int result = supprimer_ligne(cdf, lig_ind);
        if (result == 1) {
            printf("Ligne supprimée avec succès !\n");
        } else {
            printf("Erreur lors de la suppression de la ligne.\n");
        }
    } else if (choix == 3) {
        char titre[100];
        printf("Entrez le titre de la colonne à ajouter : ");
        scanf("%s", titre);
        int result = ajouter_colonne(cdf, titre);
        if (result == 1) {
            printf("Colonne ajoutée avec succès !\n");
        } else {
            printf("Erreur lors de l'ajout de la colonne.\n");
        }
    } else if (choix == 4) {
        int col_ind;
        printf("Entrez l'indice de la colonne à supprimer : ");
        scanf("%d", &col_ind);
        int result = supprimer_colonne(cdf, col_ind);
        if (result == 1) {
            printf("Colonne supprimée avec succès !\n");
        } else {
            printf("Erreur lors de la suppression de la colonne.\n");
        }
    } else if (choix == 5) {
        int col_ind;
        char nv_titre[100];
        printf("Entrez l'indice de la colonne à renommer : ");
        scanf("%d", &col_ind);
        printf("Entrez le nouveau titre de la colonne : ");
        scanf("%s", nv_titre);
        int result = renomer_colonne(cdf, col_ind, nv_titre);
        if (result == 1) {
            printf("Colonne renommée avec succès !\n");
        } else {
            printf("Erreur lors du renommage de la colonne.\n");
        }
    } else if (choix == 6) {
        int val;
        printf("Entrez la valeur à vérifier : ");
        scanf("%d", &val);
        int result = valeur_exists(cdf, val);
        if (result == 1) {
            printf("La valeur existe dans le dataframe.\n");
        } else {
            printf("La valeur n'existe pas dans le dataframe.\n");
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
            printf("La valeur à la ligne %d et à la colonne %d est : %d\n", lig, col, valeur);
        } else {
            printf("Erreur lors de l'accès à la valeur.\n");
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
            printf("Valeur remplacée !\n");
        } else {
            printf("Erreur lors du remplacement de la valeur.\n");
        }
    } else if (choix == 9) {
        afficher_titres(cdf);
    }
}
void menu_fonctionnalité(CDataframe* cdf) {
    printf("Fonctionnalités de dataframe :\n");
    printf("1. Nombre de lignes\n");
    printf("2. Nombre de colonnes\n");
    printf("3. Compter les valeurs égales à un entier\n");
    printf("4. Compter les valeurs supérieures à un entier\n");
    printf("5. Compter les valeurs inférieures à un entier\n");
    printf("Entrez votre choix : ");
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
        printf("Entrez la valeur à compter : ");
        scanf("%d", &x);
        int res = count_egal(cdf, x);
        printf("Nombre de valeurs égales à %d : %d\n", x, res);
    } else if (choix == 4) {
        int x;
        printf("Entrez la valeur à compter : ");
        scanf("%d", &x);
        int result = count_sup(cdf, x);
        printf("Nombre de valeurs supérieures à %d : %d\n", x, result);
    } else if (choix == 5) {
        int x;
        printf("Entrez la valeur à compter : ");
        scanf("%d", &x);
        int result = count_inf(cdf, x);
        printf("Nombre de valeurs inférieures à %d : %d\n", x, result);
    } else {
        printf("Choix invalide. Réessayer.\n");
    }
}
