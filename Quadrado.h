#ifndef quadradoAnimado
#define quadradoAnimado

#include <Windows.h> /* COORD */ 

#include "console_v1.5.4.h" /* EVENTO */

#define TITULO "Quadrado Animado"  
#define QUANTIDADE 10
#define CTRL 29

/* #-#-#-#-#-#-#-#-#-# Declaracoes de variaveis e constantes #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#*/
 

 /*	|------------ ATIVIDADE-----------------------------|
	|		Algumas funcoes tem como parametro ativar 	|
	|	ou desativar, que cotrolam seu comportamento	|
	|	para garantir a integridade das chamadas e a 	|
	|	correta passagem de parametro, foi criada um 	|
	|	enum que representa esses valores				|
	|---------------------------------------------------|
*/
typedef enum controle{
	NENHUMA = -1,
	JANELA1 = 0,
	JANELA2,
	JANELA3,
	JANELA4,
	JANELA5,
	JANELA6,
	JANELA7,
	JANELA8,
	JANELA9,
	JANELA10
}BOLADAVEZ;

typedef enum
{
	DESATIVAR,
	ATIVAR
}ATIVIDADE;

/*	|------------------- Booleano ------------------|
	|		Tipo de dado que armazena um valor 		|
	|	logico										|
	|-----------------------------------------------|
*/

typedef enum
{	FALSO,
	VERDADEIRO
}BOOLEANO;


typedef enum
{
	ENCERRARPROGRAMA,
	REIPRIMIRJANELA,
	CONTINUAR
	
}OQUEFAZER;
/*	|---------------- Direcao  -------------------------|
	|		Nessa estrutura sera numerada as 			|
	|	direções que o quadrado pode seguir				|
	|---------------------------------------------------|
*/

typedef enum
{	CIMA,
	DIREITA,
	BAIXO,
	ESQUERDA
}DIRECAO;

/*	|---------------- console  -------------------------|
	|		Nessa estrutura sera armazenada as 			|
	|	referencias do console, essas informacoes sao 	|
	|	para poder resetar as configurações ao final da |
	|	execução do programa 							|
	|													|
	|---------------------------------------------------|
*/

typedef struct _tela
{
	COORD dimensao_inicial;
	COORD posicao_inicial;
	COORD dimensao_maxima;
	
}CONSOLE;

/*	|---------------- Janela  --------------------------|
	|		Nessa estrutura sera armazenada as 			|
	|	referencias da janela externa					|
	|													|
	|---------------------------------------------------|
*/
	
typedef struct _Janela
{
	COORD PontoSE;
	COORD PontoID;

	int Linha, Coluna;
	COLORS CorJanela;
	BOOLEANO JanelaAtual; 
}JANELA;

/*	|-------------------  quadrado interno -------------|
	|	Nessa estrutura sera armazenada o quadrado		|
	|	que ficara se movimentando no centro 			|
	|	da janela 										|
	|													|
	|---------------------------------------------------|
*/

typedef struct _quadrado
{
	COLORS CorQuadrado;
	DIRECAO Direcao;
	int Velocidade;
	COORD Centro;

}QUADRADO;


typedef struct _ambiente
{
	QUADRADO Quadrado[QUANTIDADE];
	JANELA Janela[QUANTIDADE];
	
	int AreaTotal, Quantidade, AreaOucupada;
	COORD PontoInicial, PontoFinal; 
	BOLADAVEZ JanelaAtual;
}AMBIENTE;

/* #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# FIM DAS DECLARAÇÕES DAS VARIAVEIS E CONSTANTES #-#-#-#-#-#-#-#-#-#-#*/ 

/* ################################## DECLARAÇÕES DE FUNCOES  ###########################################*/ 
	

void apaga_quadrado(QUADRADO);


/*	|---------------  Janela ---------------------------|
	|	Ira criar a janela principal do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|	RECEBE:					|
	|	-> JANELA *: ponteiro para a janela do jogo		|	
	|	ETORNA: VOID 									|
	|---------------------------------------------------|
*/	
	
void gerencia_janela(JANELA, INT);

/*	|---------------  imprime quadrado -----------------|
	|	 	Funcao realiza a impressa do quadrado		|
	|	utilizando o centro do quadrado como referencia |
	|	ira realizar a impressao dos outros caracteres	|
	|	que compoe a figura na tela						|
	|	RECEBE: 										|
	|	-> QUADRADO: contem os valores do quadrado 		|
	|	interno;										|
	|	->ATIVIDADE: parametro que controla o 			|
	|	comportamento da funcao(ativa ou desativa);		|
	|	RETORNA:VOID									|
	|---------------------------------------------------|
*/

void imprime_quadrado(QUADRADO);

/*	|---------------  movimenta quadrado ---------------|
	|	 	Funcao realiza a movimentacao do quadrado	|
	|	não realiza a impressao do quadrado, a funcao 	|
	|	apenas pega o a direcao do quadrado contido na 	|
	|	estrutura e realiza a movimentacao do centro 	|
	|	na direcao contida la dentro					|
	|	RECEBE: 										|
	|	->QUADRADO *:ponteiro de quadrado que contem 	|
	|	as informações do quadrado interno que sera 	|
	|	movimentado;									|
	|	->JANELA: variavel que armazena a janela por 	|
	|	onde o quadrado interno irra se movimentar;		|
	|	RETORNA:VOID									|
	|---------------------------------------------------|
*/

void movimenta_quadrado(QUADRADO *,JANELA);

/*	|--------------- set Ambiente ----------------------|
	|	Ira criar a definição do prompt do jogo			|
	|	Tamanho da janela e posicao da janela			|
	|	Tamanho Maximo;									|
	|	->CONSOLE *: ponteiro que armazena os valores de| 
	|	referencia do console onde sera executada 		|
	|	o programa principal							|
	|---------------------------------------------------|
*/

void set_console(CONSOLE *, ATIVIDADE);

/*############################  FIM DAS DECLARACOES DAS FUNCOES #####################################*/ 

/* ------------------------------- implementações da nova versão ---------------------------------*/

void cria_ambiente(AMBIENTE *);

/* Retornar a telca lida */
OQUEFAZER le_teclas(EVENTO,AMBIENTE *);

void depuracao(AMBIENTE);

void executa_acao(int);

void gerencia_programa(AMBIENTE *);

#endif /* quadradoAnimado */ 