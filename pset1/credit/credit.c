#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool card_validation (long);
long first_n_digits (long, int);
int length (long);


int main(void)
{

    long n;

    do
    {
        n = get_long_long("Credit card number: ");
    }
    while (n < 1);


    // do calc for credit card validation
    if (card_validation(n))
    {
        switch(first_n_digits(n,2))
        {

            case 34:
            case 37:
                printf("AMEX\n");
                break;

            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                printf("MASTERCARD\n");
                break;

            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
                printf("VISA\n");
                break;

            default :
                printf("INVALID\n");
        }
    }

    else printf("INVALID\n");

    return 0;
}


bool card_validation (long n)
    {

        long n_working = n;
        int checksum = 0;
        int l = length(n);

        // check card length
        if (!(l == 13 || l == 15 || l == 16))
            return false;

        // checksum calc
        for (int i = 0; i < l; i++)
        {

            // if first, third, fith, etc digit
            if (i % 2 == 0)
            {
                // get last digit
                checksum += n_working % 10;

                // remove last digit
                n_working /= 10;
            }

            // if second, forth, sixth, etc digit
            else
            {
                // get last digit and multiply by 2 (if last digit is less than 5)
                if (n_working % 10 < 5)
                    checksum += 2 * (n_working % 10);

                // get last digit and multiply by 2 and figure out individual digits (if last digit is greater than 5)
                else checksum += 1 + (2 * (n_working % 10)) % 10;

                // remove last digit
                n_working /= 10;
            }
        }

        if (checksum % 10 == 0)
            return true;

        else return false;

    }


long first_n_digits (long n, int l)
{
    int n_digits = length(n);

    long first_digits = n / ((long) pow(10,(n_digits - l)));

    return first_digits;

}

int length (long n)
{
    return floor(log10(n)) + 1;
}