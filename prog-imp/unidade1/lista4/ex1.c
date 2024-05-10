#include <stdio.h>

int compras = 0;

void ValidaCompra(float *L){
  float D;
  printf("Debito: ");
  scanf("%f",&D);
  if (*L - D >= 0){
	printf("Compra possivel! \n");
	*L = *L - D;
    compras++;}
  else
	printf("Esta compra \"estourarah\" o cartao! \n");
  printf("Limite restante: %.2f \n\n",*L);}

int main(){
	float Limite;
	printf("Limite do cartao: ");
	scanf("%f",&Limite);
      while (Limite>0)
	  ValidaCompra(&Limite);
	printf("Seu limite de compras acabou!\n");
    printf("Voce fez %d compras\n", compras);
    return 0;
}
