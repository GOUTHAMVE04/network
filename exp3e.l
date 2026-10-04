%{
int v=0,c=0;
%}
%%
[aeiouAEIOU] {v++;}
[a-zA-Z] {c++;}
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

