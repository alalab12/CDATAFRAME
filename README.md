# CDATAFRAME
Nom : Aude Labat/Julie Brouet
Classe : Groupe B
lien github : https://github.com/alalab12/CDATAFRAME

Ce projet a pour but la manipulation de données en utilisant le langage C.
Pour cela, nous utilisons des structures qui sont appelées colonnes qui contiennent le nom de la colonne, sa taille( physique et logique) ou encore, le plus important, les données.
Nous avons ainsi créé ces fonctions qui agissent sur une colonne :

create_column : crée une colonne vide ainsi que son titre
insert_value : insère une valeur
free_column : libère la mémoire des données d'une colonne 
print_column : affiche la colonne
nb_occurence: compte le nombre de fois qu'une valeur est présente dans une colonne
x_pos : position d'une certaine valeur dans une colonne
val_sup : nombre de valeurs de la colonne supérieur à la valeur donnée
val_inf : nombre de valeurs de la colonne inférieur à la valeur donnée
val_egal : nombre de valeurs de la colonne égal à la valeur donnée

À l'aide des structures appelées colonnes nous allons pouvoir créer des structures appelées dataframes, qui contiennent les caractéristiques des structures colonne ainsi que le nombre de colonnes et le nombre de lignes.
Grâce à cette structure et aux fonctions créées précédemment, nous pouvoir crée des fonctionnalités qui vont nous permettre à l'utisateur de crée son dataframe.

creation_dataframe_vide : créer le dataframe vide
remplissage_utilisateur : permet à l'utilisateur de remplir le dataframe
remplissage_dur : permet de remplir le dataframe
afficher_dataframe : permet d'afficher le dataframe en entier
afficher_certaines_colonne : permet d'afficher certaines colonnes du dataframe
afficher_certaines_ligne : permet d'ajouter certaines lignes du dataframe
ajouter_ligne_valeur : permet d'ajouter une ligne au dataframe
ajouter_colonne : permet d'ajouter une colonne au dataframe
supprimer_colonne : permet de supprimer une colonne du dataframe
renomer_colonne : permet de renommer une colonne du dataframe
acceder_valeur : permet d'accéder à une valeur du dataframe
remplacer_valeur : remplace une valeur du dataframe
afficher_titre_colonne : affiche le titre d'une colonne du dataframe
nb_lignes : nombre de lignes dans le dataframe
nb_colonnes : nombre de colonnes dans le dataframe
int nb_valeur_egale : nombre de valeurs du dataframe égal à la valeur donnée
nb_valeur_sup : nombre de valeurs du dataframe supérieur à la valeur donnée
nb_valeuf_inf : ombre de valeurs du dataframe inférieur à la valeur donnée

Pour ce projet, nous allons utiliser le dataframe comme un tableau de colonnes.

