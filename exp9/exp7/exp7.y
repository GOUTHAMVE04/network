%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
int yyerror(char *);

int temp = 1;

char* newtemp()
{
    char *t = malloc(10);
    sprintf(t, "t%d", temp++);
    return t;
}
%}

%union {
    char *str;
}

%token <str> NUM ID
%type <str> E

%left '+' '-'
%left '*' '/'

%%

S : E
    {
        printf("Result = %s\n", $1);
    }
  ;

E : E '+' E
    {
        char *t = newtemp();
        printf("%s = %s + %s\n", t, $1, $3);
        $$ = t;
    }

  | E '-' E
    {
        char *t = newtemp();
        printf("%s = %s - %s\n", t, $1, $3);
        $$ = t;
    }

  | E '*' E
    {
        char *t = newtemp();
        printf("%s = %s * %s\n", t, $1, $3);
        $$ = t;
    }

  | E '/' E
    {
        char *t = newtemp();
        printf("%s = %s / %s\n", t, $1, $3);
        $$ = t;
    }

  | '(' E ')'
    {
        $$ = $2;
    }

  | NUM
    {
        $$ = $1;
    }

  | ID
    {
        $$ = $1;
    }
  ;

%%

int yyerror(char *s)
{
    printf("Invalid expression\n");
    return 0;
}

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}
