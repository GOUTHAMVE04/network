#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[2];
char act[15];

int check();

int main() {
    printf("\n\t\t SHIFT REDUCE PARSER\n");
    printf("\n GRAMMAR\n");
    printf("\n E->E+E\n E->E/E");
    printf("\n E->E*E\n E->a/b");
    printf("\n Enter the input symbol: ");
    scanf("%s", ip_sym);

    printf("\n\t Stack implementation table");
    printf("\n stack \t\t input symbol\t\t action");
 
    printf("\n $\t\t%s$\t\t\t--", ip_sym);

    len = strlen(ip_sym);
    for (i = 0; i < len; i++) {
        strcpy(act, "shift ");
        temp[0] = ip_sym[ip_ptr];
        temp[1] = '\0';
        strcat(act, temp);

        stack[st_ptr] = ip_sym[ip_ptr];
        stack[st_ptr + 1] = '\0';
        ip_sym[ip_ptr] = ' ';
        ip_ptr++;

        printf("\n $%s\t\t%s$\t\t\t%s", stack, ip_sym, act);

        while (check());
        st_ptr++;
    }

    if (!strcmp(stack, "E") && ip_ptr == len) {
        printf("\n $%s\t\t%s$\t\t\tAccept\n", stack, ip_sym);
    } else {
        printf("\n $%s\t\t%s$\t\t\tReject\n", stack, ip_sym);
    }

    return 0;
}

int check() {
    int s_len = strlen(stack);

    
    if (s_len >= 1 && (stack[s_len - 1] == 'a' || stack[s_len - 1] == 'b')) {
        char val = stack[s_len - 1];
        stack[s_len - 1] = 'E';
        printf("\n $%s\t\t%s$\t\t\tE->%c", stack, ip_sym, val);
        return 1;
    }

 
    if (s_len >= 3 && stack[s_len - 3] == 'E' && stack[s_len - 1] == 'E') {
        char op = stack[s_len - 2];
        if (op == '+' || op == '*' || op == '/') {
            stack[s_len - 3] = 'E';
            stack[s_len - 2] = '\0';
            st_ptr -= 2;
            printf("\n $%s\t\t%s$\t\t\tE->E%cE", stack, ip_sym, op);
            return 1;
        }
    }

    return 0;
}
