#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    unsigned int n = (unsigned int) atoi(argv[1]);
    if(n < 1 || n > 100)
    {
        printf("Use 'n' from 1 to 100");
        return 5;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

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

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int NewPadding = (4 - (bi.biWidth * n * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    bi.biSizeImage = ((DWORD) bi.biWidth * ((DWORD) abs(bi.biHeight)) * (DWORD) bi.biBitCount / 8) +
            (((DWORD) abs(bi.biHeight)) * (DWORD) NewPadding);
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight_origin = (abs(bi.biHeight) / n), biWidth_origin = (bi.biWidth / n); i < biHeight_origin; i++)
    {
        // temporary storage
        RGBTRIPLE strt_TempTripleStorMassive[biWidth_origin];
        RGBTRIPLE * pntr_strt_TempTripleStorMassive = strt_TempTripleStorMassive;

        for(int j = 0; j < biWidth_origin; j++)
        {
            // read RGB strt_TempTripleStor from infile
            fread((pntr_strt_TempTripleStorMassive + j), sizeof(RGBTRIPLE), 1, inptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        for(int s = 0; s < n; s++)
        {
            for(int f = 0; f < biWidth_origin; f++)
            {
                for(int t = 0; t < n; t++)
                {
                    // write RGB strt_TempTripleStor to outfile
                    fwrite((pntr_strt_TempTripleStorMassive + f), sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < NewPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    printf("Done!");
    return 0;
}
