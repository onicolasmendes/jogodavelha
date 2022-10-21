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
int validaNomePlayer2(char *nomePlayer1, char *nomePlayer2);
int validaNomePlayer1(char *nomePlayer1);
int validaNJogadoresRodada(char *comandoNJogadores, char *nJogadoresRodada);
int validaOp(char *comandoOp, char *op);
int jogoMultiplayer(char **matriz, Jogador *jogadoresTemp, Jogador *jogadores, int posicaoPlayer1, int posicaoPlayer2, int contRodada, int nJogadores, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual);
int jogoMultiplayerArquivoIniNovo(char **matriz, Jogador *jogadoresNovoIni, int contRodadaNew, int nJogadoresNovos, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual);

int jogoMultiplayerJogoAtual(char **matriz, Jogador *jogadoresTemp, Jogador *jogadores, int posicaoPlayer1, int posicaoPlayer2, int contRodada, int nJogadores);
void copiaMatriz(char ***A, char **B);
int jogoMultiplayerCarregado(char **matriz, Jogador *jogadoresTemp, Jogador *jogadores, int posicaoPlayer1, int posicaoPlayer2, int contRodada, int nJogadores);
int validaNomeArquivo(char *nomeArquivo);
int lerArquivo(char *nomeArquivo, char ***matrizJogoCarregado, Jogador *jogadoresTempJogoCarregado, int *contRodadaJogoCarregado, int *nJogadoresJogoCarregado);
int verificaNomeNoVetorPrincipal(Jogador *jogadores, char *nomePlayer, int nJogadores);

#endif
