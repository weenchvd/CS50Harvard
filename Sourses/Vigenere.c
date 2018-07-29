#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libcs50-8.1.0/cs50.h>

void PrintEncLowLetter(char Letter);
void PrintEncUppLetter(char Letter);
void PrintEncDigit(char Letter);
void CalcKeyLenth(void);

int KeyLenth, n1;
int t = 0;
string KeyWord;

int main(int argc, string argv[])
{
    if(argc != 2) return 1;
    KeyWord = argv[1];
    n1 = strlen(KeyWord);
    for(int i = 0; i < n1; i++)
    {
        if ((islower(KeyWord[i]) || isupper(KeyWord[i])) != 1) return 1;
        KeyWord[i] = tolower(KeyWord[i]);
    }
    string InputText = get_string();
    for(int i = 0, n2 = strlen(InputText); i < n2; i++)
    {
        if(islower(InputText[i]))
        {
            CalcKeyLenth();
            PrintEncLowLetter(InputText[i]);
        }
        else if(isupper(InputText[i]))
        {
            CalcKeyLenth();
            PrintEncUppLetter(InputText[i]);
        }
        else if(isdigit(InputText[i]))
        {
            CalcKeyLenth();
            PrintEncDigit(InputText[i]);
        }
        else printf("%c", InputText[i]);
    }
    return 0;
}

void CalcKeyLenth(void)
{
    KeyLenth = ((int) KeyWord[t]) - 97; //Calculate KeyLenth
    (t < (n1 - 1)) ? t++ : (t = 0);
}

void PrintEncLowLetter(char Letter)
{
    int NumLetter = (int) Letter; //Calculate EncLowLetter
    NumLetter += KeyLenth;
    if(NumLetter > 122) NumLetter = (NumLetter % 122) + 96;
    printf("%c", NumLetter);
}

void PrintEncUppLetter(char Letter)
{
    int NumLetter = (int) Letter; //Calculate EncUppLetter
    NumLetter += KeyLenth;
    if(NumLetter > 90) NumLetter = (NumLetter % 90) + 64;
    printf("%c", NumLetter);
}

void PrintEncDigit(char Letter)
{
    int NumLetter = (int) Letter; //Calculate EncDigit
    NumLetter += KeyLenth;
    if(NumLetter > 57) NumLetter = (NumLetter % 57) + 47;
    printf("%c", NumLetter);
}
