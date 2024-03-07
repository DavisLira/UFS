/* Considerando a necessidade de construir um programa para definir o 
 * valor a pagar pelo uso de um vaga de estacionamento, por tempo de 
 * uso. Onde: as vagas são numeradas, o cliente escolhe a vaga em que 
 * deseja estacionar seu carro, é registrado no sistema a hora de che-
 * gada no estacionamento; exemplo, se um carro chegou às 8:00 no es-
 * tacionamento e ocupa a vaga 15, na posição 15 do vetor é armazenada
 *  a string Placa + hora.
 * Você decide e implementa as operações a serem disponibilizados ao 
 * usuário do programa, a necessidade de aplicar subprograma e o valor 
 * pela unidade de tempo de uso do estacionamento.                  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char Estaciona[30][14];
//30 vagas
//Mantem placa com 7 caracteres, sinal de + e 5 caracteres para hora
float Valor;
char Responsavel[21], Iniciou = 0;

void AbrirCaixa(){
  printf("\n >>> Estacionamento <<< \n");
  printf(" >>>  Largas Vagas  <<< \n");
  printf("\n     ABRINDO  CAIXA \n");

  for (int i=0; i<30; i++)
     strcpy(Estaciona[i],"LIVRE");
  
  printf("\nQual o valor do estacionamento por hora de uso? ");
  scanf("%f",&Valor);
  printf("Qual o nome do responsavel? ");
  scanf(" %20[^\n]s", Responsavel);

  Iniciou=1;
}

void ClienteChega(){
  int Vaga;
  char Placa[8], Hora[5], Entrada[14];
  
  printf("\n >>> Estacionamento <<< \n");
  printf(" >>>  Largas Vagas  <<< \n");
  printf("\n   CHEGADA DE CLIENTE \n");

  if (Iniciou){
    printf("\n CAIXA ABERTO   Valor/h: %.2f", Valor);
    printf("\n Responsavel: %s\n\n", Responsavel);

    printf("Qual a vaga ocupada? ");
    scanf("%d",&Vaga);

    printf("Qual a placa do veiculo [7 digitos]? ");
    scanf(" %7[^\n]s", Placa);
    
    strcpy(Entrada,Placa);

    printf("Qual a hora de entrada [formato nn:nn]? ");
    scanf(" %5[^\n]s", Hora);

    strcat(Entrada,"+");
    strcat(Entrada,Hora);
    strcpy(Estaciona[Vaga-1],Entrada);
    printf("Chegada registrada com sucesso!\n");}
  else
    printf("\nERRO: Antes eh preciso abrir o caixa!\n");
}

void ClienteSai(){
  int Vaga;
  char Placa[8], Entrada[14], Hora[3], Min[3];
  int H, M; //hora, minuto e segundo
  
  printf("\n >>> Estacionamento <<< \n");
  printf(" >>>  Largas Vagas  <<< \n");
  printf("\n    SAIDA DE CLIENTE \n");   

  if (Iniciou){
    printf("\n CAIXA ABERTO   Valor/h: %.2f", Valor);
    printf("\n Responsavel: %s\n\n", Responsavel);
    printf("Qual a vaga ocupada? ");
    scanf("%d",&Vaga);
    
    //se vaga LIVRE, houve erro
    
    strcpy(Entrada,Estaciona[Vaga-1]);
    
    //Teste
    printf("\n>>>>>>>%s",Entrada);
   
    for (int i=0; i<7; i++)
      Placa[i] = toupper(Entrada[i]);
     
    //Teste
    printf("\n>>>>>>>Placa: %s",Placa);
    
    Hora[0] = Entrada[8];
    Hora[1] = Entrada[9];
    Hora[2] = '\0';
    H = atoi(Hora); // convete string em inteiro
    Min[0] = Entrada[11];
    Min[1] = Entrada[12];
    Min[2] = '\0';
    M = atoi(Min); // convete string em inteiro
    
    //Teste
    printf("\n>>>>>>>Hora: %d",H);
    printf("\n>>>>>>>Minutos: %d\n",M);
    
	
	  }
 else
    printf("\nERRO: Antes eh preciso abrir o caixa!\n");
}

void FecharCaixa(){
}

int main(){
  int Op;
  do{
    printf("\n >>> Estacionamento <<< \n");
    printf(" >>>  Largas Vagas  <<< \n");
    printf("\n 1 - Abrir Caixa");
    printf("\n 2 - Chegada de Cliente");
    printf("\n 3 - Saida de Cliente");
    printf("\n 4 - Fechar Caixa");
    printf("\n\n Qual a opcao desejada? ");
    do{
      scanf("%d",&Op);
      if ((Op < 1) || (Op > 4)){
        printf("\n ERRO: Opcao invalida!");
        printf("\n Qual a opcao desejada? ");}
      else
        break;
    }while (1);
    switch (Op) {
	  case 1: AbrirCaixa();
	          break;
	  case 2: ClienteChega();
	          break;
	  case 3: ClienteSai();
	          break;
	  case 4: FecharCaixa();
	          break;}
  }while (Op != 4);
	
return 0;}