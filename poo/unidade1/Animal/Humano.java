package Animal;

public class Humano extends Animal{
    public Humano(float massa, String tamanho) {
        super(massa, tamanho);
    }

    public void comunicar() {
        System.out.println("Falando...");
    }

    public void movimentar() {
        System.out.println("Andando...");
    }
}
