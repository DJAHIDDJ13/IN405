#include <stdio.h>
#include <stdlib.h>

typedef struct node { 
	int val;
	struct node* parent;
	struct node* g;
	struct node* d;
} AVL;


AVL* insertInto(AVL* a, AVL* p, int elem) {
	a = malloc(sizeof(AVL));
	a->val = elem;
	a->parent = p;
	a->d = NULL;
	a->g = NULL;
	return a;
}

AVL* insereElemUtil(AVL* a, int elem, AVL** added) {
	if(a == NULL) {
		a = insertInto(a, NULL, elem);
		*added = a;
		return a;
	}
	if(elem > a->val) {
		if(a->d == NULL) {
			a->d = insertInto(a->d, a, elem);
			*added = a->d;
		} else {
			insereElemUtil(a->d, elem, added);
		}
	} else if(elem <= a->val) {
		if(a->g == NULL) {
			a->g = insertInto(a->g, a, elem);
			*added = a->g;
		} else {
			insereElemUtil(a->g, elem, added);
		}
	}
	return a;
}

int calc_max_len(AVL* a) {
	if(a == NULL)
		return 0;
	if(a->g == NULL && a->d == NULL) {
		return 0;
	}
	int G = calc_max_len(a->g);
	int D = calc_max_len(a->d);
	
	return (G > D)? 1+G: 1+D;
}

int calc_weight(AVL* a) {
	return calc_max_len(a->d) - calc_max_len(a->g);
}

AVL* balanceAVL(AVL* a, AVL* added) {
	for(AVL* P = added->parent; P != NULL; P = P->parent) {
		if(calc_weight(P) > 1) {
			P = rotate_left(P);
		} else if(calc_weight(P) < -1){
			P = rotate_right(P);
		}
	}
	return a;	
}

AVL* insereElem(AVL* a, int elem) {
	AVL* added;
	AVL* res = insereElemUtil(a, elem, &added);
	res = balanceAVL(res, added);
	return res;
}


AVL* construireAVL(int* tab, int n) {
	AVL* res = NULL;
	for(int i=0; i<n; i++) {
		res = insereElem(res, tab[i]);
	}
	return res;
}

void print2DUtil(AVL *root, int space) 
{ 
    if (root == NULL) 
        return; 
     space += 5; 
  
    print2DUtil(root->d, space); 
  
    printf("\n"); 
    for (int i = 5; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->val); 
  
    print2DUtil(root->g, space); 
} 

int main(int argc, char** argv) {
	AVL* a = NULL;
	AVL* tmp;
	a = insereElemUtil(a, 5, &tmp);
	a = insereElemUtil(a, 6, &tmp);
	a = insereElemUtil(a, 4, &tmp);
	a = insereElemUtil(a, 7, &tmp);
	a = insereElemUtil(a, 8, &tmp);
	
	print2DUtil(a, 0);
	printf("%d\n", calc_weight(a));
}
