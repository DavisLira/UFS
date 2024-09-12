package Streaming;

public class Usuario {
    private String nome;
    private int creditos = 3;
    private Midia[] alugados = new Midia[3];

    public Usuario(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return this.nome;
    }

    public int getCreditos() {
        return this.creditos;
    }

    public void alugar(Midia midia, Midia midias[]) {
        if (this.creditos > 0) {
            System.out.println("        -- " + midia + " --");
            for (int i = 0; i < midias.length; i++) {
                System.out.println("        -- " + midias[i] + " --");
                if (midias[i] == midia) {
                    midias[i] = null;
                    break;
                } else {
                    System.out.println("Essa mídia não está disponível para aluguel.");
                    return;
                }
            }
            for (int i = 0; i < this.alugados.length; i++) {
                if (this.alugados[i] == null) {
                    this.alugados[i] = midia;
                    break;
                } else {
                    System.out.println("Você já tem 3 mídias alugadas.");
                    return;
                }
            }
            this.creditos--;
        } else {
            System.out.println("Você não tem créditos suficientes para alugar esta mídia.");
        }
    }

    public void devolver(Midia midia, Midia midias[]) {
        this.creditos++;
        for (int i = 0; i < this.alugados.length; i++) {
            if (this.alugados[i] != null && this.alugados[i] == midia) {
                this.alugados[i] = null;
                                
                for (int j = 0; j < midias.length; j++) {
                    if (midias[j] == null) {
                        midias[j] = midia;
                        return;
                    }
                }
            }
        }
    }
}
