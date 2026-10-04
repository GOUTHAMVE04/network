%{
#include <stdio.h>
%}

%%

abc     { printf("ABC"); }
"$"     { return 1; }
.       { printf("%s", yytext); }
\n      { printf("\n"); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter String: ");
    yylex();
    return 0;
}
