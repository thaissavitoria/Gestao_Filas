#include "caixa.h"

void InicializarCaixa(Caixa *caixa) {
    caixa->estado = 1;
    caixa->fila = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));
    FazFilaVazia(caixa->fila);
}

void ImprimirEstadoCaixa(Caixa *caixa) {
    printf("Estado caixa:");

    if (caixa->estado) {
        printf("ABERTO.\n");
    } else {
        printf("FECHADO.\n");
    }

    printf("Numero de clientes em espera: %u\n", caixa->fila->numClientes);
}