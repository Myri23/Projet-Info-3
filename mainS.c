#include "avlS.h"

int main(int argc, char** argv) {
    FILE *tempS2=fopen("tempS2.txt", "r"); 
    FILE *result_S1=fopen("result_S1.txt", "w");
    
    if (tempS2 == NULL || result_S1 == NULL) {
        perror("Error opening file");
        return -1;
    }

    AVL* pRoot = NULL; // Initialisation de votre AVL à NULL

    // Lecture du fichier et ajout des données dans l'AVL
    TRAJET trajet;
    int h = 0; // Initialisation de la hauteur pour l'insertion
    char line[100]; // Taille suffisante pour stocker chaque ligne
    while (fgets(line, sizeof(line), tempS2) != NULL) {
        char* token = strtok(line, ";"); // Séparer la ligne par des points-virgules
        if (token == NULL) {
            continue; // Ligne vide ou non valide, passer à la suivante
        }

        // Copie du RouteID
        strcpy(trajet.RouteID, token);

        // Copie du min
        token = strtok(NULL, ";");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.min, token);

        // Copie de la moyenne
        token = strtok(NULL, ";");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.moyenne, token);


        // Copie du max
        token = strtok(NULL, ";");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.max, token);

        // Conversion de la différence en float
        token = strtok(NULL, ";");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        trajet.difference = atof(token);

        // Insérer dans l'AVL
        pRoot = insertionAVL(pRoot, trajet, &h);
    }

    // Écriture de l'AVL dans le fichier result_S1.txt
    infixeFichier(pRoot, result_S1);

    // Fermeture des fichiers
    fclose(tempS2);
    fclose(result_S1);
    
    return 0;
}
