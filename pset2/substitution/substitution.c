#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

    string substitution = argv[1];

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(substitution) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    if (strlen(substitution) == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            char c = substitution[i];
            if (isalpha(c) == 0)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
    }

    if (strlen(substitution) == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = i + 1; j < 26; j++)
            {
                if (substitution[i] == substitution[j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }

    
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            int idx;
            if (islower(c))
            {
                idx = c - 'a';
                printf("%c", tolower(substitution[idx]));
            }
            else
            {
                idx = c - 'A';
                printf("%c", toupper(substitution[idx]));
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}