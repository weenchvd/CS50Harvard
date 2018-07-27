#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libcs50-8.1.0/cs50.h>

void PrintEncLowLetter(char Letter);
void PrintEncUppLetter(char Letter);
void PrintEncDigit(char Letter);

int KeyLenth;

int main(int argc, string argv[])
{
    if (argc != 2) return 1;
    string KeyWord = argv[1];
    for (int i = 0, n1 = strlen(KeyWord); i < n1; i++)
    {
        if (isalpha(KeyWord[i]));
        else return 1;
    }
    string InputText = get_string();
    for(int i = 0, n2 = strlen(InputText); i < n2; i++)
    {
        if(islower(InputText[i])) PrintEncLowLetter(InputText[i]);
        else if(isupper(InputText[i])) PrintEncUppLetter(InputText[i]);
        else if(isdigit(InputText[i])) PrintEncDigit(InputText[i]);
        else printf("%c", InputText[i]);
    }
}

void PrintEncLowLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter += KeyLenth;
    if(NumLetter > 122) NumLetter = (NumLetter % 122) + 96;
    printf("%c", NumLetter);
}

void PrintEncUppLetter(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter += KeyLenth;
    if(NumLetter > 90) NumLetter = (NumLetter % 90) + 64;
    printf("%c", NumLetter);
}

void PrintEncDigit(char Letter)
{
    int NumLetter = (int) Letter;
    NumLetter += KeyLenth;
    if(NumLetter > 57) NumLetter = (NumLetter % 57) + 47;
    printf("%c", NumLetter);
}

















































