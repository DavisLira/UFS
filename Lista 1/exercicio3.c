#include <stdio.h>

/*
    Código que mostra os anos das próximas 3 doses a serem tomadas
    de acordo com o ano da 1° dose e o intevalo entre as doses
*/

int main()
{
    // Declaração das variáveis
    int quantidade = 3; // Quantidade das doses que faltam a ser tomadas
    int ano, periodicidade;

    // Solicita o ano da 1° dose
    printf("Qual foi o ano da 1° dose? ");
    scanf("%d", &ano);

    // Solicita o intervalo entre as doses
    printf("Qual o intervalo entre as doses? ");
    scanf("%d", &periodicidade);

    // Mostra os proximos anos que irá tomar a vacina
    for (quantidade; quantidade > 0; quantidade--)
    {
        ano = ano + periodicidade;
        printf("%d\n", ano);
    }

    return 0;
}