#include <cs50.h>
#include <stdio.h>

void print_fn(int cnt, char type);

int main(void)
{
    // get user input
    int x;
    do
    {
        x = get_int("Height: ");
    } while (x < 1 || x > 8);

    // for each row
    for (int i = 0; i < x; i++)
    {
        int space_cnt = x - i - 1;
        int hash_cnt = i + 1;

        // for each col
        print_fn(space_cnt, ' ');
        print_fn(hash_cnt, '#');
        print_fn(2, ' ');
        print_fn(hash_cnt, '#');
        printf("\n");
    }
}

void print_fn(int cnt, char type)
{
    for (int i = 0; i < cnt; i++)
    {
        printf("%c", type);
    }
}
