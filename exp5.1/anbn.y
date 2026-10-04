%{
#include<stdio.h>
#include<stdlib.h>
%}
%token A B NL
%%
stmt: S NL {printf("\n Valid String\n");exit(0);};
S:A S B|;

%%
int yyerror(char *msg){
printf("\nInvalid string  \n");
exit(0);
}
int main(){
printf("Enter the string: \n");
yyparse();
return 0;
}

