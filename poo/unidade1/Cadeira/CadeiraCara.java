package Cadeira;

public class CadeiraCara extends Cadeira {
    private boolean estofado = true;

    public CadeiraCara(int numPernas, String material, String cor) {
        super(numPernas, material, cor);
    }

    // Getters e setters
    public boolean isEstofado() {
        return estofado;
    }

    @Override
    public String toString() {
        return "Cadeira Cara {" + "numeroDePernas=" + getNumPernas() +
                ", material= '" + getMaterial() + "'" + ", cor='" + getCor() + "'" +
                ", estofado= " + estofado + " }";
    }
}