#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

bool FuncCountColor(RGBTRIPLE * pntr_strt_TempTriple, RGBTRIPLE * pntr_strt_TriplePixel[], int ColorCntr);

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

    RGBTRIPLE strt_TriplePixel[1000] = {0xFF, 0xFF, 0xFF};
    int ColorCounter = 1;

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

            if(FuncCountColor(&strt_TempTriple, &strt_TriplePixel, ColorCounter))
            {
                ColorCounter++;
                strt_TriplePixel[ColorCounter-1] = strt_TempTriple;
            }

            if(strt_TempTriple.rgbtBlue == 0x0 && strt_TempTriple.rgbtGreen == 0x0 && strt_TempTriple.rgbtRed == 0xFF)
            {
                fwrite(&strt_TriplePixel[1], sizeof(RGBTRIPLE), 1, outptr);
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

    printf("Number of colors is %d", ColorCounter);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

bool FuncCountColor(RGBTRIPLE * pntr_strt_TempTriple, RGBTRIPLE * pntr_strt_TriplePixel[], int ColorCntr)
{
    for(int c = 0; c < ColorCntr; c++)
    {
        if ((* pntr_strt_TempTriple).rgbtBlue == (* pntr_strt_TriplePixel[c]).rgbtBlue &&
                (* pntr_strt_TempTriple).rgbtGreen == (* pntr_strt_TriplePixel[c]).rgbtGreen &&
                (* pntr_strt_TempTriple).rgbtRed == (* pntr_strt_TriplePixel[c]).rgbtRed)
        {
            return false;
        }
    }
    return true;
}
