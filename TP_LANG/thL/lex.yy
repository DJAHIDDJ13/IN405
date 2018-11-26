%{
	#include "y.tab.h"
%}

%option noyywrap

%%

[\t ]+ ;

"(" {return PAR_OUVR;} 

")" {return PAR_FERM;}

"+" {return PLUS;}

"-" {return MOINS;}

"*" {return MULT;}

[0-9]+ {yylval=atof(yytext); return FLOATANT;}

"sin" {return SIN;}

"cos" {return COS;}

"sqrt" {return SQRT;}

[a-zA-Z]+ {printf("%s: mot inconnu\n", yytext);}

%%
