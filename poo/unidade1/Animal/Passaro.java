package Animal;

public class Passaro extends Animal {
    public Passaro(float massa, String tamanho) {
        super(massa, tamanho);
    }

    public void comunicar() {
        System.out.println("Cantando...");
    }

    public void movimentar() {
        System.out.println("Voando...");
    }
}
