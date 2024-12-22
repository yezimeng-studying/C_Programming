/*输入为不确定个数的字符（字符数少于5个），输出为这些字符的图案表示。*/
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 5
#define PATTERN_HEIGHT 7

void printPattern(char input[]) {
    int len = strlen(input);
    for (int i = 0; i < PATTERN_HEIGHT; i++) {
        for (int j = 0; j < len; j++) {
            if (i == 0 || i == 3 || i == PATTERN_HEIGHT - 1) {
                for (int k = 0; k < 6; k++) {
                    printf("*");
                }
            } else {
                printf("*");
                for (int k = 0; k < 5; k++) {
                    printf(" ");
                }
                printf("*");
            }
            if (j < len - 1) {
                printf("   ");
            }
        }
        printf("\n");
    }
}

int main() {
    char input[MAX_LENGTH];
    printf("请输入少于5个字符: ");
    scanf("%s", input);
    printPattern(input);
    return 0;
}

