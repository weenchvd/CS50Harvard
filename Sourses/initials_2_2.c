#include <stdio.h>
#include <string.h>
#include <libcs50-8.1.0/cs50.h>

void PRINTLETTER(char ch1);
void printletter(char ch1);

char ch1;

int main()
{
    string S = get_string();
    ch1 = S[0];
    (S[0] > 40 && S[0] < 91) ? PRINTLETTER(ch1) : printletter(ch1);
    for(int i = 0; i < strlen(S); i++) if(S[i] == 32) (S[i + 1] > 40 && S[i + 1] < 91) ? (ch1 = S[i + 1], PRINTLETTER(ch1)) : (ch1 = S[i + 1], printletter(ch1));
    printf("\n");
}

void PRINTLETTER(char ch1) //печатает прописную букву
{
    printf("%c", ch1);
}

void printletter(char ch1) //печатает прописную букву из строчной
{
    int n = (int) ch1;
    n -=32;
    ch1 = (char) n;
    printf("%c", ch1);
}
