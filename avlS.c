#include "avlS.h"

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


int max2(int a, int b) {
    if ( a >= b) {
        return a;
    } else {
        return b;
    }
}

int min2(int a, int b) {
    if ( a >= b) {
        return b;
    } else {
        return a;
    }
}

int max3(int a, int b, int c) {
    if ( a >= b && a >= c) {
        return a;
    } else if ( b >= a && b >= c) {
        return b;
    } else {
        return c;
    }
}

int min3(int a, int b, int c) {
    if ( a <= b && a <= c) {
        return a;
    } else if ( b <= a && b <= c) {
        return b;
    } else {
        return c;
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
    pAVL->equilibre = eq_a - max2(eq_p, 0) - 1;
    pivot->equilibre = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
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
    pAVL->equilibre = eq_a - min2(eq_p, 0) + 1;
    pivot->equilibre = max3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
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
        fprintf(f, "%s %s %s %s %f\n", p->trajet.RouteID, p->trajet.min, p->trajet.moyenne, p->trajet.max, p->trajet.difference);
        infixeFichier(p->pGauche, f);
    }
}
