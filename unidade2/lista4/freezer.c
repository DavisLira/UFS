#include <stdio.h>
#include <stdlib.h>

char LIMPAR[7] = "clear";

float M[4][6]={{385,534,309,546,503,477},
        {12, 121, 12, 3, 24, 12},
        {35.9, 72.1, 46.2,74.3,78,90},
        {-28, -18, -18, -18, -22, -18}};

int Frz, Crc;

void ExibeMatriz(float Matriz[][6],int L,int C){
  printf("                      Deia   Sul  NSul  Frio   Fri   Lux \n");
  for(int i=0;i<L;i++){
    if (i==0) printf("Capacidade (litros) ");
    if (i==1) printf("Garantia (meses)    ");
    if (i==2) printf("Economia (KWh/mes)  ");
    if (i==3) printf("Temperatura Min (C) "); 
    for (int j=0; j<C; j++)
      printf("%6.1f",Matriz[i][j]);
    printf("\n");}};

void ExibeColuna(float Matriz[][6],int L,int C){
  for(int i=0;i<L;i++){
    if (i==0) printf("Capacidade (litros) ");
    if (i==1) printf("Garantia (meses)    ");
    if (i==2) printf("Economia (KWh/mes)  ");
    if (i==3) printf("Temperatura Min (C) ");
    printf("%6.1f\n",Matriz[i][C]);}}

void ExibeLinha(float Matriz[][6],int L,int C){
  printf("Deia   Sul  NSul  Frio   Fri   Lux \n");
  for(int i=0;i<C;i++)
    printf("%.1f ",Matriz[L][i]);
  printf("\n");}

void SelecionaFreezer(float Matriz[][6],int *F){
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
  *F=Op-1;};

void SelecionaCaracteristica(float Matriz[][6],int *C){
  printf("Caracteristica desejado\n");
  printf("1 - Capacidade (litros)\n");
  printf("2 - Garantia (meses)\n");
  printf("3 - Economia(kWh/mes)\n");
  printf("4 - Temperatura Minima (Celsius)\n");
  printf("Opcao: ");
  int Op;
  scanf("%d",&Op);
  *C=Op-1;};
              
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
      case 1: ExibeMatriz(M,4,6);
              break;
      case 2: SelecionaFreezer(M,&Frz);
              ExibeColuna(M,4,Frz);
              break;
      case 3: SelecionaCaracteristica(M,&Crc);
              ExibeLinha(M,Crc,6);
              break;
      case 4: printf("\n_Altera Dado_");
              break; 
      case 5: printf("\n_Melhor Freezer em Capacidade_");
              break;
      case 6: printf("\n_Melhor Freezer em Garantia_");
              break;
      case 7: printf("\n_Melhor Freezer em Economia_");
              break;
      case 8: printf("\n_Melhor Freezer em Temperatura_");
              break;
      case 9: break;}
      if (Op==9)
        break;}
  while (1);
  return 0;
}