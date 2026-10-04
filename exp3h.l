%{
#include<stdio.h>
%}
%%
[A-Z ] {;}
. {printf("%s",yytext);}
%%


