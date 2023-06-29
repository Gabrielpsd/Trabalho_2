/* 

	programa: Quadrados multiplos animados 
	Descrição: O executa no prompt de comando multiplas janelas animadas, onde o usuario pode interagir simultaneamente com todas as 
	janelas;
	
	Programador: Gabriel Pereira dos Santos Dias
	RGM: 43562
	data de modificação: 29/06/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe conio_v3.2.4.c console_v1.5.4.c quadrado.c -Wall -Werror -Wextra -pedantic -lwinmm  
	

	REGRA DE ORDENACAO: as funcoes estao ordenadas alfabeticamente por TIPO DE RETORNO, caso haja duas funcoes com o mesmo tipo de retorno 
	será ordenada alfabeticamente pelo NOME DA FUNCAO;

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

	Ambiente.PontoFinal = Console.dimensao_maxima;
	Ambiente.Quantidade = 0;
	Ambiente.JanelaAtual = 0;
	adiciona_quadrado(&Ambiente);

	clrscr();

	gerencia_janela(Ambiente.Janela[0], Ambiente.Quadrado[0].Velocidade);

	gerencia_programa(&Ambiente);
	
	set_console(&Console,DESATIVAR);
	
	return 0;
}

