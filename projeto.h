#ifndef PROJETO_H
#define PROJETO_H

#include <stdio.h>
#include <string.h>

#define Total_Cliente 10

typedef struct {
    char nome_completo[100];
    char cpf[12];
    char dateNascimento[11];
    char endereco[150];
    char telefone[20];
    float saldo;
    float bitcoin;
    float ethereum;
    float ripple;
    char senha[20];
} Cliente;

typedef struct {
    Cliente clientes[Total_Cliente];
    int qtd_cliente;
} ListaDeCliente;

void exibirMenu();

int criarCliente(ListaDeCliente *lt);
int deletarCliente(ListaDeCliente *lt);
int listarCliente(ListaDeCliente *lt);
int consultarSaldo(ListaDeCliente *lt);
int depositar(ListaDeCliente *lt);
int sacar(ListaDeCliente *lt);
int comprarCripto(ListaDeCliente *lt, double bitcoin_price, double ethereum_price, double ripple_price);
int venderCripto(ListaDeCliente *lt, double bitcoin_price, double ethereum_price, double ripple_price);
double gerarVariacao();
int atualizarCotacao(double *bitcoin_price, double *ethereum_price, double *ripple_price);
int login(ListaDeCliente *lt);

int carregarClientes(ListaDeCliente *lt, const char *nome);
int salvarClientes(ListaDeCliente *lt, const char *nome);

#endif