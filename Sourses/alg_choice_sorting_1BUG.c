#include <stdio.h>
#include <stdlib.h>
#include <libcs50-8.1.0/cs50.h>


int main(int argc, string argv[])
{
    int massive[(argc - 1)];
    int n = (argc - 1);
    for(int i = 0; i < (argc - 1); i++)
    {
        massive[i] = atoi(argv[i+1]);
    }
    printf("Unsorted list\n");
    for(int c = 0; c < n; c++)
    {
        printf("%d\t", massive[c]);
    }
    for(int i = 0, tmp_index1 = 0; i < n; i++)
    {
        for(int s = i, tmp_index2 = s; (s + 1) < n; s++)
        {
            if(massive[tmp_index2] > massive[s+1])
            {
                tmp_index2 = s + 1;
                tmp_index1 = tmp_index2;
            }
        }
        int tmp_var = massive[i];
        massive[i] = massive[tmp_index1];
        massive[tmp_index1] = tmp_var;
    }
    printf("\nSorted list\n");
    for(int c = 0; c < n; c++)
    {
        printf("%d\t", massive[c]);
    }
    return 0;
}
