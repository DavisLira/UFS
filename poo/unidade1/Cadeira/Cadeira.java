package Cadeira;

public abstract class Cadeira {
    private int numPernas;
    private String material;
    private String cor;

    public Cadeira(int numPernas, String material, String cor) {
        this.numPernas = numPernas;
        this.material = material;
        this.cor = cor;
    }

    // Getters e setters
    public int getNumPernas() {
        return numPernas;
    }

    public String getMaterial() {
        return material;
    }

    public String getCor() {
        return cor;
    }
}