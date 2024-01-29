#include <stdio.h>

int main() {
    char grade;

    printf("Enter your grade (A, B, C, D, or F): ");
    scanf("%c", &grade);

    switch (grade) {
        case 'A':
            printf("Excellent!\n");
            break;
        case 'B':
            printf("Good job!\n");
            break;
        case 'C':
            printf("Satisfactory.\n");
            break;
        case 'D':
            printf("Needs improvement.\n");
            break;
        case 'F':
            printf("Failed. You should seek help.\n");
            break;
        default:
            printf("Invalid grade entered.\n");
    }

    return 0;
}
