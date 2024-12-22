#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printE() {
    printf("\033[32m******\n*\n*\n******\n*\n*\n******\033[0m\n");
}

void printO() {
    printf("\033[34m  ****  \n *    * \n *    * \n *    * \n *    * \n  ****  \033[0m\n");
}

void printT() {
    printf("\033[31m*******\n   *   \n   *   \n   *   \n   *   \n   *   \n   *   \033[0m\n");
}

int main() {
    char input;
    printf("Enter a single character: ");
    scanf("%c", &input);

    switch(input) {
        case 'E':
        case 'e':
            printE();
            break;
        case 'O':
        case 'o':
            printO();
            break;
        case 'T':
        case 't':
            printT();
            break;
        default:
            printf("Character '%c' not recognized.\n", input);
    }

    return 0;
}

