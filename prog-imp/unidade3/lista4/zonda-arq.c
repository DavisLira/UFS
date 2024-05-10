#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct RegMoto {
    char Nome[20];
    char Modelo[10];
    char Placa[7];
    char Defeito[50];
    int Status;
    float Preco;
};

typedef struct RegMoto TpRegMoto;
TpRegMoto VZonda[50];

int Quant = -1; // Controla o preenchimento do vetor
float dinheiro = 0;

// Função para obter a data no formato dia-mês-ano
void ObterData(char *data) {
    printf("Digite a data (DD-MM-AAAA): ");
    scanf("%s", data);

    // Validar se a data está no formato correto
    while (strlen(data) != 10 || data[2] != '-' || data[5] != '-') {
        printf("Formato de data inválido. Digite novamente (DD-MM-AAAA): ");
        scanf("%s", data);
    }
}

// Função para salvar serviços incompletos em um arquivo .dat
void SalvarServicosIncompletos() {
    FILE *arquivo;
    arquivo = fopen("servicos_incompletos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.");
        return;
    }

    fwrite(&Quant, sizeof(int), 1, arquivo); // Escreve o número total de registros

    for (int i = 0; i <= Quant; i++) {
        fwrite(&VZonda[i], sizeof(TpRegMoto), 1, arquivo); // Escreve cada registro
    }

    fclose(arquivo);
}

// Função para inicializar registros a partir de um arquivo .dat
void InicializarRegistros() {
    FILE *arquivo;
    arquivo = fopen("servicos_incompletos.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de serviços incompletos não encontrado.\n");
        return;
    }

    fread(&Quant, sizeof(int), 1, arquivo); // Lê o número total de registros válidos

    for (int i = 0; i <= Quant; i++) {
        fread(&VZonda[i], sizeof(TpRegMoto), 1, arquivo); // Lê cada registro válido
    }

    fclose(arquivo);
}

// Função para registrar pagamentos em um arquivo .dat
void RegistrarPagamento(float valor, char *data) {
    FILE *arquivo;
    arquivo = fopen("historico_financeiro.dat", "a"); // Modificado para "a" (append)
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.");
        return;
    }

    fprintf(arquivo, "%s %.2f\n", data, valor);

    fclose(arquivo);
}

// Função para exibir histórico financeiro a partir de um arquivo .dat
void MostrarHistoricoFinanceiro() {
    float total = 0;
    FILE *arquivo;
    arquivo = fopen("historico_financeiro.dat", "r"); // Modificado para "r"
    if (arquivo == NULL) {
        printf("Arquivo de histórico financeiro não encontrado.\n");
        return;
    }

    printf("\n\n >>> Histórico Financeiro <<< \n\n");
    printf("%-15s | %-10s\n", "Data", "Valor");

    char data[20];
    float valor;
    while (fscanf(arquivo, "%s %f", data, &valor) != EOF) { // Corrigido para ler corretamente os dados
        total += valor;
        printf("%-15s | R$%.2f\n", data, valor);
    }

    printf("\n  Total = R$%.2f\n", total);

    fclose(arquivo);
}

// Função para verificar se a moto está no estacionamento por meio da placa
int VerificaMoto(char placa[]) {
    int Pos = -1;

    for (int Cont = 0; Cont <= Quant; Cont++) {
        if (strcmp(VZonda[Cont].Placa, placa) == 0) {
            Pos = Cont;
            break; // Adicionado para parar a busca quando a placa é encontrada
        }
    }

    return Pos;
}

void SolicitaServico() {
    system("clear");
    char Sair = 'S';
    do {
        char P[7];

        printf("\n\n >>> Motos Zonda <<< \n\n");
        printf(" Qual a placa da moto? ");
        scanf(" %[^\n]s", P);

        int Pos = VerificaMoto(P);

        if (Pos != -1) {
            printf("\n Essa moto já está no sistema!");
        } else {
            Quant++; // Ajuste para incrementar Quant apenas para entradas válidas
            printf(" Qual o nome do cliente? ");
            scanf(" %[^\n]s", VZonda[Quant].Nome);
            printf(" Qual o modelo da moto? ");
            scanf(" %[^\n]s", VZonda[Quant].Modelo);
            strcpy(VZonda[Quant].Placa, P);
            printf(" Qual o defeito da moto? ");
            scanf(" %[^\n]s", VZonda[Quant].Defeito);
        }

        VZonda[Quant].Status = 0;
        VZonda[Quant].Preco = 0;
        printf("\n\n Deseja inserir novo serviço? S|N ");
        scanf(" %c", &Sair);
        Sair = toupper(Sair);
        system("clear");
    } while (Sair != 'N');
}

void IniciaServico() {
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
    } else if (VZonda[Pos].Status == 0) {
        printf("\n Cliente %d: %s", Pos + 1, VZonda[Pos].Nome);
        printf("\n Modelo: %s", VZonda[Pos].Modelo);
        printf("\n Placa: %s", VZonda[Pos].Placa);
        printf("\n Defeito: %s", VZonda[Pos].Defeito);

        printf("\n Custo do serviço: ");
        scanf("%f", &preco);

        printf("\n O cliente aceitou o valor? S|N: ");
        scanf(" %c", &resp);
        resp = toupper(resp);

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

void RemoverSolicitacao() {
    char P[7];

    printf("Placa da moto para remover do serviço: ");
    scanf(" %[^\n]s", P);

    // busca moto no serviço
    int Pos = VerificaMoto(P);

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Pos == -1) {
        printf(" Moto não cadastrada!");
    } else {
        if (VZonda[Pos].Status != 0) {
            printf(" Não é possível remover a moto!");
        } else {
            VZonda[Pos].Status = 2;
            printf(" Solicitação removida com sucesso!");
            SalvarServicosIncompletos(); // Salvar as alterações
        }
    }
}

void ConsultarSolicitacoes() {
    system("clear");

    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Quant == -1) {
        printf(" Não há serviços cadastrados.");
    } else {
        for (int Cont = 0; Cont <= Quant; Cont++) {
            if (VZonda[Cont].Status == 0 || VZonda[Cont].Status == 1) {
                printf("\n Cliente %d: %s", Cont + 1, VZonda[Cont].Nome);
                printf("\n Modelo: %s", VZonda[Cont].Modelo);
                printf("\n Placa: %s", VZonda[Cont].Placa);
                printf("\n Defeito: %s", VZonda[Cont].Defeito);
                printf("\n Status: %d", VZonda[Cont].Status);

                if (VZonda[Cont].Preco == 0) {
                    printf("\n Preço: NÃO DEFINIDO");
                } else {
                    printf("\n Preço: %.2f", VZonda[Cont].Preco);
                }
                printf("\n --------------------- \n\n");
            }
        }
    }
}

void ConcluirServico() {
    float custo, pago, troco;
    char P[7], data[11];

    printf("Placa da moto para concluir o serviço: ");
    scanf(" %[^\n]s", P);

    // busca moto no serviço
    int Pos = VerificaMoto(P);

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Pos == -1 || VZonda[Pos].Status != 1) {
        printf(" Moto inválida ou serviço não iniciado!");
    } else {
        printf("Valor a ser pago: R$%.2f\n", VZonda[Pos].Preco);
        printf("Valor pago: ");
        scanf("%f", &pago);
        custo = VZonda[Pos].Preco;
        troco = pago - custo;

        // Obter e registrar a data
        ObterData(data);
        RegistrarPagamento(custo, data);

        system("clear");
        printf("\n\n >>> Motos Zonda <<< \n\n");

        if (troco < 0) {
            printf(" Falta dinheiro!");
        } else {
            if (troco > 0) {
                printf(" Seu troco: R$%.2f\n", troco);
            }
            VZonda[Pos].Status = 3;
            printf(" Moto concluída!");
            SalvarServicosIncompletos(); // Salvar as alterações
        }
    }
}

void EncerrarExpediente() {
    int concluiu = 0, removeu = 0;

    system("clear");
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if (Quant == -1) {
        printf(" Nenhuma moto no sistema!");
    } else {
        for (int Cont = 0; Cont <= Quant; Cont++) {
            if (VZonda[Cont].Status == 3)
                concluiu++;
            else if (VZonda[Cont].Status == 2)
                removeu++;
        }

        // Salvando os serviços incompletos apenas se houver motos incompletas
        if (concluiu + removeu != Quant + 1)
            SalvarServicosIncompletos();
    }

    printf("\n Quantidade de entradas: %d", Quant + 1);
    printf("\n Concluíram o serviço: %d", concluiu);
    printf("\n Removeram o serviço: %d", removeu);
    printf("\n Total arrecadado: R$%.2f", dinheiro);
}


int main() {
    int Opcao;
    system("clear"); // limpa tela no ReplIt

    // Inicializando registros
    InicializarRegistros();

    do {
        //Exibicao de menu e leitura da opcao. 	
        printf("\n\n >>> Motos Zonda <<< \n\n");
        printf("1 - Solicitar Servico \n");
        printf("2 - Iniciar Servico \n");
        printf("3 - Remover Solicitacao \n");
        printf("4 - Consultar Solicitacoes \n");
        printf("5 - Concluir Servico \n");
        printf("6 - Encerrar Expediente \n");
        printf("7 - Histórico Financeiro \n");
        printf("8 - Sair \n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &Opcao);
        switch (Opcao) {
            case 1:
                SolicitaServico();
                break;
            case 2:
                IniciaServico();
                break;
            case 3:
                RemoverSolicitacao();
                break;
            case 4:
                ConsultarSolicitacoes();
                break;
            case 5:
                ConcluirServico();
                break;
            case 6:
                EncerrarExpediente();
                break;
            case 7:
                MostrarHistoricoFinanceiro();
                break;
            case 8:
                break;
        }
    } while (Opcao != 8);

    return 0;
}
