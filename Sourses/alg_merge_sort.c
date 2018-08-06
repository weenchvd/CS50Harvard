#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>

int * MergeSort (int massive[], int lenth);

int main(int argc, string argv[])
{
    int q = (argc - 1);
    int massive[q];
    int * pntr_sorted_massive;
    for(int i = 0; i < q; i++)
    {
        massive[i] = atoi(argv[i+1]);
    }
    printf("Unsorted list:\n");
    for(int i = 0; i < q; i++)
    {
        printf("%d\t", massive[i]);
    }
    pntr_sorted_massive = MergeSort(massive, q);
    printf("\nSorted list:\n");
    for(int i = 0; i < q; i++)
    {
        printf("%d\t", massive[i]);
    }
    /*if(MergeSort(massive, &massive[0], &massive[q-1]))
    {
        printf("\nSorted list:\n");
        for(int i = 0; i < q; i++) printf("%d\t", massive[i]);
        return 0;
    }
    else
    {
        printf("\nSorting failed!\n");
        return 1;
    }*/
}

int * MergeSort (int massive[], int lenth)
{
    if(lenth > 1)
    {
        int middle = 0, shift = 0, left_half_lenth = 0, rigth_half_lenth = 0;
        int * left_half = 0, * right_half = 0;
        ((lenth % 2) == 1) ? (middle = ((lenth - 1) / 2) + 1) : (middle = (lenth / 2) + 1, shift = 1);

    }

}