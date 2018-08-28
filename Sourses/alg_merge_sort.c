#include <stdio.h>
#include <stdlib.h>

int * MergeSort (int *, unsigned int);

int main(int argc, char * argv[])
{
    unsigned int n = (unsigned int) (argc - 1);
    int * ptr_UnsortedMassive = calloc(n, sizeof(int));

    for(int i = 0; i < n; i++)
    {
        *(ptr_UnsortedMassive+i) = atoi(argv[i+1]);
    }
    printf("Unsorted list:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t", *(ptr_UnsortedMassive+i));
    }
    int * ptr_SortedMassive = MergeSort(ptr_UnsortedMassive, n);
    free(ptr_UnsortedMassive);
    printf("\nSorted list:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t", *(ptr_SortedMassive+i));
    }
    free(ptr_SortedMassive);
    return 0;
}

int * MergeSort (int * ptr_UnsortedMassive, unsigned int n)
{
    if(n == 1)
    {
        int * ptr_SortedMassive = malloc(sizeof(int));
        *(ptr_SortedMassive) = *(ptr_UnsortedMassive);
        return ptr_SortedMassive;
    }
    else
    {
        unsigned int n_LeftHalf = 0, n_RightHalf = 0;
        int * ptr_SortedLeftHalf = NULL;
        int * ptr_SortedRightHalf = NULL;
        if(n % 2)
        {
            n_LeftHalf = (n - 1) / 2;
            n_RightHalf = n_LeftHalf + 1;
            ptr_SortedLeftHalf = MergeSort(ptr_UnsortedMassive, n_LeftHalf);
            ptr_SortedRightHalf = MergeSort((ptr_UnsortedMassive + (n - 1) / 2), n_RightHalf);
        }
        else
        {
            n_LeftHalf = n_RightHalf = n / 2;
            ptr_SortedLeftHalf = MergeSort(ptr_UnsortedMassive, n_LeftHalf);
            ptr_SortedRightHalf = MergeSort((ptr_UnsortedMassive + n / 2), n_RightHalf);
        }

        int * ptr_SortedMassive = calloc(n, sizeof(int));
        for(int i = 0, x = 0, y = 0; i < n; i++)
        {
            if(x < n_LeftHalf && y < n_RightHalf)
            {
                if(*(ptr_SortedLeftHalf+x) < *(ptr_SortedRightHalf+y))
                {
                    *(ptr_SortedMassive+i) = *(ptr_SortedLeftHalf+x);
                    x++;
                }
                else
                {
                    *(ptr_SortedMassive+i) = *(ptr_SortedRightHalf+y);
                    y++;
                }
            }
            else if (x < n_LeftHalf)
            {
                *(ptr_SortedMassive+i) = *(ptr_SortedLeftHalf+x);
                x++;
            }
            else
            {
                *(ptr_SortedMassive+i) = *(ptr_SortedRightHalf+y);
                y++;
            }
        }
        free(ptr_SortedLeftHalf);
        free(ptr_SortedRightHalf);
        return ptr_SortedMassive;
    }
}
