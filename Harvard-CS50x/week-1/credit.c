#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // prompt for input
    long number = get_long("Number: ");
    // calculate checksum
    int productdigits = 0;
    long number1 = number;
    while (number1 /= 10)
    {
        long digit = (number1 % 10) * 2;
        if (digit > 9)
        {
            digit = digit % 10 + digit / 10;
        }
        productdigits += digit;
        // while (digit)
        //{
        // productdigits += (digit % 10);
        // digit /= 10;
        //}
        number1 /= 10;
    }
    long number2 = number;
    while (number2)
    {
        // input % 10 gives the last digit
        productdigits += (number2 % 10);
        number2 /= 100;
    }
    int integerlength(long n);
    int first2digits(long n);
    if ((productdigits % 10) == 0)
    {
        if (integerlength(number) == 15 &&
            (first2digits(number) == 34 || first2digits(number) == 37))
        {
            printf("AMEX\n");
        }
        else if (integerlength(number) == 16 &&
                 (first2digits(number) >= 51 && first2digits(number) <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((integerlength(number) == 13 || integerlength(number) == 16) &&
                 ((first2digits(number) / 10) == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int integerlength(long n)
{
    int count = 0;
    do
    {
        n /= 10;
        count++;
    }
    while (n != 0);
    return count;
}
int first2digits(long n)
{
    n /= pow(10, integerlength(n) - 2);
    return n;
}
// calculate checksum look at final digit 0/not 0, valid card/not
// check for card length and starting digits
// All American Express numbers start with 34 or 37;
// most MasterCard numbers start with 51, 52, 53, 54, or 55
// all Visa numbers start with 4.
