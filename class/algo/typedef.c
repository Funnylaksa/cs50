#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    person people[2];

    people[0].name = "EMMA";
    people[0].number = "+1-617-495-1000";

    people[1].name = "RODRIGO";
    people[1].number = "+1-949-468-2750";

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "EMMA") == 0)
        {
            printf("%s", people[i].number);
        }
    }
}
