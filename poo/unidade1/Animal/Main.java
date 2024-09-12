package Animal;

public class Main {
    public static void main(String[] args) {
        Animal[] animais = new Animal[3];

        animais[0] = new Humano(70.0f, "Grande");
        animais[1] = new Passaro(6.5f, "Médio");
        animais[2] = new Peixe(0.5f, "Pequeno");

        for (int i = 0; i < animais.length; i++) {
            animais[i].comunicar();
            animais[i].movimentar();
        }
    }
}
