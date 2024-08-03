package CorretorAutomatico;

import java.util.Scanner;

public class Sala {

    public static void menu() {
        System.out.println("\n--- Menu:");
        System.out.println("    1 - novo aluno");
        System.out.println("    2 - valor das questoes");
        System.out.println("    3 - respostas do aluno");
        System.out.println("    4 - quantidade de questoes do gabarito");
        System.out.println("    5 - respostas do gabarito");
        System.out.println("    6 - notas do aluno");
        System.out.println("    0 - sair");
        System.out.print("  Escolha a opção: ");
    }
    
    public static void main(String[] args) {
        Scanner scaner = new Scanner(System.in);

        Prova aluno = null;
        String nomeAluno = null;
        int questoes = 0;
        int[] valor = null;
        char[] respostas = null;
        
        Gabarito gabarito = null;
        int questoesGab = 0;
        char[] respostasGab = null;

        CorretorAutomatico corretor = new CorretorAutomatico();

        int opc = 0;
        do {
            menu();
            opc = scaner.nextInt();
            scaner.nextLine();

            switch (opc) {
                case 1:
                    System.out.print("Digite o nome do aluno: ");
                    nomeAluno = scaner.nextLine();
                    System.out.print("Digite a quantidade de questões: ");
                    questoes = scaner.nextInt();
                    scaner.nextLine();
                    valor = new int[questoes];
                    respostas = new char[questoes];

                    aluno = new Prova(nomeAluno, questoes);
                    break;
                
                case 2:
                    if (aluno == null) {
                        System.out.println("Aluno nao criado!");
                        break;
                    }

                    System.out.println("Digite o valor das questões");

                    for (int i = 0; i < questoes; i++) {
                        System.out.print("Valor da " + (i+1) + "° questão: ");
                        valor[i] = scaner.nextInt();
                        scaner.nextLine();
                    }

                    aluno.notasProva(valor);
                    break;

                case 3:
                    if (aluno == null) {
                        System.out.println("Aluno nao criado!");
                        break;
                    }

                    System.out.println("Digite as respostas das questões");

                    for (int i = 0; i < questoes; i++) {
                        System.out.print("Resposta da " + (i+1) + "° questão: ");
                        String input = scaner.next().toUpperCase();
                        char resposta = input.charAt(0);
                        respostas[i] = resposta;
                    }
                    
                    aluno.responder(respostas);

                    break;

                case 4:
                    System.out.print("Digite a quantidade de questões: ");
                    questoesGab = scaner.nextInt();
                    scaner.nextLine();
                    respostasGab = new char[questoes];
                    gabarito = new Gabarito(questoesGab);

                    break;
                
                case 5:
                    if (gabarito == null) {
                        System.out.println("Gabarito nao criado!");
                        break;
                    }

                    System.out.println("Digite o gabarito das questões");

                    for (int i = 0; i < questoesGab; i++) {
                        System.out.print("Resposta da " + (i+1) + "° questão: ");
                        String input = scaner.next().toUpperCase();
                        char resposta = input.charAt(0);
                        respostasGab[i] = resposta;
                    }
                    
                    gabarito.respostas(respostasGab);

                    break;

                case 6:
                    if (gabarito == null || aluno == null) {
                        System.out.println("Erro");
                        break;
                    }
                    corretor.corrigirProva(aluno, gabarito);
                    
                    break;

                default:
                    break;
            }
            
            
        } while (opc != 0);

        scaner.close();
    }
}
