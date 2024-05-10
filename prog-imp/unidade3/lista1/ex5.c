#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char LIMPAR[7] = "clear";

struct TPfreezer {
    char nome[10];
    float capacidade;
    float garantia;
    float economia;
    float temperaturaMin;
};

typedef struct TPfreezer freezer;
freezer F[6] = {
    {"Deia", 385, 12, 35.9, -28},
    {"Sul", 534, 121, 72.9, -18},
    {"NSul", 309, 12, 46.2, -18},
    {"Frio", 546, 3, 74.2, -18},
    {"Fri", 503, 24, 78, -22},
    {"Lux", 477, 12, 90, -18}
};

int Frz, Crc;

void mostraNomes(freezer vetor[6], int C) {
    printf("                      ");
    for (int i = 1; i <= C; i++) {
        printf("%s", vetor[i-1].nome);
        if (strlen(vetor[i-1].nome) == 4) {
            printf("  ");
        } else {
            printf("   ");
        }  
    }
    printf("\n");
}

void ExibeTudo(freezer vetor[6], int L, int C) {
    system(LIMPAR);
    mostraNomes(vetor, C);
    for (int i = 0; i < L; i++)
    {
        if (i==0) {
            printf("Capacidade (litros) ");
            for (int j = 0; j < C; j++)
            {
                printf("%6.1f", vetor[j].capacidade);
            }
        }
        if (i==1) {
            printf("Garantia (meses)    ");
            for (int j = 0; j < C; j++)
            {
                printf("%6.1f", vetor[j].garantia);
            }
        }
        if (i==2) {
            printf("Economia (KWh/mes)  ");
            for (int j = 0; j < C; j++)
            {
                printf("%6.1f", vetor[j].economia);
            }
        }
        if (i==3) {
            printf("Temperatura Min (C) ");
            for (int j = 0; j < C; j++)
            {
                printf("%6.1f", vetor[j].temperaturaMin);
            }
        }
        printf("\n");
    }
    
}

void ExibeFreezer(freezer vetor[6], int L, int C) {
    printf("                      ");
    printf("%s\n", vetor[C].nome);
    for(int i=0;i<L;i++) {
        if (i==0) {
            printf("Capacidade (litros) ");
            printf("%6.1f", vetor[C].capacidade);
        }
        if (i==1) {
            printf("Garantia (meses)    ");
            printf("%6.1f", vetor[C].garantia);
        }
        if (i==2) {
            printf("Economia (KWh/mes)  ");
            printf("%6.1f", vetor[C].economia);
        }
        if (i==3) {
            printf("Temperatura Min (C) ");
            printf("%6.1f", vetor[C].temperaturaMin);
        }
        printf("\n");
    }    
}

void ExibeCaracteristica(freezer vetor[6],int L,int C){
    mostraNomes(vetor, C);

    if (L == 0) {
        printf("Capacidade (litros) ");
        for (int j = 0; j < C; j++) {
            printf("%6.1f", vetor[j].capacidade);
        }
        printf("\n");
    }
    if (L == 1) {
        printf("Garantia (meses)    ");
        for (int j = 0; j < C; j++) {
            printf("%6.1f", vetor[j].garantia);
        }
        printf("\n");
    }
    if (L == 2) {
        printf("Economia (KWh/mes)  ");
        for (int j = 0; j < C; j++) {
            printf("%6.1f", vetor[j].economia);
        }
        printf("\n");
    }
    if (L == 3) {
        printf("Temperatura Min (C) ");
        for (int j = 0; j < C; j++) {
            printf("%6.1f", vetor[j].temperaturaMin);
        }
        printf("\n");
    }
}
void SelecionaFreezer(int *F){
    system(LIMPAR);
    printf("Selecione o freezer desejado:\n");
    printf("1 - Deia\n");
    printf("2 - Sul\n");
    printf("3 - NSul\n");
    printf("4 - Frio\n");
    printf("5 - Fri\n");
    printf("6 - Lux\n\n");
    printf("Opcao: ");
    int Op;
    scanf("%d",&Op);
    printf("\n\n");
    *F=Op-1;
    system(LIMPAR);
};

void SelecionaCaracteristica(int *C){
    system(LIMPAR);
    printf("Caracteristica desejado\n");
    printf("1 - Capacidade (litros)\n");
    printf("2 - Garantia (meses)\n");
    printf("3 - Economia(kWh/mes)\n");
    printf("4 - Temperatura Minima (Celsius)\n");
    printf("Opcao: ");
    int Op;
    scanf("%d",&Op);
    printf("\n\n");
    *C=Op-1;
    system(LIMPAR);
};
              
void AlteraDado(freezer vetor[6]) {
    int freezer, caracteristica;
    float valor;
    SelecionaFreezer(&freezer);
    SelecionaCaracteristica(&caracteristica);
    printf("\nDigite o valor: ");
    scanf("%f", &valor);
    if (caracteristica == 0) {
        vetor[freezer].capacidade = valor;
    }
    if (caracteristica == 1) {
        vetor[freezer].garantia = valor;
    }
    if (caracteristica == 2) {
        vetor[freezer].economia = valor;
    }
    if (caracteristica == 3) {
        vetor[freezer].temperaturaMin = valor;
    }
    ExibeTudo(vetor, 4, 6);
};

void MelhorAux(char Texto[], float Valor, int Coluna) {
    system(LIMPAR);
    printf("\nMelhor %s: %6.1f\n", Texto, Valor);

    switch (Coluna)
    {
    case 0:
        printf("Do freezer: Deia");
        break;
    case 1:
        printf("Do freezer: Sul");
        break;
    case 2:
        printf("Do freezer: NSul");
        break;
    case 3:
        printf("Do freezer: Frio");
        break;
    case 4:
        printf("Do freezer: Fri");
        break;
    case 5:
        printf("Do freezer: Lux");
        break;
    
    default:
        break;
    }
}

void Melhor(freezer vetor[6], char Texto[], int L, int C) {
    float MelhorValor = 0;
    int MelhorColuna = 0;
  
    switch (L) {
    case 0:
        for (int i = 0; i < C; i++) {
            if (MelhorValor < vetor[i].capacidade) {
            MelhorValor = vetor[i].capacidade;
            MelhorColuna = i;
            }
        }
        break;
    case 1:
        for (int i = 0; i < C; i++) {
            if (MelhorValor < vetor[i].garantia) {
            MelhorValor = vetor[i].garantia;
            MelhorColuna = i;
            }
        }
        break;
    case 2:
        for (int i = 0; i < C; i++) {
            if (MelhorValor < vetor[i].economia) {
            MelhorValor = vetor[i].economia;
            MelhorColuna = i;
            }
        }
        break;
    case 3:
        for (int i = 0; i < C; i++) {
            if (MelhorValor > vetor[i].temperaturaMin) {
            MelhorValor = vetor[i].temperaturaMin;
            MelhorColuna = i;
            }
        }
        break;
    }

  MelhorAux(Texto, MelhorValor, MelhorColuna);
};

int main(){
  do{
    printf("\n\n\n>>> Pesquisa Freezer <<<\n\n");
    printf("Selecione a opcao desejada:\n");
    printf("1 - Exibir Levantamento\n");
    printf("2 - Dados de um Freezer\n");
    printf("3 - Dados de uma Caracteristica\n");
    printf("4 - Alterar Dado\n");
    printf("5 - Melhor Freezer em Capacidade\n");
    printf("6 - Melhor Freezer em Garantia\n");
    printf("7 - Melhor Freezer em Economia\n");
    printf("8 - Melhor Freezer em Temperatura\n");
    printf("9 - Sair\n");
    int Op;
    scanf("%d",&Op);
    switch (Op){
      case 1: ExibeTudo(F,4,6);
              break;
      case 2: SelecionaFreezer(&Frz);
              ExibeFreezer(F,4,Frz);
              break;
      case 3: SelecionaCaracteristica(&Crc);
              ExibeCaracteristica(F,Crc,6);
              break;
      case 4: AlteraDado(F);
              break; 
      case 5: Melhor(F, "capacidade", 0, 6);
              break;
      case 6: Melhor(F, "garantia", 1, 6);
              break;
      case 7: Melhor(F, "economia", 2, 6);
              break;
      case 8: Melhor(F, "temperatura", 3, 6);
              break;
      case 9: break;}
      if (Op==9)
        break;}
  while (1);
  return 0;
}