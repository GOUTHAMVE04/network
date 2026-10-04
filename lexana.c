#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][20] = {
    "int", "float", "char", "double", "if", "else",
    "while", "for", "return", "void", "break",
    "continue", "do", "switch", "case", "default",
    "long", "short", "unsigned", "signed", "const"
};

int isKeyword(char str[]) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, buffer[100];
    int i = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {

        
        if (isspace(ch))
            continue;

      
        if (ch == '/') {
            char next = fgetc(fp);

            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            }
            else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
            }
            else {
                printf("%c : Operator\n", '/');
                fseek(fp, -1, SEEK_CUR);
            }
        }

        
        else if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (isKeyword(buffer))
                printf("%s : Keyword\n", buffer);
            else
                printf("%s : Identifier\n", buffer);

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        
        else if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.')) {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            printf("%s : Number\n", buffer);

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        else if (ch == '"') {
            i = 0;
            while ((ch = fgetc(fp)) != '"' && ch != EOF) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            printf("\"%s\" : String Literal\n", buffer);
        }

        
        else if (ch == '\'') {
            char c = fgetc(fp);
            fgetc(fp);
            printf("'%c' : Character Literal\n", c);
        }

       
        else if (strchr("+-*=<>!%&|", ch)) {
            printf("%c : Operator\n", ch);
        }

        
        else if (strchr("(){}[];,", ch)) {
            printf("%c : Special Symbol\n", ch);
        }
    }

    fclose(fp);
    return 0;
}

