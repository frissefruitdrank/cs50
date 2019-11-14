#include <cs50.h>
#include <stdio.h>
#include <math.h>

float input_float();
int main(void)
{
     int i = round(input_float("Change owed: ") * 100);
    int j = 0;
    int t = i;
    for ( int h = t ; t >= 25; t = t - 25)
    {
        j = j +1 ;
     }
    for ( int g = t  ; t >= 10; t = t - 10)
    {
        j = j +1 ;
     }
    for ( int g = t  ; t >= 5; t = t - 5)
    {
        j = j +1 ;
     }
    for ( int g = t  ; t >= 1; t = t-1)
    {
        j = j +1 ;
     }
   printf("%d\n",j);
}

float input_float(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    while (n <= 0);
    return n;
}
