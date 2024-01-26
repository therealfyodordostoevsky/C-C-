#include <stdio.h>

int main(void) {
    int n, i;
    printf("Enter the number of elements you want in array: ");
    scanf("%d", &n);
    // dynamically allocate memory for an integer array
    int *arr = (int*)malloc(sizeof(int)*n);
    if (!arr) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    printf("Enter %d integers:\n", n);
    for (i=0; i<n; i++) {
        printf("Element [%d]: ", i+1);
        scanf("%d", &arr[i]);
    }
    /* print out the array */
    printf("\nThe entered array is:\n");
    for (i=0; i<n; i++) {
        printf("%d\t", arr[i]);
    }
    free(arr);  // don't forget to release the memory when done!</s
    return 0;
}