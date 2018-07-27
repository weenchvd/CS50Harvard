#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>


int main()
{
    int C25 = 0, C10 = 0, C5 = 0, C1 = 0, Q = 0;
    float M, M2;
    do
    {
        printf("How much change is owed?\n");
        M = get_float();
    } while(M <= 0 || M > 1000000); // не отрицательное и не больше 1 млн.
    M2 = ((M + 0.002) * 100); // переводим в центы, 0.002 убирает баг
    int C = (int) M2; // преобразовываем в целое
    C25 = (C / 25); // кол-во монет по 25 центов
    C10 = ((C - (C25 * 25)) / 10); // кол-во монет по 10 центов
    C5 = ((C - (C25 * 25) - (C10 * 10)) / 5); // кол-во монет по 5 центов
    C1 = (C - (C25 * 25) - (C10 * 10) - (C5 *5)); // кол-во монет по 1 центу
    Q = (C25 + C10 + C5 + C1); // кол-во монет ВСЕГО
    printf("%d\n", Q);
    printf("------------------------------\n");
    //printf("%f\n", M);
    //printf("%f\n", M2);
    //printf("%d\n", C);
    //printf("%d\n", C25);
    //printf("%d\n", C10);
    //printf("%d\n", C5);
    //printf("%d\n", C1);
    //printf("sizeof(M) = %d \n", sizeof(M));
    //printf("sizeof(M2) = %d \n", sizeof(M2));
    //printf("sizeof(C) = %d \n", sizeof(C));
    //printf("INT_MIN = %d \n", INT_MIN);
    //printf("INT_MAX = %d \n", INT_MAX);
}
