#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    char cidade[50];
    char sexo[2];
    char cpf[15];
    int dia, mes, ano;
}registro;

void consultar(registro **r, int quant){
    int i;

    printf("\n\t\t\t\tCADASTROS\n");
    printf("\t------------------------------------------------------\n");
    for(i=0; i<quant; i++){
        printf("\t%d = %s - %s - %s - %s - %2d/%2d/%4d\n", i+1, r[i]->nome, r[i]->cidade, r[i]->sexo, r[i]->cpf, r[i]->dia, r[i]->mes, r[i]->ano);
    }
    printf("\t------------------------------------------------------\n");

}

int cadastrar(registro **r, int quant, int tam){

    if(quant < tam){
        registro *novo = malloc(sizeof(registro));

        printf("\nDigite o nome da pessoa: ");
        scanf("%50[^\n]", novo->nome);
        getchar();

        printf("\nDigite a cidade natal: ");
        scanf("%50[^\n]", novo->cidade);
        getchar();

        printf("\nDigite seu sexo: F, M ou O 'Outro': ");
        scanf("%2[^\n]", novo->sexo);
        getchar();

        printf("\nDigite seu CPF 'Somente numeros': ");
        scanf("%15[^\n]", novo->cpf);
        getchar();

        printf("\nDigite a data de nascimento: dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();

        r[quant] = novo;
        return 1;
    }
    else{
        printf("\n\n\tErro no cadastro, base cheia.\n");
        return 0;
    }
}

void alterar(registro **r, int quant){

    int id;
    consultar(r, quant);

    printf("\n\tDigite o codigo do cadastro que deseja alterar: ");
    scanf("%d", &id);
    getchar();
    id--;

    if(id >= 0 && id < quant){
        registro *novo = malloc(sizeof(registro));

        printf("\nDigite o nome da pessoa: ");
        scanf("%50[^\n]", novo->nome);
        getchar();

        printf("\nDigite a cidade natal: ");
        scanf("%50[^\n]", novo->cidade);
        getchar();

        printf("\nDigite seu sexo: F, M ou O 'Outro': ");
        scanf("%2[^\n]", novo->sexo);
        getchar();

        printf("\nDigite seu CPF 'Somente numeros': ");
        scanf("%15[^\n]", &novo->cpf);
        getchar();

        printf("\nDigite a data de nascimento: dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();

        r[id] = novo;

    }
    else{
        printf("\n\nCodigo invalido.\n");
    }
}

void salvar (registro **r, int quant, char arq[]){
    FILE *file = fopen(arq, "w");
    int i;

    if(file){
        fprintf(file, "%d\n", quant);
        for(i = 0;i < quant; i++){
            fputs(r[i]->nome, file);
            fputs(r[i]->cidade, file);
            fputs(r[i]->sexo, file);
            fputs(r[i]->cpf, file);
            fprintf(file, "%d %d %d\n", r[i]->dia, r[i]->mes, r[i]->ano);
        }
        fclose(file);

    }else{
       printf("\n\t\nNao foi possivel abrir e/ou criar o arquivo!\n");
    }
}

int ler_arquivo(registro **r, char arq[]){
    FILE *file = fopen(arq, "r");
    int quant = 0, i;
    registro *novo = malloc(sizeof(registro));

    if(file){
        fscanf(file, "%d\n", &quant);
        for(i = 0; i < quant; i++){
            fscanf(file, "%50[^\n]", novo->nome);
            fscanf(file, "%50[^\n]", novo->cidade);
            fscanf(file, "%2[^\n]", novo->sexo);
            fscanf(file, "%15[^\n]", novo->cpf);
            fscanf(file, "%d %d %d\n", &novo->dia, &novo->mes, &novo->ano);
            r[i] = novo;
            novo = malloc(sizeof(registro));
        }
        fclose(file);

    }else{
        printf("Nao foi possivel ler o arquivo!\n");
    }
    return quant;
}


int main(){

    registro *base[50];
    char arquivo[] = {"bancoDados.txt"};
    int opcao, tam = 50, quant = 0;

    do{
        printf("\n0 - Sair.\n");
        printf("\n1 - Cadastrar.\n");
        printf("\n2 - Alterar.\n");
        printf("\n3 - Consultar.\n");
        printf("\n4 - Salvar.\n");
        printf("\n5 - Ler base.\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1:
            quant += cadastrar(base, quant, tam);
            break;
        case 2:
            alterar(base, quant);
            break;
        case 3:
            consultar(base, quant);
            break;
        case 4:
            salvar(base, quant, arquivo);
            break;
        case 5:
            quant = ler_arquivo(base, arquivo);
            break;
        default:
            if(opcao != 0){
               printf("\n\tOpcao invalida!\n");
            }
        }

    }while(opcao != 0);

    return 0;
}
