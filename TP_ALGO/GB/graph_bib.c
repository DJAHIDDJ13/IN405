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

char* read_line(int fd) {
	char *buff = malloc(sizeof(char) * MAX);
	char c;
	read(fd, &c, 1);
	int n = 0;

	while(c == '\n' || c == '#' || c == EOF) {
		if(c == EOF) {
			perror("INVALID file\n");
			free(buff);
			return NULL;
		}
		if(c == '#') {
			while(c != '\n' && c != EOF) {
				read(fd, &c, 1);
			}
		}
		read(fd, &c, 1);
	}
	
	while(c != EOF && c != '\n' && n < MAX) {
		buff[n++] = c;
		read(fd, &c, 1);
	}
	buff[n] = 0;
	return buff;
}

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
		perror("Invalid file format\n");
		exit(-1);
	}
	
	// Initialiser la structure de graphe
	g.nbr_sommets = nbr_sommets;
	g.list = malloc(sizeof(NODE*) * nbr_sommets);
	bzero(g.list, sizeof(NODE*) * nbr_sommets); // initialiser a NULL
	
	for(int i=0; i<nbr_sommets; i++) {
		int nbr_arcs;
		ret = fscanf(f, "%d;", &nbr_arcs);
		if(ret != 1 || nbr_arcs < 0 || nbr_arcs > nbr_sommets) {
			perror("Invalid file format\n");
			exit(-1);
		}
		
		for(int j=0; j<nbr_arcs; j++) {
			int v;
			TElement w;
			ret = fscanf(f, "%d:%d", &v, &w); // A changer si on change TElement
			if(ret != 2 || v < 0 || v > nbr_sommets) {
				perror("Invalid file format\n");
				exit(-1);
			}
			
			g.list[i] = push(g.list[i], v, w); // ajouter l'arc a la liste des arcs
		}
	}
    return g;
}

GRAPH_VxV lire_graphe_vxv(char* nom_fich) {
    GRAPH_VxV g;
	GRAPH_LIST g_list = lire_graphe_liste(nom_fich);
	g.arc = creer_matrice(g_list.nbr_sommets, g_list.nbr_sommets, sizeof(TElement));
	g.weight = creer_matrice(g_list.nbr_sommets, g_list.nbr_sommets, sizeof(TElement));
	for(int i=0; i<g_list.nbr_sommets; i++) {
		NODE* temp = g_list.list[i];
		while(temp) {
			g.arc[i][temp->v] = 1;
			g.weight[i][temp->v] = temp->w;
			temp = temp->suiv;
		}
	}
    return g;
}

GRAPH_VxA lire_graphe_vxa(char* nom_fich) {
    GRAPH_VxA g;
	GRAPH_LIST g_list = lire_graphe_liste(nom_fich);
	
    return g;
}

