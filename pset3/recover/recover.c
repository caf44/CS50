#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int jpegCounter = 0;
    int file_read_return = 0;
    char filename[] = "001.jpg";

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Create block of memory to store each block
    unsigned char buffer[512];

    // search through file until first jpeg header found
    do
    {
        fread(buffer, 512, 1, inptr);
    }
    while (!(buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0));

    printf("found first jpeg block\n");

    // Create a new jpeg file
    sprintf(filename, "%03i.jpg", jpegCounter);
    FILE *outptr = fopen(filename, "w");

    do
    {
        // write date to jpeg
        fwrite(buffer,512, 1, outptr);

        // read next block of file
        file_read_return = fread(buffer, 512, 1, inptr);

        // Check if block is jpeg header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("found a neww jpeg block\n");

            // Close previous JPEG
            fclose(outptr);

            // increment jpeg counter
            jpegCounter ++;

            // Create a new jpeg file
            sprintf(filename, "%03i.jpg", jpegCounter);
            outptr = fopen(filename, "w");

        }

    }
    while (file_read_return == 1); // not EOF;

    // close files
    fclose(inptr);
    fclose(outptr);

    return 0;

}
