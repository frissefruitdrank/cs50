#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
int main(int argc, string argv[])
{
    //intake key
    if (argc != 2)
    {
        printf("Usage: ./vignere keyword\n");
        return 1;
    }
    //interate trough key char to see if it are letters if it is a number the program stops
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./vignere keyword\n");
            return 1;
        }
    }


    //getting plaintekst from user 
    string plaintext = get_string("plaintekst: ");

    
    //letting now the ciphertext is being printed next
    printf("ciphertext: ");
    //iterate trough plain tekst and adding the key and printing ciphertext
    for (int i = 0, j = 0, n = strlen(plaintext); i < n ; i++)
    {
        int key;
        
        //assining shift function to key
   
        key = shift(argv[1][j % strlen(argv[1])]);
        
        //checking if char is lower or upper and adding the key
        //returning cipher text
        if islower(plaintext[i])
        {
            printf("%c", (((plaintext[i] + key) - 97) % 26) + 97);
            j++;
        }
        else if isupper(plaintext[i])
        {
            printf("%c", (((plaintext[i] + key) - 65) % 26) + 65);
            j++;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
              

    }
    //ending the program
    printf("\n");
    return 0;
    
    
}
//function to change the key to numbers 0 to 25
int shift(char c)  
{
    if (islower(c))
    {
        return (c - 97);
    }
    else if (isupper(c))
    {
        return (c - 65);
    }
    else 
    {
        return (c);
    }
}
