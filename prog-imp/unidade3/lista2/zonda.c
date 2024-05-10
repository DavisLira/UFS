#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct RegMoto{
	char Nome[20];
	char Modelo[10];
	char Placa[7];
	char Defeito[50];
	int Status;
	float Preco;
};

typedef struct RegMoto TpRegMoto;
TpRegMoto VZonda[50];

int Quant = -1;//Controla o preenchimento do vetor
float dinheiro = 0;


// Função para verificar se a moto está no estacionamento por meio da placa
int VerificaMoto(char placa[]) {
    int Pos = -1;

    for (int Cont = 0 ; Cont<=Quant; Cont++)
        if (strcmp(VZonda[Cont].Placa, placa) == 0)
        Pos = Cont;
        
    return Pos;
}

void SolicitaServico() {
/* (1) Solicitar Serviço – quando se insere os dados supracitados, e também os campos status com valor zero sinalizando que o serviço ainda não foi feito, preço, também iniciado com zero.  Este deve estar em loop. */
    system("clear");
    char Sair='S';
    do{
	    char P[7];

        printf("\n\n >>> Motos Zonda <<< \n\n");
        printf(" Qual a placa da moto? ");
        scanf(" %[^\n]s", P);

        int Pos = VerificaMoto(P);

        if (Pos != -1) {
            printf("\n Essa moto ja está no sistema!");
        } else {
            Quant = Quant + 1;
            printf(" Qual o nome do cliente? ");
            scanf(" %[^\n]s",VZonda[Quant].Nome);
            printf(" Qual o modelo da moto? ");
            scanf(" %[^\n]s",VZonda[Quant].Modelo);
            strcpy(VZonda[Quant].Placa, P);
            printf(" Qual o defeito da moto? ");
            scanf(" %[^\n]s",VZonda[Quant].Defeito);
        }

        VZonda[Quant].Status = 0;
        VZonda[Quant].Preco = 0;
        printf("\n\n Deseja inserir novo servico? S|N ");
        scanf(" %c",&Sair);
        Sair=toupper(Sair);
        system("clear");
    } while (Sair!='N');
}

void IniciaServico(){
/*(2) Iniciar Serviço – quando o status de uma dada moto (placa) é iniciado pelo mecânico e o status para a ser um.*/
    char P[7];
    float preco;
    char resp;

    printf("Placa da moto para iniciar serviço: ");
    scanf(" %[^\n]s", P);

    // busca moto no serviço
    int Pos = VerificaMoto(P);
    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Pos == -1) {
        printf(" Moto não cadastrada!");
    } else if(VZonda[Pos].Status == 0) {
        printf("\n Cliente %d: %s", Pos+1, VZonda[Pos].Nome);
        printf("\n Modelo: %s", VZonda[Pos].Modelo);
        printf("\n Placa: %s", VZonda[Pos].Placa);
        printf("\n Defeito: %s", VZonda[Pos].Defeito);

        printf("\n Custo do serviço: ");
        scanf("%f", &preco);
        
        printf("\n O cliente aceitou o valor? S|N: ");
        scanf(" %c", &resp);
        resp=toupper(resp);

        system("clear");
        printf("\n\n >>> Motos Zonda <<< \n\n");
        switch (resp) {
        case 'S':
            VZonda[Pos].Status = 1;
            VZonda[Pos].Preco = preco;
            dinheiro += preco;
            printf(" Serviço da moto iniciada!");
            break;

        case 'N':
            VZonda[Pos].Status = 2;
            printf(" Removida solicitação da moto!");
            break;

        default:
            printf(" Resposta inválida");
            break;
        }
    } else {
        printf(" Moto inválida!");
    }
}

void RemoverSolicitacao(){
    char P[7];

    printf("Placa da moto para remover do serviço: ");
    scanf(" %[^\n]s",P);

    // busca moto no serviço
    int Pos = VerificaMoto(P);

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Pos==-1) {
        printf(" Moto não cadastrada!");
    } else {
        if (VZonda[Pos].Status != 0) {
            printf(" Não é possível remover a moto!");
        } else {
            VZonda[Pos].Status = 2;
            printf(" Solicitação removida com sucesso!");
        }
    }
}

void ConsultarSolicitacoes(){
    system("clear");
    int aux = -1;

    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Quant == -1) {
        printf(" Não há serviços cadastrados.");
    }
    else {
        for (int Cont = 0; Cont <= Quant; Cont++){
            if (VZonda[Cont].Status == 0 || VZonda[Cont].Status == 1) {
                printf("\n Cliente %d: %s", Cont+1, VZonda[Cont].Nome);
                printf("\n Modelo: %s", VZonda[Cont].Modelo);
                printf("\n Placa: %s", VZonda[Cont].Placa);
                printf("\n Defeito: %s", VZonda[Cont].Defeito);
                printf("\n Status: %d",VZonda[Cont].Status);

                if (VZonda[Cont].Preco == 0) {
                    printf("\n Preco: NAO DEFINIDO");       
                } else {
                    printf("\n Preco: %.2f",VZonda[Cont].Preco);
                }
                printf("\n --------------------- \n\n");
            } else {
                aux++;
            }
            if (aux == Quant) {
                printf(" Não tem motos esperando por serviço!");
            }
        }
    }
} 
  
void ConcluirServico(){
    float custo, pago, troco;
    char P[7];

    printf("Placa da moto para concluir o serviço: ");
    scanf(" %[^\n]s",P);

    // busca moto no serviço
    int Pos = VerificaMoto(P);

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Pos==-1 || VZonda[Pos].Status != 1) {
        printf(" Moto inválida!");
    } else {
        printf("Valor a ser pago: R$%.2f\n", VZonda[Pos].Preco);
        printf("Valor pago: ");
        scanf("%f", &pago);
        custo = VZonda[Pos].Preco;
        troco = pago - custo;

        system("clear");
        printf("\n\n >>> Motos Zonda <<< \n\n");
        
        if (troco < 0) {
            printf(" Falta dinheiro!");
        } else {
            if (troco > 0) {
                printf(" Seu troco: R$%.2f\n", troco);
            }
            VZonda[Pos].Status = 3;
            printf(" Moto liberada!!");
        }
    }

}

void EncerrarExpediente(){
    int feito = -1;
    int concluiu = 0, removeu = 0;

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    for (int Cont = 0; Cont <= Quant; Cont++){
        if (VZonda[Cont].Status == 3 || VZonda[Cont].Status == 2) {
            feito++;
        }
    }

    if (Quant == -1) {
        printf(" Nenhuma moto no sistema!");
    } else if (feito == Quant) {
        for (int Cont = 0; Cont <= Quant; Cont++){
            if (VZonda[Cont].Status == 3) concluiu++;
            else if (VZonda[Cont].Status == 2) removeu++;
        }   
    } else {
        printf(" Ainda tem Motos no serviço!");
    }

    printf("\n Quantidade de entradas: %d", Quant+1);
    printf("\n Conluiram o serviço: %d", concluiu);
    printf("\n Removeram o serviço: %d", removeu);
    printf("\n Total arrecadado: R$%.2f", dinheiro);
}

int main(){
    int Opcao;
    system("clear"); //limpa tela no ReplIt

    do{
    //Exibicao de menu e leitura da opcao. 	
        printf("\n\n >>> Motos Zonda <<< \n\n");
        printf("1 - Solicitar Servico \n");
        printf("2 - Iniciar Servico \n");
        printf("3 - Remover Solicitacao \n");
        printf("4 - Consultar Solicitacoes \n");
        printf("5 - Concluir Servico \n");
        printf("6 - Encerrar Expediente \n");
        printf("7 - Sair \n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &Opcao);	
        switch (Opcao){
            case 1: SolicitaServico(); break;
            case 2: IniciaServico(); break;
            case 3: RemoverSolicitacao(); break;
            case 4: ConsultarSolicitacoes(); break;
            case 5: ConcluirServico(); break;
            case 6: EncerrarExpediente(); break;
            case 7: break;
        }
    } while (Opcao != 7);

    return 0;
}