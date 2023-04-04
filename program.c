#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

//Funções do programa
void menu();
void gerenciarClientes(); 
    void cadastrarCliente();
    void atualizarCliente();
    void listarClientes();
    void removerCliente();
    void buscarCliente();
        int buscarPorNome(char *nome);
void gerenciarProdutos(); 
    void cadastrarProduto();
    void editarProduto();
    void listarProdutos();
    void buscarProduto();
    void removerProduto();
    int produtoVazio();
    int ultimoProdutoVazio();
void gerenciarVendas();
    void novaVenda();
    void relatorioVendas();
void carregarClientes();
void carregarProdutos();
void carregarVendas();
void salvarTudo(); 
void flush_in(); //limpa o buffer do teclado

//Estrutura do tipo Cliente
typedef struct 
{
   int codigo;
   char nome[40];
   char cpf[12];
   char telefone[11];
   char endereco[60];
   char cidade[20];
   char estado[20];

}Cliente;

//Estrutura do tipo Produto
typedef struct 
{
   int codigo;
   char nome[40];
   int estoque;
   float valor;
   int quantVenda;
}Produto;

//Estrutura do tipo Venda
typedef struct 
{
    int codigo;
    Produto itens[100];
    float valorTotal;
}Venda;

//inicialização de variáveis globais
char opcao; //variável para capturar a opção do usuário no menu principal
Cliente clientes[100]; //vetor para armazenar os clientes
Produto produtos[1000]; //vetor para armazenar os produtos
Venda vendas[1000]; //vetor para armazenar as vendas
int quantClientes=0, quantProdutos=0; marcadorClientes=0, marcadorProdutos=0, produtosVendidos=0, marcadorVendas=0;
float totalVendido=0;

int main(void) 
{
    carregarClientes();
    carregarProdutos();
    carregarVendas();
    menu();
    return 0;
}

void menu() 
{
    do {
        system("cls");
        printf("\n********************************************************\n");
        printf("\n*   NOSSA PAPELARIA - Muito Mais Variedade Pra Voce!   *\n");
        printf("\n********************************************************\n");
        printf("\n");
        printf("\nPara continuar, escolha uma opcao pressionando uma tecla...\n");
        printf("\n[C] - Gerenciar Clientes \n[P] - Gerenciar Produtos \n[V] - Gerenciar Vendas.\n[S] - Sair do Programa\n");
        opcao = getche();
        opcao = toupper(opcao);
        
        switch (opcao) 
        {
            case 'C':
                gerenciarClientes();
                break;
            case 'P':
                gerenciarProdutos();
                break;
            case 'V':
                gerenciarVendas();
                break;
            case 'S':
                salvarTudo();
                return 0;
            default:
                printf("\nERRO: Opcao invalida. Tente novamente...");
                sleep(1);
                break;
        }
        //fim do switch
    } while(opcao!='S' && opcao!='C' && opcao!='P' && opcao!='V');
    salvarTudo();
}

/**********Função de Menu Gerenciamento de Clientes************/
void gerenciarClientes() 
{
    do 
    {
        system("cls");
        printf("\n********************************************************\n");
        printf("\n*             Gerenciamento de Clientes                *\n");
        printf("\n********************************************************\n");
        printf("\nEscolha uma opcao pressionando uma tecla...\n");
        printf("\nC - Cadastrar Cliente \nA - Atualizar Cliente \nL - Listar Clientes \nR - Remover Cliente.\nB - Buscar Cliente\nS - Voltar ao Menu Principal\n");
        opcao = getche();
        opcao = toupper(opcao);
        
        switch (opcao) 
        {
            case 'C':
                cadastrarCliente();
                break;
            case 'A':
                atualizarCliente();
                break;
            case 'L':
                listarClientes();
                break;
            case 'R':
                removerCliente();
                break;
            case 'B':
                buscarCliente();
                break;
            case 'S':
                menu();
                break;
            default:
                printf("\nERRO: Opcao invalida. Tente novamente...");
                sleep(1);
                break;
        } //fim do switch
    } while(opcao!='C' && opcao!='E' && opcao!='L' && opcao!='R' && opcao!='B' && opcao!='S');
    
    
}

/**********Função de Cadastrar Cliente************/
void cadastrarCliente() 
{   
    do 
    {
        system("cls");
        quantClientes++; // incrementa a quantidade de clientes;
        printf("CADASTRO DE CLIENTE\n\n");

        //Atribui o código ao cliente. Se for o primeiro cliente, o código será 1; se não, será o código do anterior + 1;
        if(quantClientes==1) {
            clientes[marcadorClientes].codigo = quantClientes;
        } else {
            clientes[marcadorClientes].codigo=clientes[marcadorClientes-1].codigo+1;
        }        
        
        //Solicitar os dados do cliente
        do {
            printf("Nome: ");
            scanf("%[^\n]s", clientes[marcadorClientes].nome);
            flush_in();
        } while((strlen(clientes[marcadorClientes].nome))<2);
        //Solicitar cpf, validando para checar se tem 11 digitos
        do {
            printf("CPF (11 digitos): ");
            scanf("%s", clientes[marcadorClientes].cpf);
        } while((strlen(clientes[marcadorClientes].cpf))<11 || (strlen(clientes[marcadorClientes].cpf))>11);
        flush_in();
        printf("Estado: ");
        scanf("%[^\n]s", clientes[marcadorClientes].estado);
        flush_in();
        printf("Cidade: ");
        scanf("%[^\n]s", clientes[marcadorClientes].cidade);
        flush_in();
        printf("Endereco: ");
        scanf("%[^\n]s", clientes[marcadorClientes].endereco);
        flush_in();
        printf("Telefone: ");
        scanf("%s", clientes[marcadorClientes].telefone);
        flush_in();
        marcadorClientes++;
        printf("\n\nCliente cadastrado. Digite 'C' para cadastrar outro cliente, ou qualquer outra tecla para voltar ao menu de Gerenciamento de Clientes.\n");
        opcao = getche();
        opcao = toupper(opcao);

    } while(opcao=='C');
     
}

/**********Função de Editar Cliente************/
void atualizarCliente() 
{
    int i; //variável para controle de loops;
    int codValido = 0; //variável para indicar código valido (1) ou inválido(0);
    int codBusca = -1; //variável para o código buscado. permanecerá com valor '-1' se o usuário inserir um caractere ao invés de um número;
    char novaString[40]; //a nova informacao que o usuário salvará; será copiada no local desejado;

    system("cls");
    printf("Digite o codigo do cliente a ser editado ou digite 0 para cancelar...");
    
    do 
    {
        scanf("%i", &codBusca);
        flush_in(); //limpa o buffer do teclado;
        //validação do input
        if(codBusca==-1) {
            printf("\nCodigo invalido. Verifique o codigo e digite novamente: ");
            continue;
        } else if (codBusca==0){
            codValido=1;
            printf("\nVoltando ao menu 'Gerenciar Clientes'...");
            sleep(3);
        } else
        {   
            //se validado, o input será buscado no registro de clientes
            for(i=0; i<100; i++)
            {
                if(codBusca==clientes[i].codigo) //ao ser encontrado no registro, os dados sao exibidos e o usuário escolhe o campo que deseja alterar
                {
                    codValido = 1;
                    printf("\nCliente Encontrado: \n");
                    printf("\nCodigo: %i", clientes[i].codigo);
                    printf("\nNome: %s", clientes[i].nome);
                    printf("\nCPF: %s", clientes[i].cpf);
                    printf("\nTelefone: %s", clientes[i].telefone);
                    printf("\nEndereco: %s", clientes[i].endereco);
                    printf("\nCidade: %s", clientes[i].cidade);
                    printf("\nEstado: %s", clientes[i].estado);
                    
                    
                    
                    printf("\n\nQue campo voce deseja alterar?\n1 - Nome\n2 - CPF\n3 - Estado\n4 - Cidade\n5 - Endereco\n6 - Telefone\n\nPara cancelar, pressione outra tecla.\n");
                    opcao = getche();

                    switch (opcao) //aqui ocorre a alteracao dos campos, com base na opcao do usuario;
                    {
                        case '1':
                            printf("\nDigite o novo valor para o campo 'Nome': ");
                            scanf("%[^\n]s", novaString);        
                            strcpy(clientes[i].nome, novaString);
                            printf("\nNome alterado com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                        case '2':
                            printf("\nDigite o novo valor para o campo 'CPF': ");
                            scanf("%s", novaString);        
                            strcpy(clientes[i].cpf, novaString);
                            printf("\nCPF alterado com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                        case '3':
                            printf("\nDigite o novo valor para o campo 'Estado': ");
                            scanf("%s", novaString);        
                            strcpy(clientes[i].estado, novaString);
                            printf("\nEstado alterado com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                        case '4':
                            printf("\nDigite o novo valor para o campo 'Cidade': ");
                            scanf("%s", novaString);        
                            strcpy(clientes[i].cidade, novaString);
                            printf("\nCidade alterada com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                        case '5':
                            printf("\nDigite o novo valor para o campo 'Endereco': ");
                            scanf("%s", novaString);        
                            strcpy(clientes[i].endereco, novaString);
                            printf("\nEndereco alterado com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                        case '6':
                            printf("\nDigite o novo valor para o campo 'Telefone': ");
                            scanf("%s", novaString);        
                            strcpy(clientes[i].telefone, novaString);
                            printf("\nTelefone alterado com sucesso!\n");
                            sleep(1);
                            printf("\n'A' para atualizar clientes ou outra tecla para sair.\n");
                            opcao = getche();
                            opcao = toupper(opcao);
                            if(opcao =='A') {
                                atualizarCliente();
                            } else {
                                break;
                            }
                            break;
                    default:
                    printf("\nOpcao invalida. Voltando ao menu anterior...");
                    sleep(2);
                        break;
                    }
                    break;
                }
            }
        }
        //se nao encontrado no for loop anterior, a mensagem é exibida e o do..while reinicia, uma vez que o 'codValido' permanece '0';
        if(codValido==0) {
            printf("\nCliente nao encontrado. Verifique o codigo e tente novamente.\n");
        }
        
    } while(codValido==0);
}

/**********Função de Listar Clientes************/
void listarClientes() 
{   
    int i;
    system("cls");
    printf("Total de clientes cadastrados: %d\n", quantClientes);
    for(i=0; i<100;i++)
    {
        if(clientes[i].codigo!=0&&clientes[i].codigo!=NULL)
        {
            printf("\nCodigo: %i", clientes[i].codigo);
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s", clientes[i].telefone);
            printf("\nEndereco: %s", clientes[i].endereco);
            printf("\nCidade: %s", clientes[i].cidade);
            printf("\nEstado: %s", clientes[i].estado);
            
            printf("\n\n");
        }
    }
    opcao='0';
    system("pause");
}

/**********Função de Remover Cliente************/
void removerCliente() 
{
    int i; //variável para controle de loops;
    int ultimoCliente;
    int codValido = 0; //variável para indicar código valido (1) ou inválido(0);
    int codBusca = -1; //variável para o código buscado. permanecerá com valor '-1' se o usuário inserir um caractere ao invés de um número;
    char novaString[40]; //a nova informacao que o usuário salvará; será copiada no local desejado;

    system("cls");
    printf("Digite o codigo do cliente a ser removido ou digite 0 para cancelar...");

      
    
    do 
    {
        scanf("%i", &codBusca);
        flush_in(); //limpa o buffer do teclado;
        //validação do input
        if(codBusca==-1) {
            printf("\nCodigo invalido. Verifique o codigo e digite novamente: ");
            continue;
        } else if (codBusca==0){
            codValido=1;
            printf("\nVoltando ao menu 'Gerenciar Clientes'...");
            sleep(3);
        } else
        {
            for(i=0; i<100;i++)
            {
                if(clientes[i].codigo!=0&&clientes[i].codigo!=NULL)
                {
                    ultimoCliente = i;
                }
            }
              
            if (codBusca<=100 && codBusca>0)
            {
                for(i=codBusca-1; i<ultimoCliente+1; i++)
                {
                    clientes[i]=clientes[i+1];
                }
                printf("\nCliente removido com sucesso! Retornando a menu anterior...");
                quantClientes--;
                marcadorClientes--;
                codValido=1;
                opcao = '0';
                sleep(3);
            }
            
        }
        if(codValido==0) {
            printf("\nCliente nao encontrado. Verifique o codigo e tente novamente.\n");
        }    
    } while(codValido==0);   
}

/**********Função de Buscar Cliente - Exibe o menu de escolha do modo de busca (código, nome ou cpf)************/
void buscarCliente()
{   
    do 
    {
        system("cls");
        printf("\nPara buscar um cliente, escolha um tipo de busca digitando um numero: \n1 - Por nome\n2 - Por codigo\n3 - Por CPF\n\n0 - Voltar para o menu anterior\n");
        opcao = getche();
        if(opcao=='0')
        {   
            printf("\nVoltando ao menu de gerencia de clientes...");
            sleep(3);
        } else if (opcao!='1'&&opcao!='2'&&opcao!='3'&&opcao!='0')
        {
            printf("\nOpcao invalida. Tente novamente.");
            sleep(4);
        } else {
            char nomeBusca[40];
            int codigoBusca;
            int resultadoBusca;
            switch (opcao)
            {
            case '1':
                system("cls");
                printf("\nDigite o nome para buscar: ");
                scanf("%[^\n]s", nomeBusca);
                resultadoBusca = buscarPorNome(nomeBusca);    
            
                if(resultadoBusca==-1) {
                    printf("\nCliente nao encontrado!\n\n");
                    system("pause");
                } else {
                    //Mostrar as informações do cliente encontrado
                    system("cls");
                    printf("\nCliente Encontrado: \n");
                    printf("\nCodigo: %i", clientes[resultadoBusca].codigo);
                    printf("\nNome: %s", clientes[resultadoBusca].nome);
                    printf("\nCPF: %s", clientes[resultadoBusca].cpf);
                    printf("\nEstado: %s", clientes[resultadoBusca].estado);
                    printf("\nCidade: %s", clientes[resultadoBusca].cidade);
                    printf("\nEndereco: %s", clientes[resultadoBusca].endereco);
                    printf("\nTelefone: %s", clientes[resultadoBusca].telefone);
                    printf("\n\n");
                    system("pause");
                }
                break;

            case '2':
                system("cls");
                printf("\nDigite o codigo para buscar: ");
                scanf("%i", &codigoBusca);
                resultadoBusca = buscarPorCodigo(codigoBusca);    
            
                if(resultadoBusca==-1) {
                    printf("\nCliente nao encontrado!\n\n");
                    system("pause");
                } else {
                    //Mostrar as informações do cliente encontrado
                    system("cls");
                    printf("\nCliente Encontrado: \n");
                    printf("\nCodigo: %i", clientes[resultadoBusca].codigo);
                    printf("\nNome: %s", clientes[resultadoBusca].nome);
                    printf("\nCPF: %s", clientes[resultadoBusca].cpf);
                    printf("\nEstado: %s", clientes[resultadoBusca].estado);
                    printf("\nCidade: %s", clientes[resultadoBusca].cidade);
                    printf("\nEndereco: %s", clientes[resultadoBusca].endereco);
                    printf("\nTelefone: %s", clientes[resultadoBusca].telefone);
                    printf("\n\n");
                    system("pause");
                }
                break;

             case '3':
                system("cls");
                printf("\nDigite o CPF para buscar: ");
                scanf("%s", &nomeBusca);
                resultadoBusca = buscarPorCPF(nomeBusca);    
            
                if(resultadoBusca==-1) {
                    printf("\nCliente nao encontrado!\n\n");
                    system("pause");
                } else {
                    //Mostrar as informações do cliente encontrado
                    system("cls");
                    printf("\nCliente Encontrado: \n");
                    printf("\nCodigo: %i", clientes[resultadoBusca].codigo);
                    printf("\nNome: %s", clientes[resultadoBusca].nome);
                    printf("\nCPF: %s", clientes[resultadoBusca].cpf);
                    printf("\nEstado: %s", clientes[resultadoBusca].estado);
                    printf("\nCidade: %s", clientes[resultadoBusca].cidade);
                    printf("\nEndereco: %s", clientes[resultadoBusca].endereco);
                    printf("\nTelefone: %s", clientes[resultadoBusca].telefone);
                    printf("\n\n");
                    system("pause");
                }
                break;
            default:
                printf("\nOpcao invalida. Voltando ao menu anterior...");
                opcao = '0';
                sleep(3);
                break;
            }
        }
        
    } while (opcao!='1'&&opcao!='2'&&opcao!='3'&&opcao!='0');    
   
}

//*********Função que faz a busca por nome no registro de Clientes
    int buscarPorNome(char *nome) {
        int i;
        for (i=0; i<100; i++) {
            if((strcmp(clientes[i].nome, nome)==0)) {
                return(i);
            }
        }
        return(-1);
    }
    int buscarPorCodigo(int codigo) {
        int i;
        for (i=0; i<100; i++) {
            if(clientes[i].codigo==codigo) {
                return(i);
            }
        }
        return(-1);
    }
    int buscarPorCPF(char *cpf) {
    int i;
    for (i=0; i<100; i++) {
        if((strcmp(clientes[i].cpf, cpf)==0)) {
            return(i);
        }
    }
    return(-1);
}


//**********Função Menu de Gerência de Produtos*************//

void gerenciarProdutos() 
{
    do 
    {
        system("cls");
        printf("\n********************************************************\n");
        printf("\n*             Gerenciamento de Produtos                *\n");
        printf("\n********************************************************\n");
        printf("\nEscolha uma opcao pressionando uma tecla...\n");
        printf("\n[C] - Cadastrar Produto \n[E] - Editar Produto \n[L] - Listar Produtos \n[R] - Remover Produto.\n[B] - Buscar Produto\n[S] - Voltar ao Menu Principal\n");
        opcao = getche();
        opcao = toupper(opcao);
        
        switch (opcao) 
        {
            case 'C':
                cadastrarProduto();
                break;
            case 'E':
                editarProduto();
                break;
            case 'L':
                listarProdutos();
                break;
            case 'R':
                removerProduto();
                break;
            case 'B':
                buscarProduto();
                break;
            case 'S':
                menu();
                break;
            default:
                printf("\nERRO: Opcao invalida. Tente novamente...");
                sleep(3);
                break;
        } //fim do switch
    } while(opcao!='C' && opcao!='E' && opcao!='L' && opcao!='R' && opcao!='B' && opcao!='S');
       
}

//********Função para cadastrar novo produto
void cadastrarProduto()
{
    do 
    {
        system("cls");
        quantProdutos++; // incrementa a quantidade de produtos;
        marcadorProdutos = produtoVazio();
        printf("CADASTRO DE PRODUTO\n\n");
        produtos[marcadorProdutos].codigo = marcadorProdutos+1;
        do {
            printf("Descricao: ");
            scanf("%[^\n]s", produtos[marcadorProdutos].nome);
            flush_in();
        } while((strlen(produtos[marcadorProdutos].nome))<2);
        printf("Estoque: ");
        scanf("%d", &produtos[marcadorProdutos].estoque);
        flush_in();
        printf("Valor de venda: ");
        scanf("%f", &produtos[marcadorProdutos].valor);
        flush_in();
        
        printf("\n\nProduto cadastrado. Digite 'C' para cadastrar outro produto, ou qualquer outra tecla para voltar ao menu de Gerenciamento de Produtos.\n");
        opcao = getche();
        opcao = toupper(opcao);

    } while(opcao=='C');
}

//********Função para editar um produto
void editarProduto() 
{
    int codigo, op, novoEstoque;
    float novoValor;
    char novoNome[40];
    do 
    {
        system("cls");
        printf("Digite o codigo do produto que deseja editar.\n\nPara cancelar, digite '0'\n");
        scanf("%d", &codigo);
        flush_in();

        if(codigo>0&&codigo<=1000)
        {
            if(produtos[codigo-1].codigo!=NULL)
            {   
                system("cls");
                printf("Produto encontrado:");
                printf("\n\nCodigo: %i", produtos[codigo-1].codigo);
                printf("\nDescricao: %s", produtos[codigo-1].nome);
                printf("\nEstoque: %i", produtos[codigo-1].estoque);
                printf("\nValor: %.2f", produtos[codigo-1].valor);
                printf("\n\nQue campo deseja modificar?\n[1] - Descricao\n[2] - Estoque\n[3] - Valor\n\nDigite [0] para sair.");
                scanf("%d", &op);
                flush_in();
                switch(op) 
                {
                    case 1:
                        system("cls");
                        printf("Insira a nova descricao do produto: ");
                        scanf("%[^\n]s", novoNome);
                        strcpy(produtos[codigo-1].nome, novoNome);
                        if(strcmp(produtos[codigo-1].nome, novoNome)==0) {
                            printf("\n\nDescricao alterada com sucesso.\n\n");
                            system("pause");
                        } else {
                            printf("\nErro!\n\n");
                            system("pause");
                            editarProduto();
                        }
                        break;
                    case 2:
                        system("cls");
                        printf("Insira a quantidade de produtos no estoque: ");
                        scanf("%i", &novoEstoque);
                        produtos[codigo-1].estoque = novoEstoque;
                        if(produtos[codigo-1].estoque==novoEstoque) {
                            printf("\n\nEstoque alterado com sucesso.\n\n");
                            system("pause");
                        } else {
                            printf("\nErro!\n\n");
                            system("pause");
                            editarProduto();
                        }
                        break;
                    case 3:
                        system("cls");
                        printf("Insira o valor do produto: ");
                        scanf("%f", &novoValor);
                        produtos[codigo-1].valor = novoValor;
                        if(produtos[codigo-1].valor==novoValor) {
                            printf("\n\nValor alterado com sucesso.\n\n");
                            system("pause");
                        } else {
                            printf("\nErro!\n\n");
                            system("pause");
                            editarProduto();
                        }
                    case 0:
                        break;
                    default:
                        printf("\nOpcao invalida. Tente novamente!\n");
                        sleep(2);
                }

            } else 
            {
                printf("\nProduto nao encontrado... Verifique o codigo e tente novamente.");
                sleep(3);
                continue;
            }
        }
    } while(codigo!=0);
}

//********Função para listar produtos
void listarProdutos() 
{
    int i;
    system("cls");
    for(i=0; i<1000;i++)
    {
        if(produtos[i].codigo!=0&&produtos[i].codigo!=NULL)
        {
            printf("\nCodigo: %i", produtos[i].codigo);
            printf("\nDescricao: %s", produtos[i].nome);
            printf("\nEstoque: %d", produtos[i].estoque);
            printf("\nValor de venda: R$ %.2f", produtos[i].valor);
            printf("\n\n");
        }
    }
    opcao='0';
    system("pause");
}

//********Função para remover produto 
void removerProduto() 
{
    
    int input, indiceVazio;
    char op;
    indiceVazio = produtoVazio();
    system("cls");
    printf("Digite o código do produto que deseja excluir: ");
    scanf("%d", &input);
    flush_in();

    if (input>=0&&input<1000) 
    {
        if(produtos[input-1].codigo!=NULL) 
        {
            
            printf("\nCodigo: %i", produtos[input-1].codigo);
            printf("\nDescricao: %s", produtos[input-1].nome);
            printf("\nEstoque: %d", produtos[input-1].estoque);
            printf("\nValor de venda: R$ %.2f", produtos[input-1].valor);
            sleep(1);
            do 
            {
                printf("\n\nConfirmar exclusao do produto? ");
                printf("\n[S] - Sim\n[N] - Nao\n ");
                sleep(1);
                scanf("%c", &op);
                flush_in();
                op = toupper(op);
                switch(op) {
                    case 'S':
                        produtos[input-1].codigo=produtos[indiceVazio].codigo;
                        strcpy(produtos[input-1].nome, produtos[indiceVazio].nome);
                        produtos[input-1].estoque=produtos[indiceVazio].estoque;
                        produtos[input-1].valor=produtos[indiceVazio].valor;
                        sleep(1);
                        system("cls");
                        printf("Produto removido com sucesso!\n\n");
                        system("pause");
                        break;
                    case 'N':
                        printf("\n\nOperacao cancelada. Retornando...");
                        break;
                    default:
                        printf("\n\nComando invalido!");
                        break;
                }
            } while(op!='S'&&op!='N');
           
        } else {
            printf("\nProduto nao encontrado!");
            sleep(2);
        }        
    } 
    
}
//************Função que faz a busca de produtos
void buscarProduto() {
    char descricao[40];
    int i, j, result=-1;
    j = ultimoProdutoVazio();
    system("cls");
    printf("Digite o nome do produto que deseja buscar: ");
    scanf("%[^\n]s", descricao);
    flush_in();
        
    for (i=0; i<j; i++) 
    {
        if((strcmp(produtos[i].nome, descricao)==0)) 
        {
            result = i;
            break;
        }
    }

    if(result>=0) 
    {
        system("cls");
        printf("Produto encontrado!");
        printf("\n\nCodigo: %i", produtos[result].codigo);
        printf("\nDescricao: %s", produtos[result].nome);
        printf("\nEstoque: %d", produtos[result].estoque);
        printf("\nValor de venda: R$ %.2f", produtos[result].valor);
        printf("\n\n");
        system("pause");
    } else 
    {
        printf("\n\nProduto nao encontrado!\n\n");
        system("pause");
    }


}

//esta função retorna o indice do primeiro item vazio do vetor de produtos, para cadastro de novo produto;
int produtoVazio() {
    int i;
    for(i=0;i<1000;i++) {
        if(produtos[i].codigo==NULL||produtos[i].codigo==0) 
        {
           break;
        }
    }
    return(i);
}
//esta funcao retorna o indice do ultimo item vazio do vetor de produtos
int ultimoProdutoVazio() {
    int i;
    for(i=1000;i>=0;i--) {
        if(produtos[i].codigo!=NULL) 
        {
            break;
        }
    }
    return(i+1);
}

//**********Função Menu de Gerência de Vendas*************//
void gerenciarVendas() 
{
     do 
    {
        system("cls");
        printf("\n********************************************************\n");
        printf("\n*              Gerenciamento de Vendas                 *\n");
        printf("\n********************************************************\n");
        printf("\nEscolha uma opcao pressionando uma tecla...\n");
        printf("\n[V] - Nova Venda \n[R] - Relatorio de vendas \n[S] - Voltar ao Menu Principal\n");
        opcao = getche();
        opcao = toupper(opcao);
        
        switch (opcao) 
        {
            case 'V':
                novaVenda();
                break;
            case 'R':
                relatorioVendas();
                break;
            case 'S':
                menu();
                break;
            default:
                printf("\nERRO: Opcao invalida. Tente novamente...");
                sleep(3);
                break;
        } //fim do switch
    } while(opcao!='V' && opcao!='L' && opcao!='B' && opcao!='S');
}

//***********Função que inicia nova venda
void novaVenda()
{   
    int i, j, op, itemRemover, cod, codUltimoProduto, itemQuant, itemVazio=0;
    float total = 0;
    char nomeBuscado[40];
    marcadorVendas++;
    vendas[marcadorVendas].codigo=marcadorVendas;
    codUltimoProduto = (ultimoProdutoVazio()+1);
    
    do 
    {   
        total = 0;        
        system("cls");
        printf("PDV - PONTO DE VENDAS");
        printf("--------------------------------");
        printf("\nNo. da Venda: %d", vendas[marcadorVendas].codigo);
        printf("\nItens: \n");
       
        for(i=0; i<100; i++)
        {
            if(vendas[marcadorVendas].itens[i].codigo!=NULL)
            {
                printf("\nNo.: %i   Produto: %s   Quant: %i   Valor: %.2f Total: %.2f", i+1, vendas[marcadorVendas].itens[i].nome, vendas[marcadorVendas].itens[i].quantVenda, vendas[marcadorVendas].itens[i].valor, (vendas[marcadorVendas].itens[i].quantVenda * vendas[marcadorVendas].itens[i].valor));
                printf("\n------------------------------------------------------------");
                total += (vendas[marcadorVendas].itens[i].quantVenda * vendas[marcadorVendas].itens[i].valor);
            } else {
                break;
            }
        }
        printf("\n                      Total: %.2f", total);
        printf("\n\n[1] - Inserir produto   [2] - Remover produto   [3] - Cancelar Venda    [4] - Finalizar Venda");
        printf("\nDigite uma opcao: \n");
        opcao = getche();
        opcao = toupper(opcao);

        switch(opcao) 
        {
            case '1':
                printf("\n\nComo deseja selecionar o produto?  [1] - Inserir codigo  [2] - Buscar Produto por Nome\n");
                scanf("%d", &op);
                flush_in();
                if(op==1) // opção de inserir produto pelo código
                {
                    printf("\nInsira o codigo do produto: ");
                    scanf("%d", &cod);
                    printf("\nInsira a quantidade: ");
                    scanf("%d", &itemQuant);
                    flush_in();

                    if(cod<codUltimoProduto && cod>0 && produtos[cod-1].codigo!=NULL) 
                    {
                        vendas[marcadorVendas].itens[itemVazio].codigo = produtos[cod-1].codigo;
                        vendas[marcadorVendas].itens[itemVazio].valor = produtos[cod-1].valor;
                        vendas[marcadorVendas].itens[itemVazio].quantVenda = itemQuant;
                        strcpy(vendas[marcadorVendas].itens[itemVazio].nome, produtos[cod-1].nome);
                        itemVazio++;
                    } else
                    {
                        printf("\nCodigo invalido ou produto nao encontrado...");
                        sleep(2);
                    }
                } else if(op==2)  // opção de buscar produto pelo nome e inserir produto
                {
                    j = ultimoProdutoVazio();
                    printf("\nDigite o nome do produto: \n");
                    scanf("%s", nomeBuscado);
                    
                    for (i=0; i<j; i++) 
                    {
                        if((strcmp(produtos[i].nome, nomeBuscado)==0)) 
                        {
                            printf("\n\nProduto encontrado!");
                            printf("\n\nCodigo: %i", produtos[i].codigo);
                            printf("\nDescricao: %s", produtos[i].nome);
                            printf("\nEstoque: %d", produtos[i].estoque);
                            printf("\nValor de venda: R$ %.2f", produtos[i].valor);
                            printf("\n\nAdicionar este produto?  [1] Sim    [2] Nao \n");
                            scanf("%d", &op);
                            
                            if(op==1)
                            {
                                printf("\nInsira a quantidade: ");
                                scanf("%d", &itemQuant);
                                vendas[marcadorVendas].itens[itemVazio].codigo = produtos[i].codigo;
                                vendas[marcadorVendas].itens[itemVazio].valor = produtos[i].valor;
                                vendas[marcadorVendas].itens[itemVazio].quantVenda = itemQuant;
                                strcpy(vendas[marcadorVendas].itens[itemVazio].nome, produtos[i].nome);
                                itemVazio++;
                            } else if(op==2) {
                                break;
                            } else {
                                printf("\nOpcao invalida\n");
                                system("pause");
                            }
                            break;
                        } else
                        {
                            printf("\nProduto nao encontrado.");
                            sleep(1);
                        }
                    }
                }
                break;
            case '2':
                printf("\nDigite o numero do item que deseja remover: ");
                scanf("%d", &itemRemover);
                if(itemRemover>0 && itemRemover<itemVazio+1)
                {
                    for(i=itemRemover-1; i<itemVazio+1; i++)
                    {
                        vendas[marcadorVendas].itens[i]=vendas[marcadorVendas].itens[i+1];
                        
                    }
                    itemVazio--;
                } else
                {
                    printf("\nInput invalido");
                    sleep(2);
                }
                break;
            case '3':
                marcadorVendas--;
                break;
            case '4':
                //Fazer as alterações no estoque conforme estao no struct de vendas
                if(itemVazio==0)
                {
                    opcao='0';
                    printf("\nImpossivel efetuar venda sem itens...");
                    sleep(2);
                } else
                {
                    for(i=0; i<itemVazio; i++)
                    {
                        produtos[vendas[marcadorVendas].itens[i].codigo-1].estoque -= vendas[marcadorVendas].itens[i].quantVenda;
                        produtosVendidos += vendas[marcadorVendas].itens[i].quantVenda;
                    }
                    printf("\nVenda finalizada!\n");
                    totalVendido+=total;
                    system("pause");
                }

                break;
            default:
                break;

        }

    } while (opcao!='3'&&opcao!='4');
    printf("\n\nRetornando ao menu anterior...");
    sleep(2);
    return 0;
}
//***********Função que imprime relatorio de vendas
void relatorioVendas()
{
    system("cls");
    printf("RELATORIO DE VENDAS\n");
    printf("\nTotal de vendas: %d", marcadorVendas);
    printf("\nTotal de produtos vendidos: %d", produtosVendidos);
    printf("\nValor total recebido: %.2f\n\n", totalVendido);
    system("pause");    
}
//***********Função que carrega os dados de clientes do arquivo******************//
void carregarClientes()
{
    int j=0;
    FILE *fclientes;

    //Carregar os clientes registrados no arquivo txt;
    fclientes = fopen("clientes.txt", "r");
    if(fclientes == NULL)
    {
        printf("\nErro ao carregar dados...");
        sleep(2);
        exit(1);
    } else {
        while(!feof(fclientes))
        {
            fscanf(fclientes, "\n%d", &clientes[j].codigo);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].nome);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].cpf);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].telefone);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].endereco);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].cidade);
            fscanf(fclientes, "\n%[^\n]s", clientes[j].estado);
            if(clientes[j].codigo!=NULL)
            {
                j++;
                quantClientes++;
                marcadorClientes++;
            }  
        }
    }
    
    fclose(fclientes);
}
//***********Função que carrega os dados de produtos do arquivo******************//
void carregarProdutos()
{
    int j=0;
    FILE *fprodutos;

    //Carregar os clientes registrados no arquivo txt;
    fprodutos = fopen("produtos.txt", "r");
    if(fprodutos == NULL)
    {
        printf("\nErro ao carregar dados...");
        sleep(2);
        exit(1);
    } else {
        while(!feof(fprodutos))
        {
            fscanf(fprodutos, "\n%d", &produtos[j].codigo);
            fscanf(fprodutos, "\n%[^\n]s", produtos[j].nome);
            fscanf(fprodutos, "\n%i", &produtos[j].estoque);
            fscanf(fprodutos, "\n%f", &produtos[j].valor);
            
            if(produtos[j].codigo!=NULL)
            {
                j++;
                quantProdutos++;
                marcadorProdutos++;
            }  
        }
    }
    
    fclose(fprodutos);
}
//***********Função que carrega os dados de vendas do arquivo******************//
void carregarVendas()
{
    FILE *fvendas;
    fvendas = fopen("vendas.txt", "r");

    if(fvendas == NULL)
    {
        printf("\nErro ao carregar dados...");
        sleep(2);
        exit(1);
    }
    
    fscanf(fvendas, "%i", &produtosVendidos);
    fscanf(fvendas, "\n%i", &marcadorVendas);
    fscanf(fvendas, "\n%f", &totalVendido);

    fclose(fvendas);
}
//***********Função que salva os dados do programa no arquivo******************//
void salvarTudo() 
{
    int i, ultimoCliente, ultimoProduto=ultimoProdutoVazio();
    
    //Salvar os dados de clientes
    FILE *fclientes;
    fclientes = fopen("clientes.txt", "w+");
    if(fclientes == NULL)
    {
        printf("\nErro ao salvar dados...");
        sleep(2);
        exit(1);
    }

    system("cls");
    printf("Salvando...");
    sleep(2);
    
    for(i=0; i<100;i++)
    {
        if(clientes[i].codigo!=0&&clientes[i].codigo!=NULL)
        {
            ultimoCliente = i;
        } else 
        {
            break;
        }
    }

    if(quantClientes>0)
    {
        for(i=0; i<=ultimoCliente; i++)
        {
            fprintf(fclientes, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s", clientes[i].codigo, clientes[i].nome, clientes[i].cpf, clientes[i].telefone, clientes[i].endereco, clientes[i].cidade, clientes[i].estado);
            
        }
    }

    fclose(fclientes);

    //Salvar os dados de produtos;
    FILE *fprodutos;
    fprodutos=fopen("produtos.txt", "w");

    if(fprodutos == NULL)
    {
        printf("\nErro ao salvar dados...");
        sleep(2);
        exit(1);
    }

    for(i=0; i<ultimoProduto; i++)
    {
        fprintf(fprodutos, "\n%d\n%s\n%d\n%.2f", produtos[i].codigo, produtos[i].nome, produtos[i].estoque, produtos[i].valor);
        
    }

    fclose(fprodutos);

    //Salvar os dados de vendas;
    FILE *fvendas;
    fvendas=fopen("vendas.txt", "w");

    if(fvendas == NULL)
    {
        printf("\nErro ao salvar dados...");
        sleep(2);
        exit(1);
    }
    fprintf(fvendas, "%i\n%i\n%.2f", produtosVendidos, marcadorVendas, totalVendido);

    fclose(fvendas);
    system("cls");
}
//Limpa o buffer do teclado
void flush_in()
{ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}