#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // intake key
    // check if input are two arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv [0]);
        return 1;
    }

    //verify that argv is an int
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: %s key\n", argv [0]);
            return 1;
        }
    }
    //changing character to integer
    int k = atoi(argv[1]);
    //prompting user for plaintekst
    string s = get_string("plaintekst: ");
    printf("ciphertext: ");
    // adding the key per char
    char c[strlen(s)];
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //checking if char is lower or upper and adding the key
        if islower(s[i])
        {
            printf("%c", (((s[i] + k) - 97) % 26) + 97);
        }
        else if isupper(s[i])
        {
            printf("%c", (((s[i] + k) - 65) % 26) + 65);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    // end of program
    printf("\n");
    return 0;    

}
