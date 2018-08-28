#include <stdio.h>
#include <stdlib.h>

int * MergeSort (int *, int *, unsigned int);

int main(int argc, char * argv[])
{
    unsigned int Lenth = (unsigned int) (argc - 1);
    int * ptr_UnsortedMassive = calloc(Lenth, sizeof(int));
    int * ptr_SortedMassive = calloc(Lenth, sizeof(int));

    for(int i = 0; i < Lenth; i++)
    {
        *(ptr_UnsortedMassive+i) = atoi(argv[i+1]);
    }
    printf("Unsorted list:\n");
    for(int i = 0; i < Lenth; i++)
    {
        printf("%d\t", *(ptr_UnsortedMassive+i));
    }

    ptr_SortedMassive = MergeSort(ptr_UnsortedMassive, ptr_SortedMassive, Lenth);
    free(ptr_UnsortedMassive);
    printf("\nSorted list:\n");
    for(int i = 0; i < Lenth; i++)
    {
        printf("%d\t", *(ptr_SortedMassive+i));
    }
    free(ptr_SortedMassive);
    return 0;
}

int * MergeSort (int * ptr_UnsortedMassive, int * ptr_SortedMassive, unsigned int Lenth)
{
    if(Lenth == 1)
    {
        ptr_SortedMassive = ptr_UnsortedMassive;
        return ptr_SortedMassive;
    }
    else
    {
        unsigned int LenthLeftHalf = 0, LenthRightHalf = 0;
        int * ptr_SortedLeftHalf = NULL;
        int * ptr_SortedRightHalf = NULL;
        int * ptr_Temp = NULL;
        if(Lenth % 2)
        {
            LenthLeftHalf = (Lenth - 1) / 2;
            LenthRightHalf = LenthLeftHalf + 1;
            ptr_SortedLeftHalf = MergeSort(ptr_UnsortedMassive, ptr_SortedMassive, LenthLeftHalf);
            ptr_SortedRightHalf = MergeSort((ptr_UnsortedMassive+(Lenth-1)/2), (ptr_SortedMassive+(Lenth-1)/2), LenthRightHalf);
        }
        else
        {
            LenthLeftHalf = LenthRightHalf = Lenth / 2;
            ptr_SortedLeftHalf = MergeSort(ptr_UnsortedMassive, ptr_SortedMassive, LenthLeftHalf);
            ptr_SortedRightHalf = MergeSort((ptr_UnsortedMassive+Lenth/2), (ptr_SortedMassive+Lenth/2), LenthRightHalf);
            ptr_Temp = ptr_UnsortedMassive;
            ptr_UnsortedMassive = ptr_SortedLeftHalf;
            ptr_SortedMassive = ptr_Temp;
        }

        for(int i = 0, x = 0, y = 0; i < Lenth; i++)
        {
            if(x < LenthLeftHalf && y < LenthRightHalf)
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
            else if (x < LenthLeftHalf)
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
        return ptr_SortedMassive;
    }
}
