/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/
#ifndef __FUNCOES_H__
#define __FUNCOES_H__
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNomeDoJogo();
void printMenu();
void limpaBuffer();
int verificaArquivoExistente(char* nomeArquivo);
int converteCharPraInt(char c);
int verificaPlayerNoIni(char* nome, int nJogadores);
void adicionaNovoPlayer(Jogador*jogadores, Jogador *jogadoresTemp, int *nJogadores, int *posicaoPlayer, int nPlayer);
char ** criaMatriz(int n, int m);
void liberaMatriz(char **A, int n);
void captaComando(char *comandoGeral, char *comandoPrincipal, char *parametroDoComandoPrincipal);



#endif
