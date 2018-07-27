#include <stdio.h>
#include <libcs50-8.1.0/cs50.h>


void main()
{
    int H;
    do
    {
       printf("The height of the Mario staircase (from 0 to 23):\n");
       H = get_int();
    } while(H < 0 || H > 23);
    printf("------------------------------\n");
    if(H == 0) printf(" \n");
    else
    {
        for(int y = H; y > 0; y--) // y = H - высота лестницы; цикл уменьшает количество строк в лестнице
        {
            for(int x = (H + 1), S = (y - 1); x > 0; S--, x--) // x = (H + 1) - ширина лестницы; уменьшает количество символов в строке
            {
                if(S > 0)
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
            }
            printf("\n");
        }
    }
    printf("------------------------------\n");
}
