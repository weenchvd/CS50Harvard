#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

typedef struct
{
    int counter;
    BYTE  BLUE;
    BYTE  GREEN;
    BYTE  RED;
} COLORS;

bool FuncCountColor(RGBTRIPLE *, COLORS *, int);
void InsertionSorting(COLORS *, int);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    RGBTRIPLE strt_TripleWhitePixel = {0xFF, 0xFF, 0xFF};
    //RGBTRIPLE strt_TripleBlackPixel = {0x0, 0x0, 0x0};
    RGBTRIPLE strt_Blackout = {0x1F, 0x1F, 0x1F};
    COLORS strt_col_massive[1000] = {0, 0, 0, 0};
    COLORS * pntr_strt_col_massive = strt_col_massive;
    int ColorCounter = 0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE strt_TempTriple;

            // read RGB strt_TempTriple from infile
            fread(&strt_TempTriple, sizeof(RGBTRIPLE), 1, inptr);

            if(FuncCountColor(&strt_TempTriple, pntr_strt_col_massive, ColorCounter))
            {
                strt_col_massive[ColorCounter].RED = strt_TempTriple.rgbtRed;
                strt_col_massive[ColorCounter].GREEN = strt_TempTriple.rgbtGreen;
                strt_col_massive[ColorCounter].BLUE = strt_TempTriple.rgbtBlue;
                strt_col_massive[ColorCounter].counter++;
                ColorCounter++;
            }

            if(strt_TempTriple.rgbtBlue == 0x0 && strt_TempTriple.rgbtGreen == 0x0 && strt_TempTriple.rgbtRed == 0xFF)
            {
                fwrite(&strt_TripleWhitePixel, sizeof(RGBTRIPLE), 1, outptr);
            }
            else if(strt_TempTriple.rgbtRed < 0xFF)
            {
                strt_TempTriple.rgbtRed = strt_TempTriple.rgbtRed - strt_Blackout.rgbtRed;
                //strt_TempTriple.rgbtGreen = strt_TempTriple.rgbtGreen - strt_Blackout.rgbtGreen;
                //strt_TempTriple.rgbtBlue = strt_TempTriple.rgbtBlue - strt_Blackout.rgbtBlue;
                fwrite(&strt_TempTriple, sizeof(RGBTRIPLE), 1, outptr);
            }
            else fwrite(&strt_TempTriple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    InsertionSorting(pntr_strt_col_massive, ColorCounter);

    printf("Quantity of colors is %d\n", ColorCounter);

    for(int c = 0; c < ColorCounter; c++)
    {
        printf("Color RGB: %2X %2X %2X\tQuantity of pixels: %6d\n",
               strt_col_massive[c].RED, strt_col_massive[c].GREEN, strt_col_massive[c].BLUE, strt_col_massive[c].counter);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

bool FuncCountColor(RGBTRIPLE * pntr_strt_TempTriple, COLORS * pntr_strt_col_massive, int ColorCntr)
{
    for(int c = 0; c <= ColorCntr; c++)
    {
        if ((* pntr_strt_TempTriple).rgbtBlue == (* (pntr_strt_col_massive+c)).BLUE &&
                (* pntr_strt_TempTriple).rgbtGreen == (* (pntr_strt_col_massive+c)).GREEN &&
                (* pntr_strt_TempTriple).rgbtRed == (* (pntr_strt_col_massive+c)).RED)
        {
            (* (pntr_strt_col_massive+c)).counter++;
            return false;
        }
    }
    return true;
}

void InsertionSorting(COLORS * pntr_strt_col_massive, int ColorCntr)
{
    for(int i = 1; i < ColorCntr; i++)
    {
        for(int s = (i - 1); s >= 0; s--)
        {
            if((* (pntr_strt_col_massive+s+1)).counter < (* (pntr_strt_col_massive+s)).counter)
            {
                COLORS tmp = * (pntr_strt_col_massive+s+1);
                * (pntr_strt_col_massive+s+1) = * (pntr_strt_col_massive+s);
                * (pntr_strt_col_massive+s) = tmp;
            }
            else(s = -1);
        }
    }
}
