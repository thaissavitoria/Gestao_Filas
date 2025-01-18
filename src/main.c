#include "supermercado.h" 

int main() {
    unsigned int op;

    Supermercado *sup = (Supermercado *)malloc(sizeof(Supermercado));
    InicializaSupermercado(sup);

    do {
        printf("\n\n---------------SISTEMA-----------------\n");
        printf("Escolha a operação que deseja realizar:\n");
        printf("1. Cadastrar um Cliente\n");
        printf("2. Atender um Cliente\n");
        printf("3. Abrir ou Fechar um Caixa\n");
        printf("4. Imprimir a Lista de Clientes em Espera\n");
        printf("5. Imprimir o Status dos Caixas\n\n");
        printf("0. FINALIZAR\n\n");

        if (scanf("%u", &op) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
        case 1:
            CadastrarCliente(sup);
            break;

        case 2:
            AtenderCliente(sup);
            break;

        case 3:
            AbrirOuFecharCaixa(sup);
            break;

        case 4:
            ImprimirClientesCaixas(sup);
            break;

        case 5:
            ImprimirEstadosCaixas(sup);
            break;

        case 0:
            printf("SUPERMERCADO FECHADO! Obrigada por utilizar nosso programa!\n");
            free(sup);
        default:
            break;
        }
    } while (op != 0);

    return 0;
}