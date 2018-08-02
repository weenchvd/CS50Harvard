/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libcs50-8.1.0/cs50.h>


int main(int argc, string argv[])
{
    // exits the program if the number of arguments differs from 2 or 3
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // assigns the value of the first argument to "n"
    int n = atoi(argv[1]);

    // puts the value of the second argument or the value of the current time in the argument of the "srand" function
    if (argc == 3)
    {
        srand((long int) atoi(argv[2]));
    }
    else
    {
        srand((long int) time(NULL));
    }

    // outputs pseudo-random numbers one per line
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (rand() * RAND_MAX));
    }

    // success
    return 0;
}
