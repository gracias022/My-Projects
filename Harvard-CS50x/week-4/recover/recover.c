// a program that recovers JPEGs from a forensic image
// accepts exactly one command-line argument, otherwise it should remind the user of correct usage,
// and main should return 1 If forensic image cannot be opened for reading, program should inform
// the user and main should return 1. The files you generate should each be named ###.jpg, where ###
// is a three-digit decimal number, starting with 000 for the first image and counting up. Your
// program, if it uses malloc, must not leak any memory.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512]; // array name contains the address of the first element of the array
    FILE *img = NULL;
    char filename[8];
    int counter = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512) // recall: fread returns the number of bytes it has
                                               // read file pointer will automatically advance to
                                               // the next unread data when you call fread again
    {
        // Create JPEGs from the data
        // Thanks to FAT, you need only look for those signatures in a block’s first four bytes.

        // if start of new JPEG (0xff, 0xd8, 0xff, 0xe_)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // create or open new JPEG
            if (img != NULL)
            {
                // close the old file
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter); // generate filename
            img = fopen(filename, "w");             // open new file
            fwrite(buffer, sizeof(uint8_t), 512, img);
            counter++;
        }

        else
        {
            // if already found JPEG
            if (img)
            {
                fwrite(buffer, sizeof(uint8_t), 512, img);
            }
        }
    }

    // close any remaining files
    if (img != NULL)
    {
        fclose(img); // only apply fclose on img if img was pointing to a file
    }
    fclose(card); // close forensic image

    return 0;
}
