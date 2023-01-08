#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long l = get_long("cc no.: ");

    int odd = 0;
    int last_odd;
    int even = 0;
    int last_even;
    int turn = 0;

    int last;
    int second_last;
    bool valid_cs = true;
    bool valid = false;

    // keep getting last digit and adding to even and odd for checking against checksum
    while (l != 0)
    {
        int remain = l % 10;
        if (turn % 2 == 0)
        {
            last_even = remain;
            even += remain;
        }
        else
        {
            last_odd = remain;
            remain *= 2;
            if (remain >= 10)
            {
                odd += remain % 10;
                remain = remain / 10;
            }
            odd += remain;
        }
        l = l / 10;
        turn += 1;
    }

    // check if valid checksum
    if ((odd + even) % 10 != 0)
    {
        valid_cs = false;
    }

    // get 1st 2 digits
    if (turn % 2 == 0)
    {
        last = last_odd;
        second_last = last_even;
    }
    else
    {
        last = last_even;
        second_last = last_odd;
    }

    // check if amex
    if (valid_cs && turn == 15 && last == 3 && (second_last == 4 || second_last == 7))
    {
        printf("AMEX\n");
        valid = true;
    }

    // check if mastercard
    bool valid_mc_last_digit = second_last == 1 || second_last == 2 || second_last == 3 || second_last == 4 || second_last == 5;
    if (valid_cs && turn == 16 && last == 5 && valid_mc_last_digit)
    {
        printf("MASTERCARD\n");
        valid = true;
    }

    // check if visa
    if (valid_cs && (turn == 13 || turn == 16) && last == 4)
    {
        printf("VISA\n");
        valid = true;
    }

    if (!valid)
    {
        printf("INVALID\n");
    }
}