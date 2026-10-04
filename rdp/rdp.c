

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char input[100];
int pos = 0;



char stack[1000];
int top = -1;



void E();
void Eprime();
void T();
void Tprime();
void F();


void push(char c)
{
    stack[++top] = c;
}


void pop()
{
    if (top >= 0)
        top--;
}


void printStack()
{
    int i;


    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);


    printf("%20s", "");
}


void printInput()
{
    printf("%-15s", input + pos);
}


void action(char *msg)
{
    printStack();
    printInput();
    printf("%s\n", msg);
}


void error()
{
    action("ERROR: Invalid Expression");
    exit(1);
}



void E()
{
    push('E');
    action("E -> T E'");


    pop();
    T();


    Eprime();
}



void Eprime()
{
    push('P');       


    if (input[pos] == '+')
    {
        action("E' -> + T E'");


        pop();


        pos++;
        action("Match +");


        T();
        Eprime();
    }
    else if (input[pos] == '-')
    {
        action("E' -> - T E'");


        pop();


        pos++;
        action("Match -");


        T();
        Eprime();
    }
    else
    {
        action("E' -> epsilon");
        pop();
    }
}



void T()
{
    push('T');
    action("T -> F T'");


    pop();
    F();


    Tprime();
}

void Tprime()
{
    push('Q');      


    if (input[pos] == '*')
    {
        action("T' -> * F T'");


        pop();


        pos++;
        action("Match *");


        F();
        Tprime();
    }
    else if (input[pos] == '/')
    {
        action("T' -> / F T'");


        pop();


        pos++;
        action("Match /");


        F();
        Tprime();
    }
    else
    {
        action("T' -> epsilon");
        pop();
    }
}


void F()
{
    push('F');


    if ((input[pos] >= 'a' && input[pos] <= 'z') ||
        (input[pos] >= 'A' && input[pos] <= 'Z'))
    {
        action("F -> id");


        pop();


        pos++;
        action("Match id");
    }
    else if (input[pos] == '(')
    {
        action("F -> ( E )");


        pop();


        pos++;
        action("Match (");


        E();


        if (input[pos] == ')')
        {
            pos++;
            action("Match )");
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}


int main()
{
    printf("Enter an expression: ");
    scanf("%s", input);


    printf("\n%-15s %-15s %s\n",
           "Stack", "Input", "Action");
    printf("-----------------------------------------------\n");


    E();


    if (input[pos] == '\0')
    {
        printStack();
        printInput();
        printf("Accept\n");
    }
    else
    {
        error();
    }


    return 0;
}



