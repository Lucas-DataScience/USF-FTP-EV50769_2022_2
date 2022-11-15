#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50]; //nome com tipo char de 50 posicoes.
    char cidade[50]; //cidade com tipo char de 50 posicoes.
    char sexo[2]; //sexo com tipo char de 2 posicoes.
    char cpf[15]; //cpf com tipo char de 15 posicoes.
    int dia, mes, ano; //dia, mes e ano com tipo int.
}registro;
/* Acima apresenta a estrutura dos dados do sistema.*/

void consultar(registro **r, int quant){
    int i;

    printf("\n\t\t\t\t\tCADASTROS\n"); //Imprimi o layout na tela.
    printf("\t-------------------------------------------------------------------------\n"); //Imprimi o layout na tela.
    for(i=0; i<quant; i++){
        printf("\t%d = %s - %s - %s - %s - %2d/%2d/%4d\n", i+1, r[i]->nome, r[i]->cidade, r[i]->sexo, r[i]->cpf, r[i]->dia, r[i]->mes, r[i]->ano);
    }
    /* Acima mostra a impressao na tela do vetor, mostrando todos os itens e suas formatacoes. */
    printf("\t-------------------------------------------------------------------------\n"); //Imprimi o layout na tela.
}
/* Acima apresenta a funcao de consulta dos itens do vetor em memoria ou arquivo .txt */

int cadastrar(registro **r, int quant, int tam){

    if(quant < tam){ //Verifica que ha espaco no vetor.
        registro *novo = malloc(sizeof(registro)); //Aloca espaco na memoria RAM para o novo registro.

        printf("\nDigite o nome da pessoa: "); //Mostra na tela a instrucao para o usuario.
        scanf("%50[^\n]", novo->nome);         //Captura as informacoes digitadas no teclado.
        getchar();                             //'Limpa' o enter.

        printf("\nDigite a cidade natal: "); //Mostra na tela a instrucao para o usuario.
        scanf("%50[^\n]", novo->cidade);     //Captura as informacoes digitadas no teclado.
        getchar();                           //'Limpa' o enter.

        printf("\nDigite seu sexo: F, M ou O 'Outro': "); //Mostra na tela a instrucao para o usuario.
        scanf("%2[^\n]", novo->sexo);                     //Captura as informacoes digitadas no teclado.
        getchar();                                        //'Limpa' o enter.

        printf("\nDigite seu CPF 'Somente numeros': "); //Mostra na tela a instrucao para o usuario.
        scanf("%15[^\n]", novo->cpf);                   //Captura as informacoes digitadas no teclado.
        getchar();                                      //'Limpa' o enter.

        printf("\nDigite a data de nascimento: dd mm aaaa: ");  //Mostra na tela a instrucao para o usuario.
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);    //Captura as informacoes digitadas no teclado.
        getchar();                                              //'Limpa' o enter.

        r[quant] = novo; //Salvar no vetor as informacoes digitadas no teclado.
        return 1;
    }
    else{
        printf("\n\n\tErro no cadastro, base cheia.\n"); //Caso o vetor esteja cheio ira retornar a mensagem de erro.
        return 0;
    }
}
/* Acima apresenta a funcao para realizar o cadastro dos clientes no vetor. */

void alterar(registro **r, int quant){

    int id;
    consultar(r, quant);

    printf("\n\tDigite o codigo do cadastro que deseja alterar: "); //Mostra na tela a instrucao para o usuario.
    scanf("%d", &id);                                               //Captura as informacoes digitadas no teclado.
    getchar();                                                      //'Limpa' o enter.
    id--;                                                           //Subtrai o numero do ID em -1 que e a posicao correta dentro do vetor.

    if(id >= 0 && id < quant){
        registro *novo = malloc(sizeof(registro));  //Aloca espaco na memoria RAM para o novo registro.

        printf("\nDigite o nome da pessoa: ");  //Mostra na tela a instrucao para o usuario.
        scanf("%50[^\n]", novo->nome);          //Captura as informacoes digitadas no teclado.
        getchar();                              //'Limpa' o enter.

        printf("\nDigite a cidade natal: ");    //Mostra na tela a instrucao para o usuario.
        scanf("%50[^\n]", novo->cidade);        //Captura as informacoes digitadas no teclado.
        getchar();                              //'Limpa' o enter.

        printf("\nDigite seu sexo: F, M ou O 'Outro': ");   //Mostra na tela a instrucao para o usuario.
        scanf("%2[^\n]", novo->sexo);                       //Captura as informacoes digitadas no teclado.
        getchar();                                          //'Limpa' o enter.

        printf("\nDigite seu CPF 'Somente numeros': "); //Mostra na tela a instrucao para o usuario.
        scanf("%15[^\n]", &novo->cpf);                  //Captura as informacoes digitadas no teclado.
        getchar();                                      //'Limpa' o enter.

        printf("\nDigite a data de nascimento: dd mm aaaa: ");  //Mostra na tela a instrucao para o usuario.
        scanf("%d %d %d", &novo->dia, &novo->mes, &novo->ano);  //Captura as informacoes digitadas no teclado.
        getchar();                                              //'Limpa' o enter.

        r[id] = novo; //Salva as novas informacoes dentro do vetor.
    }
    else{
        printf("\n\nCodigo invalido.\n"); //Caso digite o codigo invalido retorna a mensagem com erro.
    }
}
/* Acima apresenta a funcao para alterar o registro no vetor em memoria. */

int excluir(registro **r, int quant){

    int id;
    consultar(r, quant);

    printf("\n\tDigite o codigo do cadastro que deseja excluir: "); //Mostra na tela a instrucao para o usuario.
    scanf("%d", &id);                                               //Captura as informacoes digitadas no teclado.
    getchar();                                                      //'Limpa' o enter.
    id--;                                                           //Subtrai o numero do ID em -1 que e a posicao correta dentro do vetor.

    if(id >= 0 && id < quant){
        free(r[id]); //Libera o espaco da memoria.
        if(id < quant - 1){
           r[id] = r[quant - 1]; //Copia o ultimo registro para posicao apagada e deixa a ultima posicao em branco para que seja realizada um novo cadstro.
        }
        return -1;
    }
    else{
        printf("\n\nCodigo invalido.\n"); //Caso digite o codigo invalido retorna a mensagem com erro.
        return 0;
    }
}
/* Acima apresenta a funcao para excluir os registros do vetor. */

void salvar (registro **r, int quant, char arq[]){
    FILE *file = fopen(arq, "w"); //Abre o arquivo no modo escrita.
    int i;

    if(file){
        fprintf(file, "%d\n", quant); //Escreve na tela a quantidade de registros que existe dentro do arquivo.
        for(i = 0;i < quant; i++){
            fputs(r[i]->nome, file);                                        //Salva o nome dentro do arquivo .txt.
            fputs(r[i]->cidade, file);                                      //Salva a cidade dentro do arquivo .txt.
            fputs(r[i]->sexo, file);                                        //Salva o sexo dentro do arquivo .txt.
            fputs(r[i]->cpf, file);                                         //Salva o cpf dentro do arquivo .txt.
            fprintf(file, "%d +'/'+ %d +'/'+ %d\n", r[i]->dia, r[i]->mes, r[i]->ano);   //Salva a data de nascimento dentro do arquivo .txt.
        }
        fclose(file); //Fecha o arquivo .txt

    }else{
       printf("\n\t\nNao foi possivel abrir e/ou criar o arquivo!\n"); //Mensagem de erro caso nao for possivel abrir o arquivo .txt.
    }
}
/* Acima apresenta a funcao para salvar os registros do vetor que estao em memoria em um arquivo .txt */

int ler_arquivo(registro **r, char arq[]){
    FILE *file = fopen(arq, "r"); //Abre o arqivo .txt no modo de leitura.
    int quant = 0, i;
    registro *novo = malloc(sizeof(registro)); //Aloca espaco na memoria RAM para o novo registro.

    if(file){
        fscanf(file, "%d\n", &quant); //Le a quantidade de registros salvos dentro do arquivo .txt.
        for(i = 0; i < quant; i++){
            fscanf(file, "%50[^\n]", novo->nome);                           //Le o nome.
            fscanf(file, "%50[^\n]", novo->cidade);                         //Le a cidade.
            fscanf(file, "%2[^\n]", novo->sexo);                            //Le o sexo.
            fscanf(file, "%15[^\n]", novo->cpf);                            //Le o cpf.
            fscanf(file, "%d %d %d\n", &novo->dia, &novo->mes, &novo->ano); //Le a data de nascimento.
            r[i] = novo;                                                    //Salva dentro do vetor na memoria.
            novo = malloc(sizeof(registro));                                //Aloca espaco na memoria RAM para o novo registro.
        }
        fclose(file);                                                       //Fecha o arquivo .txt.

    }else{
        printf("Nao foi possivel ler o arquivo!\n"); //Mostra mensagem de erro caso nao for possivel ler o arquivo .txt.
    }
    return quant;
}
/* Acima apresenta a funcao que e utilizada para ler a base de dados 'arquivo .txt' que contem os registros,
quando executada carrega as informacoes no vetor em memoria. */


int main(){

    registro *base[50];                     //Vetor de ponteiro para base de dados com 50 posicoes.
    char arquivo[] = {"bancoDados.txt"};    //Cria o arquivo .txt dentro da pasta raiz do main.c.
    int opcao, tam = 50, quant = 0;

    do{
        printf("\n0 - Sair.\n");            // -
        printf("\n1 - Cadastrar.\n");       //   -
        printf("\n2 - Alterar.\n");         //     -
        printf("\n3 - Consultar.\n");       //      Imprimi na tela as opcoes do menu principal para navegacao do usuario.
        printf("\n4 - Salvar.\n");          //     -
        printf("\n5 - Ler base.\n");        //   -
        printf("\n6 - Excluir.\n");         // -
        scanf("%d", &opcao);                //Le a opcao digitada no teclado.
        getchar();                          //'Limpa' o enter.

        switch(opcao){
        case 1:
            quant += cadastrar(base, quant, tam);   //Chama a funcao de cadastro.
            break;
        case 2:
            alterar(base, quant);                   //Chama a funcao de alterar cadastro.
            break;
        case 3:
            consultar(base, quant);                 //Chama a funcao de consultar os cadastros.
            break;
        case 4:
            salvar(base, quant, arquivo);           //Chama a funcao de salvar as informacoes no arquivo .txt.
            break;
        case 5:
            quant = ler_arquivo(base, arquivo);     //Chama a funcao para ler a base de dados 'arquivo .txt.'
            break;
        case 6:
            quant += excluir(base, quant);          //Chama a funcao para excluir um cadastro.
            break;
        default:
            if(opcao != 0){
               printf("\n\tOpcao invalida!\n");     //Mensagem de erro para opcao digitada errada.
            }
        }
    }while(opcao != 0); //Opcao zero finaliza o programa.
    return 0;
}
/* Acima apresenta o menu principal do programa, onde tem as opcoes a serem escolhidas pelo usuario e apos a escolha e chamado a funcao. */
