#include "avlT.h"

int main(int argc, char** argv) {

    FILE *temp_resultat_T=fopen("temp/temp_resultat_T.txt", "r"); 
    FILE *resultatsTc=fopen("temp/resultatsTc.txt", "w");
    
    if (temp_resultat_T == NULL || resultatsTc == NULL) {
        perror("Error opening file");
        return -1;
    }

    AVL* pRoot = NULL; // Initialisation de votre AVL à NULL

    // Lecture du fichier et ajout des données dans l'AVL
    VILLE ville;
    int h = 0; // Initialisation de la hauteur pour l'insertion
    char line[100]; // Taille suffisante pour stocker chaque ligne
    while (fgets(line, sizeof(line), temp_resultat_T) != NULL) {
        char* ligne = strtok(line, " "); // Séparer la ligne par des espaces
        if (ligne == NULL) {
            continue; // Ligne vide ou non valide, passer à la suivante
        }


        int traversee = atoi(ligne); // Conversion de l'entier


        ligne = strtok(NULL, "\n");  // Lire le nom de la ville restant sur la ligne
        if (ligne == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }


        strcpy(ville.nomVille, ligne);  // Utiliser ligne comme nom de ville
        ville.traversee = traversee;

        pRoot = insertionAVL(pRoot, ville, &h);  // Insérer dans l'AVL
    }

    infixeFichier(pRoot, resultatsTc);

    fclose(temp_resultat_T);
    fclose(resultatsTc);

    return 0;
}
