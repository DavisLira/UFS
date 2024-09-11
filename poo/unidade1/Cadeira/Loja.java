package Cadeira;

import java.util.Scanner;

public class Loja {

    public static void menu() {
        System.out.println("Escolha a opção de cadeira:");
        System.out.println("1 - Cadeira Cara");
        System.out.println("2 - Cadeira Escolar");
        System.out.println("3 - Cadeira Especial");
        System.out.println("4 - Cadeira Moderna");
        System.out.println("0 - Sair");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int opcao = 1;
        int pernas;
        String material;
        String cor;
        int i = 0;

        Cadeira[] cadeiras = new Cadeira[5];
        
        for (int j = 0; j < cadeiras.length; j++) {
            menu();
            opcao = scanner.nextInt();

            System.out.println("Digite o número de pernas:");
            pernas = scanner.nextInt();
            System.out.println("Digite o material:");
            material = scanner.next();
            System.out.println("Digite a cor:");
            cor = scanner.next();

            if (opcao != 0) {
                switch (opcao) {
                    case 1:
                        CadeiraCara cara = new CadeiraCara(pernas, material, cor);
                        cadeiras[i] = cara;
                        i++;
                        break;
                    case 2:
                        CadeiraEscolar escolar = new CadeiraEscolar(pernas, material, cor);
                        cadeiras[i] = escolar;
                        i++;
                        break;
                    case 3:                
                        System.out.println("Digite o número de rodas grandes:");
                        int rodasG = scanner.nextInt();                
                        System.out.println("Digite o número de rodas pequenas:");
                        int rodasP = scanner.nextInt();
                        CadeiraEspecial especial = new CadeiraEspecial(pernas, material, cor, rodasG, rodasP);
                        cadeiras[i] = especial;
                        i++;
                        break;
                    case 4:
                        System.out.println("Digite o tipo de tronco:");
                        String tronco = scanner.next();
                        CadeiraModerna moderna = new CadeiraModerna(pernas, material, cor, tronco);
                        cadeiras[i] = moderna;
                        i++;
                        break;

                    default:
                        break;
                }
            }
        }

        System.out.println(cadeiras[0]);
        for (int j = 0; j < cadeiras.length; j++) {
            System.out.println("Cadeira " + (j + 1) + ": " + cadeiras[j].toString());
        }
        scanner.close();
    }
}