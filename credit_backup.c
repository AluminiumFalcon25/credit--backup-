#include <cs50.h>
#include <stdio.h>

long get_ccn(void);
long luhn_algo(long ccn);

int main(void)
{
    long ccn = get_ccn();
    long result = luhn_algo(ccn);
    printf("result is %lu\n", result);
    if (((ccn >= 4000000000000 && ccn <= 4999999999999) || (ccn >= 4000000000000000 && ccn <= 4999999999999999)) && (result % 10 == 0))
    {
        printf("VISA\n");
    }
    else if ((ccn >= 5100000000000000 && ccn <= 5599999999999999) && (result % 10 == 0))
    {
        printf("MASTERCARD\n");
    }
    else if (((ccn >= 340000000000000 && ccn <= 349999999999999) || (ccn >= 370000000000000 && ccn <= 379999999999999)) && (result % 10 == 0))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_ccn(void)
{
    long ccn;
    do
    {
        ccn = get_long("Enter Number: ");
    }
    // while (ccn < 1000000000000 || ccn > 5599999999999999); I would use this line to keep asking if the number was not in peramaters, however, to pass the CS 50 tests I need to allow additional wrong numbers to produce an "invalid" result
    while (ccn < 0);
    printf("CCN is %lu\n", ccn);
    return ccn;
}

long luhn_algo(long ccn)
{
    int even;               /* for the calc of the even digits of ccm*/
    int even_luhn = 0;      /* sb the even digit * 2 and then the sum of the products digits*/
    int even_luhn_sum = 0;  /* sb the sum of all the evens for the final test*/
    int odd = 0;            /* var for the odd digits of i in the loop*/
    int odd_sum = 0;        /* sum of all odd digits in ccm*/
    int final_test_sum = 0; /* sum of all even and odd for final testing*/
    for (int i = 1; ccn > 1; i++)
    {
        even_luhn = 0; /* This needs to be reset to zero for each part of the loop or it will add the last calculated value to even_luhn_sum
        on odd values of i*/
        odd = 0;       /* same as above for even_luhn*/
        if (i % 2 == 0)
        {
            even = ccn % 10;
            // multiplies the even digit by 2 and then adds the digit of the result - Example - 6 * 2 = 12 and 1 + 2 = 3 so final result would be 3
            even_luhn = (even * 2 / 10) + ((even * 2) % 10);
            // printf("even_luhn is now %i\n", even_luhn);
            // This will drop the even digit off for the next loop so that eventually we will run through all the numbers
            ccn = ccn / 10;
            // printf("ccn after even loop is now %lu\n", ccn);
        }
        else
        {
            odd = ccn % 10;
            // printf("odd value is now %i\n", odd);
            ccn = ccn / 10;
            // printf("ccn after odd loop is now %lu\n", ccn);
        }

        even_luhn_sum += even_luhn;
        // printf("even_luhn_sum is now %i\n", even_luhn_sum);
        odd_sum += odd;
        // printf("odd_sum is now %i\n", odd_sum);
    }
    return even_luhn_sum + odd_sum;
}
// I copied this from cs50.h to see if this would work without the c dir.
long get_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get a long from user
    while (true)
    {
        // Get line of text, returning LONG_MAX on failure
        string line = get_string(&ap, format);
        if (line == NULL)
        {
            va_end(ap);
            return LONG_MAX;
        }

        // Return a long if only a long (in range) was provided
        if (strlen(line) > 0 && !isspace((unsigned char)line[0]))
        {
            char *tail;
            errno = 0;
            long n = strtol(line, &tail, 10);
            if (errno == 0 && *tail == '\0' && n < LONG_MAX)
            {
                va_end(ap);
                return n;
            }
        }
    }
}