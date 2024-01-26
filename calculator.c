#include <stdio.h>
#include <math.h>
#include <string.h>

double factorial(double n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(void) 
{
    char operator[10];
    double num, result;

    // Input
    printf("Enter operator (+, -, *, /, ^, %%, !, sqrt, cbrt): ");
    scanf("%s", operator);

    // Additional input for factorial, square root, and cube root
    if (strcmp(operator, "!") != 0 && strcmp(operator, "sqrt") != 0 && strcmp(operator, "cbrt") != 0) {
        printf("Enter a number: ");
        scanf("%lf", &num);
    }

    // Perform calculations based on the operator
    if (strcmp(operator, "+") == 0) {
        result = num + num;
    } else if (strcmp(operator, "-") == 0) {
        result = num - num;
    } else if (strcmp(operator, "*") == 0) {
        result = num * num;
    } else if (strcmp(operator, "/") == 0) {
        if (num != 0) {
            result = num / num;
        } else {
            printf("Error: Division by zero is not allowed.\n");
            return 1; // Exit with an error code
        }
    } else if (strcmp(operator, "^") == 0) {
        result = pow(num, num);
    } else if (strcmp(operator, "%") == 0) {
        if (num != 0) {
            result = fmod(num, num);
        } else {
            printf("Error: Modulo by zero is not allowed.\n");
            return 1; // Exit with an error code
        }
    } else if (strcmp(operator, "!") == 0) {
        result = factorial(num);
    } else if (strcmp(operator, "sqrt") == 0) {
        result = sqrt(num);
    } else if (strcmp(operator, "cbrt") == 0) {
        result = cbrt(num);
    } else {
        printf("Error: Invalid operator.\n");
        return 1; // Exit with an error code
    }

    // Output the result
    printf("Result: %.2lf\n", result);

    return 0;
}