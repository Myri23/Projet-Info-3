#include "avlT.h"

int main(int argc, char** argv) {

    FILE *result_T=fopen("result_T.txt", "r"); 
    FILE *resultatsTc=fopen("resultatsTc.txt", "w");
    
    if (result_T == NULL || resultatsTc == NULL) {
        perror("Error opening file");
        return -1;
    }

    AVL* pRoot = NULL; // Initialisation de votre AVL à NULL

    // Lecture du fichier et ajout des données dans l'AVL
    VILLE ville;
    int h = 0; // Initialisation de la hauteur pour l'insertion
    char line[100]; // Taille suffisante pour stocker chaque ligne
    while (fgets(line, sizeof(line), result_T) != NULL) {
        char* ligne = strtok(line, " "); // Séparer la ligne par des espaces
        if (ligne == NULL) {
            continue; // Ligne vide ou non valide, passer à la suivante
        }

        // Conversion de l'entier
        int traversee = atoi(ligne);

        // Lire le nom de la ville restant sur la ligne
        ligne = strtok(NULL, "\n");
        if (ligne == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }

        // Utiliser ligne comme nom de ville
        strcpy(ville.nomVille, ligne);
        ville.traversee = traversee;

        // Insérer dans l'AVL
        pRoot = insertionAVL(pRoot, ville, &h);
    }

    infixeFichier(pRoot, resultatsTc);

    fclose(result_T);
    fclose(resultatsTc);

    return 0;
}
