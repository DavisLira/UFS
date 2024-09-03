package Cadeira;

public class CadeiraEspecial extends Cadeira {
    private int rodasGrandes;
    private int rodasPequenas;

    public CadeiraEspecial(int numPernas, String material, String cor, int rodasGrandes, int rodasPequenas) {
        super(numPernas, material, cor);
        this.rodasGrandes = rodasGrandes;
        this.rodasPequenas = rodasPequenas;
    }

    // Getters e setters
    public int getRodasGrandes() {
        return rodasGrandes;
    }

    public int getRodasPequenas() {
        return rodasPequenas;
    }
}