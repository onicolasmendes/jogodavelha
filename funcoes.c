/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_RESET "\x1b[0m"
#define ANSI_BG_COLOR_CYAN "\x1b[46m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_BOLD "\x1b[1m"
#define BG_CYAN(string) ANSI_BG_COLOR_CYAN string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define WHITE(string) ANSI_COLOR_WHITE string ANSI_RESET
#define BOLD(string) ANSI_BOLD string ANSI_RESET

void printNomeDoJogo()
{
    printf("\n ");
    printf(BG_CYAN(BOLD("      ___  _______  _______  _______    ______   _______    __   __  _______  ___      __   __  _______  ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD("     |   ||       ||       ||       |  |      | |   _   |  |  | |  ||       ||   |    |  | |  ||   _   | ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD("     |   ||   _   ||    ___||   _   |  |  _    ||  |_|  |  |  |_|  ||    ___||   |    |  |_|  ||  |_|  | ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD("     |   ||  | |  ||   | __ |  | |  |  | | |   ||       |  |       ||   |___ |   |    |       ||       | ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD("  ___|   ||  |_|  ||   ||  ||  |_|  |  | |_|   ||       |  |       ||    ___||   |___ |       ||       | ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD(" |       ||       ||   |_| ||       |  |       ||   _   |   |     | |   |___ |       ||   _   ||   _   | ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD(" |_______||_______||_______||_______|  |______| |__| |__|    |___|  |_______||_______||__| |__||__| |__| ")) "\n");
    printf(" ");
    printf(BG_CYAN(BOLD("                                                                                                         ")) "\n");
    printf("\n");
};

void printMenu()
{

    printf("0. Sair do Jogo\n");
    printf("1. Começar um novo jogo\n");
    printf("2. Continuar um jogo salvo\n");
    printf("3. Continuar o jogo atual\n");
    printf("4. Exibir o ranking\n");
    printf("Durante o jogo digite \"voltar\" para retornar ao menu.\n\n");
}

void limpaBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int verificaArquivoExistente(char *nomeArquivo)
{
    FILE *arquivo;
    if (arquivo = fopen(nomeArquivo, "r"))
    {
        fclose(arquivo);
        return 1;
    }

    return 0;
}

int converteCharPraInt(char c)
{
    int num = c - '0';
    return num;
}

int verificaPlayerNoIni(char *nome, int nJogadores)
{
    FILE *arquivoIni = fopen("velha.ini", "r+");
    int lixo; // Variável para pegar o numero de jogadores
    fscanf(arquivoIni, "%d\n", &lixo);
    char nomeComparacao[64];
    for (int i = 0; i < nJogadores; i++)
    {
        fgets(nomeComparacao, 64, arquivoIni);
        nomeComparacao[strlen(nomeComparacao) - 1] = '\0';
        if (!strcmp(nome, nomeComparacao)) // Caso ele tenha identificado o nome do player no .ini
        {
            fclose(arquivoIni);
            return i;
        }
        // Pulando os dados de vitorias, empates e derrotas
        int lixo1, lixo2, lixo3;
        fscanf(arquivoIni, "%d %d %d\n", &lixo1, &lixo2, &lixo3);
    }
    fclose(arquivoIni);
    return -1;
}

void adicionaNovoPlayer(Jogador *jogadores, Jogador *jogadoresTemp, int *nJogadores, int *posicaoPlayer, int nPlayer)
{
    jogadores[(*nJogadores)] = jogadoresTemp[nPlayer];
    jogadores[(*nJogadores)].vitorias = 0; 
    jogadores[(*nJogadores)].empates = 0;
    jogadores[(*nJogadores)].derrotas = 0;
    *posicaoPlayer = *nJogadores;
    *nJogadores = *nJogadores + 1; 
}

char ** criaMatriz(int n, int m)
{
    char **matriz = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++)
    {
        matriz[i] = malloc(m * sizeof(char));
    }
    return matriz;
}

void liberaMatriz(char **A, int n)
{
    for(int i = 0; i < n; i++)
    {
        free(A[i]);
    }
    free(A);
}

void captaComando(char *comandoGeral, char *comandoPrincipal, char *parametroDoComandoPrincipal)
{
    int cont = 0;
    while(comandoGeral[cont] != ' ') //captação do primeiro comando
    {
        comandoPrincipal[cont] = comandoGeral[cont];
        cont++;
    }
    comandoPrincipal[cont] = '\0';
    cont++;
    int novoCont = 0;
    
    while (comandoGeral[cont] != ' ' && comandoGeral[cont] != '\n') //captação do parametro
    {
        parametroDoComandoPrincipal[novoCont] = comandoGeral[cont];
        cont++;
        novoCont++;
    }

    parametroDoComandoPrincipal[novoCont] = '\0';
    

}