package Apertadinho;

import java.util.Scanner;

public class Partida {
	
	public static void main(String[] args) {
		int max;
		int min;
		int chute;
		Scanner scaner = new Scanner(System.in);
		
		System.out.print("Digite o número Mínimo: ");
		min = scaner.nextInt();
		System.out.print("Digite o número Máximo: ");
		max = scaner.nextInt();
		
		Apertadinho jogo = new Apertadinho(min, max);
		
		boolean acabou;
		do {
			System.out.print("Diga um número: ");
			chute = scaner.nextInt();
			acabou = jogo.jogar(chute);
			if (acabou == false) {
				jogo.intervalo();
			}

		} while(acabou == false);
		
		
		
		scaner.close();
	}
}
