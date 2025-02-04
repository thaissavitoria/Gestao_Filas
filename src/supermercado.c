#include "supermercado.h"

#define qtdCaixas 5

void InicializaSupermercado(Supermercado *sup) {
    sup->caixas = (Caixa **)malloc(qtdCaixas * sizeof(Caixa *));
    for (unsigned int i = 0; i < qtdCaixas; i++) {
        sup->caixas[i] = (Caixa *)malloc(sizeof(Caixa));
        InicializarCaixa(sup->caixas[i]);
    }
    sup->qtdCaixasAbertos = qtdCaixas;
}

void CadastrarCliente(Supermercado *sup) {
    if (sup->qtdCaixasAbertos == 0) {
        printf("\nNão há caixas abertos para atender o cliente, antes de cadastrá-lo novamente, abra um caixa!\n");
        return;
    }

    char *nome = (char *)malloc(101 * sizeof(char));
    int resultado = 0;

    while (!resultado) {
        printf("\nNome do cliente (até 100 caracteres):\n");
        while (getchar() != '\n' && getchar() != EOF);

        fgets(nome, 101, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) > 0) {
            resultado = 1;
        } else {
            printf("O nome não pode estar vazio. Tente novamente.\n");
        }
    }

    long unsigned int cpf;
    do {
        printf("\nCPF do cliente:\n");
        resultado = scanf("%lu", &cpf);

        if (resultado != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
        }
    } while (resultado != 1);

    unsigned int prioridade;
    do {
        do {
            printf("\nPrioridade do cliente:\n 1 - Alta; 2 - Média; 3 - Baixa\n");
            resultado = scanf("%u", &prioridade);

            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);
    } while (prioridade > 3);

    unsigned int numItens;
    do {
        printf("\nNúmero de itens no carrinho do cliente:\n");
        resultado = scanf("%u", &numItens);

        if (resultado != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
        }
    } while (resultado != 1);

    unsigned int caixaEscolhido;
    bool cancelarOp = false;
    Caixa caixa;
    do {
        do {
            printf("\nEscolha o caixa em que o cliente vai entrar(1-5):\n");
            printf("\t0 - sair\n");
            resultado = scanf("%u", &caixaEscolhido);

            if (caixaEscolhido == 0) {
                printf("\nOperação cancelada!\n");
                cancelarOp = true;
                break;
            }
            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);

        if (cancelarOp) {
            break;
        }
        caixa = *sup->caixas[caixaEscolhido - 1];

        if (!caixa.estado) {
            printf("Caixa fechado, escolha outro!\n");
            caixaEscolhido = 6;
        }
    } while (caixaEscolhido > 5);

    if (cancelarOp) {
        return;
    }

    Cliente *cli = (Cliente *)malloc(sizeof(Cliente));
    cli->cpfCliente = cpf;
    cli->nome = nome;
    cli->numItens = numItens;
    cli->numPrioridade = prioridade;

    InsereClienteNaFila(sup, cli, caixaEscolhido);
}

void InsereClienteNaFila(Supermercado *sup, Cliente *cli, unsigned int numeroCaixa) {
    InsereNaFila(sup->caixas[numeroCaixa - 1]->fila, cli);
    printf("\nCliente cadastrado com sucesso\n");
}

void AtenderCliente(Supermercado *sup) {
    int resultado = 0;
    unsigned int caixaEscolhido;
    do {
        do {
            printf("\nEscolha o caixa que irá atender o cliente(1-5):\n");
            resultado = scanf("%u", &caixaEscolhido);

            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);
    } while (caixaEscolhido > 5);

    Caixa *caixa = sup->caixas[caixaEscolhido - 1];
    if (!caixa->estado) {
        printf("\nCaixa fechado, escolha outro!\n");
        return;
    }

    RemoveDaFila(sup->caixas[caixaEscolhido - 1]->fila);
}

void AbrirOuFecharCaixa(Supermercado *sup) {
    unsigned int op;
    int resultado;

    do {
        do {
            printf("\nO que deseja fazer?\n1.Abrir um caixa;\n2.Fechar um caixa;\n");
            resultado = scanf("%u", &op);

            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);
    } while (op != 1 && op != 2);

    if (op == 1) {
        AbrirCaixa(sup);
    } else {
        FecharCaixa(sup);
    }
}

void AbrirCaixa(Supermercado *sup) {
    int resultado = 0;
    unsigned int caixaEscolhido;
    do {
        do {
            printf("\nEscolha o caixa que deseja abrir(1-5):\n");
            resultado = scanf("%u", &caixaEscolhido);

            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);
    } while (caixaEscolhido > 5);

    Caixa *caixa = sup->caixas[caixaEscolhido - 1];

    if (caixa->estado) {
        printf("\nCaixa %u já está aberto!\n", caixaEscolhido);
    } else {
        caixa->estado = 1;
        sup->qtdCaixasAbertos++;
        printf("\nCaixa %u aberto com sucesso!\n", caixaEscolhido);
    }
}

void FecharCaixa(Supermercado *sup) {
    int resultado = 0;
    unsigned int caixaEscolhido;
    do {
        do {
            printf("\nEscolha o caixa que deseja fechar(1-5):\n");
            resultado = scanf("%u", &caixaEscolhido);

            if (resultado != 1) {
                printf("Entrada inválida. Tente novamente.\n");
                while (getchar() != '\n');
            }
        } while (resultado != 1);
    } while (caixaEscolhido > 5);

    Caixa *caixa = sup->caixas[caixaEscolhido - 1];
    if (!caixa->estado) {
        printf("\nCaixa %u já está fechado!\n", caixaEscolhido);
    } else {
        if (sup->qtdCaixasAbertos == 1 && caixa->fila->numClientes > 0) {
            printf("\n--------ATENÇÃO---------\n NÃO foi possível fechar o caixa %u, pois ele é o último aberto e ainda tem clientes em sua fila!", caixaEscolhido);
        } else {
            caixa->estado = 0;
            sup->qtdCaixasAbertos--;
            DistribuirClientesParaOutrasFilas(sup, caixaEscolhido);
            printf("\nCaixa %u fechado com sucesso!\n", caixaEscolhido);
        }
    }
}

void DistribuirClientesParaOutrasFilas(Supermercado *sup, unsigned int numeroCaixa) {
    Caixa *caixa = sup->caixas[numeroCaixa - 1];

    NoFila *aux = caixa->fila->inicio;

    while (aux != NULL) {
        Cliente *cliente = aux->cliente;
        Caixa *caixaMenorFila = GetCaixaComMenorNumeroDeClientes(sup);
        InsereNaFila(caixaMenorFila->fila, cliente);
        aux = aux->prox;
    }

    EsvaziaFila(caixa->fila);
}

Caixa *GetCaixaComMenorNumeroDeClientes(Supermercado *sup) {
    unsigned int numClientesMin = __INT_MAX__;
    Caixa *caixa;
    for (int i = 0; i < 5; i++) {
        if (sup->caixas[i]->estado && sup->caixas[i]->fila->numClientes < numClientesMin) {
            caixa = sup->caixas[i];
        }
    }
    return caixa;
}

void ImprimirEstadosCaixas(Supermercado *sup) {
    for (int i = 0; i < 5; i++) {
        printf("\n-----------CAIXA %u---------------\n", i + 1);
        ImprimirEstadoCaixa(sup->caixas[i]);
    }
}

void ImprimirClientesCaixas(Supermercado *sup) {
    for (int i = 0; i < 5; i++) {
        if (sup->caixas[i]->estado) {
            printf("\n-----------CAIXA %u---------------\n", i + 1);
            ImprimirFila(sup->caixas[i]->fila);
        }
    }
}
