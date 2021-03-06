#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>

int BinarySearch(int massive[], int * left_border, int * rigth_border);

int n = 0;
int * pntr_n = &n;

int main(int argc, string argv[])
{
    int q = (argc - 1);
    int massive[q];
    for(int i = 0; i < q; i++)
    {
        massive[i] = atoi(argv[i+1]);
    }
    printf("Quantity of numbers = %d. Massive:\n", q);
    for(int i = 0; i < q; i++)
    {
        printf("%d\t", massive[i]);
    }
    printf("\nEnter an integer number to search for:\t");
    scanf("%d", &n);
    int addr = BinarySearch(massive, &massive[0], &massive[q-1]);
    if(addr == -1) printf("\nNumber '%d' is not find.\n", n);
    else printf("Number '%d' is find! It is located in 'massive[%d]'.\n", n, addr);
    return 0;
}

int BinarySearch(int massive[], int * left_border, int * rigth_border)
{
    int middle = 0, shift = 0;
    int * left_border_new = 0, * right_border_new = 0;
    unsigned int lenth = rigth_border - left_border + 1;
    if(lenth > 2)
    {
        ((lenth % 2) == 1) ? (middle = ((lenth - 1) / 2) + 1) : (middle = (lenth / 2) + 1, shift = 1);
        if(* pntr_n < * (left_border + middle - 1))
        {
            left_border_new = left_border;
            right_border_new = rigth_border - middle + shift;
            BinarySearch(massive, left_border_new, right_border_new);
        }
        else if(* pntr_n > * (left_border + middle - 1))
        {
            right_border_new = rigth_border;
            left_border_new = left_border + middle;
            BinarySearch(massive, left_border_new, right_border_new);
        }
        else if(* pntr_n == * (left_border + middle - 1))
        {
            unsigned int a = (left_border + middle - 1) - &massive[0];
            return a;
        }
    }
    else
    {
        if(* left_border == * pntr_n)
        {
            unsigned int a = left_border - &massive[0];
            return a;
        }
        else if(* rigth_border == * pntr_n)
        {
            unsigned int a = rigth_border - &massive[0];
            return a;
        }
        else return -1;
    }
}
