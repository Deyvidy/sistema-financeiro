/*Considera uma empresa que deseja contador seu caixa com a seguintes caracteristicas: 
Conta:{int: codigo, string: desc}
Historico:{ int: Codigo, String: descri??o, Char: tipo (C=credito'receber', D=debito'pagar')}
Movimento:{ data: dia, mes, ano, 'conta:Conta= struct', 'struct=historico:historico', valor,String: complemento}
Sabendo que a movimenta??o do dia se resume a 100 movimento, fa?a:
1- cadastrar conta, historico 
1-1 - listar
2 cadastra movimenta??o
3- lista caixa do dia 
4- lista somente o movimento de uma conta especifica
5- lista somente o movimento de um historico especifico
obs: itens 4 e 5 devera 
*/
     
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
     
#define TAM 3
     
typedef struct CONTA_CLIENTE {
    int codigo;
    char descricao[100];
}Client;
   
     
typedef struct HISTORICO_TRANSACAO {
    int codigo;
    char descricao[100];
    char tipoDeTransacao;
}Historico;
    
     
typedef struct DATA_TRANSACAO{
    char data[10];
}Data;
   
     
typedef struct MOVIMENTACAO_CLIENTE{
    Data data[TAM];
    Client client[TAM];
    Historico historio[TAM];
    float valor;
    char complemento[100];
    int status;
}Movimentacao;
 Movimentacao movimentacao [TAM];   
     
      
void menu ( );
void cadastraConta ( int codigo, int pos );
void realizarOperacoes ( );
void login ( );
float processarOpercao ( int pos, int valor, char tipoDaOpercao );
void ExibirContaEspecifica ( );
void consultar ( );
void exibir ( int pos );
int verificarPosicao ( );
int verificarCod (int codigo);
   
// variaveis globais (contador) para saber o tamanho do vetor  (opercao) par saber quantas operacoes foram feitas;  
int contador=0, operacao=0;

    
int main ( ) {
        
    menu ( );
       
}

     
void menu ( ) {
    int op, posicao, verificaCodigo, confirmacao, conta;
    char opcoes;
    printf("[1]\t Cadastra conta\n[2]\t Entra na conta\n[3]\t Listar todas contas\n[4]\t Exibir Conta expecifica\n");
    scanf("%s",&opcoes);
         
    switch ( opcoes ) {
        case '1' : {
            posicao = verificarPosicao ( );
            if( posicao != -1 ) {
                  
                printf("Codigo: \n");
                scanf("%d",&verificaCodigo);
                  
                confirmacao = verificarCod( verificaCodigo);
                  
                if( confirmacao == 1 )
                    cadastraConta( verificaCodigo, posicao );
                else
                    printf("\nCodigo ja existente\n");
            }
            else
                printf("\nNao e possivel realizar mais cadastros!\n");         
            break;
        }
        case '2' : 
            login (  );
            break; 
        case '3' :
            consultar( );
            break;
        case '4' :
			 ExibirContaEspecifica ( );
			 break;   
        default :
            printf("opcao invalida\n");
            break;
    }
     system("pause");
     system("cls");
     menu ( );
    
}

     
void cadastraConta( int codigo, int pos ) {
    pos = verificarPosicao( );   
    
    movimentacao[pos].client[pos].codigo = codigo;
        
    printf("Conta: %d\n",movimentacao[pos].client[pos].codigo);
        
    printf("descricao\n");
    scanf("%s",&movimentacao[pos].client[pos].descricao);
       
    movimentacao[pos].status = 1; 
     
    contador++;
       
    printf("\nCadastro Realizado com Sucesso!\n\n");
    getchar();
     
    system ("pause");
    system("cls");
    menu ( );       
}

    
void login (  ) {
    int conta, validacao,pos;
    char op, resp;
    float valor, valorOp;
       
    printf("Conta: ");
    scanf("%d",&conta);
     
    while ( pos < TAM ) { 
        if ( movimentacao[pos].client[pos].codigo == conta ) { 
            if ( movimentacao[pos].status == 1 ) {
            	exibir ( pos );

                getchar();
  
                printf("\nDeseja fazer uma operacao S/N:");
                scanf("%c",&resp);
  
                if ( ( resp == 'S' ) || ( resp == 's' ) ) {
                     
                    printf("Codigo da operacao: \n");
                    scanf("%d",&movimentacao[pos].historio[pos].codigo);
                       
                    printf("Valor:\n");
                    scanf("%f",&valor);
                      
                    printf("[c]\tCredito\n[d]\tDebito\n");
                    scanf("%s",&op);
                       
                    printf("Descri??o:\n");
                    scanf("%s",&movimentacao[pos].historio[pos].descricao);
                     
                    valorOp=processarOpercao ( pos, valor, op ); 
                     
                    printf("\nOpercao feita com sucesso\n");
                    break;
                }
                else {
                    if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                        printf("operacao cancelada!\n");
                        break;
                    }
                }
            }
        }
        pos++;
        if ( pos > TAM )
            printf("\nConta nao encontrada\n");
    }
         
    system("pause");
    system("cls");
}  


void ExibirContaEspecifica ( ) {
	int pos = 0, conta;
 
    printf("\nEntre com o codigo da conta\n");
    scanf("%d",&conta);
 
    system("cls");
    
    for( pos = 0; pos < contador; pos++ ) {
    	if( conta == movimentacao[pos].client[pos].codigo ) {
    		exibir ( pos );
		}
	}
    system ("pause");
    system("cls");
    menu( );
}

//exibir contas cadastradas 
void consultar( ) { 
     int pos=0; 
    for ( pos = 0; pos < contador; pos++ ) {
    	exibir ( pos );
    }
    
    system ("pause");
    system("cls");
    menu( );
}

// funcao responsavel de printar as informacoes da conta
void exibir ( int pos ) {
	printf("\n=========================\n");
    printf("Conta: %d\n",movimentacao[pos].client[pos].codigo);
    printf("descricao %s\n",movimentacao[pos].client[pos].descricao);
    printf("saldo: %.2f\n",movimentacao[pos].valor);
}


//procesa as opercaoes debito e credito 
float processarOpercao ( int pos, int valor, char tipoDaOpercao ) {
     
    if ( tipoDaOpercao == 'c'){
        movimentacao[pos].valor+=valor;
            return movimentacao[pos].valor;
    }
    if ( tipoDaOpercao == 'd') {
        movimentacao[pos].valor-= valor;
            return movimentacao[pos].valor;
    } 
    else {
        printf("Operacao Invalida\n");
        return movimentacao[pos].valor;
    }
         
} 
   

//Verifica a posicao do vetor foi preenchida
int verificarPosicao ( ) { 
    int cont = 0;
    while ( cont < TAM ){ 
        if ( movimentacao[cont].status == 0 )
            return(cont); 
        cont++;
    }
    return(-1);
} 
   
     
//Verifica se o conta ja foi cadastrado
int verificarCod( int codigo ) {
    int cont = 0;
     
    while ( cont < contador ) {
        if ( movimentacao[cont].client[cont].codigo == codigo ) 
            return(0);
         cont++;
    }
     return(1);
}
