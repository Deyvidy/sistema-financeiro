#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
      
#define TAMC 5 //Tamanho do vetor da struct Cliente
#define TAMD 5 //Tamanho do vetor da struct Data
#define TAMH 5 //Tamanho do vetor da struct Historico
#define TAMM 5 //Tamanho do vetor da struct Movimentaca
#define TAMDIA 1
 
      
typedef struct CONTA {
    int codigo;
    char descricao[100];
    int status;
}Client;
    
      
typedef struct HISTORICO {
    int codigo;
    char descricao[100];
    char tipoDeTransacao;
    int status;
}Historico;
     
      
typedef struct DATA{
    int dia, mes, ano;
}Data;
    
      
typedef struct MOVIMENTACAO{
    Data data;
    Client client;
    Historico historico;
    float valor;
    char complemento[100];
    int status;
}Movimentacao;
  
  
//Declara??o das structs 
Client client [TAMC];
 
Historico historico [TAMH];
 
Data data [TAMD];
 
Movimentacao movimentacao [TAMM];   
 
 
//Declara??o das fun?oes      
void menu ( );
void menuExibir ( );
void menuExcluir ( );
void menuAlterar ( );
 
void cadastraConta ( int codigo, int i );
void excluirContaCliente ( );
 
void cadastraHistorico ( int codigo, int j );
void historicoExpecifico( );
 
void realizarOperacoes ( );
void listarMovimentacoes ( );
void listarTodasOpercaoes ( );
void login ( );
Client dadosClient ( int conta );
 
float processarOpercao ( );
void exibirContaEspecifica ( );
void consultarContaCliente ( );
void exibirHistorico ( int j );
void consultarHistorico( );
int buscaHistorico ( int codigo );
void exibir ( int pos );
 
int verificarPosicaoHistorico ( );
int verificarCodHistorico ( int codigo );
 
int verificarPosicao ( );
int verificarCod ( int codigo );
    
// variaveis globais (contador) para saber o tamanho do vetor  (opercao) par saber quantas operacoes foram feitas;  
int contador = 0, operacao = 0, his = 0, statusConta=0, movi=0;
 
//=============================MENU========================================    
int main ( ) {
     int op, posicao, posicaoH, verificaCodigo, confirmacao, confirmacaoH, conta;
    char opcoes;
     
    do { 
        printf("[1]\t Cadastra conta\n[2]\t Cadastra historico\n[3]\t Entra na conta\n");
        printf("[4]\t Exibir\n");
        printf("[5]\t Alterar\n");
        printf("[6]\t Excluir\n");
        printf("[0]\t Sair\n");
        scanf("%s",&opcoes);
          
    switch ( opcoes ) {
        case '1' : {
            posicao = verificarPosicao ( );
            if( posicao != -1 ) {
                   
                printf("Codigo da Conta: \n");
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
        case '2' : {
            posicaoH = verificarPosicaoHistorico ( );
            if( posicaoH != -1 ) {
                   
                printf("Codigo do Historico: \n");
                scanf("%d",&verificaCodigo);
                   
                confirmacaoH = verificarCodHistorico( verificaCodigo);
                   
                if( confirmacaoH == 1 )
                    cadastraHistorico ( verificaCodigo, posicaoH );
                else
                    printf("\nCodigo do historico ja existente\n");
            }
            else
                printf("\nNao e possivel realizar mais cadastros!\n");     
            break;
            }
        case '3' :
            login ( );              
            break;
        case '4' :
            menuExibir ( );
            break;
        case '5' :
            menuAlterar ( );              
            break;
        case '6' :
            menuExcluir ( );      
            break;
        case '0' :
            printf("Bye!!\n");
            system("");
            break;          
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='7' ); 
}
 
      
void menu ( ) {
    system("cls");
     
    int op, posicao, posicaoH, verificaCodigo, confirmacao, confirmacaoH, conta;
    char opcoes;
     
    do { 
    if( statusConta != 0 ) {
        printf("\t\t\t\%s\n",dadosClient(statusConta).descricao);
    }
    printf("[1]\t Realizar operacao\n[2]\t Exibir operacoes feitas\n[3]\t Saldo\n[4]\t Voltar\n");
    scanf("%s",&opcoes);
      
    switch ( opcoes ) {
    case '1' : {
        realizarOperacoes  ( );       
        break;
    }
    case '2' : {
        listarMovimentacoes ( );    
        break;
    }
    case '3' :
        processarOpercao ( );
        break;  
    case '4' :
        statusConta=0;
        main( );
        break;          
    default :
        printf("opcao invalida\n");
        break;
    }
    system("pause");
    system("cls");
    }while( opcoes !='3' );
     
}
 
//==============================EXIBIR====================================
void menuExibir ( ) {
    char opcoes;
     
    do { 
        printf("[1]\t Exibir todas Contas\n[2]\t Exibir Conta especifica\n");
        printf("[3]\t Exibir todos historicos\n[4]\t Exibir historico especifico\n");
        printf("[5]\t Exibir todas operacoes\n");
        printf("[0]\t Voltar\n");
        scanf("%s",&opcoes);
          
    switch ( opcoes ) {
        case '1' :
            consultarContaCliente ( );
            break;
        case '2' :
            exibirContaEspecifica ( );             
            break;
        case '3' :
            consultarHistorico ( ); 
			break;
		case '4' :
			historicoExpecifico( );
			break;	        
		case '5' :
			listarTodasOpercaoes ( );
			break;
		case '0' :
			main( );
			break;			
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='5' ); 
}
 
 
//===============================EXCLUIR===================================
void menuExcluir ( ) {
	char opcoes;
     
    do { 
        printf("[1]\t Excluir Conta\n");
        printf("[2]\t Excluir historico\n");
        printf("[3]\t Excluir operacoes\n");
        printf("[0]\t Voltar\n");
        scanf("%s",&opcoes);
          
    switch ( opcoes ) {
        case '1' :
            excluirContaCliente( );
            break;
        case '2' :
            //exibirContaEspecifica ( );             
            break;
        case '3' :
            //consultarHistorico ( ); 
			break;
		case '0' :
			main ( );
			break;	        
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='5' ); 
}
 
//==================================ALTERAR=================================
void menuAlterar ( ) {
    char opcoes;
     
    do { 
        printf("[1]\t Alterar Conta\n");
        printf("[2]\t Alterar Historico\n");
        printf("[3]\t Alterar Operacoes\n");
        printf("[0]\t Volta\n");
        scanf("%s",&opcoes);
          
    switch ( opcoes ) {
        case '1' :
            //consultarContaCliente ( );
            break;
        case '2' :
            //exibirContaEspecifica ( );             
            break;
        case '3' :
            //consultarHistorico ( ); 
			break;
		case '0' :
			main( );
			break;	        
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='5' ); 
}
 
//==========================================================================
  
      
void cadastraConta( int codigo, int i ) {
    system("cls");
    i = verificarPosicao( );   
     
    client[i].codigo = codigo;
     
         
    printf("Conta: %d\n",client[i].codigo);
         
    printf("descricao\n");
    scanf("%s",&client[i].descricao);
        
    client[i].status = 1; 
      
    contador++;
        
    printf("\nCadastro Realizado com Sucesso!\n\n");
    getchar();
      
    system ("pause");
    system("cls");
    main ( );       
}
 
 
void exibirContaEspecifica ( ) {
    int pos = 0, conta, ok=0;
  
    printf("\nEntre com o codigo da conta\n");
    scanf("%d",&conta);
  
    system("cls");
     
    for( pos = 0; pos < contador; pos++ ) {
        if( conta == client[pos].codigo ) {
            if( client[pos].status == 1 ) {
                exibir ( pos ); 
                ok=1;
            }
        }
    }
    if ( ok != 1 ) {
        printf("Conta nao encontrada\n");
    }
    system ("pause");
    system("cls");
    menuExibir ( );
}
 
 
//exibir contas cadastradas 
void consultarContaCliente( ) { 
     int pos=0; 
    for ( pos = 0; pos < contador; pos++ ) {
        if ( client[pos].status == 1 ) {
            exibir ( pos ); 
        }
    }
     
    system ("pause");
    system("cls");
    menuExibir ( );
}
 
 
// funcao responsavel de printar as informacoes da conta
void exibir ( int pos ) {
    printf("=========================\n");
    printf("Conta: %d\n",client[pos].codigo);
    printf("descricao %s\n",client[pos].descricao); 
    printf("\n");
}
 
  
void excluirContaCliente( ) {
    int cod, i = 0;
    char resp;
 
    printf("");
    scanf("%d", &cod );
 
    while ( i < contador) {
 
        if ( client[i].codigo == cod ) { 
 
            if ( client[i].status == 1 ) {
 
                exibir ( i );
                 
                getchar();
 
                printf("\nDeseja realmente exlucir? S/N:");
                scanf("%c",&resp);
 
                if ( ( resp == 'S' ) || ( resp == 's' ) )
                {
                    client[i].status=0;
                    printf("\nExclusao feita com sucesso\n");
                    break;
                }
                else
                {
                    if ( ( resp == 'N' ) || ( resp == 'n' ) )
                    {
                        printf("Exclusao cancelada!\n");
                        break;
                    }
                }
 
            }
 
        }
 
        i++;
 
        if ( i > contador )
            printf("\nCodigo nao encontrado\n");
 
    }
 
    system("pause");
    system("cls");
 
}
  
     
void cadastraHistorico ( int codigo, int j ) {
    system("cls");
    int ok;
    char op;
 
    j = verificarPosicaoHistorico ( );
    historico[j].codigo = codigo; 
     
    printf("Codigo: %d\n",historico[j].codigo);
     
    printf("Descricao:\n");
    scanf("%s",&historico[j].descricao);
       
    printf("[c]\tCredito\n[d]\tDebito\n");
    
    while( 1 ) {
        scanf("%s",&op);
        setbuf(stdin, NULL);
        if( op == 'C' || op == 'c' ) {
            historico[j].tipoDeTransacao = 'c';
            break;
        }
        if( op == 'D' || op == 'd' ) {
            historico[j].tipoDeTransacao = 'd';
            break;
        }
        else{
            printf("Operacao invalida\n");
        }
        }
     
    historico[j].status =1;
        
    printf("\nOpercao feita com sucesso\n");
     
    movimentacao[j].historico = historico[(ok - 1)];
    //codigo = movimentacao[j].client;
    his++;  
          
    system("pause");
    system("cls");
    main( );
}  
 
 
void consultarHistorico( ) { 
    int j, ok=0;
    for ( j = 0; j < his; j++ ) {
        if( historico[j].status == 1 ) {
            ok=1;
            exibirHistorico ( j );  
        }
    }
    if ( ok != 1 ) {
        printf("Sem historicos cadastrados\n");
    }
    menuExibir ( );
}
 
 
void historicoExpecifico( ) { 
    int j, codigo, ok=0;
     
    printf("Codigo do historico\n");
    scanf("%d",&codigo);
     
    for ( j = 0; j < his; j++ ) {
        if( codigo == historico[j].codigo ) {
            if( historico[j].status == 1 ) {
            ok = 1;
            exibirHistorico ( j );  
            }
        }
    }
    if ( ok != 1 ) {
        printf("Historico nao encontrado\n");
    }
    menuExibir ( );
}
 
 
void exibirHistorico ( int j ) {
     
    printf("=========================\n");
    printf("Conta: %d\n",historico[j].codigo);
    printf("descricao %s\n",historico[j].descricao);
    printf("Tipo operacao %c",historico[j].tipoDeTransacao);
    printf("\n");
     
}
 
 
void login ( ) {
    system("cls");
    int codigoDaConta;
    int i;
     
    printf("Digite sua conta \n\n");
    scanf("%d", &codigoDaConta);
     
    if( contador > 0 ) {
        for( i = 0; i < contador; i++ ) {
            if( client[i].codigo == codigoDaConta ) {
                statusConta = client[i].codigo;
                menu ( );
                break;
            }
        }
        if( statusConta == 0 ) {
            printf(" Conta nao encontrada \n \n ");
            system("pause");
            login ( );
            }
        }
  
    else {
        printf(" Nao  possui nenhuma conta cadastrada \n \n");
    }
}
 
 
void realizarOperacoes  ( ) {
    system("cls"); 
    int codigoOperacao, dia, i,j, ok=0;
    int operacaoEncontrada = 0;float valorMovimentacao;
    
    printf("Historicos:\n");
    consultarHistorico( );
     
    printf("\nCodigo do historico: \n");
    scanf("%d",&codigoOperacao);
     
    operacaoEncontrada = buscaHistorico(codigoOperacao);
    movimentacao[movi].historico = historico[(operacaoEncontrada)];
    movimentacao[movi].client = dadosClient (statusConta);
 
    printf("Valor: \n");
    scanf("%f",&movimentacao[movi].valor);
 
    printf("Data dd/mm/aa\n");
    printf("Dia: ");
    scanf("%d",&movimentacao[movi].data.dia);
    printf("Mes: ");
    scanf("%d",&movimentacao[movi].data.mes);
    printf("Ano: ");
    scanf("%d",&movimentacao[movi].data.ano);
 
    printf("Complemento: \n");
    scanf("%s",&movimentacao[movi].complemento);
    
    movimentacao[movi].status = 1;
      
    movi++;
 	printf("\nOpercao feita com sucesso!!\n");
         
    system("pause"); 
    system("cls");       
    menu( );
}
 
 
void listarMovimentacoes ( ) {
    system("cls"); 
    char descricaoTipo[20];
    int i;
  
    if( movi > 0 ) {
        printf(" \n Lista de Movimentacoes \n \n");
        for( i = 0; i < movi; i++ ) {
            if(movimentacao[i].client.codigo == dadosClient(statusConta).codigo){
  
                printf("Descricao \t %s \n", movimentacao[i].historico.descricao);
                printf("Data \t %d/ %d/%d \n",
                        movimentacao[i].data.dia,
                        movimentacao[i].data.mes,
                        movimentacao[i].data.ano
                );
  
                printf("Tipo \t %c \n",movimentacao[i].historico.tipoDeTransacao);
                printf("Complemento \t %s \n", movimentacao[i].complemento);
                printf("Valor \t %.2f \n", movimentacao[i].valor);
                printf(" \n \n");
            }
        }
    }else{
        printf("Nenhuma operacao realizada!\n");   
    }
    system("pause");
    system("cls");
    menu( );
}
 
void listarTodasOpercaoes ( ) {
    system("cls"); 
    char descricaoTipo[20];
    int i;
  
    if( movi > 0 ) {
        printf(" \n Lista de Movimentacoes \n \n");
        for( i = 0; i < movi; i++ ) {
            if(movimentacao[i].status == 1){
  
                printf("Descricao \t %s \n", movimentacao[i].historico.descricao);
                printf("Data \t %d/ %d/%d \n",
                        movimentacao[i].data.dia,
                        movimentacao[i].data.mes,
                        movimentacao[i].data.ano
                );
  
                printf("Tipo \t %c \n",movimentacao[i].historico.tipoDeTransacao);
                printf("Complemento \t %s \n", movimentacao[i].complemento);
                printf("Valor \t %.2f \n", movimentacao[i].valor);
                printf(" \n \n");
            }
        }
    }else{
        printf("Nenhuma operacao realizada!\n");   
    }
    system("pause");
    system("cls");
    menuExibir ( );
 
}
 
int buscaHistorico( int codigo ) {
    int i;
     
    for( i = 0; i < TAMH; i++ ) {
        if( historico[i].codigo == codigo) {
            return i;
        }
    }
    return 0;
}
 
 
Client dadosClient ( int conta ) {
    int i;
    for ( i = 0; i < TAMH; i++ ) {
        if( conta == client[i].codigo ) {
            return client[i];
        }
    }
}
 
 
//procesa as opercaoes debito e credito 
float processarOpercao ( ) {
    float saldo = 0;
    for(int h = 0 ; h < movi; h++){
        if(movimentacao[h].client.codigo == dadosClient(statusConta).codigo){
            if(movimentacao[h].historico.tipoDeTransacao == 'd'){
                saldo -= movimentacao[h].valor;
            }else{
                saldo += movimentacao[h].valor;
            }
        }
    }
    printf("\nSaldo atual: R$ %.2f.\n", saldo);
    system("pause");
    system("cls");
    menu();
} 
    
 
//Verifica se a posicao  do vetor ja foi preenchida por alguma historico
int verificarPosicaoHistorico ( ) { 
    int j;
    for( j = 0; j < TAMH; j++ ) {
        if ( historico[j].status == 0 ) {
            return(j);
        }
    }
    return(-1);
} 
    
      
//Verifica se o historico ja foi cadastrado
int verificarCodHistorico ( int codigo ) {
    int j;
     for( j = 0; j < his; j++ ) {
        if ( historico[j].codigo == codigo ) {
            return(0);
        }
    }
     return(1);
}
 
 
//Verifica se a posicao  do vetor ja foi preenchida por alguma conta
int verificarPosicao ( ) { 
    int i;
    for( i = 0; i < TAMC; i++ ) {
        if ( client[i].status == 0 ) {
            return(i);
        }
    }
    return(-1);
} 
    
      
//Verifica se o conta ja foi cadastrado
int verificarCod( int codigo ) {
    int i;
     for( i = 0; i < contador; i++ ) {
        if ( client[i].codigo == codigo ) {
            return(0);
        }
    }
     return(1);
}
