#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{

    // ensure one command-line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: name of forensic image \n");
        return 1;
    }
    //assinging variable to input
    char* forensic_image = argv[1];
    // open input file
    FILE *inptr = fopen(forensic_image, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", forensic_image);
        return 2;
    }


    //variable buffer to store the read information
    unsigned char buffer [512];
    //variable to store the filename
    char filename [8];
    //variable for the image count
    int imageCount = 0;
    // set outptr to null
    FILE *outptr = NULL;

    // running until end of file (!feof(inptr))
    while (fread(buffer, 512, 1, inptr))
    {

        //reading file
        //fread(buffer, 512, 1, inptr);
        //if begining of a jpeg
        if (buffer [0] == 0xff && buffer [1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close image file if one has been created
            if (imageCount > 0)
            {
                fclose(outptr);
            }

            //make a name
            sprintf(filename, "%03d.jpg", imageCount);
            //open file
            outptr = fopen(filename, "w");
            imageCount++;
        }
        //write until there is nothing to write
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
        if (inptr == NULL)
        {
            fprintf(stderr, "Could not create %d.\n", imageCount);
            return 3;
        }
    }

    // close last jpeg file
    fclose(outptr);

    // close infile
    fclose(inptr);

    // success
    return 0;

}
