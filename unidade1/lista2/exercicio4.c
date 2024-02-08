#include <stdio.h>

/*
    Código que converte a temperatura de Celsius
    para Fahrenheit e Kelvin
*/

void converteParaFahrenheit(float C, float *F) {
    *F = (C * 9/5) + 32; // Função para converter celsius em fahrenheit
}

void converteParaKelvin(float C, float *K) {
    *K = C + 273.15; // Função para converter celsius em kelvin
}

int main() {
    float Celsius, Fahrenheit, Kelvin; // Variáveis

    printf("Digite a temperatura em Celsius: "); // Salva a temperatura em celsius
    scanf("%f", &Celsius);

    converteParaFahrenheit(Celsius, &Fahrenheit); // Converte para Fahrenheit e salva o valor
    converteParaKelvin(Celsius, &Kelvin); // Converte para Kelvin e salva o valor

    // Mostra os valores
    printf("%.2f°C equivale a %.2f°F e a %.2fK\n\n", Celsius, Fahrenheit, Kelvin);

    return 0;
}