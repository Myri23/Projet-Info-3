#ifndef AVLT_H
#define AVLT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct VILLE {
    char nomVille[50];
    int traversee;
} VILLE;

typedef struct AVL {
    VILLE ville;
    struct AVL* pGauche;
    struct AVL* pDroit;
    int equilibre;
} AVL;

AVL* creerAVL(VILLE v);
int estVide(AVL* p);
int estFeuille(AVL* p);
VILLE avoirVille(AVL* p);
int aFilsGauche(AVL* p);
int aFilsDroit(AVL* p);
int recherche(AVL* p, VILLE v);
AVL* insertionAVL(AVL* pAVL, VILLE v, int* h);
void ajoutFilsDroit(AVL* p, VILLE v);
void ajoutFilsGauche(AVL* p, VILLE v);
int max2(int a, int b);
int min2(int a, int b);
int max3(int a, int b, int c);
int min3(int a, int b, int c);
AVL* RotationGauche(AVL* pAVL);
AVL* RotationDroite(AVL* pAVL);
AVL* DoubleRotationGauche(AVL* pAVL);
AVL* DoubleRotationDroite(AVL* pAVL);
AVL* equilibrerAVL(AVL* pAVL);
AVL* suppMinAVL(AVL* pAVL, int* h, VILLE* pv);
AVL* suppressionAVL(AVL* pAVL, VILLE v, int* h);
void infixeFichier(AVL* p, FILE* f);

#endif /* AVLT_H */
