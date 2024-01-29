#include <stdio.h>
#include <stdbool.h>

int main() 
{
    int number;

    printf("Enter an integer: ");
    scanf("%d",  &number);

    switch (number)
    {
        case 1:
        printf("You've entered number: 1\n");
        case 2:
        printf("You've entered number: 2\n");
        case 3:
        printf("You've entered number: 3\n");
        case 4:
        printf("You've entered number: 4\n");
        case 5:
        printf("You've entered number: 5\n");
        case 6:
        printf("You've entered number: 6\n");
        case 7:
        printf("You've entered number: 7\n");
        case 8:
        printf("You've entered number: 8\n");
        case 9:
        printf("You've entered number: 9\n");
        case 10:
        printf("You've entered number: 10\n");
        default:
        printf("Your number is more than 10, invalid integer\n");
    }
    return 0;
}