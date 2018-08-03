#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>

int BinarySearch(int massive[], int q);

int main(int argc, string argv[])
{
    int n, q = (argc - 1);
    int massive[q];
    for(int i = 0; i < q; i++)
    {
        massive[i] = atoi(argv[i+1]);
    }
    printf("Quantity of numbers = %d. Massive:\n", q);
    for(int i = 0; i < q; i++)
    {
        printf("%d\t", massive[q]);
    }
    printf("Enter a number to search for:\t");
    scanf("%d", &n);
    printf("Number '%d' is find! It is located in Massive[%d].\n", n, BinarySearch(massive, q, n)); //TODO: do IF-ELSE
    return 0;
}


int BinarySearch(int massive[], int q, int n)
{
    for(int i = 0; i != -1; i++)
    {
        ((q % 2) == 1) ? (q = (q / 2) + 1) : (q = (q / 2));
        if(n < massive[q]);
        else if(n > massive[q]);
        else return q;
    }
}







































