#include <stdio.h>

int main(){
	float Meta, Doacao, Soma = 0;

	printf("Meta da vaquinha: ");
	scanf("%f",&Meta);
	
	do{
	  printf("Valor da doacao: ");
	  scanf("%f",&Doacao);
	  Soma = Soma + Doacao;
      printf("Valor arrecadado: %.2f\n\n", Soma);}
	while (Soma<Meta);

    if (Soma > Meta) {
        printf("A Meta foi ultrapassada em: %.2f\n", Soma - Meta);
    }

	printf("A meta da vaquinha foi alcancada!\n");

    return 0;
}