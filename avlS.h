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



#endif /* AVLT_H */
