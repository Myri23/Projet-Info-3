#ifndef AVLT_H
#define AVLT_H

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

AVL* creerAVL(TRAJET t);
int estVide(AVL* p);
int estFeuille(AVL* p);
TRAJET avoirTrajet(AVL* p);
int aFilsGauche(AVL* p);
int aFilsDroit(AVL* p);
int recherche(AVL* p, TRAJET t);
AVL* insertionAVL(AVL* pAVL, TRAJET t, int* h);
void ajoutFilsDroit(AVL* p, TRAJET t);
void ajoutFilsGauche(AVL* p, TRAJET t);
AVL* RotationGauche(AVL* pAVL);
AVL* RotationDroite(AVL* pAVL);
AVL* DoubleRotationGauche(AVL* pAVL);
AVL* DoubleRotationDroite(AVL* pAVL);
AVL* equilibrerAVL(AVL* pAVL);
AVL* suppMinAVL(AVL* pAVL, int* h, TRAJET* pt);
AVL* suppressionAVL(AVL* pAVL, TRAJET t, int* h);
void infixeFichier(AVL *p, FILE *f);

#endif /* AVLT_H */
