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
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define ANSI_RESET            "\x1b[0m" 
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define ANSI_COLOR_RED        "\x1b[31m"
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET

//Protótipos das funções

//Funções que imprimem informações
void printNomeDoJogo();
void printMenu();
void imprimeMatriz(char **matriz, int n, int m);
char imprimeElemento(char **matriz, int linha, int coluna);
void printVitoriaP1();
void printVitoriaP2();
void printEmpate();
void printVitoriaBot();
void exibeRanking(Jogador *jogadores, int nJogadores);

//Funções de validação de informações
int validaNomePlayer2(char *nomePlayer1, char *nomePlayer2);
int validaNomePlayer1(char *nomePlayer1);
int validaComando(char *comandoPrincipal, char *parametroDoComandoPrincipal, char *comandoGeral, Jogador *jogadoresTemp, int posicaoPlayer);
int validaParametroDoMarcar(char *parametroDoComandoPrincipal, int *coordenadaLinha, int *coordenadaColuna, char *comandoPrincipal, char **matriz);
int validaParametroDoSalvar(char *parametroDoComandoPrincipal, char *comandoPrincipal);
int validaParametroDoVoltar(char *parametroDoComandoPrincipal, char *comandoPrincipal);
int validaNomePlayer2(char *nomePlayer1, char *nomePlayer2);
int validaNomePlayer1(char *nomePlayer1);
int validaNJogadoresRodada(char *comandoNJogadores, char *nJogadoresRodada);
int validaOp(char *comandoOp, char *op);
int validaNomeArquivo(char *nomeArquivo);

//Funções de verificação
int verificaArquivoExistente(char* nomeArquivo);
int verificaPlayerNoIni(char* nome, int nJogadores);
int verificaSeHaCaractereEspecial(char *parametroDoComandoPrincipal);
int verificaPosicaoDisponivel(char **matriz, int linha, int coluna);
int verificaNomeNoVetorPrincipal(Jogador *jogadores, char *nomePlayer, int nJogadores);
int verificaVitoria(char **matriz, int n, int m);

//Funções relacionadas a matriz
char ** criaMatriz(int n, int m);
void liberaMatriz(char **A, int n);
void inicializaMatriz(char ***matriz, int n, int m);
void copiaMatriz(char ***A, char **B);

//Funções do jogo propriamente dito
void captaComando(char *comandoGeral, char *comandoPrincipal, char *parametroDoComandoPrincipal);
void adicionaNovoPlayer(Jogador*jogadores, Jogador *jogadoresTemp, int *nJogadores, int *posicaoPlayer, int nPlayer);
void marcarPosicao(char ***matriz, int linha, int coluna, int contRodada);
int jogoMultiplayer(char **matriz, Jogador *jogadoresTemp, Jogador *jogadores, int posicaoPlayer1, int posicaoPlayer2, int contRodada, int nJogadores, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual, int nJogadoresTotal);
int jogoMultiplayerArquivoIniNovo(char **matriz, Jogador *jogadoresNovoIni, int contRodadaNew, int nJogadoresNovos, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual);
int botJogador(char **matriz, int *coordenadaLinha, int *coordenadaColuna, int contRodada);

//Funções que trabalham com o arquivo
void atualizaIni(Jogador *jogadores, int nJogadores);
int lerArquivo(char *nomeArquivo, char ***matrizJogoCarregado, Jogador *jogadoresTempJogoCarregado, int *contRodadaJogoCarregado, int *nJogadoresJogoCarregado);

//Funções do ranking
int atualizaRanking(Jogador *jogadores, int nJogadores);
int exibePosicaoRanking(Jogador *jogadores, char *nome, int nJogadores);

//Função de limpar o buffer
void limpaBuffer();
void capturaTecla();

//Funçõe de conversão
int converteCharPraInt(char c);

//Função para copiar vetor de struct
void copiaVetorStruct(Jogador *copiado, Jogador *copia, int tam);

#endif
