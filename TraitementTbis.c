#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct VILLE{
    char nomVille[50]; //nom de la ville
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
 
VILLE avoirVille(AVL* p) {
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
    } else if (p->ville.nomVille == v.nomVille && p->ville.traversee == v.traversee) {
        return 1;
    } else {
        return recherche(p->pGauche, v) || recherche(p->pDroit, v);
    }
}
 
AVL* insertionAVL(AVL* pAVL, VILLE v, int* h) {
    if (pAVL == NULL) {
        *h = 1;
        return creerAVL(v);
    } else if (v.traversee < pAVL->ville.traversee) {
        pAVL->pGauche = insertionAVL(pAVL->pGauche, v, h);
        if (*h != 0) {
            pAVL->equilibre = pAVL->equilibre - *h;
            if (pAVL->equilibre == 0) {
                *h = 0;
            } else {
                *h = 1;
            }
        }
    } else if (v.traversee > pAVL->ville.traversee) {
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
            while ((v.traversee < p->ville.traversee && aFilsGauche(p)) || (v.traversee > p->ville.traversee && aFilsDroit(p))) {
                if (v.traversee < p->ville.traversee) {
                    p = p->pGauche;
                } else {
                    p = p->pDroit;
                }
            }
 
            if (v.traversee < p->ville.traversee) {
                ajoutFilsGauche(p, v);
            } else if (v.traversee > p->ville.traversee) {
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
    if (v.traversee > p->ville.traversee) {
        p->pDroit = RetirerABRGauche(p->pDroit, v);
    } else if (v.traversee < p->ville.traversee) {
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
        VILLE tmpville;
        p->pGauche = suppMax(p->pGauche, &tmpville);
        p->ville = tmpville;
    }
    return p;
}
 
AVL* RetirerABRDroit(AVL* p, VILLE v) {
    if (p == NULL) {
        return p;
    }
    if (v.traversee > p->ville.traversee) {
        p->pDroit = RetirerABRDroit(p->pDroit, v);
    } else if (v.traversee < p->ville.traversee) {
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
        VILLE tmpville;
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
    } else if (v.traversee > pAVL->ville.traversee) {
        pAVL->pDroit = suppressionAVL(pAVL->pDroit, v, h);
    } else if (v.traversee < pAVL->ville.traversee) {
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


void villeArrivee(AVL *p, FILE *f) {
	while (p != NULL) {
		for( p, fscanf(fdata, "%d %s %s", &idtrajet, &ville.nomVille, &ville.nomVille) == 3, p->pNouveau) {
			p->ville.traversee = 0
		}
	}
}



int main(int argc, char** argv) {
	FILE *tempTbis=fopen("tempTbis.csv", "r"); 
    	FILE *resultatsT1=fopen("resultatsT1.csv", "r");
    	FILE *resultatsT2=fopen("resultatsT2.csv", "w");
    
    	if (tempTbis == NULL || resultatsT1 == NULL || resultatsT2 == NULL) {
        	perror("Error opening file");
        	return -1;
    	}
    	
    	AVL* pRoot = NULL; // Initialisation de votre AVL à NULL

    	// Lecture du fichier et ajout des données dans l'AVL
   	VILLE ville;
   	int h = 0; // Initialisation de la hauteur pour l'insertion
    	while (fscanf(resultatsT1, "%s %d", &ville.nomVille, &ville.traversee) == 2) { //changer fichier par le nom d'un des fichiers
        	pRoot = insertionAVL(pRoot, ville, &h); // Utilisez votre fonction d'insertion ici
    	}

    	
    	fclose(tempTbis);
    	fclose(resultatsT1);
    	fclose(resultatsT2);

    	return 0;
}
