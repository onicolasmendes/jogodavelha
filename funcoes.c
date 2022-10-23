/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ANSI_RESET "\x1b[0m"
#define ANSI_BG_COLOR_CYAN "\x1b[46m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_BG_COLOR_BLUE "\x1b[44m"
#define BG_CYAN(string) ANSI_BG_COLOR_CYAN string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define WHITE(string) ANSI_COLOR_WHITE string ANSI_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_RESET
#define BOLD(string) ANSI_BOLD string ANSI_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_RESET
#define RED(string) ANSI_COLOR_RED string ANSI_RESET
#define BLUE(string) ANSI_COLOR_BLUE string ANSI_RESET
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define MAGENTA(string) ANSI_COLOR_MAGENTA string ANSI_RESET
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

    printf(GREEN("0. Sair do Jogo\n"));
    printf(GREEN("1. Começar um novo jogo\n"));
    printf(GREEN("2. Continuar um jogo salvo\n"));
    printf(GREEN("3. Continuar o jogo atual\n"));
    printf(GREEN("4. Exibir o ranking\n"));
    printf(GREEN("Durante o jogo digite \"voltar\" para retornar ao menu.\n\n"));
}

void limpaBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void capturaTecla()
{
    while (getchar() != '\n')
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
        printf(RED("\nERRO - comando inválido\n"));
        printf(RED("\n%s, digite o comando: "), jogadoresTemp[posicaoPlayer].nome);
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
            printf(RED("\nERRO - Comando inválido\n\n"));
            return 0;
        }
        else
        {
            *coordenadaLinha = converteCharPraInt(parametroDoComandoPrincipal[0]);
            *coordenadaColuna = converteCharPraInt(parametroDoComandoPrincipal[1]);

            if ((*coordenadaLinha) >= 1 && (*coordenadaLinha) <= 3 && (*coordenadaColuna) >= 1 && (*coordenadaColuna) <= 3)
            {
                if (verificaPosicaoDisponivel(matriz, *coordenadaLinha, *coordenadaColuna)) // Verifica se a posição informada está disponível para jogar
                {
                    return 1;
                }
                else // Caso em que a posição está indisponível
                {
                    printf(RED("\nA posição não está disponível!\n\n"));
                    return 0;
                }
            }
            else
            {
                printf(RED("\nERRO - Comando inválido\n\n"));
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

        if (strcmp(extensaoTxt, ".txt") == 0) // Verifica se a extensão do parâmetro possui .txt no final
        {

            if (verificaSeHaCaractereEspecial(parametroDoComandoPrincipal)) // Caso em que não há caracteres especiais no nome do arquivo
            {
                return 1;
            }
            else // Caso em que há caracteres especiais no nome do arquivo
            {
                printf(RED("\nERRO - Caracter especial detectado no nome do arquivo!\n\n"));
                return 0;
            }
        }
        else // Caso em que o parametro não possui .txt ao final
        {
            printf(RED("\nERRO - Comando inválido\n\n"));
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

            printf(RED("\nERRO - O comando voltar foi passado com algum parametro\n\n"));
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
    linha--; // Para o user as posições começam a partir do 1, mas a matriz começa do 0, pra coluna e pra linha
    coluna--;
    if (matriz[linha][coluna] == '-') // Caso tenha um x ou o nessa posição a função retorna 0, caso não, a função retorna 1
    {
        return 1;
    }

    return 0;
}

void marcarPosicao(char ***matriz, int linha, int coluna, int contRodada)
{
    coluna--; // Para o user as posições começam a partir do 1, mas a matriz começa do 0, pra coluna e pra linha
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
    printf(BOLD(GREEN("\t          1  2  3")) "\n");
    printf(BOLD(RED("\t\t ")));
    printf(TAB_TL TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_TR "\n");
    printf(BOLD(RED("\t\t1")));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 0, 0));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 0, 1));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 0, 2));
    printf(TAB_VER "\n");
    printf(BOLD(RED("\t\t ")));
    printf(TAB_ML TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MR "\n");
    printf(BOLD(RED("\t\t2")));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 1, 0));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 1, 1));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 1, 2));
    printf(TAB_VER "\n");
    printf(BOLD(RED("\t\t ")));
    printf(TAB_ML TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_MR "\n");
    printf(BOLD(RED("\t\t3")));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 2, 0));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 2, 1));
    printf(TAB_VER);
    printf(BG_BLUE("%c "), imprimeElemento(matriz, 2, 2));
    printf(TAB_VER "\n");
    printf(BOLD(RED("\t\t ")));
    printf(TAB_BL TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_BR "\n");
    printf("\n");
}
char imprimeElemento(char **matriz, int linha, int coluna)
{
    if (matriz[linha][coluna] == '-')
    {
        return ' '; // Troca o elemento neutro por espaço - feita para ser chamada na função de impressão da matriz
    }
    else
    {
        return matriz[linha][coluna]; // Caso não seja o elemento neutro, a função retorna X ou O
    }
}

int verificaVitoria(char **matriz, int n, int m) // Função retorna 1, caso player 1 ganhe, 2, caso player 2 ganhe, 0, case nenhum ganhe
{
    char vitoriaPlayer1[4] = "XXX";
    char vitoriaPlayer2[4] = "OOO";
    char teste[4];
    int cont = 0;
    // Verificação por linha

    for (int i = 0; i < n; i++)
    {
        cont = 0;
        for (int j = 0; j < m; j++)
        {
            teste[cont] = matriz[i][j];
            cont++;
        }
        teste[cont] = '\0';
        if (strcmp(teste, vitoriaPlayer1) == 0) // Caso em que o player 1 ganha
        {
            return 1;
        }
        else if (strcmp(teste, vitoriaPlayer2) == 0) // Caso em que o player 2 ganha
        {
            return 2;
        }
    }

    // Verificação por coluna
    for (int i = 0; i < n; i++)
    {
        cont = 0;
        for (int j = 0; j < m; j++)
        {
            teste[cont] = matriz[j][i];
            cont++;
        }
        teste[cont] = '\0';
        if (strcmp(teste, vitoriaPlayer1) == 0) // Caso em que o player 1 ganha
        {
            return 1;
        }
        else if (strcmp(teste, vitoriaPlayer2) == 0) // Caso em que o player 2 ganha
        {
            return 2;
        }
    }

    // Verificação da diagonal principal
    cont = 0;
    for (int i = 0; i < n; i++)
    {
        teste[cont] = matriz[i][i];
        cont++;
    }
    teste[cont] = '\0';
    if (strcmp(teste, vitoriaPlayer1) == 0) // Caso em que o player 1 ganha
    {
        return 1;
    }
    else if (strcmp(teste, vitoriaPlayer2) == 0) // Caso em que o player 2 ganha
    {
        return 2;
    }

    // Verificação da diagonal secundaria
    cont = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        teste[cont] = matriz[cont][i];
        cont++;
    }
    teste[cont] = '\0';

    if (strcmp(teste, vitoriaPlayer1) == 0) // Caso em que o player 1 ganha
    {
        return 1;
    }
    else if (strcmp(teste, vitoriaPlayer2) == 0) // Caso em que o player 2 ganha
    {
        return 2;
    }

    return 0;
}

void copiaVetorStruct(Jogador *copiado, Jogador *copia, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        copia[i] = copiado[i];
    }
}

int validaNomePlayer1(char *nomePlayer1) // Validação do nome do player 1
{
    if (strcmp(nomePlayer1, "Computador") == 0 || strcmp(nomePlayer1, "computador") == 0) // Condição em que o nome é igual ao "Computador"
    {
        printf(RED("\nErro - O nome do jogador 1 é um nome reservado ao Computador\n\n"));
        return 0;
    }

    if (strcmp(nomePlayer1, " ") == 0) // O nome é um espaço
    {
        printf(RED("\nERRO - O nome do jogador 1 não pode ser um espaço\n\n"));
        return 0;
    }

    int tamanhoNomePlayer1 = (int)strlen(nomePlayer1);

    if (tamanhoNomePlayer1 == 0) // Condição em que o usuário apenas aperta enter e não informa um nome
    {
        printf(RED("\nErro - Insira um nome válido com um ou mais de um caractere, diferente de um espaço, para o jogador 1\n\n"));
        return 0;
    }

    return 1;
}

int validaNomePlayer2(char *nomePlayer1, char *nomePlayer2) // Validação do nome do player 2
{
    if (strcmp(nomePlayer1, nomePlayer2) == 0) // Condição em que um mesmo nome é inserido duas vezes
    {
        printf(RED("\nErro - O nome do jogador 2 é igual ao nome do jogador 1\n\n"));
        return 0;
    }

    if (strcmp(nomePlayer2, "Computador") == 0 || strcmp(nomePlayer2, "computador") == 0) // Condição em que o nome é igual ao "Computador"
    {
        printf(RED("\nErro - O nome do jogador 2 é um nome reservado ao Computador\n\n"));
        return 0;
    }

    if (strcmp(nomePlayer2, " ") == 0) // O nome é um espaço
    {
        printf(RED("\nERRO - O nome do jogador 2 não pode ser um espaço\n\n"));
        return 0;
    }

    int tamanhoNomePlayer2 = (int)strlen(nomePlayer2);

    if (tamanhoNomePlayer2 == 0) // Condição em que o usuário apenas aperta um enter e não informa o nome
    {
        printf(RED("\nErro - Insira um nome válido com um ou mais de um caractere para o jogador 2\n\n"));
        return 0;
    }

    return 1;
}

int validaNJogadoresRodada(char *comandoNJogadores, char *nJogadoresRodada)
{
    int tamanhoComando = strlen(comandoNJogadores);
    if (tamanhoComando == 1)
    {
        *nJogadoresRodada = comandoNJogadores[0];
        return 1;
    }
    else
    {
        printf(RED("\nErro - Número de jogadores inválido\n\n"));
        return 0;
    }
}

int validaOp(char *comandoOp, char *op)
{
    int tamanhoComando = strlen(comandoOp);
    char comandoTamanhoCorreto;

    if (tamanhoComando == 1)
    {
        *op = comandoOp[0];
    }
    else
    {
        printf(RED("\nErro - Opção inválida\n\n"));
        return 0;
    }
}

int salvarJogo(char **matriz, int nJogadores, Jogador *jogadoresTemp, int contRodada, char *parametroDoComandoPrincipal)
{
    FILE *arquivo = fopen(parametroDoComandoPrincipal, "w");

    // Numero de jogadores e nome dos jogadores
    if (nJogadores == 2)
    {
        fprintf(arquivo, "%d\n", 2);
        fprintf(arquivo, "%s\n", jogadoresTemp[0].nome);
        fprintf(arquivo, "%s\n", jogadoresTemp[1].nome);
    }
    else
    {
        fprintf(arquivo, "%d\n", 1);
        fprintf(arquivo, "%s\n", jogadoresTemp[0].nome);
    }

    // Matriz
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fprintf(arquivo, "%c ", matriz[i][j]);
        }

        fprintf(arquivo, "\n");
    }

    // Ultimo player que jogou
    if (contRodada % 2 != 0) // Se está na vez do player 1 é porque o últio a jogar foi o player 2 e vice-versa
    {
        fprintf(arquivo, "%d", 2);
    }
    else
    {
        fprintf(arquivo, "%d", 1);
    }

    fclose(arquivo);
}

int jogoMultiplayer(char **matriz, Jogador *jogadoresTemp, Jogador *jogadores, int posicaoPlayer1, int posicaoPlayer2, int contRodada, int nJogadores, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual, int nJogadoresTotal)
{
    int vitoria = 0; // Variável que determinará se houve vitória ou não
    int empate = 0;  // Variável que determinará se houve empate ou não
    int coordenadaLinha, coordenadaColuna;

    while (!vitoria && !empate) // O jogo roda enquanto não houver vitoria ou empate
    {

        char comandoGeral[64], comandoPrincipal[6], parametroDoComandoPrincipal[64];

        if (contRodada % 2 != 0) // Vez do player 1
        {
            printf(BLUE("%s, digite o comando: "), jogadoresTemp[0].nome);
            fgets(comandoGeral, 64, stdin);
            captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);

            if (validaComando(comandoPrincipal, parametroDoComandoPrincipal, comandoGeral, jogadoresTemp, 0) && (validaParametroDoMarcar(parametroDoComandoPrincipal, &coordenadaLinha, &coordenadaColuna, comandoPrincipal, matriz) || validaParametroDoSalvar(parametroDoComandoPrincipal, comandoPrincipal) || validaParametroDoVoltar(parametroDoComandoPrincipal, comandoPrincipal))) // Valida comando principal - marcar, voltar e salvar
            {
                if (strcmp(comandoPrincipal, "marcar") == 0) // Comando marcar
                {
                    marcarPosicao(&matriz, coordenadaLinha, coordenadaColuna, contRodada);
                    imprimeMatriz(matriz, 3, 3);
                    contRodada++; // Incrementa a rodada
                }
                else if (strcmp(comandoPrincipal, "voltar") == 0) // Comando voltar
                {
                    if (contRodada == 1) // Salva todos os dados do jogo na primeira rodada do game, caso os mesmos sejam requisitados na opção 3 do menu para carregar o jogo
                    {

                        copiaMatriz(matrizJogoAtual, matriz);
                        for (int i = 0; i < 2; i++)
                        {
                            jogadoresTempJogoAtual[i] = jogadoresTemp[i];
                        }
                        *posicaoPlayer1JogoAtual = posicaoPlayer1;
                        *posicaoPlayer2JogoAtual = posicaoPlayer2;
                        *contRodadaJogoAtual = contRodada;
                        *nJogadoresJogoAtual = nJogadores;
                        *posicaoPlayer2JogoAtual = posicaoPlayer2;
                    }
                    break; // Volta ao menu
                }
                else if (strcmp(comandoPrincipal, "salvar") == 0) // Comando salvar
                {
                    salvarJogo(matriz, nJogadores, jogadoresTemp, contRodada, parametroDoComandoPrincipal);
                    printf(BOLD(GREEN("\nArquivo \"%s\" salvo com sucesso!\n")) "\n", parametroDoComandoPrincipal);
                }
            }
        }
        else // Vez do player 2
        {
            if (strcmp(jogadoresTemp[1].nome, "Computador") == 0) // Jogador contra o BOT
            {
                botJogador(matriz, &coordenadaLinha, &coordenadaColuna, contRodada);
                marcarPosicao(&matriz, coordenadaLinha, coordenadaColuna, contRodada);
                contRodada++;
                imprimeMatriz(matriz, 3, 3);
            }
            else // Jogador contra outro Jogador
            {

                printf(GREEN("%s, digite o comando: "), jogadoresTemp[1].nome);
                fgets(comandoGeral, 64, stdin);
                captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);

                if (validaComando(comandoPrincipal, parametroDoComandoPrincipal, comandoGeral, jogadoresTemp, 1) && (validaParametroDoMarcar(parametroDoComandoPrincipal, &coordenadaLinha, &coordenadaColuna, comandoPrincipal, matriz) || validaParametroDoSalvar(parametroDoComandoPrincipal, comandoPrincipal) || validaParametroDoVoltar(parametroDoComandoPrincipal, comandoPrincipal))) // Valida comando principal - marcar, voltar e salvar
                {
                    if (strcmp(comandoPrincipal, "marcar") == 0) // Comando marcar
                    {
                        marcarPosicao(&matriz, coordenadaLinha, coordenadaColuna, contRodada); // Marca a posição na matriz, cuja a validação da disponibilidade foi feita no if anterior
                        imprimeMatriz(matriz, 3, 3);
                        contRodada++; // Incrementa a rodada
                    }
                    else if (strcmp(comandoPrincipal, "voltar") == 0) // Comando voltar
                    {
                        break; // Volta ao menu
                    }
                    else if (strcmp(comandoPrincipal, "salvar") == 0) // Comando salvar
                    {
                        salvarJogo(matriz, nJogadores, jogadoresTemp, contRodada, parametroDoComandoPrincipal);
                        printf(BOLD(GREEN("\nArquivo \"%s\" salvo com sucesso!\n")) "\n", parametroDoComandoPrincipal);
                    }
                }
            }
        }
        // Verifica se alguém ganhou ou se deu empate
        if (verificaVitoria(matriz, 3, 3) == 1) // Vitória do player 1
        {
            printf(BLUE("Parabens, %s ! Você ganhou a rodada!\n"), jogadores[posicaoPlayer1].nome);
            printVitoriaP1();
            jogadores[posicaoPlayer1].vitorias++; // Incrementa o número de vitórias do player
            jogadores[posicaoPlayer2].derrotas++;
            vitoria = 1;
            *posicaoPlayer2JogoAtual = -1;               // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu
            atualizaRanking(jogadores, nJogadoresTotal); // Atualiza o ranking ao final da rodada

            exibePosicaoRanking(jogadores, jogadoresTemp[0].nome, nJogadoresTotal);
            exibePosicaoRanking(jogadores, jogadoresTemp[1].nome, nJogadoresTotal);

            printf("\n\n");

            atualizaRanking(jogadores, nJogadoresTotal);

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();
            break;
        }
        else if (verificaVitoria(matriz, 3, 3) == 2) // Vitória do player 2
        {
            if (strcmp(jogadores[posicaoPlayer2].nome, "Computador") == 0)
            {
                printVitoriaBot();
            }
            else
            {
                printf(GREEN("Parabens, %s ! Você ganhou a rodada!\n"), jogadores[posicaoPlayer2].nome);
                printVitoriaP2();
            }
            jogadores[posicaoPlayer2].vitorias++;
            jogadores[posicaoPlayer1].derrotas++;
            vitoria = 1;
            *posicaoPlayer2JogoAtual = -1;               // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu
            atualizaRanking(jogadores, nJogadoresTotal); // Atualiza o ranking ao final da rodada

            exibePosicaoRanking(jogadores, jogadoresTemp[0].nome, nJogadoresTotal);
            exibePosicaoRanking(jogadores, jogadoresTemp[1].nome, nJogadoresTotal);

            atualizaRanking(jogadores, nJogadoresTotal);

            printf("\n\n");

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();
            break;
        }
        else if (verificaVitoria(matriz, 3, 3) == 0 && contRodada == 10) // Jogo deu velha
        {
            printf(MAGENTA("O game deu velha! Ambos empataram!\n\n"));
            printEmpate();
            jogadores[posicaoPlayer1].empates++;
            jogadores[posicaoPlayer2].empates++;
            empate = 1;
            *posicaoPlayer2JogoAtual = -1;               // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu
            atualizaRanking(jogadores, nJogadoresTotal); // Atualiza o ranking ao final da rodada

            exibePosicaoRanking(jogadores, jogadoresTemp[0].nome, nJogadoresTotal);
            exibePosicaoRanking(jogadores, jogadoresTemp[1].nome, nJogadoresTotal);

            printf("\n\n");

            atualizaRanking(jogadores, nJogadoresTotal);

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();
            break;
        }

        // Salva todos os dados do jogo, caso ele seja recarregado na opção 3 do menu
        copiaMatriz(matrizJogoAtual, matriz);
        // Copiando o vetor jogadoresTemp
        for (int i = 0; i < 2; i++)
        {
            jogadoresTempJogoAtual[i] = jogadoresTemp[i];
        }
        *posicaoPlayer1JogoAtual = posicaoPlayer1;
        *posicaoPlayer2JogoAtual = posicaoPlayer2;
        *contRodadaJogoAtual = contRodada;
        *nJogadoresJogoAtual = nJogadores;
    }

    return 0;
}

int jogoMultiplayerArquivoIniNovo(char **matriz, Jogador *jogadoresNovoIni, int contRodadaNew, int nJogadoresNovos, char ***matrizJogoAtual, Jogador *jogadoresTempJogoAtual, int *posicaoPlayer1JogoAtual, int *posicaoPlayer2JogoAtual, int *contRodadaJogoAtual, int *nJogadoresJogoAtual)
{
    int vitoriaNew = 0;
    int empateNew = 0;
    int coordenadaLinhaNew, coordenadaColunaNew;

    while (!vitoriaNew && !empateNew) // O jogo roda enquanto não houver vitoria ou empate
    {
        char comandoGeral[64], comandoPrincipal[6], parametroDoComandoPrincipal[64];

        if (contRodadaNew % 2 != 0) // Vez do player 1
        {
            printf(BLUE("%s, digite o comando: "), jogadoresNovoIni[0].nome);
            fgets(comandoGeral, 64, stdin);
            captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);

            if (validaComando(comandoPrincipal, parametroDoComandoPrincipal, comandoGeral, jogadoresNovoIni, 0) && (validaParametroDoMarcar(parametroDoComandoPrincipal, &coordenadaLinhaNew, &coordenadaColunaNew, comandoPrincipal, matriz) || validaParametroDoSalvar(parametroDoComandoPrincipal, comandoPrincipal) || validaParametroDoVoltar(parametroDoComandoPrincipal, comandoPrincipal))) // Valida comando principal - marcar, voltar e salvar
            {
                if (strcmp(comandoPrincipal, "marcar") == 0) // Comando marcar
                {
                    marcarPosicao(&matriz, coordenadaLinhaNew, coordenadaColunaNew, contRodadaNew);
                    imprimeMatriz(matriz, 3, 3);
                    contRodadaNew++; // Incrementa a rodada
                }
                else if (strcmp(comandoPrincipal, "voltar") == 0) // Comando voltar
                {
                    if (contRodadaNew == 1) // Salva todos os dados do jogo na primeira rodada do game, caso os mesmos sejam requisitados na opção 3 do menu para carregar o jogo
                    {

                        copiaMatriz(matrizJogoAtual, matriz);
                        for (int i = 0; i < 2; i++)
                        {
                            jogadoresTempJogoAtual[i] = jogadoresNovoIni[i];
                        }
                        *posicaoPlayer1JogoAtual = 0;
                        *posicaoPlayer2JogoAtual = 1;
                        *contRodadaJogoAtual = contRodadaNew;
                        *nJogadoresJogoAtual = nJogadoresNovos;
                    }
                    break; // Volta ao menu
                }
                else if (strcmp(comandoPrincipal, "salvar") == 0) // Comando salvar
                {
                    salvarJogo(matriz, nJogadoresNovos, jogadoresNovoIni, contRodadaNew, parametroDoComandoPrincipal);
                    printf(BOLD(GREEN("\nArquivo \"%s\" salvo com sucesso!\n")) "\n", parametroDoComandoPrincipal);
                }
            }
        }
        else // Vez do player 2
        {
            if (strcmp(jogadoresNovoIni[1].nome, "Computador") == 0) // Jogador contra o BOT
            {
                botJogador(matriz, &coordenadaLinhaNew, &coordenadaColunaNew, contRodadaNew);
                marcarPosicao(&matriz, coordenadaLinhaNew, coordenadaColunaNew, contRodadaNew);
                contRodadaNew++;
                imprimeMatriz(matriz, 3, 3);
            }
            else // Jogador contra jogador
            {

                printf(GREEN("%s, digite o comando: "), jogadoresNovoIni[1].nome);
                fgets(comandoGeral, 64, stdin);
                captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);

                if (validaComando(comandoPrincipal, parametroDoComandoPrincipal, comandoGeral, jogadoresNovoIni, 1) && (validaParametroDoMarcar(parametroDoComandoPrincipal, &coordenadaLinhaNew, &coordenadaColunaNew, comandoPrincipal, matriz) || validaParametroDoSalvar(parametroDoComandoPrincipal, comandoPrincipal) || validaParametroDoVoltar(parametroDoComandoPrincipal, comandoPrincipal))) // Valida comando principal - marcar, voltar e salvar
                {
                    if (strcmp(comandoPrincipal, "marcar") == 0) // Comando marcar
                    {
                        marcarPosicao(&matriz, coordenadaLinhaNew, coordenadaColunaNew, contRodadaNew); // Marca a posição na matriz, cuja a validação da disponibilidade foi feita no if anterior
                        imprimeMatriz(matriz, 3, 3);
                        contRodadaNew++; // Incrementa a rodada
                    }
                    else if (strcmp(comandoPrincipal, "voltar") == 0) // Comando voltar
                    {
                        break; // Volta ao menu
                    }
                    else if (strcmp(comandoPrincipal, "salvar") == 0) // Comando salvar
                    {
                        salvarJogo(matriz, nJogadoresNovos, jogadoresNovoIni, contRodadaNew, parametroDoComandoPrincipal);
                        printf(BOLD(GREEN("\nArquivo \"%s\" salvo com sucesso!\n")) "\n", parametroDoComandoPrincipal);
                    }
                }
            }
        }
        // Verifica se alguém ganhou ou se deu empate
        if (verificaVitoria(matriz, 3, 3) == 1) // Vitória do player 1
        {
            printf(BLUE("Parabens, %s ! Você ganhou a rodada!\n"), jogadoresNovoIni[0].nome);
            printVitoriaP1();
            jogadoresNovoIni[0].vitorias++; // Incrementa o número de vitórias do player
            jogadoresNovoIni[1].derrotas++;
            vitoriaNew = 1;
            *posicaoPlayer2JogoAtual = -1; // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu

            // Grava as informações que serão captadas pelo vetor principal quando verificar a existência do arquivo novamente
            FILE *arquivoIni = fopen("velha.ini", "w");
            fprintf(arquivoIni, "%d\n", nJogadoresNovos);
            for (int i = 0; i < 2; i++)
            {
                fprintf(arquivoIni, "%s\n", jogadoresNovoIni[i].nome);
                fprintf(arquivoIni, "%d %d %d\n", jogadoresNovoIni[i].vitorias, jogadoresNovoIni[i].empates, jogadoresNovoIni[i].derrotas);
            }
            fclose(arquivoIni);

            atualizaRanking(jogadoresNovoIni, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[0].nome, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[1].nome, nJogadoresNovos);
            printf("\n\n");

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();

            break;
        }
        else if (verificaVitoria(matriz, 3, 3) == 2) // Vitória do player 2
        {
            if (strcmp(jogadoresNovoIni[1].nome, "Computador") == 0)
            {
                printVitoriaBot();
            }
            else
            {
                printf(GREEN("Parabens, %s ! Você ganhou a rodada!\n"), jogadoresNovoIni[1].nome);
                printVitoriaP2();
            }
            jogadoresNovoIni[1].vitorias++;
            jogadoresNovoIni[0].derrotas++;
            vitoriaNew = 1;
            *posicaoPlayer2JogoAtual = -1; // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu

            // Grava as informações que serão captadas pelo vetor principal quando verificar a existência do arquivo novamente
            FILE *arquivoIni = fopen("velha.ini", "w");
            fprintf(arquivoIni, "%d\n", nJogadoresNovos);
            for (int i = 0; i < 2; i++)
            {
                fprintf(arquivoIni, "%s\n", jogadoresNovoIni[i].nome);
                fprintf(arquivoIni, "%d %d %d\n", jogadoresNovoIni[i].vitorias, jogadoresNovoIni[i].empates, jogadoresNovoIni[i].derrotas);
            }
            fclose(arquivoIni);

            atualizaRanking(jogadoresNovoIni, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[0].nome, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[1].nome, nJogadoresNovos);
            printf("\n\n");

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();
            break;
        }
        else if (verificaVitoria(matriz, 3, 3) == 0 && contRodadaNew == 10) // Jogo deu velha
        {
            printf(MAGENTA("O game deu velha! Ambos empataram!\n\n"));
            printEmpate();
            jogadoresNovoIni[0].empates++;
            jogadoresNovoIni[1].empates++;
            empateNew = 1;
            *posicaoPlayer2JogoAtual = -1; // Volta a variável para que o jogo finalizado não seja carregado na opção 3 do menu

            // Grava as informações que serão captadas pelo vetor principal quando verificar a existência do arquivo novamente
            FILE *arquivoIni = fopen("velha.ini", "w");
            fprintf(arquivoIni, "%d\n", nJogadoresNovos);
            for (int i = 0; i < 2; i++)
            {
                fprintf(arquivoIni, "%s\n", jogadoresNovoIni[i].nome);
                fprintf(arquivoIni, "%d %d %d\n", jogadoresNovoIni[i].vitorias, jogadoresNovoIni[i].empates, jogadoresNovoIni[i].derrotas);
            }
            fclose(arquivoIni);

            atualizaRanking(jogadoresNovoIni, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[0].nome, nJogadoresNovos);
            exibePosicaoRanking(jogadoresNovoIni, jogadoresNovoIni[1].nome, nJogadoresNovos);
            printf("\n\n");

            printf("Digite qualquer tecla para continuar!");
            capturaTecla();
            break;
        }
        // Salva todos os dados do jogo, caso ele seja recarregado na opção 3 do menu
        copiaMatriz(matrizJogoAtual, matriz);
        // Copiando o vetor jogadoresTemp
        for (int i = 0; i < 2; i++)
        {
            jogadoresTempJogoAtual[i] = jogadoresNovoIni[i];
        }
        *posicaoPlayer1JogoAtual = 0;
        *posicaoPlayer2JogoAtual = 1;
        *contRodadaJogoAtual = contRodadaNew;
        *nJogadoresJogoAtual = nJogadoresNovos;
    }
}

void printVitoriaP1()
{
    printf("\n🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈\n\n");
    printf(BLUE("██╗   ██╗██╗████████╗ ██████╗ ██████╗ ██╗ █████╗     ██████╗  ██████╗     ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      ██╗") "\n");
    printf(BLUE("██║   ██║██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗    ██╔══██╗██╔═══██╗    ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ███║") "\n");
    printf(BLUE("██║   ██║██║   ██║   ██║   ██║██████╔╝██║███████║    ██║  ██║██║   ██║    ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝    ╚██║") "\n");
    printf(BLUE("╚██╗ ██╔╝██║   ██║   ██║   ██║██╔══██╗██║██╔══██║    ██║  ██║██║   ██║    ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║") "\n");
    printf(BLUE(" ╚████╔╝ ██║   ██║   ╚██████╔╝██║  ██║██║██║  ██║    ██████╔╝╚██████╔╝    ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ██║") "\n");
    printf(BLUE("  ╚═══╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝     ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     ╚═╝") "\n\n");
    printf("🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 \n\n");
}
void printVitoriaP2()
{
    printf("\n🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈\n\n");
    printf(GREEN("██╗   ██╗██╗████████╗ ██████╗ ██████╗ ██╗ █████╗     ██████╗  ██████╗     ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗ ") "\n");
    printf(GREEN("██║   ██║██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗    ██╔══██╗██╔═══██╗    ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗") "\n");
    printf(GREEN("██║   ██║██║   ██║   ██║   ██║██████╔╝██║███████║    ██║  ██║██║   ██║    ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝") "\n");
    printf(GREEN("╚██╗ ██╔╝██║   ██║   ██║   ██║██╔══██╗██║██╔══██║    ██║  ██║██║   ██║    ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗    ██╔═══╝ ") "\n");
    printf(GREEN(" ╚████╔╝ ██║   ██║   ╚██████╔╝██║  ██║██║██║  ██║    ██████╔╝╚██████╔╝    ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ███████╗") "\n");
    printf(GREEN("  ╚═══╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝     ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚══════╝") "\n");
    printf("\n🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈 🎉🥳🪅🎈\n\n");
}
void printEmpate()
{
    printf("❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎\n\n");
    printf(YELLOW("███████╗███╗   ███╗██████╗  █████╗ ████████╗███████╗██╗") "\n");
    printf(YELLOW("██╔════╝████╗ ████║██╔══██╗██╔══██╗╚══██╔══╝██╔════╝██║") "\n");
    printf(YELLOW("█████╗  ██╔████╔██║██████╔╝███████║   ██║   █████╗  ██║") "\n");
    printf(YELLOW("██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══██║   ██║   ██╔══╝  ╚═╝") "\n");
    printf(YELLOW("███████╗██║ ╚═╝ ██║██║     ██║  ██║   ██║   ███████╗██╗") "\n");
    printf(YELLOW("╚══════╝╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝") "\n");
    printf("❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎ ❎❎❎❎\n\n");
}

void printVitoriaBot()
{
    printf("\n🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 \n\n");
    printf(GREEN("██╗   ██╗██╗████████╗ ██████╗ ██████╗ ██╗ █████╗     ██████╗  ██████╗     ██████╗  ██████╗ ████████") "\n");
    printf(GREEN("██║   ██║██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗    ██╔══██╗██╔═══██╗    ██╔══██╗██╔═══██╗╚══██╔══╝") "\n");
    printf(GREEN("██║   ██║██║   ██║   ██║   ██║██████╔╝██║███████║    ██║  ██║██║   ██║    ██████╔╝██║   ██║   ██║   ") "\n");
    printf(GREEN("╚██╗ ██╔╝██║   ██║   ██║   ██║██╔══██╗██║██╔══██║    ██║  ██║██║   ██║    ██╔══██╗██║   ██║   ██║   ") "\n");
    printf(GREEN(" ╚████╔╝ ██║   ██║   ╚██████╔╝██║  ██║██║██║  ██║    ██████╔╝╚██████╔╝    ██████╔╝╚██████╔╝   ██║   ") "\n");
    printf(GREEN("  ╚═══╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝     ╚═════╝  ╚═════╝    ╚═╝   ") "\n");
    printf("\n🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 🤖🤖🤖🤖 \n\n");
}

void copiaMatriz(char ***A, char **B)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (*A)[i][j] = B[i][j];
        }
    }
}

int exibePosicaoRanking(Jogador *jogadores, char *nome, int nJogadores) // Compara o nome do jogador com os do vetor da struct para a obtenção da posição / Soma-se um porque inicia-se do 0
{
    int posicao = -1;

    for (int i = 0; i < nJogadores; i++)
    {
        if (strcmp(jogadores[i].nome, nome) == 0)
        {
            posicao = i + 1;
        }
    }

    printf(YELLOW("O jogador %s está na posição %d no ranking\n"), nome, posicao);
    return 0;
}

int validaNomeArquivo(char *nomeArquivo)
{
    if (verificaArquivoExistente(nomeArquivo))
    {
        FILE *arquivo = fopen(nomeArquivo, "r");
        int teste;
        if (fscanf(arquivo, "%d\n", &teste)) // Verifica o primeiro número do arquivo se é um int
        {
            if (teste == 1 || teste == 2) // Valor inválido
            {
                fclose(arquivo);
                return 1;
            }
            else
            {
                fclose(arquivo);
                printf(RED("\nErro - Arquivo existe mas não apresenta o formato desejado\n\n"));
                return 0;
            }
        }
        else
        {
            fclose(arquivo);
            printf(RED("Erro - Arquivo inválido\n\n"));
        }
    }
    else
    {
        printf(RED("\nErro - O arquivo não existe\n\n"));
        return 0;
    }
}

int lerArquivo(char *nomeArquivo, char ***matrizJogoCarregado, Jogador *jogadoresTempJogoCarregado, int *contRodadaJogoCarregado, int *nJogadoresJogoCarregado)
{
    // Lendo as variáveis
    FILE *arquivo = fopen(nomeArquivo, "r");
    fscanf(arquivo, "%d\n", nJogadoresJogoCarregado);

    // Ler nome do player 1
    fgets(jogadoresTempJogoCarregado[0].nome, 64, arquivo);
    jogadoresTempJogoCarregado[0].nome[strlen(jogadoresTempJogoCarregado[0].nome) - 1] = '\0';

    if (*nJogadoresJogoCarregado == 2) // 2 players no arquivo
    {
        fgets(jogadoresTempJogoCarregado[1].nome, 64, arquivo);
        jogadoresTempJogoCarregado[1].nome[strlen(jogadoresTempJogoCarregado[1].nome) - 1] = '\0';
    }
    else // Caso em que é 1 player
    {
        strcpy(jogadoresTempJogoCarregado[1].nome, "Computador");
    }

    // Ler matriz
    int contElementosMatriz = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char elemento;
            fscanf(arquivo, "%c ", &elemento);
            if (elemento == 'X' || elemento == 'O')
            {
                contElementosMatriz++;
            }
            (*matrizJogoCarregado)[i][j] = elemento;
        }
        fscanf(arquivo, "\n");
    }

    *contRodadaJogoCarregado = contElementosMatriz + 1;
    return 0;
}

int verificaNomeNoVetorPrincipal(Jogador *jogadores, char *nomePlayer, int nJogadores)
{
    for (int i = 0; i < nJogadores; i++)
    {
        if (strcmp(jogadores[i].nome, nomePlayer) == 0)
        {
            return i;
        }
    }

    return -1;
}

int atualizaRanking(Jogador *jogadores, int nJogadores)
{
    Jogador aux;
    // Ordenando em ordem crescente por vitórias
    for (int i = 0; i < nJogadores; i++)
    {
        for (int j = 0; j < nJogadores; j++)
        {
            if (jogadores[i].vitorias > jogadores[j].vitorias)
            {
                aux = jogadores[j];
                jogadores[j] = jogadores[i];
                jogadores[i] = aux;
            }
        }
    }

    // Ordenando levando em consideração o numero de empates como segundo critério
    for (int i = 0; i < nJogadores; i++)
    {
        for (int j = 0; j < nJogadores; j++)
        {
            if ((jogadores[i].vitorias == jogadores[j].vitorias) && (jogadores[i].empates > jogadores[j].empates))
            {
                aux = jogadores[j];
                jogadores[j] = jogadores[i];
                jogadores[i] = aux;
            }
        }
    }

    // ordenando levando em consideração o numero de derrotas como terceiro criterio
    for (int i = 0; i < nJogadores; i++)
    {
        for (int j = 0; j < nJogadores; j++)
        {
            if ((jogadores[i].vitorias == jogadores[j].vitorias) && (jogadores[i].empates == jogadores[j].empates) && (jogadores[i].derrotas < jogadores[j].derrotas))
            {
                aux = jogadores[j];
                jogadores[j] = jogadores[i];
                jogadores[i] = aux;
            }
        }
    }

    return 0;
}

void exibeRanking(Jogador *jogadores, int nJogadores)
{
    atualizaRanking(jogadores, nJogadores);
    printf(BG_CYAN(BOLD(" .:RANKING:. ")) "\n");
    printf(RED(TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n"));
    printf(RED(TAB_VER));
    printf(BLUE("POSIÇÃO\t\t\t\t     NOME\t\tVITÓRIAS\tEMPATES\t\tDERROTAS"));
    printf(RED("   " TAB_VER "\n"));

    

    for (int i = 0; i < nJogadores; i++) // Imprime
    {
        printf(RED(TAB_VER));
        printf(GREEN("%5d%45s\t\t   %3d\t\t %3d\t\t%7d "), i + 1, jogadores[i].nome, jogadores[i].vitorias, jogadores[i].empates, jogadores[i].derrotas);
        printf(RED("   " TAB_VER "\n"));
    }
    printf(RED(TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_BR "\n"));
}

void atualizaIni(Jogador *jogadores, int nJogadores)
{
    atualizaRanking(jogadores, nJogadores);

    if (nJogadores <= 10) // 10 ou menos player no vetor
    {
        FILE *arquivo = fopen("velha.ini", "w");
        fprintf(arquivo, "%d\n", nJogadores);
        for (int i = 0; i < nJogadores; i++)
        {
            fprintf(arquivo, "%s\n", jogadores[i].nome);
            fprintf(arquivo, "%d %d %d\n", jogadores[i].vitorias, jogadores[i].empates, jogadores[i].derrotas);
        }

        fclose(arquivo);
    }
    else
    {
        // Forçar computador no top 10
        int indiceComputador = -1;
        for (int i = 0; i < nJogadores; i++)
        {
            if (strcmp(jogadores[i].nome, "Computador") == 0)
            {
                indiceComputador = i;
            }
        }

        if (indiceComputador > 9)
        {
            jogadores[9] = jogadores[indiceComputador];
        }

        FILE *arquivo = fopen("velha.ini", "w");
        // Atualiza arquivo
        int tamanho = 10;
        fprintf(arquivo, "%d\n", tamanho);
        for (int i = 0; i < tamanho; i++)
        {
            fprintf(arquivo, "%s\n", jogadores[i].nome);
            fprintf(arquivo, "%d %d %d\n", jogadores[i].vitorias, jogadores[i].empates, jogadores[i].derrotas);
        }

        fclose(arquivo);
    }
}

int botJogador(char **matriz, int *coordenadaLinha, int *coordenadaColuna, int contRodada)
{
    // Prioridade máxima do bot - Ganhar a rodada

    // Linha 1
    if (matriz[0][0] == 'O')
    {
        if (matriz[0][1] == 'O' && matriz[0][2] == '-')
        {
            *coordenadaLinha = 1;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[0][2] == 'O' && matriz[0][1] == '-')
        {
            *coordenadaLinha = 1;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[0][1] == 'O' && matriz[0][2] == 'O' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Linha 2
    if (matriz[1][0] == 'O')
    {
        if (matriz[1][1] == 'O' && matriz[1][2] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[1][2] == 'O' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'O' && matriz[1][2] == 'O' && matriz[1][0] == '-')
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 1;
        return 0;
    }

    // Linha 3
    if (matriz[2][0] == 'O')
    {
        if (matriz[2][1] == 'O' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'O' && matriz[2][1] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[2][1] == 'O' && matriz[2][2] == 'O' && matriz[2][0] == '-')
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 1;
        return 0;
    }

    // Coluna 1
    if (matriz[0][0] == 'O')
    {
        if (matriz[1][0] == 'O' && matriz[2][0] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 1;
            return 0;
        }
        else if (matriz[2][0] == 'O' && matriz[1][0] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 1;
            return 0;
        }
    }

    if (matriz[1][0] == 'O' && matriz[2][0] == 'O' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Coluna 2
    if (matriz[0][1] == 'O')
    {
        if (matriz[1][1] == 'O' && matriz[2][1] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 2;
            return 0;
        }
        else if (matriz[2][1] == 'O' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'O' && matriz[2][1] == 'O' && matriz[0][1] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 2;
        return 0;
    }

    // Coluna 3
    if (matriz[0][2] == 'O')
    {
        if (matriz[1][2] == 'O' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'O' && matriz[1][2] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 3;
            return 0;
        }
    }

    if (matriz[1][2] == 'O' && matriz[2][2] == 'O' && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    // Diagonal principal
    if (matriz[0][0] == 'O')
    {
        if (matriz[1][1] == 'O' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'O' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[2][2] == 'O' && matriz[1][1] == 'O' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Diagonal secundária
    if (matriz[0][2] == 'O')
    {
        if (matriz[1][1] == 'O' && matriz[2][0] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 1;
            return 0;
        }
        else if (matriz[2][0] == 'O' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'O' && matriz[2][0] == 'O' && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    // A segunda prioridade do bot é impedir uma vitória nítida do outro jogador, portanto, esses primeiros IFs vão atuar nesse tipo de situação
    // Linha 1
    if (matriz[0][0] == 'X')
    {
        if (matriz[0][1] == 'X' && matriz[0][2] == '-')
        {
            *coordenadaLinha = 1;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[0][2] == 'X' && matriz[0][1] == '-')
        {
            *coordenadaLinha = 1;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[0][1] == 'X' && matriz[0][2] == 'X' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Linha 2
    if (matriz[1][0] == 'X')
    {
        if (matriz[1][1] == 'X' && matriz[1][2] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[1][2] == 'X' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'X' && matriz[1][2] == 'X' && matriz[1][0] == '-')
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 1;
        return 0;
    }

    // Linha 3
    if (matriz[2][0] == 'X')
    {
        if (matriz[2][1] == 'X' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'X' && matriz[2][1] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[2][1] == 'X' && matriz[2][2] == 'X' && matriz[2][0] == '-')
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 1;
        return 0;
    }

    // Coluna 1
    if (matriz[0][0] == 'X')
    {
        if (matriz[1][0] == 'X' && matriz[2][0] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 1;
            return 0;
        }
        else if (matriz[2][0] == 'X' && matriz[1][0] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 1;
            return 0;
        }
    }

    if (matriz[1][0] == 'X' && matriz[2][0] == 'X' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Coluna 2
    if (matriz[0][1] == 'X')
    {
        if (matriz[1][1] == 'X' && matriz[2][1] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 2;
            return 0;
        }
        else if (matriz[2][1] == 'X' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'X' && matriz[2][1] == 'X' && matriz[0][1] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 2;
        return 0;
    }

    // Coluna 3
    if (matriz[0][2] == 'X')
    {
        if (matriz[1][2] == 'X' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'X' && matriz[1][2] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 3;
            return 0;
        }
    }

    if (matriz[1][2] == 'X' && matriz[2][2] == 'X' && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    // Diagonal principal
    if (matriz[0][0] == 'X')
    {
        if (matriz[1][1] == 'X' && matriz[2][2] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 3;
            return 0;
        }
        else if (matriz[2][2] == 'X' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'X' && matriz[2][2] == 'X' && matriz[0][0] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Diagonal secundária
    if (matriz[0][2] == 'X')
    {
        if (matriz[1][1] == 'X' && matriz[2][0] == '-')
        {
            *coordenadaLinha = 3;
            *coordenadaColuna = 1;
            return 0;
        }
        else if (matriz[2][0] == 'X' && matriz[1][1] == '-')
        {
            *coordenadaLinha = 2;
            *coordenadaColuna = 2;
            return 0;
        }
    }

    if (matriz[1][1] == 'X' && matriz[2][0] == 'X' && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }
    // Estratégia 1
    // Se o jogador jogar primeiro no meio, o bot jogara em um canto([0][0]), destinando o jogo a dar velha, impedindo a vitória do adversário
    if (matriz[1][1] == 'X' && contRodada == 2)
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    // Se o usuário jogar no canto [2][0] ou no canto [2][2], o bot joga no canto [0][2], impedindo-o de tomar um x
    if (matriz[1][1] == 'X' && contRodada == 4 && matriz[0][2] == '-' && (matriz[2][0] == 'X' || matriz[2][2] == 'X'))
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    // Estratégia 2
    // Se o jogador jogar no canto, o bot jogará no meio
    if (matriz[0][0] == 'X' && contRodada == 2)
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 2;
        return 0;
    }

    if (matriz[2][0] == 'X' && contRodada == 2)
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 2;
        return 0;
    }

    if (matriz[2][2] == 'X' && contRodada == 2)
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 2;
        return 0;
    }

    if (matriz[0][2] == 'X' && contRodada == 2)
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 2;
        return 0;
    }

    // Usuário faz a segunda jogada em um canto
    // A segunda jogada do bot irá em uma borda
    if (matriz[0][2] == 'X' && contRodada == 4 && matriz[1][2] == '-' && (matriz[0][0] == 'X' || matriz[2][0] == 'X' || matriz[2][2] == 'X'))
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 3;
        return 0;
    }

    if (matriz[0][0] == 'X' && contRodada == 4 && matriz[1][0] == '-' && (matriz[2][0] == 'X' || matriz[2][2] == 'X' || matriz[0][2] == 'X'))
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 1;
        return 0;
    }

    if (matriz[2][0] == 'X' && contRodada == 4 && matriz[1][0] == '-' && (matriz[0][0] == 'X' || matriz[2][2] == 'X' || matriz[0][2] == 'X'))
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 1;
        return 0;
    }

    if (matriz[2][2] == 'X' && contRodada == 4 && matriz[1][2] == '-' && (matriz[0][0] == 'X' || matriz[2][0] == 'X' || matriz[0][2] == 'X'))
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 3;
        return 0;
    }

    // Usuário faz a segunda jogada em uma borda longe do primeiro X
    // BOT joga no canto para bloquear o susuário
    if (matriz[0][0] == 'X' && contRodada == 4 && matriz[2][2] == '-' && (matriz[2][1] == 'X' || matriz[1][2] == 'X'))
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 3;
        return 0;
    }

    if (matriz[2][0] == 'X' && contRodada == 4 && matriz[0][2] == '-' && (matriz[0][1] == 'X' || matriz[1][2] == 'X'))
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    if (matriz[2][2] == 'X' && contRodada == 4 && matriz[0][0] == '-' && (matriz[0][1] == 'X' || matriz[1][0] == 'X'))
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }

    if (matriz[0][2] == 'X' && contRodada == 4 && matriz[2][0] == '-' && (matriz[1][0] == 'X' || matriz[2][1] == 'X'))
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 1;
        return 0;
    }

    // Estratégia 3
    // Usuário começa jogando pelas bordas e o BOT joga no meio
    if ((matriz[1][0] == 'X' || matriz[0][1] == 'X' || matriz[1][2] == 'X' || matriz[2][1] == 'X') && contRodada == 2)
    {
        *coordenadaLinha = 2;
        *coordenadaColuna = 2;
        return 0;
    }
    // Usuário forma uma linha ou coluna no formato XOX e o bot jogará no canto [0][0] do tabuleiro
    if ((matriz[1][0] == 'X' && matriz[1][2] == 'X' && contRodada == 4) || (matriz[0][1] == 'X' && matriz[2][1] == 'X' && contRodada == 4))
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 1;
        return 0;
    }
    // Agora o objetivo do BOT é aplicar um "V" contra o usuário, permitinddo duas possibilidades de vitória
    if (matriz[1][0] == 'X' && matriz[1][2] == 'X' && contRodada == 6 && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    if (matriz[1][0] == 'X' && matriz[1][2] == 'X' && contRodada == 6 && matriz[2][0] == '-')
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 1;
        return 0;
    }

    if (matriz[0][1] == 'X' && matriz[2][1] == 'X' && contRodada == 6 && matriz[2][0] == '-')
    {
        *coordenadaLinha = 3;
        *coordenadaColuna = 1;
        return 0;
    }

    if (matriz[0][1] == 'X' && matriz[2][1] == 'X' && contRodada == 6 && matriz[0][2] == '-')
    {
        *coordenadaLinha = 1;
        *coordenadaColuna = 3;
        return 0;
    }

    // Depois da aplicação de todas as estratégias implementadas acima, o BOT jogará aleatoriamente, o que seria necessário numa penúltima ou última rodada, uma vez que, no mínimo, o empate foi assegurado pelas estratégias
    //  Jogada aleatória quando sobram duas ou uma casa, situação em que o empate já foi assegurado em rodadas anteriores
    srand(time(NULL));
    int linha1 = (int)(rand() % 3) + 1;
    int coluna1 = (int)(rand() % 3) + 1;
    while (!verificaPosicaoDisponivel(matriz, linha1, coluna1))
    {
        linha1 = (int)(rand() % 3) + 1;
        coluna1 = (int)(rand() % 3) + 1;
    }

    *coordenadaLinha = linha1;
    *coordenadaColuna = coluna1;
    return 0;
}