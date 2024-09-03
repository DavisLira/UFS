package Cadeira;

public class CadeiraModerna extends Cadeira {
    private String tronco;
    private boolean rodinhas = true;

    public CadeiraModerna(int numPernas, String material, String cor, String tronco, boolean rodinhas) {
        super(numPernas, material, cor);
        this.tronco = tronco;
    }

    // Getters e setters
    public String getTronco() {
        return tronco;
    }

    public boolean isRodinhas() {
        return rodinhas;
    }
}