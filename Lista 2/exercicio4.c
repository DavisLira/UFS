#include <stdio.h>

void converteParaFahrenheit(float C, float *F) {
    *F = (C * 9/5) + 32;
}

void converteParaKelvin(float C, float *K) {
    *K = C + 273.15;
}

int main() {
    float Celsius, Fahrenheit, Kelvin;

    printf("Digite a temperatura em Celsius: ");
    scanf("%f", &Celsius);

    converteParaFahrenheit(Celsius, &Fahrenheit);
    converteParaKelvin(Celsius, &Kelvin);

    printf("%.2f°C equivale a %.2f°F e a %.2fK\n\n", Celsius, Fahrenheit, Kelvin);

    return 0;
}