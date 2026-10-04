%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char addtotable(char, char, char);
int index1 = 0;
char temp = 'A' - 1;

struct expr {
    char operand1;
    char operand2;
    char operator;
    char result;
};

struct expr arr[20];
void yyerror(char *s);
int yylex(void);
void threeAdd(void);
void fouradd(void);
void triple(void);
%}

%union {
    char symbol;
}

%token <symbol> LETTER NUMBER
%type <symbol> exp

%left '+' '-'
%left '/' '*'

%%
statement: LETTER '=' exp ';' { addtotable((char)$1, (char)$3, '='); }
         | LETTER '=' exp     { addtotable((char)$1, (char)$3, '='); }
         ;

exp: exp '+' exp { $$ = addtotable((char)$1, (char)$3, '+'); }
   | exp '-' exp { $$ = addtotable((char)$1, (char)$3, '-'); }
   | exp '/' exp { $$ = addtotable((char)$1, (char)$3, '/'); }
   | exp '*' exp { $$ = addtotable((char)$1, (char)$3, '*'); }
   | '(' exp ')' { $$ = (char)$2; }
   | NUMBER      { $$ = (char)$1; }
   | LETTER      { $$ = (char)$1; }
   ;
%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
}

char addtotable(char a, char b, char o) {
    temp++;
    arr[index1].operand1 = a;
    arr[index1].operand2 = b;
    arr[index1].operator = o;
    arr[index1].result = temp;
    index1++;
    return temp;
}

void threeAdd() {
    int i = 0;
    printf("\n--- Three Address Code ---\n");
    while (i < index1) {
        printf("%c :=\t%c\t%c\t%c\n", arr[i].result, arr[i].operand1, arr[i].operator, arr[i].operand2);
        i++;
    }
}

void fouradd() {
    int i = 0;
    printf("\n--- Quadruples ---\n");
    while (i < index1) {
        printf("%c\t%c\t%c\t%c\n", arr[i].operator, arr[i].operand1, arr[i].operand2, arr[i].result);
        i++;
    }
}

int find(char l) {
    int i;
    for (i = 0; i < index1; i++) {
        if (arr[i].result == l) break;
    }
    return i;
}

void triple() {
    int i = 0;
    printf("\n--- Triples ---\n");
    while (i < index1) {
        printf("%c\t", arr[i].operator);
        if (!isupper(arr[i].operand1))
            printf("%c\t", arr[i].operand1);
        else
            printf("pointer(%d)\t", find(arr[i].operand1));

        if (!isupper(arr[i].operand2))
            printf("%c\n", arr[i].operand2);
        else
            printf("pointer(%d)\n", find(arr[i].operand2));
        i++;
    }
}

int main() {
    printf("Enter expression: ");
    yyparse();
    threeAdd();
    fouradd();
    triple();
    return 0;
}
