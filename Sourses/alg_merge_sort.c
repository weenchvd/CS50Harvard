#include <stdio.h>
#include <stdlib.h>

int * MergeSort (int *, int);

int main(int argc, char * argv[])
{
    int n = (argc - 1);
    int massive[n];
    int * ptr_UnsortedMassive = massive;
    for(int i = 0; i < n; i++)
    {
        massive[i] = atoi(argv[i+1]);
    }
    printf("Unsorted list:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t", massive[i]);
    }
    int * ptr_SortedMassive = MergeSort(ptr_UnsortedMassive, n);
    printf("\nSorted list:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t", *(ptr_SortedMassive+i));
    }
}

int * MergeSort (int * ptr_UnsortedMassive, int n)
{
    if(n == 1)
    {
        return ptr_UnsortedMassive;
    }
    else
    {
        int n_LeftHalf = 0, n_RightHalf = 0;
        int SortedMassive[n];
        int * ptr_SortedLeftHalf = NULL;
        int * ptr_SortedRightHalf = NULL;
        int * ptr_SortedMassive = SortedMassive;
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

        for(int i = 0, x = 0, y = 0; i < n; i++)
        {
            if(x < n_LeftHalf && y < n_RightHalf)
            {
                if(*(ptr_SortedLeftHalf+x) < *(ptr_SortedRightHalf+y))
                {
                    SortedMassive[i] = *(ptr_SortedLeftHalf+x);
                    x++;
                }
                else
                {
                    SortedMassive[i] = *(ptr_SortedRightHalf+y);
                    y++;
                }
            }
            else if (x < n_LeftHalf)
            {
                SortedMassive[i] = *(ptr_SortedLeftHalf+x);
                x++;
            }
            else
            {
                SortedMassive[i] = *(ptr_SortedRightHalf+y);
                y++;
            }
        }
        return ptr_SortedMassive;
    }
}
