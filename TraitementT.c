#include <stdio.h>
#include <stdlib.h>
 
typedef struct VILLE{
    char nom;
    int nb;
} VILLE;
 
typedef struct AVL {
    VILLE ville;
    struct AVL* pRight;
    struct AVL* pLeft;
    int equilibre;
} AVL;

int main() {
    printf("Bonjour");
}