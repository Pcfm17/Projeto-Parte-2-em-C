#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOME_ARQUIVO "clientes.txt"
#define MAX_LINE_SIZE 256 // Tamanho máximo de uma linha no arquivo

int carregarClientes(ListaDeCliente *lt, const char *nome) {
    FILE *fp = fopen(nome, "r");
    if (fp == NULL) {
        lt->qtd_cliente = 0;
        return 0;
    }

    lt->qtd_cliente = 0;
    char linha[MAX_LINE_SIZE];

    while (fgets(linha, sizeof(linha), fp) != NULL && lt->qtd_cliente < Total_Cliente) {
        Cliente *cliente = &lt->clientes[lt->qtd_cliente];
        if (sscanf(linha, "%99[^;];%11[^;];%10[^;];%149[^;];%19[^;];%f;%f;%f;%f;%19[^\n]",
                    cliente->nome_completo, cliente->cpf, cliente->dateNascimento,
                    cliente->endereco, cliente->telefone, &cliente->saldo, &cliente->bitcoin, &cliente->ethereum, &cliente->ripple, cliente->senha) == 10) {
            lt->qtd_cliente++;
        }
        // A linha com fprintf(stderr, ...) foi removida
    }
    fclose(fp);
    return 0;
}

int salvarClientes(ListaDeCliente *lt, const char *nome) {
    FILE *fp = fopen(nome, "w");
    if (fp == NULL) return 1;
    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        fprintf(fp, "%s;%s;%s;%s;%s;%.2f;%.2f;%.2f;%.2f;%s\n",
                lt->clientes[i].nome_completo, lt->clientes[i].cpf, lt->clientes[i].dateNascimento,
                lt->clientes[i].endereco, lt->clientes[i].telefone, lt->clientes[i].saldo, lt->clientes[i].bitcoin, lt->clientes[i].ethereum, lt->clientes[i].ripple, lt->clientes[i].senha);
    }
    fclose(fp);
    return 0;
}


int criarCliente(ListaDeCliente *lt) {
    if (lt->qtd_cliente >= Total_Cliente) {
        printf("Limite de clientes atingido!\n");
        return 1;
    }

    Cliente *t = &lt->clientes[lt->qtd_cliente];

    printf("Escreva o nome completo:\n");
    scanf(" %[^\n]", t->nome_completo);

    printf("Escreva o seu [CPF]:\n");
    scanf(" %11s", t->cpf);

    printf("Escreva a data de nascimento (DD/MM/AAAA):\n");
    scanf(" %10s", t->dateNascimento);

    printf("Escreva o endereço em que reside:\n");
    scanf(" %[^\n]", t->endereco);

    printf("Escreva o seu número de telefone:\n");
    scanf(" %19s", t->telefone);

    printf("Escreva sua senha:\n");
    scanf(" %19s", t->senha);

    t->saldo = 0.0;
    t->bitcoin = 0.0;
    t->ethereum = 0.0;
    t->ripple = 0.0;

    lt->qtd_cliente++;
    salvarClientes(lt, NOME_ARQUIVO);

    printf("Cliente cadastrado com sucesso!\n");
    return 0;
}

int deletarCliente(ListaDeCliente *lt) {
    if (lt->qtd_cliente == 0) {
        printf("Nenhum cliente cadastrado para deletar!\n");
        return 1;
    }

    char cpf[12];
    printf("Escreva o CPF do cliente que deseja deletar:\n");
    scanf(" %11s", cpf);

    int pos = -1;
    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Cliente não encontrado!\n");
        return 2;
    }

    for (i = pos; i < lt->qtd_cliente - 1; i++) {
        lt->clientes[i] = lt->clientes[i + 1];
    }

    lt->qtd_cliente--;
    salvarClientes(lt, NOME_ARQUIVO); // Salvar a lista atualizada

    printf("Cliente deletado com sucesso!\n");
    return 0;
}

int listarCliente(ListaDeCliente *lt) {
    if (lt->qtd_cliente == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return 1;
    }

    printf("Lista de Clientes:\n");
    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        printf("\nCliente %d:\n", i + 1);
        printf("Nome: %s\n", lt->clientes[i].nome_completo);
        printf("CPF: %s\n", lt->clientes[i].cpf);
        printf("Data de Nascimento: %s\n", lt->clientes[i].dateNascimento);
        printf("Endereço: %s\n", lt->clientes[i].endereco);
        printf("Telefone: %s\n", lt->clientes[i].telefone);
        printf("Saldo: %.2f\n", lt->clientes[i].saldo);
        printf("Bitcoin: %.2f\n", lt->clientes[i].bitcoin);
        printf("Ethereum: %.2f\n", lt->clientes[i].ethereum);
        printf("Ripple: %.2f\n", lt->clientes[i].ripple);
    }
    return 0;
}

int consultarSaldo(ListaDeCliente *lt) {
    char cpf[12];
    printf("Digite o CPF do cliente para consultar o saldo:\n");
    scanf(" %11s", cpf);

    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            printf("Saldo do cliente %s: %.2f\n", lt->clientes[i].nome_completo, lt->clientes[i].saldo);
            return 0;
        }
    }

    printf("Cliente não encontrado.\n");
    return 1;
}

int depositar(ListaDeCliente *lt) {
    char cpf[12];
    float valor;
    int cliente_encontrado = 0;

    printf("Digite o CPF do cliente para depósito:\n");
    scanf(" %11s", cpf);
    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            cliente_encontrado = 1;
            printf("Digite o valor a ser depositado:\n");
            scanf("%f", &valor);

            if (valor > 0) {
                lt->clientes[i].saldo += valor;
                salvarClientes(lt, NOME_ARQUIVO);
                char descricao[100];
                snprintf(descricao, sizeof(descricao), "Depósito de R$ %.2f realizado.", valor);
                registrarMovimentacao(lt->clientes[i].cpf, descricao);
                printf("Depósito de %.2f realizado com sucesso.\n", valor);
                return 0;
            } else {
                printf("Valor inválido para depósito.\n");
                return 1;
            }
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado.\n");
        return 1;
    }
    return 1; // Adicionado para evitar warning de falta de retorno
}

int sacar(ListaDeCliente *lt) {
    char cpf[12];
    float valor;
    int cliente_encontrado = 0;

    printf("Digite o CPF do cliente para saque:\n");
    scanf(" %11s", cpf);
    int i;
    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            cliente_encontrado = 1;
            printf("Digite o valor a ser sacado:\n");
            scanf("%f", &valor);

            if (valor > 0 && valor <= lt->clientes[i].saldo) {
                lt->clientes[i].saldo -= valor;
                salvarClientes(lt, NOME_ARQUIVO);
                char descricao[100];
                snprintf(descricao, sizeof(descricao), "Saque de R$ %.2f realizado.", valor);
                registrarMovimentacao(lt->clientes[i].cpf, descricao);
                printf("Saque de %.2f realizado com sucesso.\n", valor);
                return 0;
            } else if (valor <= 0) {
                printf("Valor inválido para saque.\n");
                return 1;
            } else {
                printf("Saldo insuficiente.\n");
                return 1;
            }
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado.\n");
        return 1;
    }
    return 1; // Adicionado para evitar warning de falta de retorno
}

int comprarCripto(ListaDeCliente *lt, double bitcoin_price, double ethereum_price, double ripple_price) {
    char cpf[12];
    int escolha;
    float valor_reais;
    int cliente_encontrado = 0;
    int i;

    printf("Digite o CPF do cliente:\n");
    scanf(" %11s", cpf);

    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            cliente_encontrado = 1;
            printf("Escolha a criptomoeda:\n1. Bitcoin\n2. Ethereum\n3. Ripple\n");
            scanf("%d", &escolha);
            printf("Digite o valor em Reais a ser investido:\n");
            scanf("%f", &valor_reais);

            if (valor_reais > 0 && valor_reais <= lt->clientes[i].saldo) {
                switch (escolha) {
                    case 1:
                        lt->clientes[i].bitcoin += (valor_reais * 0.98) / bitcoin_price;
                        break;
                    case 2:
                        lt->clientes[i].ethereum += (valor_reais * 0.99) / ethereum_price;
                        break;
                    case 3:
                        lt->clientes[i].ripple += (valor_reais * 0.99) / ripple_price;
                        break;
                    default:
                        printf("Opção inválida.\n");
                        return 1;
                }
                lt->clientes[i].saldo -= valor_reais;
                salvarClientes(lt, NOME_ARQUIVO);
                char descricao[100];
                char cripto_nome[20];
                switch (escolha) {
                    case 1: strcpy(cripto_nome, "Bitcoin"); break;
                    case 2: strcpy(cripto_nome, "Ethereum"); break;
                    case 3: strcpy(cripto_nome, "Ripple"); break;
                    default: strcpy(cripto_nome, "Criptomoeda"); break;
                }
                snprintf(descricao, sizeof(descricao), "Compra de R$ %.2f em %s realizada.", valor_reais, cripto_nome);
                registrarMovimentacao(lt->clientes[i].cpf, descricao);
                printf("Compra realizada com sucesso.\n");
                return 0;
            } else if (valor_reais <= 0) {
                printf("Valor inválido para compra.\n");
                return 1;
            } else {
                printf("Saldo insuficiente.\n");
                return 1;
            }
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado.\n");
        return 1;
    }
    return 1; // Adicionado para evitar warning de falta de retorno
}

int venderCripto(ListaDeCliente *lt, double bitcoin_price, double ethereum_price, double ripple_price) {
    char cpf[12];
    int escolha;
    float quantidade;
    int cliente_encontrado = 0;
    int i;

    printf("Digite o CPF do cliente:\n");
    scanf(" %11s", cpf);

    for (i = 0; i < lt->qtd_cliente; i++) {
        if (strcmp(lt->clientes[i].cpf, cpf) == 0) {
            cliente_encontrado = 1;
            printf("Escolha a criptomoeda para venda:\n1. Bitcoin\n2. Ethereum\n3. Ripple\n");
            scanf("%d", &escolha);
            printf("Digite a quantidade a ser vendida:\n");
            scanf("%f", &quantidade);

            switch (escolha) {
                case 1:
                    if (quantidade > 0 && quantidade <= lt->clientes[i].bitcoin) {
                        lt->clientes[i].saldo += quantidade * bitcoin_price * 0.97;
                        lt->clientes[i].bitcoin -= quantidade;
                        char descricao[100];
                        snprintf(descricao, sizeof(descricao), "Venda de %.4f Bitcoin por R$ %.2f realizada.", quantidade, quantidade * bitcoin_price * 0.97);
                        registrarMovimentacao(lt->clientes[i].cpf, descricao);
                    } else {
                        printf("Quantidade inválida ou insuficiente de Bitcoin.\n");
                        return 1;
                    }
                    break;
                case 2:
                    if (quantidade > 0 && quantidade <= lt->clientes[i].ethereum) {
                        lt->clientes[i].saldo += quantidade * ethereum_price * 0.98;
                        lt->clientes[i].ethereum -= quantidade;
                        char descricao[100];
                        snprintf(descricao, sizeof(descricao), "Venda de %.4f Ethereum por R$ %.2f realizada.", quantidade, quantidade * ethereum_price * 0.98);
                        registrarMovimentacao(lt->clientes[i].cpf, descricao);
                    } else {
                        printf("Quantidade inválida ou insuficiente de Ethereum.\n");
                        return 1;
                    }
                    break;
                case 3:
                    if (quantidade > 0 && quantidade <= lt->clientes[i].ripple) {
                        lt->clientes[i].saldo += quantidade * ripple_price * 0.99;
                        lt->clientes[i].ripple -= quantidade;
                        char descricao[100];
                        snprintf(descricao, sizeof(descricao), "Venda de %.4f Ripple por R$ %.2f realizada.", quantidade, quantidade * ripple_price * 0.99);
                        registrarMovimentacao(lt->clientes[i].cpf, descricao);
                    } else {
                        printf("Quantidade inválida ou insuficiente de Ripple.\n");
                        return 1;
                    }
                    break;
                default:
                    printf("Opção inválida.\n");
                    return 1;
            }

            salvarClientes(lt, NOME_ARQUIVO);
            printf("Venda realizada com sucesso.\n");
            return 0;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente não encontrado.\n");
        return 1;
    }
    return 1; // Adicionado para evitar warning de falta de retorno
}


size_t write_data(void *ptr, size_t size, size_t nmemb, char **data) {
    size_t total_size = size * nmemb;
    *data = realloc(*data, total_size + 1);
    if (*data == NULL) {
        return 0;
    }
    memcpy(*data, ptr, total_size);
    (*data)[total_size] = '\0';
    return total_size;
}

// Função para gerar um número aleatório entre -5% e +5%
double gerarVariacao() {
    return ((double)rand() / RAND_MAX) * 0.10 - 0.05; // Gera um número entre -0.05 e 0.05
}

int atualizarCotacao(double *bitcoin_price, double *ethereum_price, double *ripple_price) {
    srand(time(NULL));

    *bitcoin_price += *bitcoin_price * gerarVariacao();
    *ethereum_price += *ethereum_price * gerarVariacao();
    *ripple_price += *ripple_price * gerarVariacao();

    printf("Cotação Bitcoin (variada): USD %.22f\n", *bitcoin_price);
    printf("Cotação Ethereum (variada): USD %.2f\n", *ethereum_price);
    printf("Cotação Ripple (variada): USD %.2f\n", *ripple_price);

    return 0;
}

// Função para acessar a conta com CPF e senha.
int login(ListaDeCliente *lt) {
    char cpf_digitado[12];
    char senha_digitada[20];
    int tentativas = 3;

    while (tentativas > 0) { // Loop para tentativas de login
        printf("Digite o CPF (ou 'sair' para encerrar): ");
        if (scanf(" %11s", cpf_digitado) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (strcmp(cpf_digitado, "sair") == 0) {
            return 1; // Encerra o programa se o usuário digitar "sair"
        }

        printf("Digite a senha: ");
        if (scanf(" %19s", senha_digitada) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        int i;
        for (i = 0; i < lt->qtd_cliente; i++) {
            if (strcmp(lt->clientes[i].cpf, cpf_digitado) == 0 && strcmp(lt->clientes[i].senha, senha_digitada) == 0) {
                printf("Login realizado com sucesso!\n");
                return 0; // Login bem-sucedido
            }
        }

        tentativas--;
        if (tentativas > 0) {
            printf("CPF ou senha incorretos. %d tentativas restantes.\n", tentativas);
        } else {
            printf("Número máximo de tentativas excedido. Acesso negado.\n");
            return 2; // Falha no login após várias tentativas
        }
    }
    return 2; // Falha no login
}

void registrarMovimentacao(const char *cpf, const char *descricao) {
    char nome_arquivo[50];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "extrato_%s.txt", cpf);

    FILE *fp = fopen(nome_arquivo, "a");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de extrato");
        return;
    }

    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char horario[26];
    strftime(horario, 26, "%d/%m/%Y %H:%M:%S", tm_info);

    fprintf(fp, "[%s] %s\n", horario, descricao);
    fclose(fp);
}

void exibirExtrato() {
    char cpf[12];
    printf("Digite o CPF do cliente para exibir o extrato:\n");
    scanf(" %11s", cpf);

    char nome_arquivo[50];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "extrato_%s.txt", cpf);

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        printf("Nenhuma movimentação encontrada para este cliente.\n");
        return;
    }

    char linha[256];
    printf("\nExtrato de movimentações:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        printf("%s", linha);
    }
    fclose(fp);
}


void exibirMenu(){
    printf("\nMenu Cliente:\n");
    printf("1. Criar Cliente\n");
    printf("2. Deletar Cliente\n");
    printf("3. Listar Cliente\n");
    printf("4. Consultar Saldo\n");
    printf("5. Depositar\n");
    printf("6. Sacar\n");
    printf("7. Compra de criptomoeda\n");
    printf("8. Venda de criptomoeda\n");
    printf("9. Atualizar cotação\n");
    printf("10. Exibir Extrato\n");
    printf("11. Voltar\n");
}