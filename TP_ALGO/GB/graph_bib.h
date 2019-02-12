#ifndef GRAPH_BIB_H
#define GRAPH_BIB_H

#include <sys/types.h>
#define TElement int
#define MAX 200

// Les structures
// structure de matrice
typedef struct {
    size_t elm_size;
    TElement** mat;
    int width;
    int height;
} MAT;

// structure de liste
typedef struct node {
	int v;
    size_t elm_size;
    TElement w;
    struct node* suiv;
} NODE;

// Structure de graphe
#define GB_DIRECTED 1
#define GB_MULTI 2
#define GB_WEIGHTED 4

typedef struct {
    int type;
    int nbr_sommets;
    int nbr_arcs;
    NODE** list;
    NODE** pred;
} GRAPH_LIST;

typedef struct {
    int type;
    MAT arc;
    MAT weight;
} GRAPH_VxV;

typedef struct {
    int type;
    MAT arc;
    TElement* weight;
} GRAPH_VxA;

// Les prototypes
// lecture
GRAPH_VxV lire_graphe_vxv(char* nom_fich);
GRAPH_VxA lire_graphe_vxa(char* nom_fich);
GRAPH_LIST lire_graphe_liste(char* nom_fich);

// ecriture
void ecrire_graphe_liste(const char* nom_fich, GRAPH_LIST g);
void ecrire_graphe_vxv(const char* nom_fich, GRAPH_VxV g);
void ecrire_graphe_vxa(const char* nom_fich, GRAPH_VxA g);

// manipulation
MAT floyd_warshall_rec(GRAPH_VxV g);
int* tri_top_list(GRAPH_LIST g);
#endif // GRAPH_BIB_H
