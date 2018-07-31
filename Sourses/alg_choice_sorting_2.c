#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>


int main()
{
    //int n  = 4;
    //int massive[4] = {6, 90, 43, 1};
    printf("Enter quantity of numbers:\t");
    int n =  get_int();
    int massive[n];
    for(int i = 0; i < n; i++)
    {
        printf("Enter the number #%d:\t", (i + 1));
        massive[i] = get_int();
    }
    printf("Unsorted list\n");
    for(int c = 0; c < n; c++)
    {
        printf("%d\t", massive[c]);
    }
    for(int i = 0, tmp_index1 = 0; i < (n - 1); i++)
    {
        tmp_index1 = 0;
        for(int s = i, tmp_index2 = s; s < (n - 1); s++)
        {
            if(massive[tmp_index2] > massive[s+1])
            {
                tmp_index2 = s + 1;
                tmp_index1 = tmp_index2;
            }
        }
        if(tmp_index1 > i)
        {
            int tmp_var = massive[i];
            massive[i] = massive[tmp_index1];
            massive[tmp_index1] = tmp_var;
        }
    }
    printf("\nSorted list\n");
    for(int c = 0; c < n; c++)
    {
        printf("%d\t", massive[c]);
    }
    return 0;
}

/*int n = 0;
    int massive[0];
    for(int i = 0, j = 0; i == j; i++)
    {
        printf("Enter the number #%d:\t", (i + 1));
        massive[i] = get_int();
        (massive[i] != 0) ? (n++, j = n) : (j = 0);
    }*/
