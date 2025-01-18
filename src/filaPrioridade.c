#include "filaPrioridade.h"

void FazFilaVazia(FilaPrioridade *fila) {
    fila->inicio = NULL;
    fila->numClientes = 0;
}

void InsereNaFila(FilaPrioridade *fila, Cliente *cli) {
    if (cli == NULL) return;

    NoFila *aux = fila->inicio;
    NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
    novoNo->cliente = cli;
    novoNo->prox = NULL;

    if (FilaVazia(fila) || aux->cliente->numPrioridade > cli->numPrioridade) {
        novoNo->prox = fila->inicio;
        fila->inicio = novoNo;
        fila->numClientes++;
        return;
    }

    NoFila *anterior = NULL;

    while (aux != NULL && aux->cliente->numPrioridade <= cli->numPrioridade) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux != NULL && aux->cliente->numPrioridade == cli->numPrioridade) {
        while (aux != NULL && aux->cliente->numPrioridade == cli->numPrioridade) {
            anterior = aux;
            aux = aux->prox;
        }
    }

    if (anterior == NULL) {
        fila->inicio = novoNo;
    } else {
        anterior->prox = novoNo;
    }
    novoNo->prox = aux;

    fila->numClientes++;
}

void RemoveDaFila(FilaPrioridade *fila) {
    if (FilaVazia(fila)) {
        printf("\nNão há clientes para serem atendidos nessa fila\n");
        return;
    }

    printf("here\n");
    NoFila *aux = fila->inicio;

    fila->inicio = aux->prox;
    free(aux);

    fila->numClientes--;
    printf("\nCliente atendido com sucesso\n");
}

void EsvaziaFila(FilaPrioridade *fila) {
    while (!FilaVazia(fila)) {
        NoFila *aux = fila->inicio;
        fila->inicio = aux->prox;
        free(aux);
        fila->numClientes--;
    }
}


bool FilaVazia(FilaPrioridade *fila) {
    return fila->inicio == NULL;
}

void ImprimirFila(FilaPrioridade *fila) {
    if (FilaVazia(fila)) return;

    NoFila *aux = fila->inicio;

    while (aux) {
        ImprimirCliente(aux->cliente);
        aux = aux->prox;
    }
}

void ImprimirCliente(Cliente *cli) {
    printf("\n----------------CLIENTE----------------\n");
    printf("Nome: %s\n", cli->nome);
    printf("CPF: %ld\n", cli->cpfCliente);
    printf("Número de itens no carrinho: %u\n", cli->numItens);
    printf("Prioridade: ");

    if (cli->numPrioridade == 1) {
        printf("ALTA\n");
    } else if (cli->numPrioridade == 2) {
        printf("MÉDIA\n");
    } else {
        printf("BAIXA\n");
    }
}