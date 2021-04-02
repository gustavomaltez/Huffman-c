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
    printf("%c",no->dado);

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
    noDeFrequencia *no;

    no->dado = dado;
    no->proximo = NULL;
    no->frequencia = 1;

    //Caso a lista esteja vazia aponta a raiz para o nó
    if (raizFrequencia == NULL)
    {
        raizFrequencia->proximo = no;
    }
    else
    { //Caso contrario, percorre até o último nó e o adiciona posteriormente
        noDeFrequencia *noAuxiliar = raizFrequencia;

        do
        {
            noAuxiliar = noAuxiliar->proximo;
        } while (noAuxiliar->proximo != NULL);

        noAuxiliar->proximo = no;
    }
}

void contabilizarFrequenciaDoDado(char dado)
{
    //Busca pelo dado
    noDeFrequencia *no = buscarNoDeFrequenciaDoDado(raizFrequencia, dado);

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

void imprimirLista(noDeFrequencia *no)
{   
    printf("DADO: %c, FREQUENCIA %d", no->dado, no->frequencia);

    while(no->proximo != NULL){
        return imprimirLista(no->proximo);
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

        contabilizarFrequenciaDoDado(c);
        //exibe o caracter lido na tela
        printf("%c", c);

    } while (c != EOF);

    imprimirLista(raizFrequencia);
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