#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

bool FuncCountColor(RGBTRIPLE *, struct colors *, int ColorCntr);

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
    RGBTRIPLE strt_TripleBlackPixel = {0x0, 0x0, 0x0};
    //RGBTRIPLE strt_TriplePixel[1000] = {0x0, 0x0, 0x0};
    //RGBTRIPLE * pntr_strt_TriplePixel = strt_TriplePixel;
    struct colors
    {
        int counter;
        int RED;
        int GREEN;
        int BLUE;
    };
    struct colors strt_col_massive[1000] = {0, 0, 0, 0};
    struct colors * pntr_strt_col_massive = strt_col_massive;
    //int MassiveColorCounter[1000] = {0};
    //int * pntr_MassiveColorCounter = MassiveColorCounter;
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

            if(FuncCountColor(&strt_TempTriple, pntr_strt_col_massive, ColorCounter)
            {
                ColorCounter++;
                pntr_strt_col_massive[ColorCounter-1].RED = strt_TempTriple.rgbtRed;
                pntr_strt_col_massive[ColorCounter-1].GREEN = strt_TempTriple.rgbtGreen;
                pntr_strt_col_massive[ColorCounter-1].BLUE = strt_TempTriple.rgbtBlue;
            }

            if(strt_TempTriple.rgbtBlue == 0x0 && strt_TempTriple.rgbtGreen == 0x0 && strt_TempTriple.rgbtRed == 0xFF)
            {
                fwrite(&strt_TripleWhitePixel, sizeof(RGBTRIPLE), 1, outptr);
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

    printf("Number of colors is %d\n", ColorCounter);

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

bool FuncCountColor(RGBTRIPLE * pntr_strt_TempTriple, struct colors * pntr_strt_col_massive, int ColorCntr)
{
    for(int c = 0; c <= ColorCntr; c++)
    {
        if ((* pntr_strt_TempTriple).rgbtBlue == (* (pntr_strt_col_massive+c)).BLUE &&
                (* pntr_strt_TempTriple).rgbtGreen == (* (pntr_strt_col_massive+c)).GREEN &&
                (* pntr_strt_TempTriple).rgbtRed == (* (pntr_strt_col_massive+c)).RED)
        {
            (* (pntr_strt_col_massive + c)).counter++;
            return false;
        }
    }
    return true;
}
