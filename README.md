Nome: Paulo César Fachetti Motta
RA: 24.224.012-5

OBJETIVO:
O objetivo desse projeto de Exchange de Criptomoedas é fazer login com um cliente salvo no txt, efetuar transações de compra e venda de criptomoedas tendo como depositar e sacar o seu dinheiro e também a variação das criptomoedas de -5% do valor inicial ou +5% do valor inicial.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Compilação:

Juntar os códigos: O compilador pega os arquivos main.c e projeto.c e lê todo o código deles. Ele também olha o arquivo projeto.h para entender as definições (como Cliente, ListaDeCliente e as funções declaradas).

Traduzir para a língua do computador: O compilador converte o código C que você escreveu para uma linguagem que o seu computador entende (chamada código de máquina ou código objeto). Ele faz isso para cada arquivo .c separadamente.

Verificar erros: Durante a tradução, o compilador verifica se você cometeu algum erro de escrita no código C (como esquecer um ponto e vírgula ou usar uma variável que não existe). Se encontrar erros, ele te avisa.

Ligar os pedaços: Depois de traduzir os arquivos .c para arquivos objeto, um programa chamado "linker" junta esses pedaços, incluindo qualquer código extra necessário (como funções para imprimir na tela). O resultado final é um único arquivo executável.

Como você faz isso (exemplo usando um compilador chamado GCC):

Abra o terminal ou prompt de comando e navegue até a pasta onde os arquivos estão. Digite:

Bash

gcc main.c projeto.c -o sistema_cripto
gcc: é o nome do compilador.
main.c projeto.c: são os arquivos de código que você quer compilar.
-o sistema_cripto: diz ao compilador para criar um arquivo executável chamado sistema_cripto.
Execução:

Dar a ordem: Depois que o arquivo sistema_cripto é criado, você diz ao seu computador para rodar esse programa.
O programa começa: O computador carrega o código do arquivo sistema_cripto na memória e começa a executar as instruções, começando pela função main() no arquivo main.c.
Passo a passo: O programa segue as instruções que você escreveu, como mostrar mensagens na tela, pedir para você digitar coisas, guardar informações e fazer cálculos.
Fim: O programa continua executando até chegar ao final da função main() ou encontrar uma instrução para parar.
Como você faz isso (depois de compilar):

No mesmo terminal, digite:

Bash

./sistema_cripto
./: diz ao computador para procurar o programa na pasta atual.
sistema_cripto: é o nome do arquivo executável que você criou.
Aí o programa vai começar a rodar e você poderá interagir com ele!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Iniciar: Ao rodar o programa, você será recebido com uma mensagem de boas-vindas e solicitado a fazer login ou criar uma nova conta.
Login/Cadastro:
Se já tiver conta, digite seu CPF e senha.
Se for novo, escolha a opção de criar conta e siga as instruções para fornecer seus dados (nome, CPF, data de nascimento, endereço, telefone e senha).
Menu Principal: Após o login bem-sucedido, um menu com diversas opções será exibido:
Criar Cliente: (Geralmente usado apenas no início ou para adicionar mais contas).
Deletar Cliente: Remove uma conta existente (requer o CPF).
Listar Cliente: Mostra informações de todos os clientes cadastrados.
Consultar Saldo: Exibe o saldo em Reais da sua conta (requer o CPF).
Depositar: Adiciona um valor em Reais ao seu saldo (requer o CPF e o valor).
Sacar: Retira um valor em Reais do seu saldo (requer o CPF e o valor, e verifica se há saldo suficiente).
Compra de criptomoeda: Permite comprar Bitcoin, Ethereum ou Ripple usando seu saldo em Reais. Você escolhe a criptomoeda e o valor a investir.
Venda de criptomoeda: Permite vender suas criptomoedas (Bitcoin, Ethereum ou Ripple) e receber o valor em Reais no seu saldo. Você escolhe a criptomoeda e a quantidade a vender.
Atualizar cotação: Simula a mudança nos preços das criptomoedas.
Voltar: Encerra o programa e salva os dados dos clientes.
Interação: Para usar o programa, basta digitar o número da opção desejada no menu e pressionar Enter. Siga as instruções que aparecerão na tela para fornecer as informações necessárias (como CPF, valores, quantidade de criptomoedas, etc.).
Sair: Quando terminar de usar o programa, escolha a opção 10 (Voltar) para encerrá-lo e garantir que seus dados sejam salvos.
Em resumo, o programa funciona através de um menu interativo onde você escolhe as ações que deseja realizar para gerenciar sua conta e suas operações com criptomoedas.
