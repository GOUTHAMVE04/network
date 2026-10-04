%{
#include "y.tab.h"
%}

%option noyywrap

%%
[a-zA-Z][a-zA-Z0-9]* return id;
[0-9]+(\.[0-9]*)?    return num;
[+/*]                return op;
[ \t]+               ; 
.                    return yytext[0];
\n                   return 0;
%%
