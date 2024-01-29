#include <stdio.h>

int main() {
    int num = 42;
    char character = 'A';
    char string[20] = "Hello, World!";

    // Printing values using printf
    printf("Integer: %d\n", num);
    printf("Character: %c\n", character);
    printf("String: %s\n", string);

    // Reading values using scanf
    int inputNum;
    char inputChar;
    char inputString[20];

    printf("Enter an integer: ");
    scanf("%d", &inputNum);

    printf("Enter a character: ");
    scanf(" %c", &inputChar);  // Note the space before %c to consume any leading whitespace.

    printf("Enter a string: ");
    scanf("%s", inputString);

    // Displaying the input values
    printf("Entered Integer: %d\n", inputNum);
    printf("Entered Character: %c\n", inputChar);
    printf("Entered String: %s\n", inputString);

    return 0;
}
