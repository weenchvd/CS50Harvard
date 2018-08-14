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

typedef uint8_t BYTE;

bool WriteRestoredFile(FILE *, BYTE *, int);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Use ./recover infile\n");
        return 1;
    }

    int Counter = 1;
    //int * Pntr_Counter = &Counter;
    char * Pntr_Infile = argv[1];

    FILE * Pntr_FO = fopen(Pntr_Infile, "r");
    if(Pntr_FO == NULL)
    {
        fprintf(stderr, "File %s does not open\n", Pntr_Infile);
        return 2;
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
                if(WriteRestoredFile(Pntr_FO, Pntr_TempStor, Counter));
                {
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
}

bool WriteRestoredFile(FILE * Pntr_FO, BYTE * Pntr_TempStor, int Counter)
{
    char NameFile[] = "RestoredFile-";
    char Extension[] = ".jpg";

    FILE * Pntr_FW = fopen(NameFile(Counter)Extension, "w");
    if(Pntr_FW == NULL)
    {
        fclose(Pntr_FO);
        fprintf(stderr, "File %s%d%s does not create\n", NameFile, Counter, Extension);
        return false;
    }

    while(1)
    {
        fread(Pntr_TempStor, sizeof(BYTE), 1, Pntr_FO);
        fwrite(Pntr_TempStor, sizeof(BYTE), 1 , Pntr_FW);
        if(* Pntr_TempStor == 0xFF)
        {
            fread(Pntr_TempStor, sizeof(BYTE), 1, Pntr_FO);
            if(* Pntr_TempStor == 0xD9)
            {
                fwrite(Pntr_TempStor, sizeof(BYTE), 1 , Pntr_FW);
                fclose(Pntr_FW);
                return true;
            }
            fwrite(Pntr_TempStor, sizeof(BYTE), 1 , Pntr_FW);
        }
    }
}
