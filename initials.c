#include <stdio.h>
#include <string.h>
#include "Libs/libcs50-8.1.0/cs50.h"


int main()
{
    string S = get_string();
    char ch1 = S[0];
    if(S[0] > 40 && S[0] < 91)
    {
        printf("%c", S[0]);
    }
    else
    {
        int n = (int) S[0];
        n -=32;
        ch1 = (char) n;
        printf("%c", ch1);
    }

    for(int i = 0; i < strlen(S); i++)
    {
        if(S[i] == 32)
        {
            if(S[i + 1] > 40 && S[i + 1] < 91)
            {
                printf("%c", S[i + 1]);
            }
            else
            {
                int n = (int) S[i + 1];
                n -=32;
                ch1 = (char) n;
                printf("%c", ch1);
            }
        }
    }
    printf("\n");
}
