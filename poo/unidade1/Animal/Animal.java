package Animal;

public abstract class Animal {
    private float massa;
    private String tamanho;

    public Animal(float massa, String tamanho) {
        this.massa = massa;
        this.tamanho = tamanho;
    }

    public float getMassa() {
        return massa;
    }

    public String getTamanho() {
        return tamanho;
    }

    public abstract void comunicar();

    public abstract void movimentar();
}
