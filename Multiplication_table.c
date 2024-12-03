#include <stdio.h>

int main() {
    int firstNumber, secondNumber, size;

    printf("Welcome to my magical multiplication table, Please enter the first number: ");
    scanf("%d", &firstNumber);

    printf("Please enter the second number: ");
    scanf("%d", &secondNumber);

    printf("Please enter the third number (for the table's looking): ");
    scanf("%d", &size);

    printf("\nMultiplication Table:\n");

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }

    printf("\nMultiplication table has made, See you!\n");
    return 0;
}
