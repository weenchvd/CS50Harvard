#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Libs/libcs50-8.1.0/cs50.h"

void GetEncUppLetter(char Letter);
void GetEncLowLetter(char Letter);

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
        if(Text[i] > 64 && Text[i] < 91) GetEncUppLetter(Text[i]);
        else if(Text[i] > 96 && Text[i] < 123) GetEncLowLetter(Text[i]);
        else printf("%c", Text[i]);
    }
    return 0;
}

void GetEncUppLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter = KeyLenth + 64;
    if(NumLetter > 90) NumLetter = (NumLetter % 90) + 64;
    char EncUppLetter = (char) NumLetter;
    printf("%c", EncUppLetter);
}

void GetEncLowLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter = KeyLenth + 96;
    if(NumLetter > 122) NumLetter = (NumLetter % 90) + 96;
    char EncUppLetter = (char) NumLetter;
    printf("%c", EncUppLetter);
}
