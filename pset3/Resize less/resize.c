// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage 4 inputs necasary: n, infile, outfile
    if (argc != 4)
    {
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // check if input n is a positive integer 0 to 100
    if (n >= 100 || n < 0)
    {
        fprintf(stderr, "%d is not within peremiters\n ", n);
        return 4;
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

    //determine new dimensions
    int Oldwidth = bi.biWidth;
    int Oldheight = bi.biHeight;
    int Newwidth = Oldwidth * n;
    int Newheight = Oldheight * n;

    //determine new padding
    int inPadding = (4 - (Oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (Newwidth * sizeof(RGBTRIPLE) % 4)) % 4;

    //adjusting headers
    bi.biWidth = Newwidth;
    bi.biHeight = Newheight;
    bi.biSizeImage = ((Newwidth * sizeof(RGBTRIPLE)) + outPadding) * abs(Newheight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(Oldheight); i < biHeight; i++)
    {
        //we need to write each line n times we use for loop for this vertically
        for (int j = 0 ; j < n; j++)
        {

            // iterate over pixels in scanline
            for (int g = 0; g < Oldwidth; g++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile for scale times
                for (int s = 0; s < n; s++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding, if any
            fseek(inptr, inPadding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }
            // move pointer to the beginning of the scanline because we need to write the line again
            //size of move is pixels * width + padding
            fseek(inptr, -((sizeof(RGBTRIPLE)*Oldwidth) + inPadding), SEEK_CUR);

        }
        //move the pointer forward to the next scan line, because we just moved it back in the forloop above this.
        fseek(inptr, (Oldwidth * sizeof(RGBTRIPLE)) + inPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;


}
