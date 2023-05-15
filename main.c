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
#include "Quadrado.h" /* ATIVIDADE */ 


int main(int argc , char **argv)
{
	CONSOLE Console;
	AMBIENTE Ambiente; 
	
	argc = argc; 
	argv = argv;
	
	srand(time(NULL));
	
	set_console(&Console, ATIVAR);
	
	CriaAmbiente(&Ambiente);
	
	set_console(&Console,DESATIVAR);
	
	
	return 0;
}

