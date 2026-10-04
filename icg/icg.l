%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval.symbol = (char)(yytext[0]); return NUMBER; }
[a-z]       { yylval.symbol = (char)(yytext[0]); return LETTER; }
[ \t]       ;
.           { return yytext[0]; }
\n          { return 0; }
%%

int yywrap() {
    return 1;
}
