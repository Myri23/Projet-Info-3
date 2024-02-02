#include "avlS.h"

int main(int argc, char** argv) {
    FILE *temp_resultat_S=fopen("temp/temp_resultat_S.txt", "r"); 
    FILE *resultatsSc=fopen("temp/resultatsSc.txt", "w");
    
    if (temp_resultat_S == NULL || resultatsSc == NULL) {
        perror("Error opening file");
        return -1;
    }

    AVL* pRoot = NULL; // Initialisation de votre AVL à NULL

    // Lecture du fichier et ajout des données dans l'AVL
    TRAJET trajet;
    int h = 0; // Initialisation de la hauteur pour l'insertion
    char line[100]; // Taille suffisante pour stocker chaque ligne
    while (fgets(line, sizeof(line), temp_resultat_S) != NULL) {
        char* token = strtok(line, " "); // Séparer la ligne par des points-virgules
        if (token == NULL) {
            continue;  // Ligne vide ou non valide, passer à la suivante
        }

        // Copie du RouteID
        strcpy(trajet.RouteID, token);

        // Copie du min
        token = strtok(NULL, " ");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.min, token);

        // Copie de la moyenne
        token = strtok(NULL, " ");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.moyenne, token);


        // Copie du max
        token = strtok(NULL, " ");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        strcpy(trajet.max, token);

        // Conversion de la différence en float
        token = strtok(NULL, " ");
        if (token == NULL) {
            continue; // Ligne non valide, passer à la suivante
        }
        trajet.difference = atof(token);

        // Insérer dans l'AVL
        pRoot = insertionAVL(pRoot, trajet, &h);
    }

    // Écriture de l'AVL dans le fichier resultatsSc.txt
    infixeFichier(pRoot, resultatsSc);

    // Fermeture des fichiers
    fclose(temp_resultat_S);
    fclose(resultatsSc);
    
    return 0;
}
