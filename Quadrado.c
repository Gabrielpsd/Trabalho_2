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


/*	|---------------  Cria ponto ---------------------------|
	|	 Para que possa ser criado as zonas de impacto		|
	|	do quadrado interno, ele seguira refernecia por 3 	|
	|	pontos princiapais(centro e diagonais) essa funcao 	|
	|	tem o objetivo de criar esses valores inicias para 	|
	|	o programa trabalhar								|
	|-------------------------------------------------------|
*/

void cria_ponto(JANELA *Janela)
{	
	
	Janela->coluna = COLUNA;
	Janela->linha = LINHA;
	
	
	Janela->ponto1.X = 1;
	Janela->ponto1.Y = 1;
	
	Janela->ponto2.X = Janela->ponto1.X + Janela->coluna ;
	Janela->ponto2.Y = Janela->ponto1.Y + Janela->linha ;
	
}

/*	|---------------  Cria quadrado  -----------------------|
	|	 	Funcao ira definir os valores padrao do quadrado|
	|	interno, essa funcao so sera chamada na 			|
	|	inicializaçao do programa, a partir dai as 			|
	|	alterações na estrutura sera feita por outras 		|
	|	funcoes;												|
	|-------------------------------------------------------|
*/

void cria_quadrado(QUADRADO *quadrado , JANELA Janela)
{
	quadrado->cor = 1;
	
	quadrado->velocidade = VELOCIDADE;
	quadrado->direcao = rand()%3;
	imprime_quadrado(*quadrado,ATIVAR);

}

/*	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|	A funcao utiliza os 3 pontos da estrutura PONTO 	|
	|	como referencia, trocando a cor do fundo 		 	|
	|	caracter por caracter conectando os  pontos das  	|
	|	diagonais											|
	|-------------------------------------------------------|
*/

void gerencia_janela(JANELA *Janela)
{
	int i; 	
	clrscr();
	textbackground(Janela->cor);
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da linha e da coluna
	essas funcoes serao 4 for's para criar as linhas e as colunas
	*/
		
	for(i = 0; i < Janela->coluna; ++i)
	{
		/* linha superior */ 
		gotoxy(Janela->ponto1.X + i,Janela->ponto1.Y);
		putchar(CARACTER_HORIZONTAL);
		
		/*linha inferior*/
		gotoxy(Janela->ponto1.X+i,Janela->ponto2.Y-1);
		putchar(CARACTER_HORIZONTAL);
	
	}
	
	for(i = 0; i < Janela->linha; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(Janela->ponto1.X,Janela->ponto1.Y + i);
		putchar(CARACTER_VERTICAL);
		
		/*coluna horizontal direita */ 
		gotoxy(Janela->ponto2.X,Janela->ponto1.Y+i);
		putchar(CARACTER_VERTICAL);
	}
	
	
}


void gerencia_programa(AMBIENTE *Ambiente)
{
	movimenta_quadrado(Ambiente, JANELA)
}
	
/*	|---------------  imprime info -------------------------|
	|	 Funcao ira realizar a impressao das informacoes 	|
	|	solicitadas no exercicio, essas informações estao	|
	|	contidas dentro da estrutura QUADRADO, a funcao 	|
	|	apenas lea informação que esta la dentro e 			|
	|	imprime o valor, tambem dentro do quadrado			|
	|	ha um coord que serve como referencia para 			|
	|	posicionar os textos na tela do usuario, essas 		|
	|	posicoes sao criadas no inicio do programa e nao 	|
	|	sofrem alteracao com o decorrer do mesmo;		|
	|-------------------------------------------------------|
*/
void imprime_info(QUADRADO quadrado)
{
		
		textbackground(BLACK);
		textcolor(RED);
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+1);
		printf("Direcao atual: ");
		
		switch(quadrado.direcao)
		{
			case (CIMA):
				printf("Cima  ");
				break;
			case (DIREITA):
				printf("Direita  ");
				break;
			case(BAIXO):
				printf("Baixo  ");
				break;
			case(ESQUERDA):
				printf("Esquerda");
				break;
		}
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+2);
		printf("Tecla digitada: %s ", quadrado.texto);
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+3);
		printf("Velocidade atual: %.df segundos",quadrado.velocidade);
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

void imprime_quadrado(QUADRADO quadrado, ATIVIDADE funcao)
{
	int i, j; 
	
	if(funcao)
	{
		textcolor(quadrado.cor);
		/* imprime como se fosse uma matriz*/
		for(i = 0; i < 3 ;++i)
		{
			for(j = 0; j < 3; ++j)
			{
				if(!(j== 1 && i ==1))
				{
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
				putchar(42);
				}
			}
		}
	}
	else
	{
		textbackground(BLACK);
		textcolor(BLACK);
		/* imprime como se fosse uma matriz*/
		for(i = 0; i < 3; ++i)
		{
			for(j = 0; j < 3; ++j)
			{
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
				putchar(32);
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

int Le_Teclas(){
	
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
							
						default:
							break;
					}
				
				}
			}
		
		}
		
	return 0;	
}

void movimenta_quadrado(QUADRADO *quadrado, JANELA janela)
{
	
	imprime_quadrado(*quadrado, 1);
	Sleep(quadrado->velocidade);
	imprime_quadrado(*quadrado, 0);
		
	switch (quadrado->direcao)
	{
		
		/* case (0) */ 
		case (CIMA):
			imprime_info(*quadrado);
	
			if(quadrado->centro.Y - 2 == janela.ponto1.Y)
				quadrado->direcao = BAIXO;
			else
				quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
			
			break;
		/* case (2) */ 
		case (BAIXO):
			imprime_info(*quadrado);
			
			if(quadrado->centro.Y + 3 == janela.ponto2.Y)
				quadrado->direcao = CIMA;
			else
				quadrado->centro.Y =(quadrado->centro.Y)+1;
			
			break;
		/* case (3) */ 
		case (ESQUERDA):
			imprime_info(*quadrado);
				
			if(quadrado->centro.X - 2 == janela.ponto1.X)
				quadrado->direcao = DIREITA;
			else
				quadrado->centro.X = (quadrado->centro.X) - 1 ;
			
			break;
		/* case (1) */ 
		case (DIREITA):
			imprime_info(*quadrado);
				
			if(quadrado->centro.X + 2 == janela.ponto2.X)
				quadrado->direcao = ESQUERDA;
			else
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
			
			break;
	}
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
		setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
		setEstadoBarraTarefas(INVISIVEL);
		setTituloConsole(TITULO);	
		setCursorStatus(DESLIGAR);
		
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

void CriaAmbiente(AMBIENTE *Ambiente)
{
	cria_ponto(&Ambiente->Janela[0]);
	cria_quadrado(&Ambiente->Quadrado[0], Ambiente->Janela[0]);
	gerencia_janela(&Ambiente->Janela[0]);	
}