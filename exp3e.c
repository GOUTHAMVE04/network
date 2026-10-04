%{
int v,c=0;
%}
%%
([a][e][i][o][u][A][E][I][O][U])+ {v++;}
(a-zA-z) {c++;}
["$"] {return 0;}
. ;
%%
#include<stdio.h>
int main()
{
	printf("Enter the String");
	yylex();
	printf("The number of \nvowels are%d \n cosanants%d",v,c);
}

