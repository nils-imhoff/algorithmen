#include <stdio.h>
#include <stdlib.h>

void delArray(int arr[], int n, int u)
{
    int i;
    if(u == n)
    {
        --n;
        return;
    }
    for(i=u-1 ; i < n; i++)
    {   
        arr[i] = arr[i+1];
    }

    --n;
}

void addArray(int arr[], int n, int u, int v)
{
    int i; 
    for(i=n; i > u; i--)
    {
        arr[i] = arr[i+1];
    }
        arr[u] = v;
        n++;
}

void addLastArray(int arr[], int n, int v)
{
    arr[n] = v;
}

void printArray(int arr[], int n)
{
    int i;
    for(i = 0; i< n; i++)
    {
        printf("%d \n", arr[i]);
    }
}
int main(int argc, char *argv[])
{
    int arr[10] = {1,2,3,4,5};
    int n = 5;
    printArray(arr, n);
    delArray(arr, n, 2);
    printf("==================================\n");
    printArray(arr, n);
    return EXIT_SUCCESS;
}
