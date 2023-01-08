#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string s = get_string("Text: ");
    float letters = count_letters(s);
    float words = count_words(s);
    float sentences = count_sentences(s);

    float L = letters / words * 100.0;
    float S = sentences / words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // printf("%f letters\n", letters);
    // printf("%f words\n", words);
    // printf("%f sentences\n", sentences);
    // printf("%f S\n", S);
    // printf("%f L\n", L);
    // printf("index = %f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %g\n", round(index));
    }
}

int count_letters(string text)
{
    int length = strlen(text);
    int letters = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int length = strlen(text);
    int words = 1;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int length = strlen(text);
    int sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

