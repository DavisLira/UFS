// Projeto pague pouco

#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp

struct TpFarma{
	char Nome[21];
	float Preco;
	int QEstoque;
};
  
typedef struct TpFarma TpFARMA;

TpFARMA RgFarma;
  
FILE *ArqFarma;

long int Tamanho = 21 * sizeof(char) + sizeof(float) + sizeof(int);
// long int Tamanho = sizeof(tpFarma);

void Incluir() {
    char R;

    do{
        //system("cls");
        char Farmaco[21];

        printf("*** inclusao ***\n\n");
        printf("Nome: ");
        scanf("%s",Farmaco);
        int Achou=0;
        char add;

        fseek(ArqFarma, 0, SEEK_SET);

        do {
            fread(&RgFarma,Tamanho,1,ArqFarma);

            if (strcmp(RgFarma.Nome,Farmaco) == 0){
                Achou = 1;
            }
        } while (!feof(ArqFarma) && (Achou==0));

        if (Achou == 0) {
            strcpy(RgFarma.Nome, Farmaco);
            printf("Preco: ");
            scanf("%f",&RgFarma.Preco);
            printf("Estoque: ");
            scanf("%d",&RgFarma.QEstoque);
            fseek(ArqFarma,0,2);
            fwrite(&RgFarma,Tamanho,1,ArqFarma);
        } else if(RgFarma.QEstoque == 0) {
            // Melhoria para adicionar excluído
            printf("Esse fármaco está excluído!\n");       
            printf("Deseja adicionar ao estoque? S/N ");
            scanf(" %c",&add);
            add = toupper(add);
            if (add == 'S') {
                printf("\nQuantidade: ");
                scanf("%d",&RgFarma.QEstoque);
                fseek(ArqFarma, -Tamanho, SEEK_CUR);
                fwrite(&RgFarma, Tamanho, 1, ArqFarma);
            }
        } else {
            printf("Esse fármaco ja esta salvo!\n");
        }

        printf("\nNova inclusao? S/N ");
        scanf(" %c",&R);
        R=toupper(R);
    } while (R!='N');

    return;
}

long int TArquivo(){
	fseek(ArqFarma,0,2);
	long int R=ftell(ArqFarma)/Tamanho;
	return R;
}

void Excluir(){
    printf("*** excluir ***\n\n");
    fseek(ArqFarma,0,0);
    printf("Qual farmaco? ");
    char Farmaco[21];
    scanf("%s",Farmaco);
    int Achou=0;

    do {
        fread(&RgFarma,Tamanho,1,ArqFarma);

        if (strcmp(RgFarma.Nome,Farmaco) == 0){
            Achou = 1;	
            printf("Nome: %s\n",RgFarma.Nome);
            printf("Valor: %f\n",RgFarma.Preco);
            printf("Estoque: %d\n",RgFarma.QEstoque);
        }

    } while (!feof(ArqFarma) && (Achou==0));

    if (Achou == 0)
        printf("Registro inexistente!"); 
    else{
        char resp;
        printf("Confirmar exclusao S|N? ");
        scanf(" %c", &resp);
        resp = toupper(resp);

        if (resp == 'S') {
            RgFarma.QEstoque = 0;
            fseek(ArqFarma,-Tamanho,1);
            fwrite(&RgFarma,Tamanho,1,ArqFarma);
            printf(">>> Remocao efetuada com sucesso! <<<\n");
            fclose(ArqFarma);
            ArqFarma=fopen("Farmacos.dat","a+b");
        }
        if(resp == 'N') {
            printf(">>> Remocao cancelada! <<<\n");
        }
    }
    return;
}

void Alterar() {
    printf("*** alterar ***\n\n");
    fseek(ArqFarma,0,0);
    printf("Qual farmaco? ");
    char Farmaco[21];
    scanf("%s",Farmaco);
    int Achou=0;

    do {
        fread(&RgFarma,Tamanho,1,ArqFarma);

        if (strcmp(RgFarma.Nome,Farmaco) == 0){
            Achou = 1;	
            printf("Nome: %s\n",RgFarma.Nome);
            printf("Valor: %f\n",RgFarma.Preco);
            printf("Estoque: %d\n",RgFarma.QEstoque);
        }

    } while (!feof(ArqFarma) && (Achou==0));

    if (Achou == 0)
        printf("Registro inexistente!"); 
    else{
        char resp;
        printf("Qual a alteração? P|Q: ");
        scanf(" %c", &resp);
        resp = toupper(resp);

        if (resp == 'P')
        {
            printf("Qual o novo preco? \n"); 
            scanf("%f",&RgFarma.Preco);
        }
        if (resp == 'Q')
        {
            printf("Qual a nova quantidade? \n");
            scanf("%d",&RgFarma.QEstoque);
        }
        
        fseek(ArqFarma,-Tamanho,1);
        fwrite(&RgFarma,Tamanho,1,ArqFarma);
        printf(">>> Alteracao efetuada com sucesso! <<<\n");
    }

    //system("pause");
    fclose(ArqFarma);
    ArqFarma=fopen("Farmacos.dat","a+b");
    return;
}
	
// Melhoria para modos de edição
void Editar(char modo){
    if (TArquivo()!=0){
        fclose(ArqFarma); //modo a + b
        ArqFarma=fopen("Farmacos.dat","r+b");
        //system("cls");
        if (modo == 'A') {
            Alterar();
        }
        if (modo == 'E') {
            Excluir();
        }
    
    } else {
        printf("Arquivo Vazio. Nao existem dados a alterar.");
    }
    //system("pause");

    return;
}

void Consultar(){
    //system("cls");
    printf("*** consulta ***\n\n");  
    fseek(ArqFarma,0,0);
    printf("Qual farmaco? ");
    char Farmaco[21];
    scanf("%s",Farmaco);
    int Achou=0;

    do{
	    fread(&RgFarma,Tamanho,1,ArqFarma);
	    if (strcmp(RgFarma.Nome,Farmaco) == 0){
	        Achou=1;
	        printf("Nome: %s\n",RgFarma.Nome);
            printf("Valor: R$%.2f\n",RgFarma.Preco);
            printf("Estoque: %d\n",RgFarma.QEstoque);}}
    while(!feof(ArqFarma) && (Achou==0));

    if (Achou==0)
      printf("Registro inexistente!");  
    //system("pause");
    return;
}

void LTodos(){
    //system("cls");
    printf("*** lista todos ***\n\n"); 
    fseek(ArqFarma,0,0);
    do {
        fread(&RgFarma,Tamanho,1,ArqFarma);
        if (!feof(ArqFarma) && RgFarma.QEstoque>0) {
            printf("Nome: %s\n",RgFarma.Nome);
            printf("Valor: R$%.2f\n",RgFarma.Preco);
            printf("Estoque: %d\n",RgFarma.QEstoque);
            printf("***\n\n");
        }
    } while (!feof(ArqFarma));

    //system("pause");
}

int main(){
    ArqFarma = fopen("Farmacos.dat","a+b");
    char Opcao;

    do{
	  //system("cls");
    printf("\n\n> > > Pague Pouco < < < \n\n");
    printf("Que deseja fazer? \n\n");
    printf("I - Incluir \n");  
    printf("E - Excluir \n");
    printf("A - Alterar \n");
    printf("C - Consultar \n");
    printf("T - Listar Todos \n");
    printf("S - Sair \n\n");
    scanf(" %c", &Opcao);
    Opcao = toupper(Opcao);

    switch (Opcao){
        case 'I': Incluir(); break; 
        case 'E': Editar('E'); break; 
        case 'A': Editar('A'); break; 
        case 'C': Consultar(); break; 
        case 'T': LTodos(); break;}} 
    while (Opcao != 'S');

    fclose(ArqFarma);
    return 0;
}