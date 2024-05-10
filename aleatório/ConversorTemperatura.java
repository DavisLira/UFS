import java.util.Scanner;

public class ConversorTemperatura {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Conversor de Temperatura");
        System.out.println("Escolha a opção desejada:");
        System.out.println("1. Converter de Celsius para Fahrenheit");
        System.out.println("2. Converter de Fahrenheit para Celsius");
        System.out.print("Opção: ");
        int opcao = scanner.nextInt();

        if (opcao == 1) {
            System.out.print("Digite a temperatura em Celsius: ");
            double celsius = scanner.nextDouble();
            double fahrenheit = converterCelsiusParaFahrenheit(celsius);
            System.out.println(celsius + "°C equivalem a " + fahrenheit + "°F.");
        } else if (opcao == 2) {
            System.out.print("Digite a temperatura em Fahrenheit: ");
            double fahrenheit = scanner.nextDouble();
            double celsius = converterFahrenheitParaCelsius(fahrenheit);
            System.out.println(fahrenheit + "°F equivalem a " + celsius + "°C.");
        } else {
            System.out.println("Opção inválida.");
        }

        scanner.close();
    }

    public static double converterCelsiusParaFahrenheit(double celsius) {
        return (celsius * 9 / 5) + 32;
    }

    public static double converterFahrenheitParaCelsius(double fahrenheit) {
        return (fahrenheit - 32) * 5 / 9;
    }
}
