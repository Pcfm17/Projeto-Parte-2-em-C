#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NOME_ARQUIVO "clientes.txt"
#define MAX_LINE_SIZE 256 // Tamanho máximo de uma linha no arquivo

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    ListaDeCliente lista_clientes;
    lista_clientes.qtd_cliente = 0;

    // Carregar os clientes do arquivo ao iniciar o programa
    carregarClientes(&lista_clientes, NOME_ARQUIVO);

    double bitcoin_price = 30000.0;
    double ethereum_price = 2000.0;
    double ripple_price = 0.5;

    atualizarCotacao(&bitcoin_price, &ethereum_price, &ripple_price);

    printf("========================================================\n");
    printf(" Bem-vindo ao Sistema de Gerenciamento de Criptomoedas\n");
    printf("========================================================\n\n");

    printf("Por favor, faça o login para continuar.\n\n");

    printf("Escolha uma das opções de login:\n\n");

    // As opções de login fixas foram removidas para usar os dados carregados do arquivo.

    if (login(&lista_clientes) != 0) {
        printf("Programa encerrado.\n");
        return 1;
    }

    int escolha;
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                criarCliente(&lista_clientes);
                break;
            case 2:
                deletarCliente(&lista_clientes);
                break;
            case 3:
                listarCliente(&lista_clientes);
                break;
            case 4:
                consultarSaldo(&lista_clientes);
                break;
            case 5:
                depositar(&lista_clientes);
                break;
            case 6:
                sacar(&lista_clientes);
                break;
            case 7:
                comprarCripto(&lista_clientes);
                break;
            case 8:
                venderCripto(&lista_clientes);
                break;
            case 9:
                atualizarCotacao(&bitcoin_price, &ethereum_price, &ripple_price);
                break;
            case 10:
                printf("Encerrando o programa e salvando os dados...\n");
                salvarClientes(&lista_clientes, NOME_ARQUIVO);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 10);

    return 0;
}