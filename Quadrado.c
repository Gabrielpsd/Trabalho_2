/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 
#include <Windows.h> /* Sleep() */

#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(),MaxDimensaoJanela(),getPosicaoJanela(), setPosicaoJanela() 
setDimensaoJanela() ,setTituloConsole() ,setCursorStatus(),Sleep() */ 
#include "Quadrado.h" /* cria_janela() */

/* essa referencia é utilizada para imprimir as infromacoes na tela
ela somasse a posicao do ponto apenas para poder imprimir em determinado local da tela(no canto inferior esquerdo nesse caso)
*/

#define LINHA 18
#define COLUNA 31
#define VELOCIDADE 100 /*dada em milisegundos */ 
#define CARACTER_HORIZONTAL 32
#define CARACTER_VERTICAL 32
#define CARACTER_IMPRESSO 42 /*ASTERISCO NA TABELA ASCII*/
#define BORDA_JANELA 32 /* ESPACO NA TABELA ASCII*/

/*dimensoa 168 * 42 */
/*	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|	A funcao utiliza os 3 pontos da estrutura PONTO 	|
	|	como referencia, trocando a cor do fundo 		 	|
	|	caracter por caracter conectando os  pontos das  	|
	|	diagonais											|
	|-------------------------------------------------------|
*/

void gerencia_janela(JANELA Janela, int Velocidade)
{
	
	int i; 	

	if(Janela.JanelaAtual == VERDADEIRO)
		textbackground(Janela.CorJanela);
	else
		textbackground(LIGHTGRAY);
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
	
	textcolor(BLACK);
	gotoxy(Janela.PontoSE.X,Janela.PontoID.Y-1);
	printf("Velocidade Quadrado: %d",Velocidade);


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
	
	textcolor(quadrado.CorQuadrado);
	/* imprime como se fosse uma matriz*/
	for(i = 0; i < 3 ;++i)
	{
		for(j = 0; j < 3; ++j)
		{
			if(!(j== 1 && i ==1))
			{
			gotoxy((quadrado.Centro.X - 1) +j, (quadrado.Centro.Y - 1) + i);
			putchar(CARACTER_IMPRESSO);
			}
		}
	}

}

/*	|---------------  movimenta quadrado -------------------|
	|	 A funcao movimenta quadrado, realiza o deslocamento|
	|	do ponto central do quadrado para uma posicao em 	|
	|	Direcao a que esta contida no campo direcao 		|
	|	armazenado dentro da propria estrura QAUDRADO 	 	|
	|-------------------------------------------------------|
*/

OQUEFAZER le_teclas(EVENTO evento, AMBIENTE *Ambiente){
	
	int controle;
	COORD Auxiliar;

		if(evento.tipo_evento & KEY_EVENT)
		{
			if(evento.teclado.status_tecla == LIBERADA)
			{
				switch(evento.teclado.codigo_tecla)
				{
					case ESPACO:
						
						
						if(Ambiente->Quantidade < 10){
							Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
							/*Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = DARKGRAY;
							Ambiente->Quadrado[Ambiente->JanelaAtual].CorQuadrado = DARKGRAY;*/
							Ambiente->JanelaAtual++;
							Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
							Ambiente->Quantidade++;
						}

						return REIPRIMIRJANELA;

						break;

					case F2:
						
						if(Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade < 1000)
							Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade++;

							
						break;
					
					/*-- diminui a velocidade interna do quadrado -- */ 
					case F1: 

						if(Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade >1)
							Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade--;

						break;

					case SETA_PARA_DIREITA:
						
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = DIREITA;
						break;

					case SETA_PARA_ESQUERDA:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = ESQUERDA;
						break;

					case SETA_PARA_BAIXO:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = BAIXO;
						break;
						
					case SETA_PARA_CIMA:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = CIMA;
						break;
					
					/*-- aumenta area do quadrado externo para esquerda -- */
					case F3:
						return F3;
					/*-- diminui a borda do quadrado da esquerda --*/ 							
					case F4:
						return F4;
					
					/*-- aumenta a area do quadrado para direita --*/
					case F5:
						return F5;
						
					/*-- diminui a area da do quadrado para direita --*/
					case F6: 
						return F6;
						
					/*-- aumenta a areda do quadrado para cima --*/
					case F7:
						return F6;
							
					/*-- diminui a area superior --*/ 
					case F8:
						return F8;
						
					/*-- aumenta a area para baixo --*/
					case F9:
						return F9;
						
					/*--diminui a area para baixo --*/
					case F10:
						return F10;
						
					/*--alterna a cor do quadrado --*/
					case CTRL:
						return 0;
						
					/*-- alterna a cor do quadrado --*/
					case TAB:
						return TAB;

					/*-- finaliza programa --*/
					case ESC:
							return ENCERRARPROGRAMA;
				}
				
			}


			
		} 
		else if(evento.tipo_evento & MOUSE_EVENT)
		{
			if(evento.mouse.botao_clicou & BOTAO_ESQUERDO_PRESSIONADO)
			{
				Auxiliar  = evento.mouse.posicao;
				
				for(controle = 0; controle < Ambiente->Quantidade; ++controle)
				{
					if((Ambiente->Janela[controle].PontoSE.X > Auxiliar.X) && (Ambiente->Janela[controle].PontoSE.Y > Auxiliar.Y))
					{
						if((Ambiente->Janela[controle].PontoID.X < Auxiliar.X) && (Ambiente->Janela[controle].PontoID.Y < Auxiliar.Y))
						{
						Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
						Ambiente->JanelaAtual = controle;
						Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
						}
					}

				}

				return REIPRIMIRJANELA;
			}

			return CONTINUAR;
		}

		return 1; 
}

void movimenta_quadrado(QUADRADO *Quadrado, JANELA janela)
{	
	
	apaga_quadrado(*Quadrado);
	
	switch (Quadrado->Direcao)
	{
		

		case (CIMA):
		
	
			if(Quadrado->Centro.Y - 2 == janela.PontoSE.Y)
				Quadrado->Direcao = BAIXO;
			else
				Quadrado->Centro.Y = (Quadrado->Centro.Y) - 1 ;
			
			break;

		case (BAIXO):
			
			
			if(Quadrado->Centro.Y + 3 == janela.PontoID.Y)
				Quadrado->Direcao = CIMA;
			else
				Quadrado->Centro.Y =(Quadrado->Centro.Y)+1;
			
			break;

		case (ESQUERDA):
			
				
			if(Quadrado->Centro.X - 2 == janela.PontoSE.X)
				Quadrado->Direcao = DIREITA;
			else
				Quadrado->Centro.X = (Quadrado->Centro.X) - 1 ;
			
			break;
		case (DIREITA):
			
				
			if(Quadrado->Centro.X + 2 == janela.PontoID.X)
				Quadrado->Direcao = ESQUERDA;
			else
				Quadrado->Centro.X = (Quadrado->Centro.X) + 1 ;
			
			break;
	}

	imprime_quadrado(*Quadrado);
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

	int i;

	Ambiente->Quantidade = 1;
	Ambiente->JanelaAtual = 0;


	Ambiente->Janela[0].PontoSE.X = 2;
	Ambiente->Janela[0].PontoSE.Y = 2; 

	Ambiente->Janela[0].Linha = LINHA;
	Ambiente->Janela[0].Coluna = COLUNA;

	Ambiente->Janela[0].PontoID.X = Ambiente->Janela[0].PontoSE.X + Ambiente->Janela[0].Coluna;
	Ambiente->Janela[0].PontoID.Y = Ambiente->Janela[0].PontoSE.Y + Ambiente->Janela[0].Linha; 

	Ambiente->Janela[0].CorJanela = rand()%15 + 1; 
	Ambiente->Janela[0].JanelaAtual = FALSO;

	/* -------------------- QUADRADOS SUPERIORES ------------------*/
	for(i = 1; i < 5;++i)
	{
		Ambiente->Janela[i].PontoSE.X = Ambiente->Janela[i-1].PontoID.X + 2;
		Ambiente->Janela[i].PontoSE.Y = Ambiente->Janela[i-1].PontoSE.Y; 

		Ambiente->Janela[i].Linha = LINHA;
		Ambiente->Janela[i].Coluna = COLUNA;

		Ambiente->Janela[i].PontoID.X = Ambiente->Janela[i].PontoSE.X + Ambiente->Janela[i].Coluna;
		Ambiente->Janela[i].PontoID.Y = Ambiente->Janela[i].PontoSE.Y + Ambiente->Janela[i].Linha; 
		Ambiente->Janela[i].CorJanela = rand()%15 + 1; 

		Ambiente->Janela[i].JanelaAtual = FALSO;
	}

	/*---------------------- QUADRADOS INFERIORES ---------------------*/

	Ambiente->Janela[5].PontoSE.X = Ambiente->Janela[0].PontoSE.X;
	Ambiente->Janela[5].PontoSE.Y = Ambiente->Janela[0].PontoID.Y + 2 ; 

	Ambiente->Janela[5].Linha = LINHA;
	Ambiente->Janela[5].Coluna = COLUNA;

	Ambiente->Janela[5].PontoID.X = Ambiente->Janela[5].PontoSE.X + Ambiente->Janela[5].Coluna;
	Ambiente->Janela[5].PontoID.Y = Ambiente->Janela[5].PontoSE.Y + Ambiente->Janela[5].Linha; 

	Ambiente->Janela[5].JanelaAtual = FALSO;

	Ambiente->Janela[5].CorJanela = rand()%15 + 1; 
	
	for(i = 6; i < 10;++i)
	{
		Ambiente->Janela[i].PontoSE.X = Ambiente->Janela[i-1].PontoID.X + 2;
		Ambiente->Janela[i].PontoSE.Y = Ambiente->Janela[i-1].PontoSE.Y; 

		Ambiente->Janela[i].Linha = LINHA;
		Ambiente->Janela[i].Coluna = COLUNA;

		Ambiente->Janela[i].PontoID.X = Ambiente->Janela[i].PontoSE.X + Ambiente->Janela[i].Coluna;
		Ambiente->Janela[i].PontoID.Y = Ambiente->Janela[i].PontoSE.Y + Ambiente->Janela[i].Linha; 
		Ambiente->Janela[i].CorJanela = rand()%15 + 1;
		Ambiente->Janela[i].JanelaAtual = FALSO;
	}

	for(i = 0; i < 10; ++i)
	{
		Ambiente->Quadrado[i].Centro.X = Ambiente->Janela[i].PontoID.X - Ambiente->Janela[i].Coluna / 2;
		Ambiente->Quadrado[i].Centro.Y = Ambiente->Janela[i].PontoID.Y - Ambiente->Janela[i].Linha / 2;
		Ambiente->Quadrado[i].Velocidade = rand()%1000;
		Ambiente->Quadrado[i].Direcao = rand() %4;
		Ambiente->Quadrado[i].CorQuadrado = rand()%15 + 1;
	}

	clrscr();

}

void apaga_quadrado(QUADRADO Quadrado){

	int i,j;
	

	textbackground(BLACK);
	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			gotoxy(Quadrado.Centro.X - 1 + j, Quadrado.Centro.Y - 1 + i);
			putchar(BORDA_JANELA);
		}
	}

}

void gerencia_programa(AMBIENTE *Ambiente)
{
	int i,controle;	
	EVENTO evento;
	OQUEFAZER auxiliar;

	i = controle = 0;

	auxiliar = CONTINUAR;

	gerencia_janela(Ambiente->Janela[0], Ambiente->Quadrado[0].Velocidade);


	do
	{	
		/* operador ternario, substitui o if */
		i = (i == 1000) ?  0 : i + 1;

		if(hit(ALL))
		{
			evento = Evento();
			auxiliar = le_teclas(evento, Ambiente);
		}

		if(auxiliar == REIPRIMIRJANELA)
		{
			for(controle = 0; controle < Ambiente->Quantidade; ++controle)
				gerencia_janela(Ambiente->Janela[controle], Ambiente->Quadrado[controle].Velocidade);

			auxiliar = CONTINUAR;
		}

		for(controle = 0; controle < Ambiente->Quantidade;++controle)
		{	
			if(i%Ambiente->Quadrado[controle].Velocidade == 0)
				movimenta_quadrado(&Ambiente->Quadrado[controle],Ambiente->Janela[controle]);

		}

		++i;
	
	}while(auxiliar != ENCERRARPROGRAMA);

}


void depuracao(AMBIENTE Ambiente)
{	
	int i;
	for(i = 9; i < 10; ++i)
	{
		
		printf(" --------------- %do janela -------------------\n ", i+1);
		printf("Diagonal superior esquerda: X = %d e Y = %d \n ",Ambiente.Janela[i].PontoSE.X,Ambiente.Janela[i].PontoSE.Y);
		printf("Diagonal inferior direita: X = %d e Y = %d \n ",Ambiente.Janela[i].PontoID.X,Ambiente.Janela[i].PontoID.Y);
		printf("Linha = %d e coluna = %d \n ",Ambiente.Janela[i].Linha,Ambiente.Janela[i].Coluna);
		printf("Cor = %d \n ",Ambiente.Janela[i].CorJanela);

		printf("     -> QUADRADO: \n\n");
		printf("\tCentro: X = %d e Y = %d \n ",Ambiente.Quadrado[i].Centro.X,Ambiente.Quadrado[i].Centro.Y);
		printf("\tVelocidade: X = %d Direcao = %d \n ",Ambiente.Quadrado[i].Velocidade,Ambiente.Quadrado[i].Direcao);
		printf(" --------------- ---------  -------------------\n ");

		getchar();
	}

	
}
