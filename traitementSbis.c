#include <stdio.h>
#include <stdlib.h>

typedef struct avl {
  int id;
  float distance_min;
  float distance_max;
  float distance_moy;
  float diff;
  struct avl *fd;
  struct avl *fg;  
  int equilibre;
} Avl;

Avl *creerAvl(int id, float min, float max, float moy, float diff) {  
  Avl *new = malloc(sizeof(Avl));
  if (new == NULL) {
    printf("erreur d'allocation dynamique");
    exit(1);
  }
  new->id = id;
  new->distance_min = min;
  new->distance_max = max;
  new->distance_moy = moy;
  new->diff = diff;
  new->fd = NULL;
  new->fg = NULL;
  new->equilibre = 0;
  return new;
}                                                                     

int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

int min2(int a, int b, int c) {
  return min(min(a, b), c);
}

int max2(int a, int b, int c) {
  return max(max(a, b), c);
}

Avl *rotationG(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  pivot = a->fd;
  a->fd = pivot->fg;
  pivot->fg = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - max(eq_pivot, 0) - 1;
  pivot->equilibre = min2(eq_a - 2, eq_a + eq_pivot - 2, eq_pivot - 1);
  a = pivot;
  return a;
}

Avl *rotationD(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  pivot = a->fg;
  a->fg = pivot->fd;
  pivot->fd = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - min(eq_pivot, 0) + 1;
  pivot->equilibre = max2(eq_a + 2, eq_a + eq_pivot + 2, eq_pivot + 1);
  a = pivot;
  return a;
}


Avl *DoubleRG(Avl *a) {
  a->fd = rotationD(a->fd);
  return rotationG(a);
}

Avl *DoubleRD(Avl *a) {
  a->fg = rotationG(a->fg);
  return rotationD(a);
}

Avl *equilibreAVL(Avl *a) {
  if (a->equilibre >= 2) {
    if (a->fd->equilibre >= 0) {
      return rotationG(a);
    } else {
      return DoubleRG(a);
    }
  } else if (a->equilibre <= -2) {
    if (a->fg->equilibre <= 0) {
      return rotationD(a);
    } else {
      return DoubleRD(a);
    }
  }
  return a;
}

Avl *insertionAVL(Avl *a,int id, float min, float max, float moy, float diff, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvl(id, min, max,  moy, diff);
  } 
  else if (diff < a->diff) {
    a->fg = insertionAVL(a->fg, id,  min, max,  moy, diff, h);
    *h = -*h;
  } 
  else if (diff > a->diff) {
    a->fd = insertionAVL(a->fd, id, min, max,  moy, diff, h);
  } 
  else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVL(a);
    if (a->equilibre == 0) {
      *h = 0;
    } 
    else {
      *h = 1;
    }
  }
  return a;
}
