#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "graph_bib.h"

// Les fonctions d'utilités
MAT creer_matrice(int w, int h, size_t s) {
    MAT m;
    m.elm_size = s;
    m.width = w;
    m.height = h;
    m.mat = malloc(sizeof(void*) * h);
    for(int i=0; i<h; i++) {
        m.mat[i] = malloc(s * w);
        for(int j=0; j<w; j++) {
            m.mat[i][j] = 0;
        }
    }
    return m;
}

int list_len(NODE* n) {
	int count = 0;
	while(n != NULL) {
		count++;
		n = n->suiv;
	}
	return count;
}

NODE* push(NODE* n, int v, TElement w) {
    NODE* t = malloc(sizeof(NODE));
    t->v = v;
    t->w = w;
    t->suiv = n;
    return t;
}

NODE* pop(NODE* n) {
    if(n == NULL)
        return NULL;
    NODE* t = n->suiv;
    free(n);
    return t;
}

NODE* pop_first(NODE* n, int *popped) {
	if(n == NULL)
		return NULL;
	if(n->suiv == NULL) {
		*popped = n->v;
		free(n);
		return NULL;
	}
	NODE* temp;
	for(temp=n; temp->suiv; temp->suiv->suiv);
	free(temp->suiv);
	temp->suiv = NULL;
	
	return n;
}

GRAPH_LIST lire_graphe_liste(char* nom_fich) {
    GRAPH_LIST g;
    FILE* f;
    if((f = fopen(nom_fich, "r")) == NULL) {
		perror("Cant open file\n");
		exit(-1);
	}
	
	// Recuperer nbr des sommets
	int nbr_sommets;
	int ret = fscanf(f, "%d\n", &nbr_sommets);
	if(ret != 1 || nbr_sommets < 1) {
		fprintf(stderr, "%d: Invalid value %d\n", ftell(f), nbr_sommets);
		exit(-1);
	}

	// Initialiser la structure de graphe
	g.nbr_sommets = nbr_sommets;
	g.nbr_arcs = 0;
	// graphe
	g.list = malloc(sizeof(NODE*) * nbr_sommets);
	bzero(g.list, sizeof(NODE*) * nbr_sommets); // initialiser a NULL
	// predecesseurs
	g.pred = malloc(sizeof(NODE*) * nbr_sommets);
	bzero(g.pred, sizeof(NODE*) * nbr_sommets); // initialiser a NULL

	// Le calcul de type de graphe
	g.type = 0;
	int* tab_temp = malloc(sizeof(int) * nbr_sommets); // temporaire pour determiner le type
	bzero(tab_temp, sizeof(int) * nbr_sommets);
	TElement som_w = 0;

	for(int i=0; i<nbr_sommets; i++) {
		int nbr_arcs;
		ret = fscanf(f, "%d;", &nbr_arcs);
		if(ret != 1 || nbr_arcs < 0 || nbr_arcs > nbr_sommets) {
			fprintf(stderr, "%d: Invalid value %d\n", ftell(f), nbr_arcs);
			exit(-1);
		}
		for(int j=0; j<nbr_arcs; j++) {
			int v;
			TElement w;
			ret = fscanf(f, "%d:%d", &v, &w); // A changer si on change TElement
			if(ret != 2 || v < 0 || v > nbr_sommets) {
				fprintf(stderr, "%d: Invalid value %d:%d\n", ftell(f),  v, w); // A changer si on change TElement
				exit(-1);
			}
			g.list[i] = push(g.list[i], v, w); // ajouter l'arc a la liste des arcs
			g.pred[v] = push(g.pred[v], i, -1); // et a la liste des preds, le poids est ignore
			
			tab_temp[i] ++;
			tab_temp[v] ++;
			som_w += w;
		}
		g.nbr_arcs += nbr_arcs;
	}
	int i=0;
	while(i < nbr_sommets && (tab_temp[i] == 2  || tab_temp[i] == 0)) i++;
	if(i != nbr_sommets) // si au moins 1 elm de tab_temp n'est pas 2
		g.type |= GB_DIRECTED;
	if(som_w != 0) // si toute les poids sont 0
		g.type |= GB_WEIGHTED;
	free(tab_temp);
	
    return g;
}

GRAPH_VxV lire_graphe_vxv(char* nom_fich) {
    GRAPH_VxV g;
	GRAPH_LIST g_list = lire_graphe_liste(nom_fich);
	g.type = g_list.type;
	g.arc = creer_matrice(g_list.nbr_sommets, g_list.nbr_sommets, sizeof(TElement));
	g.weight = creer_matrice(g_list.nbr_sommets, g_list.nbr_sommets, sizeof(TElement));
	
	for(int i=0; i<g_list.nbr_sommets; i++) {
		NODE* temp = g_list.list[i];
		while(temp) {
			g.arc.mat[i][temp->v] = 1;
			g.weight.mat[i][temp->v] = temp->w;

			temp = temp->suiv;
		}
	}

    return g;
}

GRAPH_VxA lire_graphe_vxa(char* nom_fich) {
    GRAPH_VxA g;
	GRAPH_LIST g_list = lire_graphe_liste(nom_fich);
	g.type = g_list.type;
	g.arc = creer_matrice(g_list.nbr_sommets, g_list.nbr_arcs, sizeof(TElement));
	g.weight = malloc(sizeof(TElement) * g_list.nbr_arcs);
	
	int comp_arc = 0;
	for(int i=0; i<g_list.nbr_sommets; i++) {
		NODE* temp = g_list.list[i];
		while(temp) {
			g.arc.mat[comp_arc][i] = 1;
			g.arc.mat[comp_arc][temp->v] = -1;
			g.weight[comp_arc] = temp->w;

			temp = temp->suiv;
			comp_arc ++;
		}
	}
	
    return g;
}

void ecrire_graphe_liste(const char* nom_fich, GRAPH_LIST g) {
    FILE* f;
    if((f = fopen(nom_fich, "w")) == NULL) {
		perror("Cant open file\n");
		exit(-1);
	}
	fprintf(f, "%d\n", g.nbr_sommets);
	for(int i=0; i<g.nbr_sommets; i++) {
		NODE* list = g.list[i];
		fprintf(f, "%d;", list_len(list));
		while(list) {
			fprintf(f, "%d:%d ", list->v, list->w);
			list = list->suiv;
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void ecrire_graphe_vxv(const char* nom_fich, GRAPH_VxV g) {
    FILE* f;
    if((f = fopen(nom_fich, "w")) == NULL) {
		perror("Cant open file\n");
		exit(-1);
	}
	fprintf(f, "%d\n", g.arc.width);
	for(int i=0; i<g.arc.width; i++) {
		int nbr_arcs = 0;
		for(int tmp=0; tmp<g.arc.height; tmp++)
			nbr_arcs+=g.arc.mat[i][tmp];

		fprintf(f, "%d;", nbr_arcs);
		for(int j=0; j<g.arc.height; j++) {
			if(g.arc.mat[i][j]) {
				fprintf(f, "%d:%d ", j, g.weight.mat[i][j]);
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void ecrire_graphe_vxa(const char* nom_fich, GRAPH_VxA g) {
    FILE* f;
    if((f = fopen(nom_fich, "w")) == NULL) {
		perror("Cant open file\n");
		exit(-1);
	}
	
	fprintf(f, "%d\n", g.arc.width);
	for(int i=0; i<g.arc.width; i++) {
		int nbr_arcs = 0;
		for(int tmp=0; tmp<g.arc.height; tmp++)
			nbr_arcs += g.arc.mat[tmp][i] == 1;

		fprintf(f, "%d;", nbr_arcs);
		for(int j=0; j<g.arc.height; j++) {
			if(g.arc.mat[j][i] == 1) {
				fprintf(f, "%d:%d ", j, g.weight[j]);
			}
		}
		fprintf(f, "\n");
	}
}

MAT floyd_warshall_rec_util(GRAPH_VxV g, MAT m, int k) {
	if(k == 0) {
		for(int i=0; i<g.arc.height; i++) {
			for(int j=0; j<g.arc.width; j++) {
				m.mat[i][j] = (i == j)? 1: g.arc.mat[i][j];
			}
		}
	} else {
		floyd_warshall_rec_util(g, m, k-1);
		for(int i=0; i<g.arc.height; i++) {
			for(int j=0; j<g.arc.width; j++) {
				m.mat[i][j] = (m.mat[i][j] || (m.mat[i][k] && m.mat[k][j]));
			}
		}
	}
	return m;
}


MAT floyd_warshall_rec(GRAPH_VxV g) {
	MAT m = creer_matrice(g.arc.width, g.arc.height, sizeof(TElement));
	return floyd_warshall_rec_util(g, m, g.arc.width-1);
}


int* tri_top_list(GRAPH_LIST g) {
	int n = g.nbr_sommets;
	
	// init
	int* res = malloc(sizeof(int) * n);
	NODE* M = NULL;
	int* T = malloc(sizeof(int) * n);
	for(int i=0; i<n; i++) {
		T[i] = list_len(g.pred[i]);
		if(T[i] == 0) {
			M = push(M, i, 0);
		}
	}
	
	int nbr_tris = 1;
	int i = 0;
	while(i < n && M) {
		nbr_tris *= list_len(M);
		
		int tmp = M->v;
		M = pop(M);
		res[i] = tmp;
		T[tmp] = -1;
		
		for(NODE* u=g.list[tmp]; u; u=u->suiv) {
			T[u->v] --;
			if(T[u->v] == 0)
				M = push(M, u->v, 0);
		}
		
		i++;
	}
	printf("%d\n", i);
	if(i < n) {
		printf("Aucune Tri possible\n");
		free(res);
		res = NULL;
	}
	printf("nbr tris = %d\n", nbr_tris);
	return res;
}


//~ int* colorer(GRAPH_LIST g) {
	//~ int niveaux = malloc(sizeof(int) * g.nbr_sommets);
//~ }

//~ int est_biparti(GRAPH_LIST g) {
	
//~ }
