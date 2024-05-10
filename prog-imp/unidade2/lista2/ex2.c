#include <stdio.h>
#include <ctype.h>

int main()
{
    char palavra[21];

    printf("Digite uma palavra de no maximo 20 caracteres: \n");
    scanf(" %20[^\n]s",palavra);
    // fgets(palavra, 20, stdin);
    
    for (int i = 0; i < 20; i++)
    {
        palavra[i] = tolower(palavra[i]);
    }

    palavra[0] = toupper(palavra[0]);
    
    printf("%s\n", palavra);
    
    return 0;
}