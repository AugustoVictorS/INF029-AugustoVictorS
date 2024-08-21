#include <stdio.h>
#include <stdlib.h>
#include "EstruturaVetores.h"
#define TAM 10

Vetor vetorPrincipal[TAM];


int ehPosicaoValida(int posicao){
    return (posicao >= 1 && posicao <= 10);
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao' com tamanho 'tamanho'.

Retorno (int):
    SUCESSO - Estrutura criada com sucesso.
    JA_TEM_ESTRUTURA_AUXILIAR - Já existe uma estrutura na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
    SEM_ESPACO_DE_MEMORIA - Falha na alocação de memória.
    TAMANHO_INVALIDO - O tamanho deve ser maior ou igual a 1.
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (tamanho <= 0){
        retorno = TAMANHO_INVALIDO;
    } else if (vetorPrincipal[posicao - 1].array != NULL){
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    } else {
        vetorPrincipal[posicao - 1].array = malloc(sizeof(int) * tamanho);

        if (vetorPrincipal[posicao - 1].array == NULL){
            retorno = SEM_ESPACO_DE_MEMORIA;
        } else {
            vetorPrincipal[posicao - 1].tamanho = tamanho;
            vetorPrincipal[posicao - 1].quantidade = 0;
            retorno = SUCESSO;
        }
    }
    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'.

Retorno (int):
    SUCESSO - Inserido com sucesso.
    SEM_ESPACO - Estrutura auxiliar sem espaço disponível.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else if (vetorPrincipal[posicao - 1].quantidade == vetorPrincipal[posicao - 1].tamanho) {
        retorno = SEM_ESPACO;
    } else {
        vetorPrincipal[posicao - 1].array[vetorPrincipal[posicao - 1].quantidade] = valor;
        vetorPrincipal[posicao - 1].quantidade++;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: excluir o número final da estrutura auxiliar da posição 'posicao'.

Retorno (int):
    SUCESSO - Excluído com sucesso.
    ESTRUTURA_AUXILIAR_VAZIA - Estrutura auxiliar está vazia.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else if (vetorPrincipal[posicao - 1].quantidade == 0) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    } else {
        vetorPrincipal[posicao - 1].quantidade--;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: excluir o número 'valor' da estrutura auxiliar da posição 'posicao'.
Caso o número seja encontrado, os números posteriores devem ser movidos para preencher a lacuna.

Retorno (int):
    SUCESSO - Excluído com sucesso.
    NUMERO_INEXISTENTE - Número não encontrado na estrutura auxiliar.
    ESTRUTURA_AUXILIAR_VAZIA - Estrutura auxiliar está vazia.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int encontrado = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else if (vetorPrincipal[posicao - 1].quantidade == 0) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    } else {
        for (int i = 0; i < vetorPrincipal[posicao - 1].quantidade; i++) {
            if (vetorPrincipal[posicao - 1].array[i] == valor) {
                encontrado = 1;
                for (int j = i; j < vetorPrincipal[posicao - 1].quantidade - 1; j++) {
                    vetorPrincipal[posicao - 1].array[j] = vetorPrincipal[posicao - 1].array[j + 1];
                }
                vetorPrincipal[posicao - 1].quantidade--;
                retorno = SUCESSO;
                break;
            }
        }
        if (!encontrado) {
            retorno = NUMERO_INEXISTENTE;
        }
    }

    return retorno;
}

/*
Objetivo: retornar os números da estrutura auxiliar da posição 'posicao'.
Os números devem ser armazenados em 'vetorAux'.

Retorno (int):
    SUCESSO - Recuperado com sucesso.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else {
        for (int i = 0; i < vetorPrincipal[posicao - 1].quantidade; i++) {
            vetorAux[i] = vetorPrincipal[posicao - 1].array[i];
        }
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retornar os números ordenados da estrutura auxiliar da posição 'posicao'.
Os números devem ser armazenados em 'vetorAux'.

Retorno (int):
    SUCESSO - Recuperado com sucesso.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
*/

// Função auxiliar para o merge no Merge Sort
void merge(int vetorAux[], int inicio, int meio, int fim)
{
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = vetorAux[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = vetorAux[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetorAux[k] = L[i];
            i++;
        } else {
            vetorAux[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetorAux[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetorAux[k] = R[j];
        j++;
        k++;
    }
}

// Função auxiliar para ordenação Merge Sort
void mergeSort(int vetorAux[], int inicio, int fim)
{
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetorAux, inicio, meio);
        mergeSort(vetorAux, meio + 1, fim);
        merge(vetorAux, inicio, meio, fim);
    }
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else {
        for (int i = 0; i < vetorPrincipal[posicao - 1].quantidade; i++) {
            vetorAux[i] = vetorPrincipal[posicao - 1].array[i];
        }
        mergeSort(vetorAux, 0, vetorPrincipal[posicao - 1].quantidade - 1);
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retornar os números de todas as estruturas auxiliares, na ordem que aparecem na estrutura principal.
Os números devem ser armazenados em 'vetorAux'.

Retorno (int):
    SUCESSO - Recuperado com sucesso.
    ESTRUTURA_AUXILIAR_VAZIA - Nenhuma estrutura auxiliar possui números.
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int indice = 0;
    int encontrouElemento = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].array != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[indice] = vetorPrincipal[i].array[j];
                indice++;
                encontrouElemento = 1;
            }
        }
    }

    if (!encontrouElemento) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    } else {
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retornar os números ordenados de todas as estruturas auxiliares.
Os números devem ser armazenados em 'vetorAux'.

Retorno (int):
    SUCESSO - Recuperado com sucesso.
    ESTRUTURA_AUXILIAR_VAZIA - Nenhuma estrutura auxiliar possui números.
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int quantidadeTotal = 0;
    int encontrouElemento = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].array != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[quantidadeTotal] = vetorPrincipal[i].array[j];
                quantidadeTotal++;
                encontrouElemento = 1;
            }
        }
    }

    if (!encontrouElemento) {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    } else {
        mergeSort(vetorAux, 0, quantidadeTotal - 1);
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar na posição 'posicao' para um novo tamanho 'novoTamanho'.
O novo tamanho pode ser maior ou menor que o tamanho atual.

Retorno (int):
    SUCESSO - Tamanho modificado com sucesso.
    SEM_ESTRUTURA_AUXILIAR - Não existe estrutura auxiliar na posição.
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar.
    SEM_ESPACO_DE_MEMORIA - Falha na alocação de memória para o novo tamanho.
    NOVO_TAMANHO_INVALIDO - O novo tamanho não pode ser menor que a quantidade de elementos já existente.
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;

    if (!ehPosicaoValida(posicao)){
        retorno = POSICAO_INVALIDA;
    } else if (vetorPrincipal[posicao - 1].array == NULL) {
        retorno = SEM_ESTRUTURA_AUXILIAR;
    } else if (novoTamanho < vetorPrincipal[posicao - 1].quantidade) {
        retorno = NOVO_TAMANHO_INVALIDO;
    } else {
        int *novoArray = realloc(vetorPrincipal[posicao - 1].array, sizeof(int) * novoTamanho);

        if (novoArray == NULL) {
            retorno = SEM_ESPACO_DE_MEMORIA;
        } else {
            vetorPrincipal[posicao - 1].array = novoArray;
            vetorPrincipal[posicao - 1].tamanho = novoTamanho;
            retorno = SUCESSO;
        }
    }

    return retorno;
}
/*Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
    int getQuantidadeElementosEstruturaAuxiliar(int posicao)
    {
        int resultado = 0;

        if (!ehPosicaoValida(posicao)) {
            resultado = POSICAO_INVALIDA;
        } else if (vetorPrincipal[posicao - 1].array != NULL) {
            if (vetorPrincipal[posicao - 1].quantidade == 0) {
                resultado = ESTRUTURA_AUXILIAR_VAZIA;
            } else {
                resultado = vetorPrincipal[posicao - 1].quantidade;
            }
        } else {
            resultado = SEM_ESTRUTURA_AUXILIAR;
        }

        return resultado;
    }


/*
Objetivo: retornar a quantidade total de elementos em todas as estruturas auxiliares.

Retorno (int):
    A quantidade total de elementos em todas as estruturas auxiliares.
*/
int getQuantidadeElementosDeTodasEstruturasAuxiliares()
{
    int quantidadeTotal = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].array != NULL) {
            quantidadeTotal += vetorPrincipal[i].quantidade;
        }
    }

    return quantidadeTotal;
}
/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/

No *montarListaEncadeadaComCabecote()
{
    No *no = (No*)malloc(sizeof(No));
    if(no == NULL){
        return NULL;
    }
    no->prox = NULL;
    return no;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No *atual = inicio->prox;  // Começa após o cabeçote

    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        i++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio != NULL && *inicio != NULL) {
        No *atual = (*inicio)->prox;
        No *proxNo;

        while (atual != NULL) {
            proxNo = atual->prox;
            free(atual);
            atual = proxNo;
        }

        free(*inicio);  // Libera o cabeçote
        *inicio = NULL;  // Define o ponteiro de início como NULL
    }
}


/*
Objetivo: liberar a memória de todas as estruturas auxiliares e inicializar as variáveis globais.

Retorno (void).
*/
void inicializar()
{
    for (int a=0; a<TAM; a++){
        vetorPrincipal[a].array = NULL;
    }
}

void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].array != NULL) {
            free(vetorPrincipal[i].array);
            vetorPrincipal[i].array = NULL;
            vetorPrincipal[i].tamanho = 0;
            vetorPrincipal[i].quantidade = 0;
        }
    }
}
