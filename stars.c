#include <stdio.h>

int main() {
    int rows = 5;  // You can change this value to control the size of the pattern
    char letter = 'N';

    // Print the upper part of the pattern
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%c", letter);
        }
        printf("\n");
    }

    // Print the lower part of the pattern
    for (int i = rows - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("%c", letter);
        }
        printf("\n");
    }

    return 0;
}