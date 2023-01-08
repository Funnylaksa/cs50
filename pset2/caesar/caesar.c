#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    key = key % 26;
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int c = plaintext[i] + key;
            if (isupper(plaintext[i]))
            {
                if (c > 90)
                {
                    c = c - 26;
                }
            }
            else if (islower(plaintext[i]))
            {
                if (c > 122)
                {
                    c = c - 26;
                }
            }
            printf("%c", c);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}