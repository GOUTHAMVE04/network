%{
int c=0;
%}
%%
[a-zA-Z0-9]+ {printf("word %s Length of word %d \n",yytext,yyleng);}
["$"]|["\n"] {return 0;}
.;
%%
#include<stdio.h>
int main()

{
	printf("Enter String ");
	yylex();
	
}


