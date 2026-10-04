%{
#include <stdio.h>
#include <stdlib.h>

int v = 1;
int yylex(void);
int yyerror(const char *msg);
%}

%token num id op

%%
start : id '=' s
      ;

s     : id x
      | num x
      | '-' num x
      | '(' s ')' x
      ;

x     : op s
      | '-' s
      | /* empty */
      ;
%%

int yyerror(const char *msg) {
    v = 0;
    printf("Invalid arithmetic expression.\n");
    return 0;
}

int main(void) {
    printf("Enter the arithmetic expression:\n");
    yyparse();
    if (v) {
        printf("Valid expression.\n");
    }
    return 0;
}
