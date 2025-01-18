#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include "caixa.h" 
#include "string.h"

typedef struct Supermercado {
    Caixa **caixas;
    unsigned int qtdCaixasAbertos;
} Supermercado;

void InicializaSupermercado(Supermercado *sup);


void CadastrarCliente(Supermercado *sup);
void InsereClienteNaFila(Supermercado *sup, Cliente *cli, unsigned int numeroCaixa);

void AtenderCliente(Supermercado *sup);

void AbrirOuFecharCaixa(Supermercado *sup);
void AbrirCaixa(Supermercado *sup);
void FecharCaixa(Supermercado *sup);
void DistribuirClientesParaOutrasFilas(Supermercado *sup, unsigned int numeroCaixa);
Caixa *GetCaixaComMenorNumeroDeClientes(Supermercado *sup);

void ImprimirEstadosCaixas(Supermercado *sup);

void ImprimirClientesCaixas(Supermercado *sup);

#endif