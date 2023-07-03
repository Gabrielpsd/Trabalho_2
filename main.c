/* 

	programa: Multiplos quadrados animados
	Descrição: O executa no prompt de comando multiplas janelas animadas, onde o usuario pode interagir simultaneamente com todas as 
	janelas, podendo adicionar, trocar a cor a direção e também velocidade do ;
	
	Programador: Gabriel Pereira dos Santos Dias
	RGM: 43562
	data de modificação: 30/06/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execuçãoss recomenda-se que configure seu prompt de comando para que utilize as propriedades
	herdadas do prompt.
		 
	
	codigo para compilação: gcc main.c -o saida.exe conio_v3.2.4.c console_v1.5.4.c quadrado.c -Wall -Werror -Wextra -pedantic -lwinmm  
	

	REGRA DE ORDENACAO: as funcoes estao ordenadas alfabeticamente por TIPO DE RETORNO, caso haja duas funcoes com o mesmo tipo de retorno 
	será ordenada alfabeticamente pelo NOME DA FUNCAO;

	link para o Repositorio: https://github.com/Gabrielpsd/Trabalho_2


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
	
	/* artificio para acabar com warning*/
	argc = argc; 
	argv = argv;
	
	/*define uma semente para geração dos valores aleatorios gerados no sistema*/
	srand(time(NULL));
	
	/* comfigura o console para executar o programa */
	set_console(&Console, ATIVAR);

	/* determina os valores inicias para algumas variaveis de controle*/
	Ambiente.PontoFinal = Console.dimensao_maxima;
	Ambiente.Quantidade = 0;
	Ambiente.JanelaAtual = 0;

	/* adiciona o primeiro quadrado na tela */
	adiciona_quadrado(&Ambiente);

	/*limpa a tela do usuario*/
	clrscr();

	/* imprimime a primeira janela do ambiente */
	gerencia_janela(Ambiente.Janela[0], Ambiente.Quadrado[0].Velocidade);

	/* chama a funcao que gerencia o programa */
	gerencia_programa(&Ambiente);
	
	/* redefine os valores do console para como estava antes da execução do programa */
	set_console(&Console,DESATIVAR);
	
	return 0;
}

