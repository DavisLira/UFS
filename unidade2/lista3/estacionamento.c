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

                                                    // ARRAY AUXILIAR 3° QUESTAO
                                                    // 14 horários de 6 às 20
int HorasEntradas[14], MaiorQtd = 0, MaiorHorario = 0;
const char LIVRE[5] = "LIVRE";
float Dinheiro = 0;

void AbrirCaixa(){
  printf("\n >>> Estacionamento <<< \n");
  printf(" >>>  Largas Vagas  <<< \n");
  printf("\n     ABRINDO  CAIXA \n");

  for (int i=0; i<30; i++)
     strcpy(Estaciona[i],"LIVRE");
  
                                                    // Iniciar os horários com 0
  for (int i = 0; i < 14; i++)
  {
    HorasEntradas[i] = 0;
  }

  printf("\nQual o valor do estacionamento por hora de uso? ");
  scanf("%f",&Valor);
  printf("Qual o nome do responsavel? ");
  scanf(" %20[^\n]s", Responsavel);

  Iniciou=1;
}

void ClienteChega(){
  int Vaga, H;
  char Placa[8], Hora[5], Entrada[14];
  
  printf("\n >>> Estacionamento <<< \n");
  printf(" >>>  Largas Vagas  <<< \n");
  printf("\n   CHEGADA DE CLIENTE \n");

  if (Iniciou){
    printf("\n CAIXA ABERTO   Valor/h: %.2f", Valor);
    printf("\n Responsavel: %s\n\n", Responsavel);

    printf("Qual a vaga ocupada? ");
    scanf("%d",&Vaga);

                                                    // Verifica se a vaga solicitada
                                                    // está livre ou ocupada
    int livre = 0;
    for (int i = 0; i < 5; i++) {
      if (Estaciona[Vaga-1][i] == LIVRE[i]) {
        livre++;
      }
    }

    if (livre != 5) {
      printf("ESSA VAGA ESTÁ OCUPADA\n");
      return;
    }

    printf("Qual a placa do veiculo [7 digitos]? ");
    scanf(" %7[^\n]s", Placa);

                                                    // Verifica o tamanho da placa
    if (strlen(Placa) != 7) {
      printf("Erro ao ler a placa!\n");
      return;
    }
    
    
    strcpy(Entrada,Placa);

    printf("Qual a hora de entrada [formato nn:nn]? ");
    scanf(" %5[^\n]s", Hora);

    strcat(Entrada,"+");
    strcat(Entrada,Hora);
    
    Hora[0] = Entrada[8];
    Hora[1] = Entrada[9];
    Hora[2] = '\0';
    H = atoi(Hora);

                                                    // Verifica horário de entrada
    if (H < 6 || H > 19) {
      printf("ESTACIONAMENTO FECHADO!\n");
      return;
    }
    printf("Chegada registrada com sucesso!\n");

    HorasEntradas[H-6]++;
    strcpy(Estaciona[Vaga-1],Entrada);

    }
  else
    printf("\nERRO: Antes eh preciso abrir o caixa!\n");
}

void ClienteSai(){
  int Vaga;
  char Placa[8], Entrada[14], Hora[3], Min[3];
  int H, M; //hora, minuto e segundo
  
                                                    // ADIÇÃO DA 2° QUESTÃO
  float custo, pago, troco;
  char HorarioSaida[6], HoraSaida[3], MinSaida[3];
  int HSaida, MSaida;
  
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
    
                                                    // VERIFICA SE VAGA ESTA LIVRE
    int livre = 0;
    for (int i = 0; i < 5; i++)
    {
      if (Entrada[i] == LIVRE[i])
      {
        livre++;
        if (livre == 5)
        {
          printf("ESSA VAGA TA LIVRE\n");
          return;
        }
      }
    }
    
    //Teste
    printf("\n>>>>>>>%s",Entrada);
   
    for (int i=0; i<7; i++)
      Placa[i] = toupper(Entrada[i]);
     
                                                    // AJUSTE PARA MOSTRAR PLACA
    strncpy(Placa, Placa, 7);
    Placa[7] = '\0';

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
    
                                                    // SEGUNDA QUESTÃO

    printf("Qual o horario de saída [formato nn:nn]? ");
    scanf(" %5[^\n]s", HorarioSaida);

    HoraSaida[0] = HorarioSaida[0];
    HoraSaida[1] = HorarioSaida[1];
    HoraSaida[2] = '\0';
    HSaida = atoi(HoraSaida); // convete string em inteiro
    MinSaida[0] = HorarioSaida[3];
    MinSaida[1] = HorarioSaida[4];
    MinSaida[2] = '\0';
    MSaida = atoi(MinSaida); // convete string em inteiro

    if (HSaida >= H) {

      if (MSaida > M) {
        HSaida++;
      }

      custo = (HSaida - H) * Valor;

      printf("Valor a pagar: R$ %.2f\n", custo);
      printf("Valor pago: ");
      scanf("%f", &pago);

      troco = pago - custo;

      if (troco < 0) {
        printf("Falta dinheiro!\n");
      } else {
        if (troco > 0) {
          printf("Seu troco: R$%.2f \n", troco);
        }
        
        strcpy(Estaciona[Vaga-1],"LIVRE");
        printf("ESTACIONAMENTO LIBERADO!\n");

                                                    // Calculando o total acumulado
        Dinheiro += custo;
      }
      
    } else {
      printf("Horário inválido!\n");
    }
	
	  }
 else
    printf("\nERRO: Antes eh preciso abrir o caixa!\n");
}

void FecharCaixa(){
  char Entrada[14];

                                                    // Mostra a quantidade de carros
                                                    // que chegaram em cada 
                                                    // intervalo de horarios
  printf("\n");
  for (int i = 0; i < 14; i++) {
    printf("Horario %d às %d: %d\n", i+6, i+7, HorasEntradas[i]);
    if (MaiorQtd < HorasEntradas[i] && MaiorHorario < i)
    {
      MaiorQtd = HorasEntradas[i];
    }
  }
  printf("\n");

  printf("Horario mais movimentado: %d horas\n", MaiorHorario+6);

  printf("Saldo ao fim do dia: R$ %.2f\n", Dinheiro);

                                                    // Acessa cada vaga
  for (int i = 0; i < 30; i++) {
    int livre = 0;
    int vago = 0;
                                                    // Verifica se a vaga
                                                    // está livre
    for (int j = 0; j < 5; j++) {
      if (Estaciona[i][j] == LIVRE[j]) {
        livre++;
      }
    }
                                                    // Se a vaga não estiver
                                                    // livre, mostra ocupada
    if (livre != 5) {
      printf("VAGA %d OCUPADA\n", i+1);
    }
    
  }
  
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