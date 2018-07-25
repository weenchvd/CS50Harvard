#include <stdio.h>
#include "Libs/libcs50-8.1.0/cs50.h"



int main()
{
    float M;
    do
    {
        printf("How much change is owed?\n");
        M = get_float();
    } while(M <= 0 || M > 1000);
    double M2 = (M * 100);
    int C = (int) M2;






    printf("%f\n", M);
    printf("%f\n", M2);
    printf("%d\n", C);
}


