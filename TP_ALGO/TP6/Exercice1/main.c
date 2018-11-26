#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {OPERATEUR, OPERAND} TCaractere;
typedef struct {
	TCaractere tcar;
	union {
		char opr;
		double opd;
	} ncar;
} TElmArbr;

typedef struct node {
	TElmArbr data;
	struct node* g;
	struct node* d;
} Arbre;

typedef struct nd {
	Arbre* val;
	struct nd* suiv;
} PILE;

PILE* creer_pile() {
	return NULL;
}

PILE* push(PILE* p, Arbre* a) {
	PILE* m = malloc(sizeof(PILE));
	m->val = a;
	m->suiv = p;
	
	return m;
}

PILE* pop(PILE* p) {
	if(!p)
		return NULL;
	PILE* s = p->suiv;
	free(p);
	return s;
}

Arbre* top(PILE* p) {
	return p->val;
}

Arbre* transform_string(const char* string){
	int cmpt = 0;
	PILE *operateurs = creer_pile(), *arbres = creer_pile();
	while(cmpt<strlen(string)) {
		if(isdigit(string[cmpt])){
			double res = atof(string+cmpt);
			while(isdigit(string[cmpt])) {
				cmpt++;
			}
			if(string[cmpt] == '.') {
				cmpt++;
				while(isdigit(string[cmpt])) {
					cmpt++;
				}
			}
			
			Arbre* opd = malloc(sizeof(Arbre));
			opd->g = NULL;
			opd->d = NULL;
			opd->data.tcar = OPERAND;
			opd->data.ncar.opd = res;
			
			arbres = push(arbres, opd);
		} else if(string[cmpt] == '+' || string[cmpt] == '-' || string[cmpt] == '*' || string[cmpt] == '/') {
			Arbre* opr = malloc(sizeof(Arbre));
			opr->g = NULL;
			opr->d = NULL;
			opr->data.tcar = OPERATEUR;
			opr->data.ncar.opr = string[cmpt];
			
			operateurs = push(operateurs, opr);
			cmpt++;
		} else if(string[cmpt] == ')') {
			Arbre* a1 = top(arbres);
			arbres = pop(arbres);
			Arbre* a2 = top(arbres);
			arbres = pop(arbres);
			
			Arbre* a12 = top(operateurs);
			operateurs = pop(operateurs);
			a12->g = a1;
			a12->d = a2;
			
			arbres = push(arbres, a12);
			cmpt++;
		} else if(isspace(string[cmpt]) || string[cmpt] == '(') {
			cmpt++;
		} else {
				fprintf(stderr, "%c: invalid character\n", string[cmpt]);
				exit(0);
		}
	}
	if(operateurs) {
		fprintf(stderr, "invalid expression\n");
		exit(0);		
	}
	if(arbres){
		if(arbres->suiv){
			fprintf(stderr, "invalid expression\n");
			exit(0);			
		}
	}
	return arbres->val;
}

double evaluate(double a, double b, char opr) {
		switch(opr) {
			case '+': return a+b;
			case '*': return a*b;
			case '-': return a-b;
			case '/': return a/b;
		}
		return 0;
}

double evaluate_expression(Arbre* a) {
	if(a->data.tcar == OPERAND) {
		return a->data.ncar.opd;
	} else {
		char opr = a->data.ncar.opr;
		double y = evaluate_expression(a->g);
		double x = evaluate_expression(a->d);
		return evaluate(x, y, opr);
	}
	return -1;
}

int main(int argc, char** argv) {
	if(argc < 2)
		return 0;
	char* chaine = malloc(sizeof(char)* 200);
	for(int i=1; i<argc; i++){
		strcat(chaine, argv[i]);
	}
	Arbre* arbre_expression = transform_string(chaine);
	double result = evaluate_expression(arbre_expression);
	printf("%s = %g\n", chaine, result);
	return 0;
}
