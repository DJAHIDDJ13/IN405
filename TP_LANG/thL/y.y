%{
#include <stdio.h>
#include <math.h>
%}

%union {
	double dval;
	int    ival;
}
%token <dval> FLOTTANT
%token PAR_OUVR PAR_FERM 
%type <dval> expr nombre ligne
%left PLUS MOINS
%left MULT DIV
%right SIN COS TAN ATAN SQRT

%%

ligne:
	expr {printf("expression = %.10g\n", $1);}
	;

expr:
	  nombre {$$=$1;}
	| PAR_OUVR expr PAR_FERM {$$=$2;}
	| expr PLUS expr {$$=$1+$3;}
	| expr MOINS expr {$$=$1-$3;}
	| expr MULT expr {$$=$1*$3;}
	| expr DIV expr {$$=$1/$3;}
	| COS PAR_OUVR expr PAR_FERM {$$=cos($3);}
	| SIN PAR_OUVR expr PAR_FERM {$$=sin($3);}
	| SQRT PAR_OUVR expr PAR_FERM {$$=sqrt($3);} 
	| MOINS expr {$$=-$2;}
	;
nombre:
	  FLOTTANT {$$=$1;} 
	;

%%

main(){
	yyparse();
	printf("result = %d\n", result);
}
yyerror(const char* arg){
	printf("%s\n", arg);
}
