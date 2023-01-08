#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    string s = "HI!";

    int * n = malloc(sizeof(int));
    *n = 50;
    printf("%p %p %i \n", n, &n, *n);

    int k = 5;
    int *pk;
    pk = &k;
    printf("%i %p\n", k, &k);
    printf("%i %p\n", *pk, &pk);

    // pk follows k's value change
    k = 20;
    printf("%i %p\n", k, &k);
    printf("%i %p\n", *pk, &pk);

    // printf("%p %c\n", &s[0], s[0]);
    // printf("%p %c\n", &s[1], s[1]);
    // printf("%p %c\n", &s[2], s[2]);
    // printf("%p %c\n", &s[3], s[3]);
    // printf("%p %c\n", &s[4], s[4]);
    // printf("%p %c\n", &s[5], s[5]);

    // for (int i = 0; i < 30; i++)
    // {
    //     printf("%p %c\n", &s[i], s[i]);
    // }
}