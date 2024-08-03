package Apertadinho;

public class Apertadinho {
	private int sec;
	private int max;
	private int min;
	
	public Apertadinho (
		int min,
		int max
	) {
		this.min = min;
		this.max = max;
		this.sec = (int) (Math.random() * (max - min) + 1) + min;
	}
	
	public boolean jogar(int chute) {
		if(chute < this.sec) {
			System.out.println("Número menor que o secreto!");
			System.out.println("");
			this.min = chute;
			return false;
		} else if (chute > this.sec) {
			System.out.println("Número maior que o secreto!");
			System.out.println("");
			this.max = chute;
			return false;
		} else {
			System.out.println("Acertou!");
			System.out.println("O número secreto era " + this.sec + "!");
			System.out.println("");
			return true;
		}
	}
	
	public void intervalo () {
		System.out.println("O intervalo atual é de: " + this.min + " até " + this.max);
	}
}
