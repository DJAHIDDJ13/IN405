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

//~ int list_len(NODE* n) {
	//~ int count = 0;
	//~ while(n != NULL) {
		//~ count++;
		//~ n = n->suiv;
	//~ }
//~ }

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
// Les fonctions de control des graphes
//~ GRAPH_VxV creer_graphe_vxv(int nbr_v, size_t element_size, int type) {
    //~ GRAPH_VxV res;
    //~ res.type = type;
    //~ res.arc = creer_matrice(nbr_v, nbr_v, element_size);
    //~ if(type & GB_WEIGHTED) {
        //~ res.weight  = creer_matrice(nbr_v, nbr_v, element_size);
    //~ }
    //~ return res;
//~ }

//~ GRAPH_VxV ajout_arc_vxv(GRAPH_VxV g, int x, int y, TElement w) {
    //~ if(x >= 0 && y >= 0 && x < g.arc.width && y < g.arc.height) {
        //~ g.arc.mat[x][y] = 1;
        //~ if(!(g.type & GB_DIRECTED)) {
            //~ g.arc.mat[y][x] = 1;
        //~ }
        //~ if(g.type & GB_WEIGHTED) {
            //~ g.weight.mat[x][y] = w;
        //~ }
    //~ }
    //~ return g;
//~ }
//~ GRAPH_VxV supp_arc_vxv(GRAPH_VxV g, int x, int y) {
    //~ if(x >= 0 && y >= 0 && x < g.arc.width && y < g.arc.height) {
        //~ g.arc.mat[x][y] = 0;
        //~ if(!(g.type & GB_DIRECTED)) {
            //~ g.arc.mat[y][x] = 0;
        //~ }
        //~ if(g.type & GB_WEIGHTED) {
            //~ g.weight.mat[x][y] = 0;
        //~ }
    //~ }
    //~ return g;
//~ }

//~ char* read_line(int fd) {
	//~ char *buff = malloc(sizeof(char) * MAX);
	//~ char c;
	//~ read(fd, &c, 1);
	//~ int n = 0;

	//~ while(c == '\n' || c == '#' || c == EOF) {
		//~ if(c == EOF) {
			//~ perror("INVALID file\n");
			//~ free(buff);
			//~ return NULL;
		//~ }
		//~ if(c == '#') {
			//~ while(c != '\n' && c != EOF) {
				//~ read(fd, &c, 1);
			//~ }
		//~ }
		//~ read(fd, &c, 1);
	//~ }
	
	//~ while(c != EOF && c != '\n' && n < MAX) {
		//~ buff[n++] = c;
		//~ read(fd, &c, 1);
	//~ }
	//~ buff[n] = 0;
	//~ return buff;
//~ }

//~ GRAPH_LIST lire_graphe_liste(char* nom_fich) {
    //~ GRAPH_LIST g;
    //~ int f;
    //~ if((f = open(nom_fich, O_RDONLY)) < 0) {
        //~ fprintf(stderr, "%s: file doesn't exist\n", nom_fich);
        //~ exit(-1);
    //~ }
	//~ printf("%d\n", f);
	//~ char* buff = read_line(f);
	//~ if(buff == NULL) {
		//~ perror("EOF\n");
		//~ exit(-1);
	//~ }
	
	//~ int n;
	//~ if(sscanf(buff, "%d", &n) != 1 || n < 1){
		//~ perror("bad file format\n");
		//~ exit(-1);
	//~ }
	//~ g.vertices_num = n;
	//~ g.graph = malloc(sizeof(NODE*) * n);
	//~ free(buff);
	//~ for(int i=0; i<n; i++) {
		//~ buff = read_line(f);
		//~ char* pch = strtok(buff, ",");
		//~ g.graph[i] = NULL;
		//~ while(pch != NULL) {
			//~ int v;
			//~ TElement w;
			//~ if(sscanf(pch, "%d:%d", &v, &w) != 2) { // a change si on change TElement 
				//~ perror("bad file format\n");
				//~ exit(-1);
			//~ }
			//~ g.graph[i] = push(g.graph[i], v, w);
			//~ pch = strtok(NULL, ",");
		//~ }
		//~ free(buff);
	//~ }
	//~ close(f);
    //~ return g;
//~ }

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
/*
 	int nbr_sommets;
	int ret = fscanf(f, "%d\n", &nbr_sommets);
	if(ret != 1 || nbr_sommets < 1) {
		fprintf(stderr, "%d: Invalid value %d\n", ftell(f), nbr_sommets);
		exit(-1);
	}
	
	// Initialiser la structure de graphe
	g.nbr_sommets = nbr_sommets;
	g.list = malloc(sizeof(NODE*) * nbr_sommets);
	bzero(g.list, sizeof(NODE*) * nbr_sommets); // initialiser a NULL
	
	for(int i=0; i<nbr_sommets; i++) {
		int arc_index;
		ret = fscanf(f, "%d;", &arc_index);
		if(ret != 1 || arc_index < 0 || arc_index >= nbr_sommets) {
			fprintf(stderr, "%d: Invalid value %d\n", ftell(f), arc_index);
			exit(-1);
		}
		do {
			int v;
			TElement w;
			ret = fscanf(f, "%d:%d", &v, &w);
			if(ret != 2 || v < 0 || v >= nbr_sommets) {
				fprintf(stderr, "%d: Invalid value %d:%d\n", ftell(f),  v, w);
				exit(-1);
			}
			g.list[arc_index] = push(g.list[arc_index], v, w);
		} while(ret == 2);
 * */
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
			g.arc.mat[i][comp_arc] = 1;
			g.arc.mat[temp->v][comp_arc] = -1;
			g.weight[comp_arc] = temp->w;

			temp = temp->suiv;
			comp_arc ++;
		}
	}
	
    return g;
}





