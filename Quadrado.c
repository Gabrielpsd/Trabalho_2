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

#define LINHA 30
#define COLUNA 40
#define VELOCIDADE 100 /*dada em milisegundos */ 
#define CARACTER_HORIZONTAL 32
#define CARACTER_VERTICAL 32
#define CARACTER_IMPRESSO 42 /*ASTERISCO NA TABELA ASCII*/
#define BORDA_JANELA 32 /* ESPACO NA TABELA ASCII*/

/*dimensoa 168 * 42 */

/*		|---------------  Gerencia programa --------------------|
		|	 Realiza o cotrole de das movimentações do quadrado	|
		|	le realiza o reconhecimento de algum evento e 		|
		|	repassa a informacao e dpois com o retorno da funcao|
		|	le_teclas ela segue para a o novo parametro 		|
		|	de acordo com o retorno do que receber;				|
		|		Unica funcao que esta fora da ordem alfabetica, |
		|	por ser a que realiza o controle de todas as		|
		|	chamadas; 											|			
		|-------------------------------------------------------|
*/

void gerencia_programa(AMBIENTE *Ambiente)
{
	int i,controle;	
	EVENTO evento;
	OQUEFAZER auxiliar;

	i = controle = 0;

	auxiliar = CONTINUAR;


	do
	{	
		/* operador ternario, substitui o if;
		toda vez que i atingir 1000 ele retornara para 1, i representa os milissegundos */
		i = (i == 1000) ?  0 : i + 1;


		/* verifica se houve algum evento, tanto de telcado quanto de mouse */
		if(hit(ALL))
		{

			/* armazena o evento que ocorreu*/
			evento = Evento();

			/* repassa o evento para ser tratado*/
			auxiliar = le_teclas(evento, Ambiente);
		}

		/* caso o parametro de retorno seja o de REIMPRIMIR a janela ele entrara nesse if e ira realizar a impressao de todas as janeas novamente*/
		if(auxiliar == REIPRIMIRJANELA)
		{	
			clrscr();
			for(controle = 0; controle < Ambiente->Quantidade; ++controle)
				gerencia_janela(Ambiente->Janela[controle], Ambiente->Quadrado[controle].Velocidade);

			auxiliar = CONTINUAR;
		}


		/* realizada a movimentacao dos quadrado*/
		for(controle = 0; controle < Ambiente->Quantidade;++controle)
		{	

			/* o controle é feito em milisegundos e toda a vez que a contagem atingir a velocidade do quadrado ele 
			chamara a funcao que movimenta o quadrado */
			if(i%Ambiente->Quadrado[controle].Velocidade == 0)
				movimenta_quadrado(&Ambiente->Quadrado[controle],Ambiente->Janela[controle]);

		}

		/* realiza o incremento do i que nesse caso representa que mais um milissegundo no tempo de execucao */
		++i;
	
	}while(auxiliar != ENCERRARPROGRAMA);

}

BOOLEANO valida_janela(AMBIENTE Ambiente, JANELA Janela){

	int contador, i , j ;

	BOOLEANO Retorno;

	/* A principio vamos assumir que a janela atual nao conlfita com nenhuma, e vamos procurar se ha algum caso falso para essa afirmacao*/
	Retorno = VERDADEIRO;
	/*funcao que ira validar se ha algum conflito entre as janelas passadas*/

	/* 1o comparando as linhas com as colunas */

	/* Verificando se o ponto ID da janela se encotnra dentro do "Ambiente console", verificando se eles não são maiores que o ultimo ponto disponivel */
	if(Janela.PontoID.X > Ambiente.PontoFinal.X || Janela.PontoID.Y > Ambiente.PontoFinal.Y)
		return FALSO;

	/* Verificando se o ponto se da janela se encotnra dentro do "Ambiente console", verificando se eles não são maiores que o ultimo ponto disponivel*/
	if(Janela.PontoSE.X > Ambiente.PontoFinal.X || Janela.PontoSE.Y > Ambiente.PontoFinal.Y)
		return FALSO;

	/* verificando se as coordeadas naão são menores que o ponto inicial */
	if(Janela.PontoSE.X < 1 || Janela.PontoSE.Y < 1 )
		return FALSO;
	
	/* verificando se as coordeadas naão são menores que o ponto inicial */
	if(Janela.PontoID.X < 1 || Janela.PontoID.Y < 1 )
		return FALSO;

	contador = 0; 
	
	do/*(contador = 0; contador < Ambiente.Quantidade; ++contador)*/
	{
		i = 0;

		while (i <= Janela.Linha)
		{
			j = 0;
			while(j <= Janela.Coluna)
			{
				/* ------- Precisamos verificar se alguns dos quatro pontos da janela não estão conflitando com alguem */
				if(Ambiente.Janela[contador].JanelaAtual == FALSO)
				{

					/* condicional que verifica se há algum ponto da janela sendo comparada que esta contida dentro de outra janela */
					if(Janela.PontoSE.X + j >= Ambiente.Janela[contador].PontoSE.X && Janela.PontoSE.Y + i >= Ambiente.Janela[contador].PontoSE.Y)
						if(Janela.PontoSE.X + j <= Ambiente.Janela[contador].PontoID.X && Janela.PontoSE.Y + i <= Ambiente.Janela[contador].PontoID.Y)
							Retorno = FALSO;

			
				}

				++j;
			}

			++i;
		}

	contador++;

	}while(contador < Ambiente.Quantidade);	


	if(Janela.Linha < 5 || Janela.Coluna < 5)
		return FALSO;

	return Retorno;
}


/*	|---------------  Apaga quadrado    ----------------|
	|	 	Funcao ira receber um quadrado e atraves 	|
	|	da sua coordenada do centro e ira realizar a 	|
	|	exclusao do mesmo. A exclusao ocorre realizando	|
	|	a sobreposicao das posicoes que o quadrado esta	|
	|	por um caractere espaco com a cor de fundo 		|
	|	preta.											|
	|---------------------------------------------------|
*/

void apaga_quadrado(QUADRADO Quadrado)
{

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

/*	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|		A funcao recebe uma JANELA  ,que ja vai estar 	|
	|	com	os pontos das diagonais determinados, e ira 	|
	|	realizar a ligacao entre esses pontos com o 		|
	|	caracter de espaco com a cor de fundo armazenado 	|
	|	na janela para a janela em utilizacao e a coloracao |
	|	cinza para os demais;								|
	|		Tambem recebe a velocidade do quadrado interno 	|
	|	que deve ser passado na chamada						|
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
	

	/*imprime a velocidade da janela */
	textcolor(BLACK);
	gotoxy(Janela.PontoSE.X,Janela.PontoID.Y-1);
	printf("V:%d",Velocidade);

	if(Janela.JanelaAtual == VERDADEIRO)
	{
		gotoxy(Janela.PontoSE.X,Janela.PontoSE.Y);
		textcolor(BLACK);
		printf("Atual");
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
	
	if(quadrado.QuadradoAtual)
		textcolor(quadrado.CorQuadrado);
	else
		textcolor(LIGHTGRAY);

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
	|	 	A funcao movimenta o quadrado, 					|
	|		1o - ela primeiramente apaga o quadrado atual; 	|
	|		2o - depois seta a posicao do centro para a nova| 
	|	direcao que o quadrado esta se movimentando; 		|
	|		3o reimprime o quadrado na nova posicao;		|
	|	OBS: o tempo de movimentacao deve ser controlado	|
	|	nas chamadas da funcao;								|
	|-------------------------------------------------------|
*/

void movimenta_quadrado(QUADRADO *Quadrado, JANELA janela)
{	
	
	/* apaga o quadrado atual*/
	apaga_quadrado(*Quadrado);
	

	/* reposiciona o quadrado na nova direcao, realizando as validacoes de conflito com a borda da janela*/
	switch (Quadrado->Direcao)
	{
		

		/* "andar" para cima nada mais é que diminuir minha coordenada do Y do centro do quadrado */
		case (CIMA):
		
	
			if(Quadrado->Centro.Y - 2 == janela.PontoSE.Y)
				Quadrado->Direcao = BAIXO;
			else
				Quadrado->Centro.Y = (Quadrado->Centro.Y) - 1 ;
			
			break;

		/* "andar" para baix nada mais é que aumentar minha coordenada do Y do centro do quadrado */
		case (BAIXO):
			
			
			if(Quadrado->Centro.Y + 3 == janela.PontoID.Y)
				Quadrado->Direcao = CIMA;
			else
				Quadrado->Centro.Y =(Quadrado->Centro.Y)+1;
			
			break;

		/* "andar" para esquerda nada mais é que diminuir minha coordenada do X do centro do quadrado */
		case (ESQUERDA):
			
				
			if(Quadrado->Centro.X - 2 == janela.PontoSE.X)
				Quadrado->Direcao = DIREITA;
			else
				Quadrado->Centro.X = (Quadrado->Centro.X) - 1 ;
			
			break;
		
		/* "andar" para direita nada mais é que aumentar minha coordenada do X do centro do quadrado */
		case (DIREITA):
			
				
			if(Quadrado->Centro.X + 2 == janela.PontoID.X)
				Quadrado->Direcao = ESQUERDA;
			else
				Quadrado->Centro.X = (Quadrado->Centro.X) + 1 ;
			
			break;
	}

	/* reimprime o novo quadrado*/
	imprime_quadrado(*Quadrado);
}

/*	|---------------  Le teclas ----------------------------|
	|	 Funcao que é chamada quando o programa reconhece	|
	|	um evento. Realizada a filtragem do evento realiza 	|
	|	as alterações, quando necessario, e retorna como	|
	|	parametro como o programa deve prosseguir de acordo	|
	|	com o evento lido	 								|
	|-------------------------------------------------------|
*/

OQUEFAZER le_teclas(EVENTO evento, AMBIENTE *Ambiente)
{
	
	int controle;
	COORD Auxiliar;
	JANELA JanelaAuxiliar;

		if(evento.tipo_evento & KEY_EVENT)
		{
			/* caso a tecla digitada pelo usário seja a telca control */
			if(evento.teclado.status_teclas_controle & LEFT_CTRL_PRESSED)
			{
				if(Ambiente->Quantidade < 10)
					adiciona_quadrado(Ambiente);
				
				return REIPRIMIRJANELA;
			}

			/* caso a telca digitada pelo usuario seja diferente de CTRL*/
			else if (evento.teclado.status_tecla == LIBERADA)
			{
				
				switch(evento.teclado.codigo_tecla)
				{
					/* altera cor da janela atual para uma nova aleatoria*/
					case ESPACO:
						Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = rand()%15 + 1;
						return REIPRIMIRJANELA;
						break;

					/* aumetna a velocida do quadrado atual em 1 milisegundo*/
					case F2:
						
						if(Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade < 1000)
							Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade++;

							
						break;
					
					/*-- diminui a velocidade interna do quadrado -- */ 
					case F1: 

						if(Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade >1)
							Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade--;

						break;

					/* caso o usuario pressione a tecla da seta para direita no telcado */
					case SETA_PARA_DIREITA:
						
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = DIREITA;
						break;

					/* caso o usuario pressione a tecla da seta para esquerda no telcado */
					case SETA_PARA_ESQUERDA:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = ESQUERDA;
						break;

					/* caso o usuario pressione a tecla da seta para baixo no telcado */
					case SETA_PARA_BAIXO:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = BAIXO;
						break;
					
					/* caso o usuario pressione a tecla da seta para cima no telcado */
					case SETA_PARA_CIMA:
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = CIMA;
						break;
					
					/*-- aumenta area do quadrado externo para esquerda -- */
					case F3:

						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoSE.X--;

						JanelaAuxiliar.Coluna++;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;
					/*-- diminui a borda do quadrado da esquerda --*/ 							
					case F4:

						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoSE.X++;
						JanelaAuxiliar.Coluna--;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;
					
					/*-- aumenta a area do quadrado para direita --*/
					case F5:

						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoID.X++;
						JanelaAuxiliar.Coluna++;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;
						
					/*-- diminui a area da do quadrado para direita --*/
					case F6: 

						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoID.X--;
						JanelaAuxiliar.Coluna--;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;

					/*-- aumenta a areda do quadrado para cima --*/
					case F7:
						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoSE.Y--;
						JanelaAuxiliar.Linha++;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;	
					/*-- diminui a area superior --*/ 
					case F8:
						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoSE.Y++;
						JanelaAuxiliar.Linha--;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;

					/*-- aumenta a area para baixo --*/
					case F9:
						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoID.Y++;
						JanelaAuxiliar.Linha++;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;
					/*--diminui a area para baixo --*/
					case F10:
						
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoID.Y--;
						JanelaAuxiliar.Linha--;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;

					/*--alterna a cor do quadrado --*/
					case CTRL:
						return 0;
						
					/*-- alterna a cor do quadrado --*/
					case TAB:
						Ambiente->Quadrado[Ambiente->JanelaAtual].CorQuadrado = rand()%15 + 1; 
						return TAB;

					/*-- finaliza programa --*/
					case ESC:
							return ENCERRARPROGRAMA;
				}
			}	
		} 
		else if(evento.tipo_evento & MOUSE_EVENT) /* caso o evento que seja feito no console seja de mouse */
		{
			if(evento.mouse.botao_clicou & BOTAO_ESQUERDO_PRESSIONADO)
			{

				Auxiliar  = evento.mouse.posicao;
		

				/* andara por todas as janeas que há no ambiente e verifica se as coordenadas que a funcao evento retorna esta contido em alguma delas*/
				for(controle = 0; controle < Ambiente->Quantidade; ++controle)
				{
					if((Ambiente->Janela[controle].PontoSE.X < Auxiliar.X) && (Ambiente->Janela[controle].PontoSE.Y < Auxiliar.Y))
					{
						/* caso a coordenada retornada por Evento esteja no meio de alguma janela, essa se tornara a janela principal*/
						if((Ambiente->Janela[controle].PontoID.X > Auxiliar.X) && (Ambiente->Janela[controle].PontoID.Y > Auxiliar.Y))
						{
						Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = FALSO;
						Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
						Ambiente->JanelaAtual = controle;
						Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
						Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;
						}
					}

				}

				return REIPRIMIRJANELA;
			}

			return CONTINUAR;
		}

		return 1; 
}

/*		|---------------  Ajusta quadrado ----------------------|
		|	 	Essa função é chamada quando há a movimentação	|
		|	da janela externa, a funcao recebe o ambiente para 	|
		|	pegar a janela atual e movimentar o quadrado interno|
		|	caso ele esteja ulptrapassando alguma borda 		|
		|-------------------------------------------------------|
*/

void ajusta_quadrado(QUADRADO *Quadrado, JANELA Janela)
{


		/* conflito na parte inferior da janela*/
	if(Quadrado->Centro.Y == (Janela.PontoID.Y - 2))
			Quadrado->Centro.Y--;
	else if(Quadrado->Centro.Y == Janela.PontoSE.Y + 1) /*conlfito na parte superior da janela*/
		Quadrado->Centro.Y++;

		/* conflito na parte esquerda da janela */
	if(Quadrado->Centro.X == Janela.PontoSE.X + 1)
		Quadrado->Centro.X++;
	else if(Quadrado->Centro.X == Janela.PontoID.X - 1)/* conlfito com a parte direita horizontalmente */
		Quadrado->Centro.X--;

}


/*		|---------------  Set console --------------------------|
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

/*		|---------------  Adiciona QUadrado --------------------|
		|		A funcao ira realizar a varredura da janela, 	|
		|	e ira colocar a janela onde conseguir;				|
		|		 O programa basicamente cria uma janela com 	|
		|	tamanho aleatorio, e ira tentar posicionar o mesmo 	|
		|	não cosneguindo ele diminui as coordenadas e tenta	|
		|	posicionar novamente e assim ele vai a exaustao 	|
		|	sendo que quando o quadrado atingiu o menor tamanho |
		|	possivel ele sai sem adicionar janela alguma, e caso|
		|	ele consiga colcoar alguma janela ele adiciona a 	|
		|	janela na vetor Janela de Ambiente					| 
		|														|
		|-------------------------------------------------------|
*/
void adiciona_quadrado(AMBIENTE *Ambiente)
{
	JANELA JanelaAuxiliar; 
	BOOLEANO controle;
	int i, auxiliar; 


	/* criando uam janela com valores aleatorios*/
	JanelaAuxiliar.Linha = rand()%LINHA + 10;
	JanelaAuxiliar.Coluna = rand()% COLUNA + 10;

	JanelaAuxiliar.PontoSE.X = 1;
	JanelaAuxiliar.PontoSE.Y = 1;

	JanelaAuxiliar.PontoID.X = JanelaAuxiliar.PontoSE.X + JanelaAuxiliar.Coluna;
	JanelaAuxiliar.PontoID.Y = JanelaAuxiliar.PontoSE.Y +JanelaAuxiliar.Linha;
	JanelaAuxiliar.JanelaAtual = VERDADEIRO;
	
	/*definindo a janela atual como sendo a falsa a ser considerada no programa*/
	auxiliar = Ambiente->JanelaAtual;
	Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
	Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = FALSO;
	
	/* quando eu tiver uam janela menor que 5x5 ela nao tera capacidade de armazenar um quadrado, logo não há necessidade de continuar tentando 
	colocar mais janelas no programa*/
	while(JanelaAuxiliar.Linha > 5 && JanelaAuxiliar.Coluna > 5)
	{	
		/*chute inicial, assume-se que é válida e verifica se algum valor é inválido */
		controle = VERDADEIRO;
		

		/* andando com a janela auxiliar na vertical */
		while(JanelaAuxiliar.PontoID.Y < Ambiente->PontoFinal.Y)
		{
			/*andando com a janela na horixontal*/
			while(JanelaAuxiliar.PontoID.X <= Ambiente->PontoFinal.X)
			{
					i = 0;

					while (i < Ambiente->Quantidade)
					{		
						/*
							controle = Verifica_janelas(JanelaAuxiliar ,Ambiente->Janela[i]);
						*/
							controle = valida_janela(*Ambiente, JanelaAuxiliar);
							++i;

							if(controle == FALSO)
								break;

					}

				if(controle)
					break;

				/* anda com o quadrado para a direita */
				JanelaAuxiliar.PontoSE.X++;
				JanelaAuxiliar.PontoID.X++;
			}

			if(controle)
				break;

			JanelaAuxiliar.PontoID.Y++;
			JanelaAuxiliar.PontoSE.Y++;
			JanelaAuxiliar.PontoSE.X=1;
			JanelaAuxiliar.PontoID.X = JanelaAuxiliar.PontoSE.X + JanelaAuxiliar.Coluna;
		}

		if(controle)
			break;

		JanelaAuxiliar.Linha--;
		JanelaAuxiliar.Coluna--;

		JanelaAuxiliar.PontoSE.X = 1;
		JanelaAuxiliar.PontoSE.Y = 1;

		JanelaAuxiliar.PontoID.X = JanelaAuxiliar.PontoSE.X + JanelaAuxiliar.Coluna;
		JanelaAuxiliar.PontoID.Y = JanelaAuxiliar.PontoSE.Y +JanelaAuxiliar.Linha;

	}

	if(controle == FALSO)
	{

		Ambiente->JanelaAtual=auxiliar;
		Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
		Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;

	}
		else if(controle)
	{	
		
		++Ambiente->Quantidade;
		Ambiente->JanelaAtual = Ambiente->Quantidade-1;
		Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
		Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
		Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = rand()%15 + 1;
		Ambiente->Quadrado[Ambiente->JanelaAtual].CorQuadrado = rand()%15+1;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = rand()%4;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade = rand()%1000;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Centro.X = Ambiente->Janela[Ambiente->JanelaAtual].PontoID.X - Ambiente->Janela[Ambiente->JanelaAtual].Coluna / 2;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Centro.Y = Ambiente->Janela[Ambiente->JanelaAtual].PontoID.Y - Ambiente->Janela[Ambiente->JanelaAtual].Linha / 2;
		Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;
	}

}

BOOLEANO Verifica_janelas2(JANELA Janela1, JANELA Janela2)
{	
	BOOLEANO Retorno; 
	int i, j ; 

	i = 0;

	Retorno = VERDADEIRO;

	while(i < Janela1.Linha)
	{	
		j = 0;

		while( j < Janela1.Coluna)
		{
			if(Janela1.PontoSE.X + j >= Janela2.PontoSE.X && Janela1.PontoSE.Y + i >= Janela2.PontoSE.Y)
				if(Janela1.PontoSE.X + j  <= Janela2.PontoID.X && Janela1.PontoSE.Y + i <= Janela2.PontoID.Y)
					Retorno = FALSO;
			
			++j;
		}

		++i;
	}

	return Retorno;
}