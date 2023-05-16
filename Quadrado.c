/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 



#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(),MaxDimensaoJanela(),getPosicaoJanela(), setPosicaoJanela() 
setDimensaoJanela() ,setTituloConsole() ,setCursorStatus(),Sleep() */ 
#include "Quadrado.h" /* cria_janela() */

/* essa referencia é utilizada para imprimir as infromacoes na tela
ela somasse a posicao do ponto apenas para poder imprimir em determinado local da tela(no canto inferior esquerdo nesse caso)
*/

#define LINHA 20
#define COLUNA 50
#define VELOCIDADE 100 /*dada em milisegundos */ 
#define CARACTER_HORIZONTAL 32
#define CARACTER_VERTICAL 32
#define CARACTER_IMPRESSO 42 /*ASTERISCO NA TABELA ASCII*/
#define BORDA_JANELA 32 /* ESPACO NA TABELA ASCII*/


/*	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|	A funcao utiliza os 3 pontos da estrutura PONTO 	|
	|	como referencia, trocando a cor do fundo 		 	|
	|	caracter por caracter conectando os  pontos das  	|
	|	diagonais											|
	|-------------------------------------------------------|
*/

void gerencia_janela(JANELA Janela)
{
	
	int i; 	
	clrscr();
	textbackground(Janela.CorJanela);
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da Linha e da Coluna
	essas funcoes serao 4 for's para criar as Linhas e as Colunas
	*/
	for(i = 0; i < Janela.Coluna; i++)
	{
		/* Linha superior */ 
		gotoxy(Janela.PontoSE.X + i,Janela.PontoSE.Y);
		putchar(CARACTER_HORIZONTAL);
		
		/*Linha inferior*/
		gotoxy(Janela.PontoSE.X  + i,Janela.PontoID.Y-1);
		putchar(CARACTER_HORIZONTAL);
	
	}

	for(i = 0; i < Janela.Linha; i++)
	{
		/* Coluna horizontal da esquerda */ 
		gotoxy(Janela.PontoSE.X,Janela.PontoSE.Y + i);
		putchar(CARACTER_VERTICAL);
		
		/*Coluna horizontal direita */ 
		gotoxy(Janela.PontoID.X,Janela.PontoSE.Y+i);
		putchar(CARACTER_VERTICAL);
	}
	
	textbackground(0);
}

/*	|----------------  Imprime Quadrado --------------------|
	|	 	A funcao recebe o quadrado como referencia, 	|
	|	a partir dai ele pega o ponto centro e atraves desse| 
	|	ponto ele realiza as operacoes, a cor dos caracteres|
	|	e a posicao de referencia estao contidas dentro da 	|
	|	estrutura;											|
	|		A funcao recebe o parametro enum que serve para |
	|	imprimir ou apagar o quadrado da tela, caso o 		|
	|	parametro seja para ativar ele imprime os dados como| 
	|	sendo uma matriz; e caso o parametro seja DESTIVAR	|
	|	ela realiza a exclusao sobreponto as posicoes do 	|
	|	quadrado porem com um novo caracter 'espaco' com o 	|
	|	fundo de cor preto;									|
	|-------------------------------------------------------|
*/

void imprime_quadrado(QUADRADO quadrado)
{
	int i, j; 
	
	if(funcao)
	{
		textcolor(quadrado.CorQuadrado);
		/* imprime como se fosse uma matriz*/
		for(i = 0; i < 3 ;++i)
		{
			for(j = 0; j < 3; ++j)
			{
				if(!(j== 1 && i ==1))
				{
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
				putchar(CARACTER_IMPRESSO);
				}
			}
		}
	}

}

/*	|---------------  movimenta quadrado -------------------|
	|	 A funcao movimenta quadrado, realiza o deslocamento|
	|	do ponto central do quadrado para uma posicao em 	|
	|	direcao a que esta contida no campo direcao 		|
	|	armazenado dentro da propria estrura QAUDRADO 	 	|
	|-------------------------------------------------------|
*/

int le_teclas(){
	
	EVENTO evento; 
	
	if(hit(KEYBOARD_HIT))
	{
			
		evento = Evento();
			
		if(evento.tipo_evento & KEY_EVENT)
		{
			if(evento.teclado.status_tecla == LIBERADA)
			{
				switch(evento.teclado.codigo_tecla)
				{
						
						case F2:
								return F2;
							break;
						
					/*-- diminui a velocidade interna do quadrado -- */ 
						case F1: 
							return F1;

						case SETA_PARA_DIREITA:
						
							return F1;
						case SETA_PARA_ESQUERDA:
							
							return F1;
						case SETA_PARA_BAIXO:
							return F1;
							
						case SETA_PARA_CIMA:
							return F1;
						
						/*-- aumenta area do quadrado externo para esquerda -- */
						case F3:
							return F1;
						/*-- diminui a borda do quadrado da esquerda --*/ 							
						case F4:
							return F1;
						
						/*-- aumenta a area do quadrado para direita --*/
						case F5:
							return F1;
							
						/*-- diminui a area da do quadrado para direita --*/
						case F6: 
							return F1;
							
						/*-- aumenta a areda do quadrado para cima --*/
						case F7:
							return F1;
								
						/*-- diminui a area superior --*/ 
						case F8:
							return F1;
							
						/*-- aumenta a area para baixo --*/
						case F9:
							return F1;
							
						/*--diminui a area para baixo --*/
						case F10:
							return F1;
							
						/*--alterna a cor do quadrado --*/
						case ESPACO:
							return F1;
							
						/*-- alterna a cor do quadrado --*/
						case TAB:
							return F1;
							
						/*-- finaliza programa --*/
						case ESC:
							return F1;
					}
				
				}
			}
		
		}	

		return 0; 
}

void movimenta_quadrado(QUADRADO *Quadrado)
{
	Quadrado->CorQuadrado = GREEN;

	int i = 0;

	for(i = 0; i < 10; ++i)
	{
		imprime_quadrado(*Quadrado);
		sleep(1000);
		apaga_quadrado(*Quadrado);
		Quadrado->Centro = Quadrado->Centro+1;
	}
	/*
	switch (quadrado->direcao)
	{
		

		case (CIMA):
		
	
			if(quadrado->centro.Y - 2 == janela.PontoSE.Y)
				quadrado->direcao = BAIXO;
			else
				quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
			
			break;

		case (BAIXO):
			
			
			if(quadrado->centro.Y + 3 == janela.PontoID.Y)
				quadrado->direcao = CIMA;
			else
				quadrado->centro.Y =(quadrado->centro.Y)+1;
			
			break;

		case (ESQUERDA):
			
				
			if(quadrado->centro.X - 2 == janela.PontoSE.X)
				quadrado->direcao = DIREITA;
			else
				quadrado->centro.X = (quadrado->centro.X) - 1 ;
			
			break;
		case (DIREITA):
			
				
			if(quadrado->centro.X + 2 == janela.PontoID.X)
				quadrado->direcao = ESQUERDA;
			else
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
			
			break;
	}
	*/
}

/*		|---------------  Set ambiente -------------------------|
		|	 Configura o console inicial ao mesmo tempo			|	
		|	ele armazena os dados para que a janela retorne		|
		|	a como estava no inicio do programa 	 		 	|
		|	 Essa funcao tem tanto a atividade de configurar   	|
		|	o console inicial como de restaurar as configurações|
		|	que estavam anteriormente							|
		|-------------------------------------------------------|
*/

void set_console(CONSOLE *console, ATIVIDADE status)
{
	if(status){
		
		/* armazena todos os valores atuais do console 
		assim como sua posicao maxima, para que o console de usuario 
		seja configurado no jogo e depois consiga retornar ao finalizar o programa
		*/
		
		console->dimensao_inicial = getPosicaoJanela();	
		console->dimensao_maxima = MaxDimensaoJanela();
		console->posicao_inicial = getPosicaoJanela();

		/* em alguns casos os valores iniciais da janela podem vir negativos 
			caso isso ocorra o programa ira determinar um valor valido para os parametros 
			para que quando forem utilizados eles consigam gerar um retorno
		*/
		if(console->dimensao_inicial.X <= 0 || console->dimensao_inicial.Y <= 0)
			{
				console->dimensao_inicial = console->dimensao_maxima; 
			}
		
		if(console->posicao_inicial.X < 0 || console->posicao_inicial.Y < 0 )
		{
				console->posicao_inicial.X = 0; 
				console->posicao_inicial.Y = 0;
		}
		
		/* configura a tela do usuario */ 
		setPosicaoJanela(0,0);
		
		setEstadoBarraTarefas(INVISIVEL);
		setTituloConsole(TITULO);	
		setCursorStatus(DESLIGAR);
		setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
		
	}else{
		
		gotoxy(console->dimensao_maxima.X/4,console->dimensao_maxima.Y/4);
		textcolor(WHITE);
		printf("FIM DA EXECUCAO DO PROGRAMA");
		gotoxy(console->dimensao_maxima.X,console->dimensao_maxima.Y);
		setPosicaoJanela(console->posicao_inicial.X,console->posicao_inicial.Y);
		setDimensaoJanela(console->dimensao_inicial.X,console->dimensao_inicial.Y);
		setEstadoBarraTarefas(VISIVEL);
		setCursorStatus(LIGAR);
	}
}

void cria_ambiente(AMBIENTE *Ambiente)
{
	printf("Entrou aqui (1)");
	

	Ambiente->Janela[0].PontoSE.X = 1;
	Ambiente->Janela[0].PontoSE.Y = 1; 

	Ambiente->Janela[0].Linha = LINHA;
	Ambiente->Janela[0].Coluna = COLUNA;

	Ambiente->Janela[0].PontoID.X = Ambiente->Janela[0].PontoSE.X + Ambiente->Janela[0].Coluna;
	Ambiente->Janela[0].PontoID.Y = Ambiente->Janela[0].PontoSE.Y + Ambiente->Janela[0].Linha; 

	Ambiente->Janela[0].CorJanela = 2; 

	gerencia_janela(Ambiente->Janela[0]);

	movimenta_quadrado(&Ambiente->Quadrado);

	getchar();
}

void apaga_quadrado(QUADRADO Quadrado){

	int i,j;

	backGroundColor(BLACK);
	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			gotoxy(Quadrado.Centro.X - 1 - j; Quadrado.Centro.Y - 1 - i);
			puchar(BORDA_JANELA);
		}
	}

}

