// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r"); // fopen returns a pointer to a file
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(
        argv[3]); // atof() converts a character string to a double-precision floating-point value.

    // TODO: Copy header from input file to output file
    // WAV file begins with a header that's always exactly 44 bytes long
    uint8_t header[HEADER_SIZE]; // HEADER_SIZE = number of bytes in the header (alr defined before)
                                 //  Name of array A is a constant pointer to the first element of
                                 //  the array
    fread(header, HEADER_SIZE, 1, input); // header is an address
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // Create a buffer for a single sample
    int16_t buffer;
    // Read single sample into buffer
    // int16_t is a type that stores a 16-bit signed (positive/ negative) integer
    // We can treat each sample of audio in a WAV file as an int16_t value.
    while (fread(&buffer, sizeof(int16_t), 1,
                 input)) // fread will return the number of items of data successfully read.
    {
        // update volume of sample
        buffer *= factor;

        // Write updated sample to new file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
