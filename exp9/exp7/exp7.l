%{
#include "y.tab.h"
#include <string.h>
%}

%%

[0-9]+      {
                yylval.str = strdup(yytext);
                return NUM;
            }

[a-zA-Z]    {
                yylval.str = strdup(yytext);
                return ID;
            }

[+\-*/=()]  { return yytext[0]; }

[ \t]       ;

\n          { return 0; }

.           { return yytext[0]; }

%%
