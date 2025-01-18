#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Cliente {
    char *nome;
    long int cpfCliente;
    unsigned int numPrioridade;
    unsigned int numItens;
} Cliente;

typedef struct NoFila {
    Cliente *cliente;
    struct NoFila *prox;
} NoFila;

typedef struct FilaPrioridade {
    NoFila *inicio;
    unsigned int numClientes;
} FilaPrioridade;

void FazFilaVazia(FilaPrioridade *fila);

void InsereNaFila(FilaPrioridade *fila, Cliente *cli);
void RemoveDaFila(FilaPrioridade *fila);

bool FilaVazia(FilaPrioridade *fila);

void EsvaziaFila(FilaPrioridade *fila);

void ImprimirFila(FilaPrioridade *fila);

void ImprimirCliente(Cliente *cli);

#endif