#include <stdio.h>
#include "Libs/libcs50-8.1.0/cs50.h"

int main(void) {
    int min;
    do {
        min = get_int("Сколько минут ты провел в душе?\n");
    } while (min < 0);
    printf("Ты израсходовал %i полулитровых бутылок воды!\n", min * 12);
}
