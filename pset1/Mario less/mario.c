#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);
int main(void)
{
    int i = get_positive_int("Height: ");
    
    for (int j = 0; j < i; j++)
    {
        for (int g = i - 1 ; g > j; g--)
        {
            printf(" ");
        }
        printf("#");
        for (int h = 0; h < j ; h++)
        {
            printf("#");
        }
        printf("\n");
    }

}
// promt user for positive integer
int get_positive_int(string prompt)
{
    
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while ((n <= 0) || (n > 8));
    return n;

}
