/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 
#include <Windows.h> /* Sleep() */

#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(), setPosicaoJanela(),setDimensaoJanela() ,
setTituloConsole() ,setCursorStatus(), tamanhoJanelaConsole(); getPosicaoJanela();MaxDimensaoJanela();*/ 
#include "Quadrado.h" /* BOLADAVEZ, ATIVIDADE, BOOLEANO, ,OQUEFAZER ,DIRECAO,CONSOLE,JANELA, QUADRADO, AMBIENTE, valida_janela(),
cria_janela(),le_teclas(),adiciona_quadrado(),ajusta_quadrado(),apaga_quadrado(),gerencia_janela(),imprime_quadrado(),gerencia_programa()
movimenta_quadrado(),set_console() */

/*tamanhos maximos que um quadrado pode ser gerado aleatoriamente*/
#define LINHA 30
#define COLUNA 40

#define VELOCIDADE 100 /*dada em milisegundos */ 
#define CARACTER_HORIZONTAL 32 /* caso queira alterar o caraceter das colunas das janela sque é impresso (caratere em ASCII)*/
#define CARACTER_VERTICAL 32	/* caso queira alterar o caraceter das colunas das janela sque é impresso (caratere em ASCII)*/
#define CARACTER_IMPRESSO 42 /*ASTERISCO NA TABELA ASCII*/
#define BORDA_JANELA 32 /* ESPACO NA TABELA ASCII*/

#define QUANTIDADE_QUADRADOS 10 /* define a quantidade maxima de quadrados */

/*
	REGRA DE ORDENACAO: as funcoes estao ordenadas alfabeticamente por TIPO DE RETORNO, caso haja duas funcoes com o mesmo tipo de retorno 
	será ordenada alfabeticamente pelo NOME DA FUNCAO;
*/

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
	/*enquanto o parametro passo por le_telcas() não for para encerrar o programa ele fica preso nesse ciclo */
	}while(auxiliar != ENCERRARPROGRAMA);

}

/*		|---------------  Valida Janela ------------------------|
		|		A função recebe uma janela e verifica se é 		|
		|	possível colocar ela no ambiente, caso ela encontre	|
		|	alguma inconsistência ao tentar posicionar a janela	|
		|	o retorno será falso, caso seja possivel posicioar a| 
		|	janela o retorno sera verdadeiro;					|
		|-------------------------------------------------------|
*/

BOOLEANO valida_janela(AMBIENTE Ambiente, JANELA Janela)
{

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
	
	/* ira fazer uma varredura por todos os pontos internos da janela passada e verificar se ela conflita com alguma janela 
	*/
	do/*(contador = 0; contador < Ambiente.Quantidade; ++contador)*/
	{
		i = 0;

		/* controla a janela verticalmente */
		while (i <= Janela.Linha)
		{
			j = 0;
			/*controla a janela horizontalmente*/
			while(j <= Janela.Coluna)
			{
				/* ------- Precisamos verificar se alguns dos quatro pontos da janela não estão conflitando com alguem */
				if(Ambiente.Janela[contador].JanelaAtual == FALSO)
				{

					/* condicional que verifica se há algum ponto da janela sendo comparada que esta contida dentro de outra janela */
					if((Janela.PontoSE.X + j >= Ambiente.Janela[contador].PontoSE.X) && (Janela.PontoSE.Y + i >= Ambiente.Janela[contador].PontoSE.Y))
						if((Janela.PontoSE.X + j <= Ambiente.Janela[contador].PontoID.X) && (Janela.PontoSE.Y + i <= Ambiente.Janela[contador].PontoID.Y))
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
	while(JanelaAuxiliar.Linha > 5 || JanelaAuxiliar.Coluna > 5)
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
						
							controle = valida_janela(*Ambiente, JanelaAuxiliar);
							++i;
							
							/* achou algum conflito ou outra invalidacao entre as janelas */
							if(controle == FALSO)
								break;

					}

				/* caso o controle seja verdadeiro, significa que a janela passou na validação e pode ser colocada no console, logo pode sair desse 
				ciclo de execução */
				if(controle)
					break;

				/* anda com o quadrado para a direita */
				JanelaAuxiliar.PontoSE.X++;
				JanelaAuxiliar.PontoID.X++;
			}

			/* caso o controle seja verdadeiro, significa que a janela passou na validação e pode ser colocada no console, logo pode sair desse 
			ciclo de execução */

			if(controle)
				break;
			/*Recoloca o quadrado na posicao inicial em ponto superior esquerdo = 1 porem com o y incrementado  em uma posição para baixo */
			JanelaAuxiliar.PontoID.Y++;
			JanelaAuxiliar.PontoSE.Y++;
			JanelaAuxiliar.PontoSE.X=1;
			JanelaAuxiliar.PontoID.X = JanelaAuxiliar.PontoSE.X + JanelaAuxiliar.Coluna;
		}

		if(controle)
			break;

		/*redimenciona o quadrado diminuido o seu tamanho para tentar colocar ele novamente*/
		if(JanelaAuxiliar.Linha > 5)
			JanelaAuxiliar.Linha--;
		if(JanelaAuxiliar.Coluna > 5)
			JanelaAuxiliar.Coluna--;


		/* reposiciona o quadrado no inicio do console */
		JanelaAuxiliar.PontoSE.X = 1;
		JanelaAuxiliar.PontoSE.Y = 1;
		JanelaAuxiliar.PontoID.X = JanelaAuxiliar.PontoSE.X + JanelaAuxiliar.Coluna;
		JanelaAuxiliar.PontoID.Y = JanelaAuxiliar.PontoSE.Y +JanelaAuxiliar.Linha;

	}

	if(controle == FALSO)
	{
		/* caso seja falso, indica que não foi possivel colocar nenhum quadrado na tela logo não há mais espaço para posicionar quadrado na tela*/
		Ambiente->JanelaAtual=auxiliar;
		Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
		Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;

	}
	/* if adicionado por precaução, mas não necessita*/
	else if(controle)
	{	
		/* caso entre nessa condicional significa que a janela foi bem sucessida a ser posicionada 
		basta nesse caso apenas colcar os outros atributos faltantes da janela e do quadrado interno */
		++Ambiente->Quantidade;
		Ambiente->JanelaAtual = Ambiente->Quantidade-1;
		Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
		Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
		Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = BLUE;;
		Ambiente->Quadrado[Ambiente->JanelaAtual].CorQuadrado = LIGHTGRAY;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = rand()%4;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Velocidade = rand()%1000;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Centro.X = Ambiente->Janela[Ambiente->JanelaAtual].PontoID.X - Ambiente->Janela[Ambiente->JanelaAtual].Coluna / 2;
		Ambiente->Quadrado[Ambiente->JanelaAtual].Centro.Y = Ambiente->Janela[Ambiente->JanelaAtual].PontoID.Y - Ambiente->Janela[Ambiente->JanelaAtual].Linha / 2;
		Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;
	}

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
	
	/*coloca a cor do quadrado para preto*/
	textbackground(BLACK);


	/* realiza a sobreposicao das posicoes do quadrado atual pela cor preta */
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

	/* so imprimia a cor da janela que for a que estiver selecionada */
	if(Janela.JanelaAtual == VERDADEIRO)
		textbackground(Janela.CorJanela);
	else
		textbackground(LIGHTGRAY);
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da Linha e da Coluna
	essas funcoes serao 4 for's para criar as Linhas e as Colunas
	*/


	for(i = 0; i <= Janela.Coluna; i++)
	{
		/* Linha superior */ 
		gotoxy(Janela.PontoSE.X + i,Janela.PontoSE.Y);
		putchar(CARACTER_HORIZONTAL);
		
		/*Linha inferior*/
		gotoxy(Janela.PontoSE.X  + i,Janela.PontoID.Y);
		putchar(CARACTER_HORIZONTAL);
	
	}

	for(i = 0; i <= Janela.Linha; i++)
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
	gotoxy(Janela.PontoSE.X,Janela.PontoID.Y);
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
	|	 	A função recebe um quadrado e faz a impressao 	|
	|	baseada no centro, imprime como se fosse uma matriz |
	|	de 3X3 sendo o centro do quadrado o centro da matriz|
	|-------------------------------------------------------|
*/

void imprime_quadrado(QUADRADO quadrado)
{
	int i, j; 
	
	/* so imprimia a cor do quadrado que for a que estiver selecionada */
	if(quadrado.QuadradoAtual)
		textcolor(quadrado.CorQuadrado);
	else
		textcolor(LIGHTGRAY);

	/* imprime como se fosse uma matriz*/
	for(i = 0; i < 3 ;++i)
	{
		for(j = 0; j < 3; ++j)
		{
			/* não é necessario imrpimir o centro da matriz, e i =j indica o centro da "matriz"*/
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

		/* "andar" para baixo nada mais é que aumentar minha coordenada do Y do centro do quadrado */
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
	/* caso o ususario tenha iniciado o programa*/
	if(status)
	{
		
		/* armazena todos os valores atuais do console 
		assim como sua posicao maxima, para que o console de usuario 
		seja configurado no jogo e depois consiga retornar ao finalizar o programa
		*/
		
		console->dimensao_inicial = tamanhoJanelaConsole();
		console->posicao_inicial = getPosicaoJanela();
		console->dimensao_maxima = MaxDimensaoJanela();

		/* configura a tela do usuario */ 
		setPosicaoJanela(0,0);
		setTituloConsole(TITULO);	
		setCursorStatus(DESLIGAR);
		setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
	
	}
	/*caso o usuario tenha pressionado a telca ESC */
	else
	{
		clrscr();
		/* configura a tela do usuario para os valores iniciais na chamada do programa */
		gotoxy(console->dimensao_maxima.X/2,console->dimensao_maxima.Y/4);
		textcolor(WHITE);
		printf("----------------------------");
		gotoxy(console->dimensao_maxima.X/2,(console->dimensao_maxima.Y/4)+1);
		printf("FIM DA EXECUCAO DO PROGRAMA");
		gotoxy(console->dimensao_maxima.X/2,(console->dimensao_maxima.Y/4)+2);
		printf("----------------------------");
		setPosicaoJanela(console->posicao_inicial.X,console->posicao_inicial.Y);
		setDimensaoJanela(console->dimensao_inicial.X,console->dimensao_inicial.Y);
		
		
		setCursorStatus(LIGAR);
	}
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

		/* caso o eventi identificado seja de teclado iniciara essa função */
		if(evento.tipo_evento & KEY_EVENT)
		{
			/* caso a tecla digitada pelo usário seja a telca control */
			if(evento.teclado.status_teclas_controle & LEFT_CTRL_PRESSED)
			{
				/* controla a quantidade de quadrados */
				if(Ambiente->Quantidade < QUANTIDADE_QUADRADOS)
					adiciona_quadrado(Ambiente);
				
				return REIPRIMIRJANELA;
			}
			/* caso a tecla pressionada seja o ALT esquerdo */
			else if(evento.teclado.status_teclas_controle & LEFT_ALT_PRESSED)
			{
				/* o sistema ira sortear uma nova janela de forma aleatoria*/

				/* enquanto o numero gerado for o da janela atual ele ficara gerando o um novo valor*/
				do
				{
					controle = rand()%Ambiente->Quantidade;

				/* foi colocado um operador de castin para o tipo BOLADAVEZ*/
				}while((BOLADAVEZ)controle == Ambiente->JanelaAtual);

				/*fazendo a troca da janela atual, colocando falso para a que estava e depois passsando para verdadeiro a nova janela*/
				Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = FALSO;
				Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
				Ambiente->JanelaAtual = controle;
				Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
				Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;
				Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = BLUE;

			}
			/* caso a telca digitada pelo usuario seja diferente de CTRL*/
			else if (evento.teclado.status_tecla == LIBERADA)
			{
				
				/*ira pegar o codigo da tecla lido, lembrado que as teclas foram definas na biblioteca console, 
				referenciando seu nome a seu respectivo codigo */
				switch(evento.teclado.codigo_tecla)
				{
					/* altera cor da janela atual para uma nova aleatoria*/
					case ESPACO:
						Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = rand()%15 + 1;
						return REIPRIMIRJANELA;
						break;

					/* aumenta a velocida do quadrado atual em 1 milisegundo*/
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
						
						/* altera a direção do quadrado atual para a direita */
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = DIREITA;
						break;

					/* caso o usuario pressione a tecla da seta para esquerda no telcado */
					case SETA_PARA_ESQUERDA:

						/* altera a direção do quadrado atual para a esquerda */
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = ESQUERDA;
						break;

					/* caso o usuario pressione a tecla da seta para baixo no telcado */
					case SETA_PARA_BAIXO:

						/* altera a direção do quadrado atual para baixo */
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = BAIXO;
						break;
					
					/* caso o usuario pressione a tecla da seta para cima no telcado */
					case SETA_PARA_CIMA:

						/* altera a direção do quadrado atual para a cima */
						Ambiente->Quadrado[Ambiente->JanelaAtual].Direcao = CIMA;
						break;
					
					/*-- aumenta area do quadrado externo para esquerda -- */
					case F3:

						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
						JanelaAuxiliar = Ambiente->Janela[Ambiente->JanelaAtual];

						JanelaAuxiliar.PontoSE.X--;

						JanelaAuxiliar.Coluna++;

						/* CASO VALIDO REALIZA A SUBISTUICAO DA JANELA */
						if(valida_janela(*Ambiente, JanelaAuxiliar))
						{
							/* atrbui-se a janela auxilia para a atual caso a vlaidação esteja correta */
							Ambiente->Janela[Ambiente->JanelaAtual] = JanelaAuxiliar;
							ajusta_quadrado( &Ambiente->Quadrado[Ambiente->JanelaAtual],Ambiente->Janela[Ambiente->JanelaAtual]);
						}
						
						return REIPRIMIRJANELA;
					/*-- diminui a borda do quadrado da esquerda --*/ 							
					case F4:

						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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

						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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

						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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
						
						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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
						
						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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
						
						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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
						
						/* faz-se uma copia da janela atual para uma auxiliar para garantir a permanecia dos valores*/
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
		/* caso o evento que seja feito no console seja de mouse */
		else if(evento.tipo_evento & MOUSE_EVENT)
		{
			if(evento.mouse.botao_clicou & BOTAO_ESQUERDO_PRESSIONADO)
			{
				
				/*variavel auxiliar que recebera o valor de COORD retornado pelo evento */
				Auxiliar  = evento.mouse.posicao;
		

				/* andara por todas as janeas que há no ambiente e verifica se as coordenadas que a funcao evento retorna esta contido em alguma delas*/
				for(controle = 0; controle < Ambiente->Quantidade; ++controle)
				{
					if((Ambiente->Janela[controle].PontoSE.X-1 <= Auxiliar.X) && (Ambiente->Janela[controle].PontoSE.Y-1 <= Auxiliar.Y))
					{
						/* caso a coordenada retornada por Evento esteja no meio de alguma janela, essa se tornara a janela principal*/
						if((Ambiente->Janela[controle].PontoID.X > Auxiliar.X) && (Ambiente->Janela[controle].PontoID.Y > Auxiliar.Y))
						{
							Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = FALSO;
							Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = FALSO;
							Ambiente->JanelaAtual = controle;
							Ambiente->Janela[Ambiente->JanelaAtual].JanelaAtual = VERDADEIRO;
							Ambiente->Quadrado[Ambiente->JanelaAtual].QuadradoAtual = VERDADEIRO;
							Ambiente->Janela[Ambiente->JanelaAtual].CorJanela = BLUE;
							Ambiente->Quadrado[Ambiente->JanelaAtual].CorQuadrado = LIGHTGRAY;
						}
					}

				}

				return REIPRIMIRJANELA;
			}

			return CONTINUAR;
		}

		return 1; 
}