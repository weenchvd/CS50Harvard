#include <stdio.h>
#include <stdint-gcc.h>
#include <stdbool.h>

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#define QUANTITYDIGIT 6

const char FileNamePrefix[] = "RestoredFile-";
const char FileNamePostfix[] = ".jpg";

typedef uint8_t BYTE;

typedef union
{
    char Letter;
    int LetterNumber;
} FILECOUNTER;

bool WriteRestoredFile(FILE *, BYTE *, BYTE *, char *, int);
void IncreaseFileNameCounter(char *, FILECOUNTER *, int);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Use ./recover infile\n");
        return 1;
    }

    int Counter = 1;
    char * Pntr_Infile = argv[1];

    FILE * Pntr_FO = fopen(Pntr_Infile, "r");
    if(Pntr_FO == NULL)
    {
        fprintf(stderr, "File %s does not open\n", Pntr_Infile);
        return 2;
    }

    //создание имени файла со счетчиком в названии
    FILECOUNTER Union_FileCounter[QUANTITYDIGIT];
    FILECOUNTER * Pntr_Union_FileCounter = Union_FileCounter;
    for(int x = 0; x < QUANTITYDIGIT; x++)
    {
        (*(Pntr_Union_FileCounter+x)).LetterNumber = 48;
    }
    Union_FileCounter[QUANTITYDIGIT-1].LetterNumber = 49;

    int q1 = (sizeof(FileNamePrefix) / sizeof(FileNamePrefix[0])) - 1;
    int q2 = (sizeof(FileNamePostfix) / sizeof(FileNamePostfix[0])) - 1;
    char FileName[q1+QUANTITYDIGIT+q2];
    char * Pntr_FileName = FileName;

    for(int y = 0; y < q1; y++)
    {
        FileName[y] = FileNamePrefix[y];
    }
    for(int t = q1, f = 0; t < (q1 + QUANTITYDIGIT); t++, f++)
    {
        FileName[t] = (*(Pntr_Union_FileCounter+f)).Letter;
    }
    for(int m = (q1 + QUANTITYDIGIT), n = 0; m < (q1 + QUANTITYDIGIT + q2); m++, n++)
    {
        FileName[m] = FileNamePostfix[n];
    }


    BYTE TempStor;
    BYTE * Pntr_TempStor = &TempStor;
    while(fread(Pntr_TempStor, sizeof(BYTE), 1, Pntr_FO) != EOF)
    {
        if(* Pntr_TempStor == 0xFF)
        {
            BYTE TempStorMassive[4] = {0xFF};
            BYTE * Pntr_TempStorMassive = TempStorMassive;

            for(int i = 0; i < 3; i++)
            {
                fread((Pntr_TempStorMassive + i + 1), sizeof(BYTE), 1, Pntr_FO);
            }

            if(TempStorMassive[1] == 0xD8 && TempStorMassive[2] == 0xFF &&
               TempStorMassive[3] >= 0xE0 && TempStorMassive[3] <= 0xEF)
            {
                if(WriteRestoredFile(Pntr_FO, Pntr_TempStor, Pntr_TempStorMassive, Pntr_FileName, Counter))
                {
                    IncreaseFileNameCounter(Pntr_FileName, Pntr_Union_FileCounter, q1);
                    Counter++;
                }
                else
                {
                    fclose(Pntr_FO);
                    return 3;
                }
            }
        }
    }
    printf("End of source. Files restored.\n");
    return 0;
}

bool WriteRestoredFile(FILE * Pntr_FO, BYTE * Pntr_TempStor, BYTE * Pntr_TempStorMassive, char * Pntr_FileName, int Counter)
{
    FILE * Pntr_FW = fopen(Pntr_FileName, "w");
    if(Pntr_FW == NULL)
    {
        fclose(Pntr_FO);
        fprintf(stderr, "File \"%s\" does not create\n", Pntr_FileName);
        return false;
    }

    for(int i = 0; i < 4; i++)
    {
        fwrite((Pntr_TempStorMassive + i), sizeof(BYTE), 1, Pntr_FW);
    }

    while(fread(Pntr_TempStor, sizeof(BYTE), 1, Pntr_FO) != EOF)
    {
        fwrite(Pntr_TempStor, sizeof(BYTE), 1 , Pntr_FW);
        if(* Pntr_TempStor == 0xFF)
        {
            if(fread(Pntr_TempStor, sizeof(BYTE), 1, Pntr_FO) != EOF)
            {
                fwrite(Pntr_TempStor, sizeof(BYTE), 1 , Pntr_FW);
                if(* Pntr_TempStor == 0xD9)
                {
                    fclose(Pntr_FW);
                    return true;
                }
            }
            else
            {
                fclose(Pntr_FW);
                fprintf(stderr, "Error: File does not create! End of source.\n");
                return false;
            }
        }
    }

    fclose(Pntr_FW);
    fprintf(stderr, "Error: File does not create! End of source.\n");
    return false;
}

void IncreaseFileNameCounter(char * Pntr_FileName, FILECOUNTER * Pntr_Union_FileCounter, int q1)
{
    (*(Pntr_Union_FileCounter+q1+QUANTITYDIGIT-1)).LetterNumber++;
    for(int s = (q1 + QUANTITYDIGIT - 1); s > (q1 - 1); s--)
    {
        if((*(Pntr_Union_FileCounter+s)).LetterNumber > 57)
        {
            if((Pntr_Union_FileCounter + s) == (Pntr_Union_FileCounter + q1))
            {
                fprintf(stderr, "The file counter was full and zeroed.\n");
                for(int x = 0; x < QUANTITYDIGIT; x++)
                {
                    (*(Pntr_Union_FileCounter+x)).LetterNumber = 48;
                }
                (*(Pntr_Union_FileCounter+QUANTITYDIGIT-1)).LetterNumber = 49;
            }
            else
            {
                (*(Pntr_Union_FileCounter+s)).LetterNumber = 48;
                (*(Pntr_Union_FileCounter+s-1)).LetterNumber++;
            }
        }
    }

    for(int t = q1, f = 0; t < (q1 + QUANTITYDIGIT); t++, f++)
    {
        *(Pntr_FileName+t) = (*(Pntr_Union_FileCounter+f)).Letter;
    }
}
