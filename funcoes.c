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
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL "\u250F"  // ┏ (top-left)
#define TAB_ML "\u2523"  // ┣ (middle-left)
#define TAB_BL "\u2517"  // ┗ (bottom-left)
#define TAB_TJ "\u2533"  // ┳ (top-join)
#define TAB_MJ "\u254B"  // ╋ (middle-join)
#define TAB_BJ "\u253B"  // ┻ (bottom-join)
#define TAB_TR "\u2513"  // ┓ (top-right)
#define TAB_MR "\u252B"  // ┫ (middle-right)
#define TAB_BR "\u251B"  // ┛ (bottom-right)

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

    if (comandoGeral[cont] == '\n') // Caso em que não há nenhum parâmetro, somente o comando - comando voltar
    {
        parametroDoComandoPrincipal[0] = '\0';
    }
    else if (comandoGeral[contMaisUm] != '\n') // Verifica se o próximo caracter corresponde ao final do comando e dos parametros informados
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
    else // Caso em que foi passado apenas um caracter como parametro, como nenhum dos comandos usam apenas um caracter como parametro, atribui-se '1' ao parametroDoComandoPrincipal - valor aleatório - esse '1', sozinho, tbm não é um parametro que sera utilizado em nenhum outro comando
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

int validaParametroDoMarcar(char *parametroDoComandoPrincipal, int *coordenadaLinha, int *coordenadaColuna, char *comandoPrincipal, char **matriz)
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
                if (verificaPosicaoDisponivel(matriz, *coordenadaLinha, *coordenadaColuna))
                {
                    return 1;
                }
                else
                {
                    printf("A posição não está disponível!\n");
                    return 0;
                }
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
        char extensaoTxt[5]; // Armazena a extensão do arquivo, que deve ser um .txt
        int cont = 0;
        for (int i = tamanhhoDoParametro - 3; i <= tamanhhoDoParametro; i++)
        {
            extensaoTxt[cont] = parametroDoComandoPrincipal[i];
            cont++;
        }
        extensaoTxt[cont] = '\0';
        printf("%s\n\n", extensaoTxt);
        if (strcmp(extensaoTxt, ".txt") == 0) // Verifica se a extensão do parâmetro possui .txt no final
        {
            
            if (verificaSeHaCaractereEspecial(parametroDoComandoPrincipal)) // Caso em que não há caracteres especiais no nome do arquivo
            {
                return 1;
            }
            else // Caso em que há caracteres especiais no nome do arquivo
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
        if (parametroDoComandoPrincipal[0] == '\0') // Verifica se não foi passado nenhum parâmetro
        {

            return 1;
        }
        else // Caso em que o comando foi digitado corretamente, mas foi passado algum parâmetro, o que invalida a chamada do comando
        {

            return 0;
        }
    }
    else // Caso em que o comando digitado não foi o voltar
    {
        return 0;
    }
}

int verificaSeHaCaractereEspecial(char *parametroDoComandoPrincipal)
{
    int tamanho = strlen(parametroDoComandoPrincipal) - 4; // Posições antes do .txt
    for (int i = 0; i < tamanho; i++)
    {
        if ((int)parametroDoComandoPrincipal[i] == 92 || (int)parametroDoComandoPrincipal[i] == 47 || (int)parametroDoComandoPrincipal[i] == 124 || (int)parametroDoComandoPrincipal[i] == 60 || (int)parametroDoComandoPrincipal[i] == 62 || (int)parametroDoComandoPrincipal[i] == 42 || (int)parametroDoComandoPrincipal[i] == 58 || (int)parametroDoComandoPrincipal[i] == 34 || (int)parametroDoComandoPrincipal[i] == 63) // Todos os caracteres especiais que não podem existir em nome de arquivos
        {

            return 0;
        }
    }

    return 1;
}

void inicializaMatriz(char ***matriz, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            (*matriz)[i][j] = '-'; // Inicializa a matriz com o caracter -, considerado o caracter neutro, nesse caso
        }
    }
}

int verificaPosicaoDisponivel(char **matriz, int linha, int coluna)
{
    linha--; //Para o user as posições começam a partir do 1, mas a matriz começa do 0, pra coluna e pra linha
    coluna--;
    if (matriz[linha][coluna] == '-') // Caso tenha um x ou o nessa posição a função retorna 0, caso não, a função retorna 1
    {
        return 1;
    }

    return 0;
}

void marcarPosicao(char ***matriz, int linha, int coluna, int contRodada)
{
    coluna--; //Para o user as posições começam a partir do 1, mas a matriz começa do 0, pra coluna e pra linha
    linha--;
    if (contRodada % 2 != 0) // Jogador 1 - Joga o x
    {
        (*matriz)[linha][coluna] = 'X';
    }
    else // Jogador 2 - joga o O
    {
        (*matriz)[linha][coluna] = 'O';
    }
}

void imprimeMatriz(char **matriz, int n, int m)
{

    printf("\n");
    printf("  1 2 3\n");
    printf(" "TAB_TL   TAB_HOR   TAB_TJ   TAB_HOR   TAB_TJ   TAB_HOR   TAB_TR   "\n");
    printf("1"TAB_VER "%c" TAB_VER "%c" TAB_VER "%c" TAB_VER "\n", imprimeElemento(matriz, 0, 0),imprimeElemento(matriz, 0, 1),imprimeElemento(matriz, 0, 2));
    printf(" "TAB_ML TAB_HOR TAB_MJ TAB_HOR TAB_MJ TAB_HOR TAB_MR "\n");
    printf("2"TAB_VER "%c" TAB_VER "%c" TAB_VER "%c" TAB_VER "\n", imprimeElemento(matriz, 1, 0),imprimeElemento(matriz, 1, 1),imprimeElemento(matriz, 1, 2));
    printf(" "TAB_ML TAB_HOR TAB_MJ TAB_HOR TAB_MJ TAB_HOR TAB_MR "\n");
    printf("3"TAB_VER "%c" TAB_VER "%c" TAB_VER "%c" TAB_VER "\n",imprimeElemento(matriz, 2, 0),imprimeElemento(matriz, 2, 1),imprimeElemento(matriz, 2, 2 ));
    printf(" "TAB_BL TAB_HOR TAB_BJ TAB_HOR TAB_BJ TAB_HOR TAB_BR "\n");
    printf("\n");
}

char imprimeElemento(char **matriz, int linha, int coluna)
{
    if(matriz[linha][coluna] == '-')
    {
        return ' '; //Troca o elemento neutro por espaço - feita para ser chamada na função de impressão da matriz
    }
    else
    {
        return matriz[linha][coluna]; //Caso não seja o elemento neutro, a função retorna X ou O
    }
}

int verificaVitoriaEEmpate(char **matriz, int n, int m)
{
    char vitoriaPlayer1[3] = "XXX";
    char vitoriaPlayer2[3] = "OOO";
    char teste[3];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {

        }
    }

}