#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Afficher_Tab(int *tab, int N){
	printf("[");
	for(int i=0; i<N; i++){
		printf("%d%s",tab[i], i==N-1?"":",");
	}
	printf("]\n");
}

int *Swap(int *tab, int a, int b){
	int c = tab[a];
	tab[a] = tab[b];
	tab[b] = c;
	return tab;
}

int *Tri_Insertion(int *tab, int N){
	for(int i=1; i<N; i++){
		int j = i;
		while(j>0 && tab[j-1] > tab[j]){
			tab = Swap(tab, j , j-1);
			j--;
		}
	}
	return tab;
}
int *Fusion(int *tab, int a, int m, int b){
	int i = a;
	int j = m;
	int *temp = malloc(sizeof(int) * (b-a));
	while(i <= m || j <= b){
		if(tab[i] < tab[j]){
			temp[i-a+j-m] = tab[i];
			i++;
		} else {
			temp[i-a+j-m] = tab[j];
			j++;
		}
	}
	for(int k=a; k<b; k++)
		tab[k] = temp[k-a];
		
	free(temp);
	return tab;
}
int *Tri_Fusion(int *tab, int a, int b){
	if(b-a > 2){
		int m = (a+b)/2;
		tab = Tri_Fusion(tab, a, m);
		tab = Tri_Fusion(tab, m, b);
		tab = Fusion(tab, a, m, b);
	}
	return tab;
}


int *Init_Tab_Alea(int *tab, int N){
	for(int i=0; i<N; i++)
		tab[i] = rand() % 100 + 100;
	return tab;
}
int *Copy_Array(int *tab, int N){
	int *res = malloc(sizeof(int) * N);
	for(int i=0; i<N; i++){
		res[i] = tab[i];
	}
	return res;
}
int main(int argc, char **argv){
	srand((unsigned) time(NULL));

	// Initialisation de tableau aléatoirement
	int N = 10;
	int *tab = malloc(sizeof(int) * N);
	printf("Tableau originale: \n");
	tab = Init_Tab_Alea(tab, N);
	Afficher_Tab(tab, N);
	printf("\n");
	// Test de Tri insertion 
	int *test = Copy_Array(tab, N);
	test = Tri_Insertion(test, N);
	printf("Apres le tri par insertion: \n");
	Afficher_Tab(test, N);
	
	// Test de Tri Fusion
	test = Copy_Array(tab, N);
	printf("Apres le tri fusion: \n");
	test = Tri_Fusion(tab, 0, N);
	Afficher_Tab(tab, N);
	free(test);
	// Test de Tri Rapide
	
	free(tab);
	return 0;
}
