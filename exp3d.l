%{
int l,b,w,ch=0;
%}
%%
["\n"] {l++;}
[" "]+ {b++;}
[a-zA-Z0-9]+ {w++;ch+=yyleng;}
["$"] {return 0;}

. ;
%%
#include<stdio.h>
void main()
{
	printf("Enter the sequence");
	yylex();
	printf("\n no of \nlines: %d \n word: %d \n blank: %d \ncharacters:%d ",l,w,b,ch);
}
