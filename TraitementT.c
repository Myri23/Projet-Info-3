#include <stdio.h>
#include <stdlib.h>
 
typedef struct VILLE{
    char nomVille; //nom de la ville
    int traversee; //nombre de fois où la ville est traversée 
} VILLE;
 
typedef struct AVL {
    VILLE ville;
    struct AVL* pGauche;
    struct AVL* pDroit;
    int equilibre;
} AVL;

AVL* creerAVL(VILLE v) {
    AVL* pNouveau = malloc(sizeof(AVL));
    if (pNouveau == NULL) {
        exit(10);
    }
    pNouveau->ville = v;
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
 
int avoirVille(AVL* p) {
    if (estVide(p)) {
        exit(20);
    }
    return p->ville;
}
 
int aFilsGauche(AVL* p) {
    return (!estVide(p) && (p->pGauche != NULL));
}
 
int aFilsDroit(AVL* p) {
    return (!estVide(p) && (p->pDroit != NULL));
}

int recherche(AVL* p, VILLE v) {
    if (p == NULL) {
        return 0;
    } else if (p->ville == v) {
        return 1;
    } else {
        return recherche(p->pGauche, v) || recherche(p->pDroit, v);
    }
}
 
AVL* insertionAVL(AVL* pAVL, VILLE v, int* h) {
    if (pAVL == NULL) {
        *h = 1;
        return creerAVL(v);
    } else if (v < pAVL->ville) {
        pAVL->pGauche = insertionAVL(pAVL->pGauche, v, h);
        if (*h != 0) {
            pAVL->equilibre = pAVL->equilibre - *h;
            if (pAVL->equilibre == 0) {
                *h = 0;
            } else {
                *h = 1;
            }
        }
    } else if (v > pAVL->ville) {
        pAVL->pDroit = insertionAVL(pAVL->pDroit, v, h);
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
 
void ajoutFilsDroit(AVL* p, VILLE v) {
    if (estVide(p)) {
        exit(33);
    }
    if (aFilsDroit(p)) {
        exit(34);
    }
    p->pDroit = creerAVL(v);
    if (p->pDroit == NULL) {
        exit(35);
    }
}
 
void ajoutFilsGauche(AVL* p, VILLE v) {
    if (estVide(p)) {
        exit(30);
    }
    if (aFilsGauche(p)) {
        exit(31);
    }
    p->pGauche = creerAVL(v);
    if (p->pGauche == NULL) {
        exit(32);
    }
}

void ajoutABR(AVL* p, VILLE v) {
    if (!estVide(p)) {
        if (!recherche(p, v)) {
            while ((v < p->ville && aFilsGauche(p)) || (v > p->ville && aFilsDroit(p))) {
                if (v < p->ville) {
                    p = p->pGauche;
                } else {
                    p = p->pDroit;
                }
            }
 
            if (v < p->ville) {
                ajoutFilsGauche(p, v);
            } else if (v > p->ville) {
                ajoutFilsDroit(p, v);
            }
        }
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
    pivot->equilibre = fmin(eq_a - 2, fmax(eq_a + eq_p - 2, eq_p - 1));
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
    pAVL->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(eq_a - 2, fmax(eq_a + eq_p - 2, eq_p - 1));
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

AVL* suppMax(AVL* p, VILLE* pv) { //verifier si c un simple pointeur ici ou un double pointeur
    if (p->pDroit != NULL) {
        p->pDroit = suppMax(p->pDroit, pv);
    } else {
        *pv = p->ville;
        AVL* tmp = p;
        p = p->pGauche;
        free(tmp);
    }
    return p;
}
 
AVL* suppMin(AVL* p, VILLE* pv) { //verifier si c un simple pointeur ici ou un double pointeur
    if (p->pGauche != NULL) {
        p->pGauche = suppMin(p->pGauche, pv);
    } else {
        *pv = p->ville;
        AVL* tmp = p;
        p = p->pDroit;
        free(tmp);
    }
    return p;
}

AVL* RetirerABRGauche(AVL* p, VILLE v) {
    if (p == NULL) {
        return p;
    }
    if (v > p->ville) {
        p->pDroit = RetirerABRGauche(p->pDroit, v);
    } else if (v < p->ville) {
        p->pGauche = RetirerABRGauche(p->pGauche, v);
    } else {
        if (p->pGauche == NULL) {
            AVL* tmp = p->pDroit;
            free(p);
            return tmp;
        } else if (p->pDroit == NULL) {
            AVL* tmp = p->pGauche;
            free(p);
            return tmp;
        }
        int tmpville;
        p->pGauche = suppMax(p->pGauche, &tmpville);
        p->ville = tmpville;
    }
    return p;
}
 
AVL* RetirerABRDroit(AVL* p, VILLE v) {
    if (p == NULL) {
        return p;
    }
    if (v > p->ville) {
        p->pDroit = RetirerABRDroit(p->pDroit, v);
    } else if (v < p->ville) {
        p->pGauche = RetirerABRDroit(p->pGauche, v);
    } else {
        if (p->pGauche == NULL) {
            AVL* tmp = p->pDroit;
            free(p);
            return tmp;
        } else if (p->pDroit == NULL) {
            AVL* tmp = p->pGauche;
            free(p);
            return tmp;
        }
        int tmpville;
        p->pGauche = suppMax(p->pGauche, &tmpville);
        p->ville = tmpville;
    }
    return p;
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

AVL* suppMinAVL(AVL* pAVL, int* h, VILLE* pv) {
    AVL* tmp;
 
    if (pAVL->pGauche == NULL) {
        *pv = pAVL->ville;
        *h = -1;
        tmp = pAVL; 
        pAVL = pAVL->pDroit; 
        free(tmp);
        return pAVL; 
    } else {
        pAVL->pGauche = suppMinAVL(pAVL->pGauche, h, pv);
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
 
AVL* suppressionAVL(AVL* pAVL, VILLE v, int* h) {
    AVL* tmp;
 
    if (pAVL == NULL) {
        *h = 1;
        return pAVL;
    } else if (v > pAVL->ville) {
        pAVL->pDroit = suppressionAVL(pAVL->pDroit, v, h);
    } else if (v < pAVL->ville) {
        pAVL->pGauche = suppressionAVL(pAVL->pGauche, v, h);
        *h = -*h;
    } else if (aFilsDroit(pAVL)) {
        pAVL->pDroit = suppMinAVL(pAVL->pDroit, h, &(pAVL->ville));
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



int main() {
    
    return 0;
}