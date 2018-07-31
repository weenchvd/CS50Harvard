#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>


int main(int argc, string argv[])
{
    int n = (argc - 1);
    int massive[n];
    for(int i = 0; i < n; i++) massive[i] = atoi(argv[i+1]);
    printf("Unsorted list:\n");
    for(int i = 0; i < n; i++) printf("%d\t", massive[i]);
    for(int i = 1; i < n; i++)
    {
        for(int s = (i - 1); s >= 0; s--)
        {
            if(massive[s+1] < massive[s])
            {
                int tmp = massive[s+1];
                massive[s+1] = massive[s];
                massive[s] = tmp;
            }
            else(s = -1);
        }
    }
    printf("\nSorted list:\n");
    for(int i = 0; i < n; i++) printf("%d\t", massive[i]);
    return 0;
}
