%{
#include <stdio.h>
#include <stdlib.h>

int f = 0;
int yylex(void);
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'

%%
ArithmeticExpression : E { printf("Result=%d\n", $1); return 0; }
                     ;

E : E '+' E { $$ = $1 + $3; }
  | E '-' E { $$ = $1 - $3; }
  | E '*' E { $$ = $1 * $3; }
  | E '/' E { $$ = $1 / $3; }
  | E '%' E { $$ = $1 % $3; }
  | '(' E ')' { $$ = $2; }
  | NUMBER { $$ = $1; }
  ;
%%

int yyerror(const char *s) {
    printf("Entered arithmetic expression is Invalid\n\n");
    f = 1;
    return 0;
}

int main(void) {
    printf("Enter Arithmetic Expression :\n");
    yyparse();
    if (f == 0) {
        printf("\n");
    }
    return 0;
}
