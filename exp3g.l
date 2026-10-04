%{
int c=1;
%}
%%
["\n"] {printf("%d.",++c);}
["$"] {return 0;}
.+ ;

%%
#include<stdio.h>
int main()
{
	printf("Enter the String\n");
	printf("1.");
	yylex();
	
}
