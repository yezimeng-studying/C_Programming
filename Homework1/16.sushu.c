#include <stdio.h>

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int number;
    printf("Enter a positive number: ");
    scanf("%d", &number);
    if (isPrime(number)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    return 0;
}

