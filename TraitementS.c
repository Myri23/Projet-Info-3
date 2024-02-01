#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct TRAJET{ //TRAJET
    char RouteID[50];
    char max[50];
    char min[50];
    char moyenne[50];
    float difference;
} TRAJET;


 
typedef struct AVL {
    TRAJET trajet;
    struct AVL* pGauche;
    struct AVL* pDroit;
    int equilibre;
} AVL;



AVL* creerAVL(TRAJET t) {
    AVL* pNouveau = malloc(sizeof(AVL));
    if (pNouveau == NULL) {
        exit(10);
    }
    pNouveau->trajet = t;
    pNouveau->pGauche = NULL;
    pNouveau->pDroit = NULL;
    pNouveau->equilibre = 0;
    return pNouveau;
}

int estVide(AVL* p) {
    return p == NULL;
}
 
int estFeuille(AVL* p) {
    return (!estVide(p) && p->pGauche == NULL && p->pDroit == NULL);
}
 
TRAJET avoirTrajet(AVL* p) {
    if (estVide(p)) {
        exit(20);
    }
    return p->trajet;
}
 
int aFilsGauche(AVL* p) {
    return (!estVide(p) && (p->pGauche != NULL));
}
 
int aFilsDroit(AVL* p) {
    return (!estVide(p) && (p->pDroit != NULL));
}

int recherche(AVL* p, TRAJET t) {
    if (p == NULL) {
        return 0;
    } else if (p->trajet.RouteID == t.RouteID && p->trajet.difference == t.difference) {
        return 1;
    } else {
        return recherche(p->pGauche, t) || recherche(p->pDroit, t);
    }
}
 
AVL* insertionAVL(AVL* pAVL, TRAJET t, int* h) {
    if (pAVL == NULL) {
        *h = 1;
        return creerAVL(t);
    } else if (t.difference < pAVL->trajet.difference) {
        pAVL->pGauche = insertionAVL(pAVL->pGauche, t, h);
        if (*h != 0) {
            pAVL->equilibre = pAVL->equilibre - *h;
            if (pAVL->equilibre == 0) {
                *h = 0;
            } else {
                *h = 1;
            }
        }
    } else if (t.difference > pAVL->trajet.difference) {
        pAVL->pDroit = insertionAVL(pAVL->pDroit, t, h);
        if (*h != 0) {
            pAVL->equilibre = pAVL->equilibre + *h;
            if (pAVL->equilibre == 0) {
                *h = 0;
            } else {
                *h = 1;
            }
        }
    } else {
        *h = 0;
    }
    return pAVL;
}
 
void ajoutFilsDroit(AVL* p, TRAJET t) {
    if (estVide(p)) {
        exit(33);
    }
    if (aFilsDroit(p)) {
        exit(34);
    }
    p->pDroit = creerAVL(t);
    if (p->pDroit == NULL) {
        exit(35);
    }
}
 
void ajoutFilsGauche(AVL* p, TRAJET t) {
    if (estVide(p)) {
        exit(30);
    }
    if (aFilsGauche(p)) {
        exit(31);
    }
    p->pGauche = creerAVL(t);
    if (p->pGauche == NULL) {
        exit(32);
    }
}


AVL* RotationGauche(AVL* pAVL) {
    AVL* pivot;
    int eq_a;
    int eq_p;
    pivot = pAVL->pDroit;
    pAVL->pDroit = pivot->pGauche;
    pivot->pGauche = pAVL;
 
    eq_a = pAVL->equilibre;
    eq_p = pivot->equilibre;
    pAVL->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(eq_a - 2, fmin(eq_a + eq_p - 2, eq_p - 1));
    pAVL = pivot;
    return pAVL;
}
 
AVL* RotationDroite(AVL* pAVL) {
    AVL* pivot;
    int eq_a;
    int eq_p;
    pivot = pAVL->pGauche;
    pAVL->pGauche = pivot->pDroit;
    pivot->pDroit = pAVL;
 
    eq_a = pAVL->equilibre;
    eq_p = pivot->equilibre;
    pAVL->equilibre = eq_a - fmin(eq_p, 0) + 1;
    pivot->equilibre = fmax(eq_a + 2, fmax(eq_a + eq_p + 2, eq_p + 1));
    pAVL = pivot;
    return pAVL;
}
 
AVL* DoubleRotationGauche(AVL* pAVL) {
    pAVL->pDroit = RotationDroite(pAVL->pDroit);
    return RotationGauche(pAVL);
}
 
AVL* DoubleRotationDroite(AVL* pAVL) {
    pAVL->pGauche = RotationGauche(pAVL->pGauche);
    return RotationDroite(pAVL);
}


AVL* equilibrerAVL(AVL* pAVL) {
    if (pAVL->equilibre >= 2) {
        if (pAVL->pDroit->equilibre >= 0) {
            return RotationGauche(pAVL);
        } else {
            return DoubleRotationGauche(pAVL);
        }
    } else if (pAVL->equilibre <= -2) {
        if (pAVL->pGauche->equilibre <= 0) {
            return RotationDroite(pAVL);
        } else {
            return DoubleRotationDroite(pAVL);
        }
    }
    return pAVL;
}

AVL* suppMinAVL(AVL* pAVL, int* h, TRAJET* pt) {
    AVL* tmp;
 
    if (pAVL->pGauche == NULL) {
        *pt = pAVL->trajet;
        *h = -1;
        tmp = pAVL; 
        pAVL = pAVL->pDroit; 
        free(tmp);
        return pAVL; 
    } else {
        pAVL->pGauche = suppMinAVL(pAVL->pGauche, h, pt);
        *h = -*h;
    }
 
    if (*h != 0) {
        pAVL->equilibre = pAVL->equilibre + *h;
        if (pAVL->equilibre == 0) {
            *h = -1;
        } else {
            *h = 0;
        }
    }
 
    return pAVL;
}
 
AVL* suppressionAVL(AVL* pAVL, TRAJET t, int* h) {
    AVL* tmp;
 
    if (pAVL == NULL) {
        *h = 1;
        return pAVL;
    } else if (t.difference > pAVL->trajet.difference) {
        pAVL->pDroit = suppressionAVL(pAVL->pDroit, t, h);
    } else if (t.difference < pAVL->trajet.difference) {
        pAVL->pGauche = suppressionAVL(pAVL->pGauche, t, h);
        *h = -*h;
    } else if (aFilsDroit(pAVL)) {
        pAVL->pDroit = suppMinAVL(pAVL->pDroit, h, &(pAVL->trajet));
    } else {
        tmp = pAVL;
        pAVL = pAVL->pGauche;
        free(tmp);
        *h = -1;
    }
 
    if (pAVL == NULL) {
        *h = 0;
    }
 
    if (*h != 0) {
        pAVL->equilibre = pAVL->equilibre + *h;
    }
 
    if (pAVL->equilibre == 0) {
        *h = 0;
    } else {
        *h = 1;
    }
 
    return pAVL;
}

void infixeFichier(AVL *p, FILE *f) {
    if (!estVide(p)) {
        infixeFichier(p->pDroit, f);
        fprintf(f, "%s;%s;%s;%s;%f\n", p->trajet.RouteID, p->trajet.min, p->trajet.moyenne, p->trajet.max, p->trajet.difference);
        infixeFichier(p->pGauche, f);
    }
}


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





