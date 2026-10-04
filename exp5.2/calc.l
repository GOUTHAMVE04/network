%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern int yylval;
%}

%option noyywrap

%%
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
[ \t]+    ;
\n        return 0;
.         return yytext[0];
%%
