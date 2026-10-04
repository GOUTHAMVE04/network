#include <stdio.h>

int main()
{
    int n, m;
    int transition[20][10];
    int final[20];
    int marked[20][20] = {0};
    int i, j, k;
    char symbols[10];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols: ");
    for (i = 0; i < m; i++)
        scanf(" %c", &symbols[i]);

    printf("\nEnter transition table:\n");
    printf("States are numbered from 0 to %d\n", n - 1);

    for (i = 0; i < n; i++)
    {
        printf("State %d:\n", i);

        for (j = 0; j < m; j++)
        {
            printf("  On %c -> ", symbols[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    printf("\nEnter number of final states: ");
    int f;
    scanf("%d", &f);

    for (i = 0; i < n; i++)
        final[i] = 0;

    printf("Enter final states: ");
    for (i = 0; i < f; i++)
    {
        int state;
        scanf("%d", &state);
        final[state] = 1;
    }

    
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (final[i] != final[j])
            {
                marked[i][j] = 1;
            }
        }
    }

   
    int changed;

    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (marked[i][j])
                    continue;

                for (k = 0; k < m; k++)
                {
                    int p = transition[i][k];
                    int q = transition[j][k];

                    if (p == q)
                        continue;

                    int a = p < q ? p : q;
                    int b = p < q ? q : p;

                    if (marked[a][b])
                    {
                        marked[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }

    } while (changed);

    printf("\nEquivalent states:\n");

    int found = 0;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (!marked[i][j])
            {
                printf("(%d, %d)\n", i, j);
                found = 1;
            }
        }
    }

    if (!found)
        printf("No equivalent states.\n");

    printf("\nMinimized DFA state groups:\n");

    int group[20];

    for (i = 0; i < n; i++)
        group[i] = i;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (!marked[i][j])
                group[j] = group[i];
        }
    }

    for (i = 0; i < n; i++)
    {
        if (group[i] == i)
        {
            printf("{ ");

            for (j = 0; j < n; j++)
            {
                if (group[j] == i)
                    printf("%d ", j);
            }

            printf("}\n");
        }
    }

    return 0;
}
