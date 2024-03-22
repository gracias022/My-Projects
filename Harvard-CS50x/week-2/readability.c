#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
    //  If grade level is 16 or higher, program should output “Grade 16+”.
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // If grade level is less than 1, program should output “Before Grade 1”.
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    int lettercount = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            lettercount++;
        }
    }
    return lettercount;
}

int count_words(string text)
{
    // Return the number of words in text
    int wordcount = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            wordcount++;
        }
    }
    // add the last word of the input
    return ++wordcount;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int sentcount = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        switch (text[i])
        {
            case '.':
            case '?':
            case '!':
                sentcount++;
                break;
        }
    }
    return sentcount;
}
