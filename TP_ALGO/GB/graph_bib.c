#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "graph_bib.h"
#include <time.h>
// Les fonctions d'utilités
// pour la matrice
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
void free_matrice(MAT m ) {
	for(int i=0; i<m.height; i++) {
		free(m.mat[i]);
	}
	free(m.mat);
}

// pour la liste chainee
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
void free_list(NODE* l) {
	while((l = pop(l)));
}

// pour le tas
HEAP creer_heap(int capacity) {
	HEAP h;
	h.size = 0;
	h.capacity = capacity;
	h.pos = malloc(sizeof(int) * capacity);
	h.tab = malloc(sizeof(struct heap_elem) * capacity);
	
	return h;
}

HEAP insert_heap(HEAP h, struct heap_elem elm) {
	if(h.size+1 > h.capacity) {
		perror("heap capacity reached\n");
		return h;
	}
	
	h.tab[h.size] = elm;
	h.size ++;
	h.pos[elm.v] = h.size-1;

	int i = h.size;
	int p = i / 2 ; // le parent
	while(h.tab[p-1].w > h.tab[i-1].w && i > 1) {
		SWAP(h.pos[h.tab[p-1].v], h.pos[h.tab[i-1].v])

		SWAP(h.tab[p-1].v, h.tab[i-1].v) // swap h[i] and h[p]
		SWAP(h.tab[p-1].w, h.tab[i-1].w) // swap h[i] and h[p]		

		i = p;
		p = i / 2;
	}
	
	return h;
}

HEAP min_heapify(HEAP h, int idx) {
	// gradually get it back to top
	int i = idx;
	int p = i / 2 ; // le parent
	while(h.tab[p-1].w > h.tab[i-1].w && i > 1) {
		SWAP(h.pos[h.tab[p-1].v], h.pos[h.tab[i-1].v])

		SWAP(h.tab[p-1].v, h.tab[i-1].v) // swap h[i] and h[p]
		SWAP(h.tab[p-1].w, h.tab[i-1].w) // swap h[i] and h[p]		

		i = p;
		p = i / 2;
	}

} 

HEAP delete_heap(HEAP h) {
	if(h.size <= 1) {
		h.size = 0;
		return h;
	}
	h.pos[h.tab[0].v] = -1;
	h.tab[0] = h.tab[h.size-1];

	int v = h.tab[0].v;
	h.pos[v] = 0;
	
	h.size --;
	int i = 1;
	int fg = i * 2;// fils gauche
	while((h.tab[i-1].w > h.tab[fg-1].w || h.tab[i-1].w > h.tab[fg].w)
			&& fg < h.size) {
				
		if(h.tab[i-1].w > h.tab[fg-1].w) {
			SWAP(h.pos[h.tab[i-1].v], h.pos[h.tab[fg-1].v])
			
			SWAP(h.tab[i-1].v, h.tab[fg-1].v)
			SWAP(h.tab[i-1].w, h.tab[fg-1].w)			
		} else {
			SWAP(h.pos[h.tab[i-1].v], h.pos[h.tab[fg].v])

			SWAP(h.tab[i-1].v, h.tab[fg].v)
			SWAP(h.tab[i-1].w, h.tab[fg].w)
		}
		i = fg;
		fg = i * 2;
	}
	
	return h;
}

void free_heap(HEAP h) {
	free(h.tab);
}

// les fonctions
GRAPH_LIST creer_graphe_liste(int taille) {
	if(taille < 0) {
		perror("taille");
		exit(EXIT_FAILURE);
	}
	
    GRAPH_LIST g;

	// Initialiser la structure de graphe
	g.nbr_sommets = taille;
	g.nbr_arcs = 0;
	// graphe
	g.list = malloc(sizeof(NODE*) * taille);
	bzero(g.list, sizeof(NODE*) * taille); // initialiser a NULL
	// predecesseurs
	g.pred = malloc(sizeof(NODE*) * taille);
	bzero(g.pred, sizeof(NODE*) * taille); // initialiser a NULL
	
	return g;
}

GRAPH_LIST ajout_arc_graphe_liste(GRAPH_LIST g, int src, int dest, TElement w) {
	g.list[src] = push(g.list[src], dest, w);
	return g;
}

GRAPH_LIST generate_graphe_liste(int taille) {
	srand(time(NULL));
	GRAPH_LIST g = creer_graphe_liste(taille);
	
	for(int i=0; i<g.nbr_sommets; i++) {
		for(int j=0; j<g.nbr_sommets; j++) {
			if(rand()%100 < 40) {
				ajout_arc_graphe_liste(g, i, j, rand()%20);
			}
		}
	}
	return g;
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

	g = creer_graphe_liste(nbr_sommets);
	
	// Le calcul de type de graphe
	g.type = 0;
	int* tab_temp = malloc(sizeof(int) * nbr_sommets); // temporaire pour determiner le type
	bzero(tab_temp, sizeof(int) * nbr_sommets);
	TElement som_w = 0;

	for(int i=0; i<nbr_sommets; i++) {
		int nbr_arcs;
		ret = fscanf(f, "%d;", &nbr_arcs);
		if(ret != 1 || nbr_arcs < 0 || nbr_arcs > nbr_sommets) {
			fprintf(stderr, "%d:%d: Invalid value %d\n", i, ftell(f), nbr_arcs);
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

void free_graphe_liste(GRAPH_LIST g) {
	for(int i=0; i<g.nbr_sommets; i++) {
		free_list(g.list[i]);
		free_list(g.pred[i]);
	}
	free(g.list);
	free(g.pred);
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
	free_graphe_liste(g_list);
    return g;
}

void free_graphe_vxv(GRAPH_VxV g) {
	free_matrice(g.arc);
	free_matrice(g.weight);
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
	free_graphe_liste(g_list);
    return g;
}

void free_graphe_vxa(GRAPH_VxA g) {
	free_matrice(g.arc);
	free(g.weight);
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

void dijkstra(int *path, TElement *dist, GRAPH_LIST g, int src, int (*cmp)(void*, void*)) {
	int n = g.nbr_sommets;
	HEAP h = creer_heap(n);
	
	// init
	for(int i=0; i<n; i++) {
		dist[i] = INF;
		path[i] = -1;
			
		struct heap_elem e = {dist[i], i};
		h = insert_heap(h, e);
	}
	dist[src] = 0;
	path[src] = -1;
	
	while(h.size > 0) {
		// get min elem
		struct heap_elem e = h.tab[0];
		h = delete_heap(h);
		int v = e.v;
		// update all adjacents of v
		for(NODE* c=g.list[v]; c != NULL; c = c->suiv) {
			TElement w = c->w;
			int u = c->v;
			
			//~ w + dist[v] < dist[u] 
			int a = w + dist[v];
			int b = dist[u];
			if(cmp(&a, &b) < 0 && (h.pos[u] > 0 || h.pos[u] < h.size) || dist[u] == INF) {
				dist[u] = dist[v] + w;
				path[u] = v;
				
				// decrease in min heap
				int toDecrease = h.pos[u];
				h.tab[toDecrease].w = dist[u];
				min_heapify(h, toDecrease);
			}
		}
	}
}

void find_max_min_path(int* path, GRAPH_VxV g, int s, int t) {
	
}

int find_max_flow(GRAPH_VxV g, int s, int t) {
	// init
	int n = g.arc.height;
	int max_flow = 0;
	
	MAT flows = creer_matrice(n, n, sizeof(TElement));

	int* path = malloc(sizeof(int) * n);
	bzero(path, sizeof(int) * n);
	
	// itérations
	find_max_min_path(path, g, s, t);
	while(path[t] != -1) {
		int cur = t;
		int path_flow = INF;
		while(path[cur] != -1) {
			if(path_flow > g.weight.mat[cur][path[cur]])
				path_flow = g.weight.mat[cur][path[cur]];
		}
		
		max_flow += path_flow;
		cur = t;
		while(path[cur] != -1) {
			if(g.arc.mat[path[cur]][cur] == 1) {
				flows.mat[path[cur]][cur] += path_flow;
			} else {
				flows.mat[path[cur]][cur] -= path_flow;
			}
		}
 		find_max_min_path(path, g, s, t);
	}
	
	free_matrice(flows);
	free(path);
	return max_flow;
}

int* niveaux(GRAPH_LIST g) {
	int n = g.nbr_sommets;
	
	int *niveaux = malloc(sizeof(int) * n);
	bzero(niveaux, sizeof(int) * n);
	
	// init
	int* S = malloc(sizeof(int) * n);
	NODE* file = NULL;
	for(int i=0; i<n; i++) {
		S[i] = list_len(g.pred[i]);
		if(S[i] == 0) {
			file = push(file, i, 0);
		}
	}
	int i;
	for(i=0; i<n && file; i++) {
		// mark all current elements in file in level i
		NODE* temp = NULL;
		while(file) {
			int v = file->v;
			S[v] = -1;
			niveaux[v] = i;
			
			temp = push(temp, v, 0);
			file = pop(file);
		}
		
		// update S and file
		while(temp) {
			int v = temp->v;
			for(NODE* next=g.list[v]; next; next=next->suiv) {
				int w = next->v;
				S[w]--;
				if(S[w] == 0) {
					file = push(file, w, 0);
				}
				printf("w = %d\n", w);
			}
			temp = pop(temp);
		}
	}
	if(i < n) {
		free(niveaux);
		niveaux = NULL;
	}
	free(S);
	return niveaux;
}

int est_biparti(GRAPH_LIST g) {
	
}
