#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libcs50-8.1.0/cs50.h>

void PrintEncUppLetter(char Letter);
void PrintEncLowLetter(char Letter);

int KeyLenth;

int main(int argc, string argv[])
{
    if(argc != 2) return 1;
    KeyLenth = atoi(argv[1]);
    if(KeyLenth < 1) return 1;
    KeyLenth %= 26;

    string Text = get_string();
    for(int i = 0, n = strlen(Text); i < n; i++)
    {
        if(Text[i] > 64 && Text[i] < 91) PrintEncUppLetter(Text[i]);
        else if(Text[i] > 96 && Text[i] < 123) PrintEncLowLetter(Text[i]);
        else printf("%c", Text[i]);
    }
    return 0;
}

void PrintEncUppLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter += KeyLenth;
    if(NumLetter > 90) NumLetter = (NumLetter % 90) + 64;
    printf("%c", NumLetter);
}

void PrintEncLowLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter += KeyLenth;
    if(NumLetter > 122) NumLetter = (NumLetter % 122) + 96;
    printf("%c", NumLetter);
}
/* Даже если результат имеет тип int (int NumLetter), оператор printf использует плейсхолдер %с для символов.
 * Таким образом, программа печатает символ, связанный с целочисленным результатом */
