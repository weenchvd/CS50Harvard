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
    double M2 = ((M + 0.002) * 100.0);
    int C = (int) M2;






    printf("%f\n", M);
    printf("%f\n", M2);
    printf("%d\n", C);
    //printf("sizeof(M) = %d \n", sizeof(M));
    //printf("sizeof(M2) = %d \n", sizeof(M2));
    //printf("sizeof(C) = %d \n", sizeof(C));
    //printf("INT_MIN = %d \n", INT_MIN);
    //printf("INT_MAX = %d \n", INT_MAX);
}


