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
int validaComando(char *comandoPrincipal, char *parametroDoComandoPrincipal, char *comandoGeral, Jogador *jogadoresTemp, int posicaoPlayer);
int validaParametroDoMarcar(char *parametroDoComandoPrincipal, int *coordenadaLinha, int *coordenadaColuna, char *comandoPrincipal, char **matriz);
int validaParametroDoSalvar(char *parametroDoComandoPrincipal, char *comandoPrincipal);
int validaParametroDoVoltar(char *parametroDoComandoPrincipal, char *comandoPrincipal);
int verificaSeHaCaractereEspecial(char *parametroDoComandoPrincipal);
int verificaPosicaoDisponivel(char **matriz, int linha, int coluna);
void inicializaMatriz(char ***matriz, int n, int m);
void marcarPosicao(char ***matriz, int linha, int coluna, int contRodada);
void imprimeMatriz(char **matriz, int n, int m);
char imprimeElemento(char **matriz, int linha, int coluna);
int verificaVitoria(char **matriz, int n, int m);
void copiaVetorStruct(Jogador *copiado, Jogador *copia, int tam);


#endif
