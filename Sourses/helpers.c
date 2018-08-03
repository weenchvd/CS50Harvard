/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n < 1) return false;
    for(int i = 0; i < n; i++)
    {
        if(value == values[i]) return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 1; i < n; i++)
    {
        for(int s = (i - 1); s >= 0; s--)
        {
            if(values[s+1] < values[s])
            {
                int tmp = values[s+1];
                values[s+1] = values[s];
                values[s] = tmp;
            }
            else(s = -1);
        }
    }
}
