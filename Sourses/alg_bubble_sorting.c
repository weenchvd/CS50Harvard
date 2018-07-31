#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>


int main(int argc, string argv[])
{
    int n = (argc - 1);
    int massive[n];
    for(int i = 0; i < n; i++) massive[i] = atoi(argv[i+1]);
    printf("Unsorted list:\n");
    for(int i = 0; i < n; i++) printf("%d\t", massive[i]);
    for(int i = (n - 1); i > 0; i--)
    {
        for(int s = 0; s < i; s++)
        {
            if(massive[s] > massive[s+1])
            {
                int tmp = massive[s];
                massive[s] = massive[s+1];
                massive[s+1] = tmp;
            }
        }
    }
    printf("\nSorted list:\n");
    for(int i = 0; i < n; i++) printf("%d\t", massive[i]);
    return 0;
}
