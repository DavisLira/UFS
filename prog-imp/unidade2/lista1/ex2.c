// Loja do sr. ze com 10% de juros / mes no credito em ate 10x

#include <stdio.h>

void calculaJuros(float valor, int mes, float *juros, float *total) {
    *juros = valor * 0.1 * mes;
    *total = valor + *juros;
}

int main() {
    float valorCompra, juros, total;

    printf("Digite o valor da compra: R$");
    scanf("%f", &valorCompra);

    if(valorCompra > 300) {
        printf("Voce pode parcelar a compra em ate 10x as parcelas sao: \n");

        for (int mes = 1; mes < 11; mes++)
        {
        
            calculaJuros(valorCompra, mes, &juros, &total);
            
            if (mes == 1) {
                printf("Pagamento em %d mes - Juros: R$%.2f - Total: R$%.2f - parcela 1x R$%.2f\n", mes, juros, total, total/mes);
            } else {
                printf("Pagamento em %d meses - Juros: R$%.2f - Total: R$%.2f - parcela %dx R$%.2f\n", mes, juros, total, mes, total/mes);
            }
            
        }
        
    } else {
        printf("A compra nao pode ser parcelada!\n");
    }

    printf("\n");

    return 0;
}
