// create a program that enables you to encrypt messages using a substitution cipher.
// At the time the user executes the program, they should decide, by providing a command-line
// argument, on what the key should be in the secret message they’ll provide at runtime.
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{

    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (argc != 2)
    {
        printf("Only one command-line argument should be provided.\n");
        return 1;
    }
    int checkalpha(string text);
    if (checkalpha(argv[1]) == 1)
    {
        return 1;
    }
    int len = strlen(argv[1]);
    if (len != 26)
    {
        printf("Key must contain 26 alphabetic characters.\n");
        return 1;
    }

    int checkduplicate(string text);
    if (checkduplicate(argv[1]) == 1)
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    // Copy plaintext to ciphertext
    char ciphertext[strlen(plaintext) + 1]; // Creating an array of characters from plaintext.
                                            // Allocate space for null terminator
    strcpy(ciphertext, plaintext);          // copy the contents of plaintext into ciphertext.
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] =
                    toupper(argv[1][plaintext[i] - 'A']); // ensure case remains unchanged
            }
            else
            {
                ciphertext[i] =
                    tolower(argv[1][plaintext[i] - 'a']); // ensure case remains unchanged
            }
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

int checkalpha(string text)
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            printf("Key must contain 26 alphabetic characters.\n");
            return 1;
        }
    }
    return 0;
}

// nested loop to find duplicates
// outer loop iterates till the second last char
int checkduplicate(string text)
{
    for (int i = 0, len = strlen(text); i < len - 1; i++)
    {
        int foundDuplicate = 0;
        // Compare with the rest of the characters
        for (int j = i + 1; j < len; j++)
        {
            if (text[i] == text[j])
            {
                foundDuplicate = 1;
                printf("Key must contain 26 distinct alphabetic characters.\n");
                return 1; // Stop searching once a duplicate is found
            }
        }
    }
    return 0;
}
