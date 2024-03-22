//  a program that calculates the approximate grade level needed to comprehend some text.
// print as output “Grade X” where “X” is the grade level computed, rounded to the nearest integer
//  If grade level is 16 or higher, program should output “Grade 16+” instead of giving the exact
//  index number.
// If grade level is less than 1, program should output “Before Grade 1”.
// The Coleman-Liau index of a text is designed to output that (U.S.) grade level needed to
// understand some text. Formula: index = 0.0588 * L - 0.296 * S - 15.8 where L is the average
// number of letters per 100 words in the text, S is the average number of sentences per 100 words
// in the text.

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string Text = get_string("Text: ");
    int lettercount = 0;
    int wordcount = 0;
    int sentcount = 0;
    for (int i = 0, len = strlen(Text); i < len; i++)
    {
        if (isupper(Text[i]) || islower(Text[i]))
        {
            lettercount++;
        }
        if (Text[i] == ' ')
        {
            wordcount++;
        }
        switch (Text[i])
        {
            case '.':
            case '?':
            case '!':
                sentcount++;
                break;
        }
    }
    // add the last word of the input
    wordcount++;

    float L = ((float) lettercount / wordcount) * 100;
    float S = ((float) sentcount / wordcount) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
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
