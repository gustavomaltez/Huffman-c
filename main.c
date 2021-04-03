#include <stdio.h>
#include <stdlib.h>

typedef struct noDeFrequencia
{
    char dado;
    unsigned int frequencia;
    struct noDeFrequencia *proximo;
} noDeFrequencia;

noDeFrequencia *raizFrequencia = NULL;

//Faz uma busca na lista encadeada de frequencia de dados por um dado especifico
noDeFrequencia *buscarNoDeFrequenciaDoDado(noDeFrequencia *no, char dado)
{
    //Retorna NULL se o nó passado como parametro for NULL
    if (no == NULL)
    {
        return NULL;
    }

    //Verifica se o dado é o que estamos procurando
    if (no->dado != dado)
    {
        //Se o dado não for o que estamos procurando e o ponteiro proximo for NULL
        //Então o dado não existe, logo retornamos NULL
        if (no->proximo == NULL)
        {
            return NULL;
        }

        //Caso o ponteiro proximo não seja null, então fazemos uma nova busca
        return buscarNoDeFrequenciaDoDado(no->proximo, dado);
    }
    else //Caso o dado do no for igual o que buscamos então retornamos o no
    {
        return no;
    }
}

void adicionarNoDeFrequencia(char dado)
{
    //Cria um novo nó
    noDeFrequencia *no = malloc(sizeof(noDeFrequencia));

    no->dado = dado;
    no->proximo = NULL;
    no->frequencia = 1;

    //Caso a lista esteja vazia adiciona o nó na raiz
    if (raizFrequencia == NULL)
    {
        raizFrequencia = no;
    }
    else
    { //Caso contrario, percorre até o último nó e o adiciona posteriormente
        noDeFrequencia *noAuxiliar = raizFrequencia;

        while (noAuxiliar->proximo != NULL)
        {
            noAuxiliar = noAuxiliar->proximo;
        }

        noAuxiliar->proximo = no;
    }
}

void contabilizarFrequenciaDoDado(char dado)
{
    //Busca pelo dado
    noDeFrequencia *no = malloc(sizeof(noDeFrequencia));
    no = buscarNoDeFrequenciaDoDado(raizFrequencia, dado);

    //Se o nó não existir, então criamos um
    if (no == NULL)
    {
        adicionarNoDeFrequencia(dado);
    }
    else //incrementa a frequencia do nó em 1
    {
        no->frequencia = no->frequencia + 1;
    }
}

void imprimirListaDeFrequencia(noDeFrequencia *no)
{
    printf("CARACTER: %c | V. NUMERICO: %d | FREQUENCIA %d\n", no->dado, no->dado, no->frequencia);

    while (no->proximo != NULL)
    {
        return imprimirListaDeFrequencia(no->proximo);
    }
}

//Essa função utiliza um tipo de "Buble Sort" para ordenar os elementos
void ordenaListaDeFrequenciaEmOrdemCrescente()
{   
    noDeFrequencia *noAuxiliar = raizFrequencia;
    int frequenciaAuxiliar;
    char dadoAuxiliar;

    //Percorre toda lista ordenando os nós
    while (noAuxiliar->proximo != NULL)
    {
        if (noAuxiliar->proximo->frequencia < noAuxiliar->frequencia)
        {   
            //Salva os valores antigos do nó antes de serem alterados
            frequenciaAuxiliar = noAuxiliar->frequencia;
            dadoAuxiliar = noAuxiliar->dado;

            //Passa os valores do nó a frente para o nó anterior
            noAuxiliar->dado = noAuxiliar->proximo->dado;
            noAuxiliar->frequencia = noAuxiliar->proximo->frequencia;

            //Passa os valores do nó anterior para o nó a frente
            noAuxiliar->proximo->dado = dadoAuxiliar;
            noAuxiliar->proximo->frequencia = frequenciaAuxiliar;

            //Volta o nó auxiliar para a raiz para começar outra verificação
            noAuxiliar = raizFrequencia;
        }

        //Caso a frequencia do proximo não seja menor que a frequencia do atual
        //Apenas avança para o proximo nó, fazendo uma nova verificação
        noAuxiliar = noAuxiliar->proximo;
    }
}

int main()
{
    FILE *pont_arq = fopen("test.txt", "r");
    char c;

    do
    {
        //faz a leitura do caracter no arquivo apontado por pont_arq
        c = getc(pont_arq);

        //Verifica se o caracter é diferente de -1
        //Nos testes o -1 retorna sempre no final do texto e pode ser confundido com um espaço
        if (c != -1)
        {
            contabilizarFrequenciaDoDado(c);
        }

        //exibe o caracter lido na tela

    } while (c != EOF);

    //Imprime a lista de frequencia de caracteres (essa função é apenas para debugar)
    imprimirListaDeFrequencia(raizFrequencia);
    ordenaListaDeFrequenciaEmOrdemCrescente();
    printf("\n\n ---------- \n\n");
    imprimirListaDeFrequencia(raizFrequencia);
    return 0;
}

// typedef struct noDeHuffman
// {
//     char dado;
//     unsigned int frequencia;
//     struct noDeHuffman *esquerda;
//     struct noDeHuffman *direita;
// } noDeHuffman;

// noDeHuffman *raiz = NULL;

// noDeHuffman *criarNovoNoDeHuffman(char dado, unsigned int frequencia)
// {
//     noDeHuffman *no = malloc(sizeof(noDeHuffman));

//     if (no)
//     {
//         no->dado = dado;
//         no->frequencia = frequencia;
//         no->esquerda = NULL;
//         no->direita = NULL;
//     }

//     return no;
// }