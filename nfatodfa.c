#include <stdio.h>

int transition[20][20][20];
int dfaStates[20][20];

int nStates, nSymbols, nFinal;
int finalStates[20];
char symbols[20];

int dfaCount = 0;

/* Find the position of a symbol in alphabet */
int findSymbol(char ch)
{
    for (int i = 0; i < nSymbols; i++)
    {
        if (symbols[i] == ch)
            return i;
    }

    return -1;
}

/* Print a DFA state */
void printState(int state[])
{
    printf("{");

    for (int i = 1; i <= nStates; i++)
    {
        if (state[i] == 1)
            printf("q%d", i);
    }

    printf("}");
}

/* Check whether two DFA states are same */
int sameState(int a[], int b[])
{
    for (int i = 1; i <= nStates; i++)
    {
        if (a[i] != b[i])
            return 0;
    }

    return 1;
}

/* Check whether DFA state already exists */
int stateExists(int state[])
{
    for (int i = 0; i < dfaCount; i++)
    {
        if (sameState(dfaStates[i], state))
            return 1;
    }

    return 0;
}

/* Check whether a DFA state is final */
int isFinal(int state[])
{
    for (int i = 0; i < nFinal; i++)
    {
        if (state[finalStates[i]] == 1)
            return 1;
    }

    return 0;
}

int main()
{
    int nTransitions;
    int from, to;
    char ch;

    /* Input alphabet */
    printf("Number of alphabets?\n");
    scanf("%d", &nSymbols);

    printf("\nEnter the alphabets:\n");

    for (int i = 0; i < nSymbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    /* Input states */
    printf("Enter the number of states?\n");
    scanf("%d", &nStates);

    /* Start state */
    int start;
    printf("Enter the start state?\n");
    scanf("%d", &start);

    /* Final states */
    printf("Enter the number of final states?\n");
    scanf("%d", &nFinal);

    printf("Enter the final states?\n");

    for (int i = 0; i < nFinal; i++)
    {
        scanf("%d", &finalStates[i]);
    }

    /* Input transitions */
    printf("Enter no of transitions?\n");
    scanf("%d", &nTransitions);

    printf("Transition is in the format 'qno alphabet qno'\n");
    printf("States number must be greater than zero\n\n");

    printf("Enter transition?\n");

    for (int i = 0; i < nTransitions; i++)
    {
        scanf("%d %c %d", &from, &ch, &to);

        int symbol = findSymbol(ch);

        if (symbol == -1)
        {
            printf("Error: Alphabet not found\n");
            return 0;
        }

        /*
           Store transition.

           Example:
           q1 --a--> q2

           transition[1][0][2] = 1
        */
        transition[from][symbol][to] = 1;
    }

    /*
       Initial DFA state = {start state}

       Example:
       NFA start = q1

       DFA start = {q1}
    */
    dfaStates[0][start] = 1;
    dfaCount = 1;

    printf("\nEquivalent DFA...\n");
    printf("Transitions of DFA\n");

    /*
       Process every DFA state
    */
    for (int current = 0; current < dfaCount; current++)
    {
        for (int s = 0; s < nSymbols; s++)
        {
            int newState[20] = {0};

            /*
               Find all NFA states reachable
               using this input symbol.
            */
            for (int i = 1; i <= nStates; i++)
            {
                if (dfaStates[current][i] == 1)
                {
                    for (int j = 1; j <= nStates; j++)
                    {
                        if (transition[i][s][j] == 1)
                        {
                            newState[j] = 1;
                        }
                    }
                }
            }

            /*
               If at least one state was found
            */
            int empty = 1;

            for (int i = 1; i <= nStates; i++)
            {
                if (newState[i] == 1)
                {
                    empty = 0;
                    break;
                }
            }

            if (empty)
            {
                printState(dfaStates[current]);
                printf("%c\tNULL\n", symbols[s]);
            }
            else
            {
                /*
                   Add the new DFA state
                   if it does not already exist.
                */
                if (!stateExists(newState))
                {
                    for (int i = 1; i <= nStates; i++)
                    {
                        dfaStates[dfaCount][i] = newState[i];
                    }

                    dfaCount++;
                }

                printState(dfaStates[current]);
                printf("%c\t", symbols[s]);

                printState(newState);
                printf("\n");
            }
        }
    }

    /* Print all DFA states */
    printf("\nStates of DFA:\n");

    for (int i = 0; i < dfaCount; i++)
    {
        printState(dfaStates[i]);
        printf("\n");
    }

    /* Print alphabets */
    printf("\nAlphabets:\n");

    for (int i = 0; i < nSymbols; i++)
    {
        printf("%c\t", symbols[i]);
    }

    /* Print start state */
    printf("\nStart State:\n");

    printf("{q%d}", start);

    /* Print final states */
    printf("\nFinal states:\n");

    for (int i = 0; i < dfaCount; i++)
    {
        if (isFinal(dfaStates[i]))
        {
            printState(dfaStates[i]);
            printf("\t");
        }
    }

    printf("\n");

    return 0;
}
