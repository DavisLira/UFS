package Cadeira;

public class CadeiraEscolar extends Cadeira {
    private boolean bracos = true;

    public CadeiraEscolar(int numPernas, String material, String cor) {
        super(numPernas, material, cor);
    }

    // Getters e setters
    public boolean isBracos() {
        return bracos;
    }
}