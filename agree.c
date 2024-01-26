#include <stdio.h>

int main(void) 
{
    printf("Do you agree? ");
    
    char C = getchar();

    if (C == 'Y' || C == 'y')
    {
        printf("Agreed\n");
    }
    else if (C == 'N' || C == 'n')
    {
        printf("Disagreed\n");
    }
    else 
    {
        printf("Invalid input\n");
    }

    return 0;
}