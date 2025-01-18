#ifndef CAIXA_H
#define CAIXA_H

#include "filaPrioridade.h"

typedef struct Caixa {
    bool estado;
    FilaPrioridade *fila;
    /*
        0-fechado
        1-aberto
    */
} Caixa;

void InicializarCaixa(Caixa *caixa);

void ImprimirEstadoCaixa(Caixa *caixa);

#endif