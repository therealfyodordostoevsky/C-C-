#include <stdio.h>
    /*print Fahrenheit-Celcius table
    for fahr = 0, 20, ..., 300 */
int main()
{
    int fahr, celcius;
    int lower, upper, step;
    lower = 0;         /*lower index of temperature range */
    upper = 100;       /*upper index of temperature range */    
    step = 20;         /*step size - how much to increase the index value each */
    fahr = lower;
    while (fahr <= upper)
    {
        celcius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celcius);
        fahr = fahr + step;
    }
    
}