/* 

	programa: Quadrados multiplos animados 
	Descrição: O executa no prompt de comando multiplas janelas aniamdas, onde o usuario pode interagir simultaneamente com todas as 
	janelas;
	
	Programador: Gabriel Pereira dos Santos Dias
	RGM: 43562
	data de modificação: 09/05/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe conio_v3.2.4.c console_v1.5.4.c graphics_v1.1.c quadrado.c -lgdi32 -Wall -Werror -Wextra -pedantic -lwinmm  
	
*/
#include <stdio.h> /*NULL*/
#include <time.h> /* time() */ 
#include <stdlib.h> /* srand(), rand() */ 

#include "conio_v3.2.4.h" /* COLORS */ 
#include "Quadrado.h"

#define QUANTIDADE 1
#define COR_INICIO_JANELA 9

int main(int argc , char **argv)
{
	
	JANELA *Janela, refJanela;
	CONSOLE *console , Pointer_console;
	QUADRADO *quadrado, refquad;
	
	console = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	argc = argc; 
	argv = argv;
	
	srand(time(NULL));
	
	Janela->cor = COR_INICIO_JANELA;
	
	set_ambiente(console, ATIVAR);
	cria_ponto(Janela);
	cria_quadrado(quadrado, *Janela);
	gerencia_janela(Janela);
	imprime_info(*quadrado);
	
	gerencia_programa( Janela, quadrado);
	
	set_ambiente(console,DESATIVAR);
	
	
	return 0;
}

