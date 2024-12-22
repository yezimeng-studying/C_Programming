#include <stdio.h>

void printBits(char c) {
    for (int i = 7; i >= 0; i--) {
        printf("The %d bit is %d,\n", i + 1, (c & (1 << i))? 1 : 0);
    }
}

int main() {
    char input;
    printf("Enter a character: ");
    scanf("%c", &input);
    printBits(input);
    return 0;
}

