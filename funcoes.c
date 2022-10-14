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

char **criaMatriz(int n, int m)
{
    char **matriz = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        matriz[i] = malloc(m * sizeof(char));
    }
    return matriz;
}

void liberaMatriz(char **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
    }
    free(A);
}

void captaComando(char *comandoGeral, char *comandoPrincipal, char *parametroDoComandoPrincipal)
{
    int cont = 0;
    while (comandoGeral[cont] != ' ' && comandoGeral[cont] != '\n') // captação do primeiro comando
    {
        comandoPrincipal[cont] = comandoGeral[cont];
        cont++;
    }
    comandoPrincipal[cont] = '\0';

    int contMaisUm = cont + 1;

    if (comandoGeral[cont] == '\n') //Caso em que não há nenhum parâmetro, somente o comando - comando voltar
    {
        parametroDoComandoPrincipal[0] = '\0';
    }
    else if(comandoGeral[contMaisUm] != '\n') //Verifica se o próximo caracter corresponde ao final do comando e dos parametros informados
    {
        cont++;
        int novoCont = 0;

        while (comandoGeral[cont] != '\n') // captação do parametro
        {
            parametroDoComandoPrincipal[novoCont] = comandoGeral[cont];
            cont++;
            novoCont++;
        }

        parametroDoComandoPrincipal[novoCont] = '\0';
    }
    else //Caso em que foi passado apenas um caracter como parametro, como nenhum dos comandos usam apenas um caracter como parametro, atribui-se '1' ao parametroDoComandoPrincipal - valor aleatório - esse '1', sozinho, tbm não é um parametro que sera utilizado em nenhum outro comando
    {
        parametroDoComandoPrincipal[0] = '1';
        parametroDoComandoPrincipal[1] = '\0';
    }
}

int validaComando(char *comandoPrincipal, char *parametroDoComandoPrincipal, char *comandoGeral, Jogador *jogadoresTemp, int posicaoPlayer)
{
    while (strcmp(comandoPrincipal, "marcar") != 0 && strcmp(comandoPrincipal, "voltar") != 0 && strcmp(comandoPrincipal, "salvar") != 0)
    {
        printf("\nERRO - comando inválido\n\n%s, digite o comando: ", jogadoresTemp[posicaoPlayer].nome);
        fgets(comandoGeral, 64, stdin);
        captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);
    }
    return 1;
}

int validaParametroDoMarcar(char *parametroDoComandoPrincipal, int *coordenadaLinha, int *coordenadaColuna, char *comandoPrincipal)
{
    if (strcmp(comandoPrincipal, "marcar") == 0) // O comando digitado deve ser o "marcar"
    {
        if (strlen(parametroDoComandoPrincipal) != 2)
        {
            printf("\nERRO - Comando inválido\n\n");
            return 0;
        }
        else
        {
            *coordenadaLinha = converteCharPraInt(parametroDoComandoPrincipal[0]);
            *coordenadaColuna = converteCharPraInt(parametroDoComandoPrincipal[1]);

            if ((*coordenadaLinha) >= 1 && (*coordenadaLinha) <= 3 && (*coordenadaColuna) >= 1 && (*coordenadaColuna) <= 3)
            {
                return 1;
            }
            else
            {
                printf("\nERRO - Comando inválido\n\n");
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}

int validaParametroDoSalvar(char *parametroDoComandoPrincipal, char *comandoPrincipal)
{
    if (strcmp(comandoPrincipal, "salvar") == 0)
    {
        int tamanhhoDoParametro = (int)strlen(parametroDoComandoPrincipal) - 1;
        char extensaoTxt[4]; // Armazena a extensão do arquivo, que deve ser um .txt
        int cont = 0;
        for (int i = tamanhhoDoParametro - 3; i <= tamanhhoDoParametro; i++)
        {
            extensaoTxt[cont] = parametroDoComandoPrincipal[i];
            cont++;
        }
        extensaoTxt[cont] = '\0';
        if (strcmp(extensaoTxt, ".txt") == 0) // Verifica se a extensão do parâmetro possui .txt no final
        {
            if(verificaSeHaCaractereEspecial(parametroDoComandoPrincipal)) //Caso em que não há caracteres especiais no nome do arquivo
            {
                return 1;
            }
            else //Caso em que há caracteres especiais no nome do arquivo
            {
                printf("\nERRO - Caracter especial detectado no nome do arquivo!\n\n");
                return 0;
            }
        }
        else // Caso em que o parametro não possui .txt ao final
        {
            printf("\nERRO - Comando inválido\n\n");
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int validaParametroDoVoltar(char *parametroDoComandoPrincipal, char *comandoPrincipal)
{
    if (strcmp(comandoPrincipal, "voltar") == 0) // Verifica se o comando em questão é o voltar
    {
        if (parametroDoComandoPrincipal[0] == '\0') //Verifica se não foi passado nenhum parâmetro
        {
            
            return 1;
        }
        else //Caso em que o comando foi digitado corretamente, mas foi passado algum parâmetro, o que invalida a chamada do comando
        {
            
            return 0;
        }
        
    }
    else //Caso em que o comando digitado não foi o voltar
    {
        return 0;
    }
}

int verificaSeHaCaractereEspecial(char *parametroDoComandoPrincipal)
{
    int tamanho = strlen(parametroDoComandoPrincipal) - 4; //Posições antes do .txt
    for (int i = 0; i < tamanho; i++)
    {
        if((int) parametroDoComandoPrincipal[i] == 92 || (int)parametroDoComandoPrincipal[i] == 47 || (int)parametroDoComandoPrincipal[i] == 124 || (int)parametroDoComandoPrincipal[i] == 60 || (int)parametroDoComandoPrincipal[i] == 62 || (int)parametroDoComandoPrincipal[i] == 42 || (int)parametroDoComandoPrincipal[i] == 58 || (int)parametroDoComandoPrincipal[i] == 34 || (int)parametroDoComandoPrincipal[i] == 63) //Todos os caracteres especiais que não podem existir em nome de arquivos
        {
            
            return 0;
        }
    }

    return 1;   
}