#ifndef quadradoAnimado
#define quadradoAnimado

#include <Windows.h> /* COORD */ 

#include "console_v1.5.4.h" /* EVENTO */

/* titulo do console */
#define TITULO "Multiplos Quadrados Animados"  

/* quantidade de quadrados maximo na tela*/
#define QUANTIDADE 10
/* #-#-#-#-#-#-#-#-#-# Declaracoes de tipos de dados e constantes #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#*/
 

 /*	|------------ BOLADAVEZ-----------------------------|
	|		a quantidade de quadrados para esse programa| 
	|	é 10 logo esse enum não é fléxivel para mais 	|
	|	quadrados, mas a funcao desse enum é garantir a |
	|	integridade dos valores para que não extrapole e| 
	|	pegue lixo de memoria, tendo apenas valores 	|
	|	previsiveis, e é utilizada para controlar 		|
	|	qual o quadrado que esta sendo controlado para 	|
	|	atualmente 										|
	|---------------------------------------------------|
*/

typedef enum controle{
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

/*	|------------ ATIVIDADE-----------------------------|
	|		Algumas funcoes tem como parametro ativar 	|
	|	ou desativar, que cotrolam seu comportamento	|
	|	para garantir a integridade das chamadas e a 	|
	|	correta passagem de parametro, foi criada um 	|
	|	enum que representa esses valores				|
	|---------------------------------------------------|
*/

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


/*	|---------------- OQUEFAZER  ---------------------------|
	|		Esse eh um tipo de dado criado exclusivamente	|
	|	para a funcao le_teclas, pois assim que sair 		|
	|	da funcao ele parametrizará o comportamento de 		|
	|	outras chamadas										|
	|-------------------------------------------------------|
*/

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
	int horizontal,vertical;
	
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

/*	|-------------------  quadrado  --------------------|
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
	BOOLEANO QuadradoAtual;

}QUADRADO;

/*	|------------------- Ambiente ----------------------|
	|	Estrutura que armazena as janelas e os quadrados| 
	|	alem de da quantididade e os limites das bordas |
	|	do console;										|
	|---------------------------------------------------|
*/

typedef struct _ambiente
{
	QUADRADO Quadrado[QUANTIDADE];
	JANELA Janela[QUANTIDADE];
	
	int Quantidade;
	COORD PontoInicial, PontoFinal; 
	BOLADAVEZ JanelaAtual;
}AMBIENTE;

/* #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# FIM DAS DECLARAÇÕES DAS VARIAVEIS E CONSTANTES #-#-#-#-#-#-#-#-#-#-#*/ 

/* ################################## DECLARAÇÕES DE FUNCOES  ###########################################*/ 

/*	|---------------  Valida  Janela -------------------|
	|	 	Funcao que recebe uma janela e verifica 	|
	|	se é possível colocar a janela no ambiente,		|
	|	filtrando os dados de tamanho e conflitos		|
	|	RECEBE: 										|
	|	->JANELA: variavel que sera comparada e 		|
	|	validada dentro da funcao						|
	|	->AMBIENTE: Variavel que armazena todas as 		|
	|	janelas atuais e utiliza como referencia		|
	|	RETORNA:enum BOOLEANO verdadeiro ou falso 		|
	|---------------------------------------------------|
*/

BOOLEANO valida_janela(AMBIENTE, JANELA);

/*	|---------------  Le teclas  -----------------------|
	|	 	Funcao que ira realizar a filtragem do 		|
	|	evento ocorrido(teclado ou mouse) no console 	|
	|	e ira realizar o devido tratamento do mesmo, 	|
	|	realizando as mudanças necessárias  			|
	|	RECEBE: 										|
	|	->EVENTO: variável que armazena o Evento 		|
	|	ocorrido no console								|
	|	->AMBIENTE: Variavel que armazena todas as 		|
	|	janelas atuais e utiliza como referencia		|
	|	RETORNA:enum OQUEFAZER para ser utilzado na 	|
	|	funcao Gerencia_programa; 						|
	|---------------------------------------------------|
*/

OQUEFAZER le_teclas(EVENTO,AMBIENTE *);

/*	|--------------- Adiciona quadrado  ----------------|
	|	 	Funcao que ira realizar o calculo e as 		|
	|	devidas validações para adicionar um quadrado	|
	|	na janela;							 			|
	|	RECEBE: 										|
	|	->AMBIENTE: ponteiro que armazena o ambiente 	|
	|	RETORNA: sem retorno 							|
	|---------------------------------------------------|
*/

void adiciona_quadrado(AMBIENTE *);

/*	|---------------  Ajusta Quadrado  -----------------|
	|	 	Quando o usuario faz alguma alteração na 	|
	|	janela pode ser necessário ajustar o quadrado 	|
	|	que se movimenta internamente, como por exemplo	|
	|	caso ele esteja se movimentando verticalmente 	|
	|	encostado na borda esquerda e a respectiva		|
	|	for diminuida o quadrado precisara ser deslocado| 
	|	para direita e essa é a tarefa dessa função   	|
	|	RECEBE: 										|
	|	->EVENTO: Ponteiro do quadrado interno para 	|
	|	que seja ajustado								|
	|	->JANELA: Variável que armaze a janela que 		|
	|	contem o quadrado do primeiro parametro			|
	|	para verificar conflitos						|
	|	RETORNA:sem retorno						 		|
	|---------------------------------------------------|
*/

void ajusta_quadrado(QUADRADO *, JANELA);

/*	|---------------  apaga quadrado -------------------|
	|	 	Funcao que recebe um quadrado e com suas 	|
	|	coordanas ira apaga-lo							|
	|	RECEBE: 										|
	|	-> QUADRADO: varivael do tipo quadrado 			|
	|	ambiente a ser modificado 						|
	|	RETORNA: sem retorno 							|
	|---------------------------------------------------|
*/

void apaga_quadrado(QUADRADO);

/*	|---------------  gerencia Janela ------------------|
	|		Funcao que realiza a impressão da janela 	|
	|	que o quadrado se movimenta						|
	|	RECEBE:											|
	|	-> JANELA: Variavel que armazena os dados da 	|
	|	janela a ser impressa;							|
	|	->INT: valor que armazena a velocidade do		|
	|	quadrado interno para ser impressa na janela	|	
	|	RETORNA: sem retorno 							|
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
	|	RETORNA:sem retorno								|
	|---------------------------------------------------|
*/

void imprime_quadrado(QUADRADO);


/*	|--------------- Gerencia programa   ---------------|
	|	 	Funcao que realiza as chamadas do 			|
	|	programa princial;								|
	|	RECEBE: 										|
	|	->AMBIENTE: POnteiro que armazena um AMBIENTE	|
	|	a ser trabalhado								|
	|	RETORNA: sem retorno									|
	|---------------------------------------------------|
*/

void gerencia_programa(AMBIENTE *);

/*	|---------------  movimenta quadrado ---------------|
	|	 	Funcao realiza a movimentacao do quadrado,	|
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

/*	|--------------- set Console  ----------------------|
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

#endif /* quadradoAnimado */ 