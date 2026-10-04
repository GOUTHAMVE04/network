#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_KEYWORDS 5
#define MAX_BUFFER 256
const char *keywords[MAX_KEYWORDS] = {"int", "void", "main", "return", "include"};
const char operators[] = "+-*/%=";
const char punctuation[] = ",;{}()[]";
int isKeyword(char *word) {
 for (int i = 0; i < MAX_KEYWORDS; i++) {
 if (strcmp(word, keywords[i]) == 0)
 return 1;
 }
 return 0;
}
int isOperator(char ch) {
 for (int i = 0; i < strlen(operators); i++) {
 if (ch == operators[i])
 return 1;
 }
 return 0;
}
int isPunctuation(char ch) {
 for (int i = 0; i < strlen(punctuation); i++) {
 if (ch == punctuation[i])
 return 1;
 }
 return 0;
}
void lexer(char *filename) {
 FILE *file = fopen(filename, "r");
 if (!file) {
 printf("Unable to open file.\n");
 return;
 }
 char ch, buffer[MAX_BUFFER];
 int i = 0;
 while ((ch = fgetc(file)) != EOF) {
 // Ignore white spaces, tabs, and new lines
 if (isspace(ch)) continue;
 // Handle comments
 if (ch == '/') {
7 char next = fgetc(file);
 if (next == '/') {
 while ((ch = fgetc(file)) != '\n' && ch != EOF);
 continue;
 } else if (next == '*') {
 while (1) {
 ch = fgetc(file);
 if (ch == '*' && (ch = fgetc(file)) == '/') break;
 if (ch == EOF) break;
 }
 continue;
 } else {
 ungetc(next, file);
 }
 }
 // Collect a word
 if (isalpha(ch)) {
 buffer[i++] = ch;
 while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
 buffer[i++] = ch;
 }
 buffer[i] = '\0';
 ungetc(ch, file);
 if (isKeyword(buffer)) {
 printf("%s is a keyword\n", buffer);
 } else {
 printf("%s is an identifier\n", buffer);
 }
 i = 0;
 }
 // Collect numbers
 else if (isdigit(ch)) {
 buffer[i++] = ch;
 while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
 buffer[i++] = ch;
 }
 buffer[i] = '\0';
 ungetc(ch, file);
 printf("%s is a constant\n", buffer);
 i = 0;
 }
 // Operators
 else if (isOperator(ch)) {
 printf("%c is an operator\n", ch);
 }
 // Punctuation
 else if (isPunctuation(ch)) {
 printf("%c is a punctuation\n", ch);
 }
 }
8 fclose(file);
}
int main() {
 lexer("input.c");
 return 0;
}
Input
# include<stdio.h>
void main()
{
 int a , b , c ;
 a = 10 ;
 b = 20 ;
 c = a / b ;
 printf ( "%d\n", c ) ;
}
