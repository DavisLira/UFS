package Animal;

public class Peixe extends Animal{
    public Peixe(float massa, String tamanho) {
        super(massa, tamanho);
    }

    public void comunicar() {
        System.out.println("Glub glub...");
    }

    public void movimentar() {
        System.out.println("Nadando...");
    }
}
