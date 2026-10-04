%{
#include <stdio.h>
#include <stdlib.h>
int v=1;
%}
%token digit letter
%%
start: letter s
s:letter s|digit s| ;
%%

int yyerror(char *str)
{
v=0;
printf("Its not a valid variable name.\n");
return 0;
}
int main(){
printf("Enter a name for an identifier: ");
yyparse();
if(v){
printf("It is a valid variable name.\n");
}
}
