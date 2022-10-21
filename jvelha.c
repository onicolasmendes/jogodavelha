/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/
#include "funcoes.h"

int main(int argc, char const *argv[])
{
    // Arquivo .ini

    int unicaVez = 0;
    printNomeDoJogo();
    printf("Bora jogar um jogo da velha?\n\n");
    Jogador *jogadores = malloc(40 * sizeof(Jogador)); // Devido ao fato do uso do realloc não ser recomendado, o vetor terá 30 posições a mais do que o máximo do arquivo .ini, infelizmente, impondo tal limitação ao game
    int condArquivo;
    int nJogadores;

    // Variáveis para salvar um jogo atual que será jogado posteriormente - opção 3 do Menu
    char **matrizJogoAtual;
    matrizJogoAtual = criaMatriz(3, 3);
    Jogador *jogadoresTempJogoAtual = malloc(2 * sizeof(Jogador));
    int posicaoPlayer1JogoAtual, posicaoPlayer2JogoAtual = -1, contRodadaJogoAtual, nJogadoresJogoAtual;

    while (1)
    {

        if (verificaArquivoExistente("velha.ini"))
        {
            if (unicaVez == 0)
            {
                FILE *arquivoIni = fopen("velha.ini", "r+");

                fscanf(arquivoIni, "%d\n", &nJogadores); // Armazena o número de jogadores
                for (int i = 0; i < nJogadores; i++)     // Armazenará os dados dos jogadores no vetor de struct
                {
                    fgets(jogadores[i].nome, 64, arquivoIni);
                    jogadores[i].nome[strlen(jogadores[i].nome) - 1] = '\0'; // Removendo \n
                    fscanf(arquivoIni, "%d %d %d\n", &jogadores[i].vitorias, &jogadores[i].empates, &jogadores[i].derrotas);
                }

                fclose(arquivoIni);
            }

            unicaVez++;

            condArquivo = 1; // Variável para saber a condição do arquivo .ini; 1 caso o arquivo já exista e 0 caso o arquivo seja novo
        }
        else
        {
            FILE *arquivoIni = fopen("velha.ini", "w+"); // Cria o arquivo caso não exista
            fclose(arquivoIni);
            condArquivo = 0;
        }

        printMenu();
        printf("Escolha uma opção: ");
        char op;
        char comandoOp[128]; // lerá a linha toda do comando
        fgets(comandoOp, 128, stdin);
        comandoOp[strlen(comandoOp) - 1] = '\0';

        while (!validaOp(comandoOp, &op)) // Valida o tamanho do comando que foi passado pelo usuário referente a opção
        {
            printf("Escolha uma opção: ");
            fgets(comandoOp, 128, stdin);
            comandoOp[strlen(comandoOp) - 1] = '\0';
        }

        while (op != '0' && op != '1' && op != '2' && op != '3' && op != '4') // Valida o conteúdo propriamente dito da opção do usuário
        {
            printf("\nERRO - Opção inválida\n\n");
            printMenu();
            printf("Digite uma opção válida: ");
            scanf("%c", &op);
            limpaBuffer();
        }

        switch (op)
        {
        case '0': // Sair do jogo

            if (verificaArquivoExistente("velha.ini"))
            {
                // Atualiza .ini
                atualizaIni(jogadores, nJogadores);
            }

            return 0;
            break;

        case '1': // Começar um novo jogo
            printf("Digite o número de jogadores (1 ou 2): ");
            char nJogadoresRodada;
            char comandoNumJogadores[128]; // Vai ler a linha digitada
            fgets(comandoNumJogadores, 128, stdin);
            comandoNumJogadores[strlen(comandoNumJogadores) - 1] = '\0';

            while (!validaNJogadoresRodada(comandoNumJogadores, &nJogadoresRodada)) // Validação do tamanho do comando prar o nJogadoresRodada inserido pelo usuário
            {
                printf("Digite o número de jogadores (1 ou 2): ");
                fgets(comandoNumJogadores, 128, stdin);
                comandoNumJogadores[strlen(comandoNumJogadores) - 1] = '\0';
            }

            while (nJogadoresRodada != '1' && nJogadoresRodada != '2') // Valida o conteúdo que indica o número de jogadores
            {
                printf("Erro - Valor inválido!\nDigite novamente o número de jogadores (1 ou 2):");
                scanf("%c", &nJogadoresRodada);
            }

            int nJogadoresRodadaConvertido = converteCharPraInt(nJogadoresRodada); // Convertendo para int

            if (condArquivo == 0) // Arquivo .ini acabou de ser criado
            {
                Jogador *jogadoresNovoIni = malloc(2 * sizeof(Jogador)); // Vetor para os primeiros jogadores, uma vez que o ini acabou de ser criado

                printf("Digite o nome do jogador 1:");
                fgets(jogadoresNovoIni[0].nome, 64, stdin);
                jogadoresNovoIni[0].nome[strlen(jogadoresNovoIni[0].nome) - 1] = '\0'; // Removendo \n

                while (!validaNomePlayer1(jogadoresNovoIni[0].nome)) // Validação do nome do player 1
                {
                    printf("Digite o nome do jogador 1:");
                    fgets(jogadoresNovoIni[0].nome, 64, stdin);
                    jogadoresNovoIni[0].nome[strlen(jogadoresNovoIni[0].nome) - 1] = '\0'; // Removendo \n
                }

                if (nJogadoresRodadaConvertido == 2) // 2 players
                {
                    printf("Digite o nome do jogador 2:");
                    fgets(jogadoresNovoIni[1].nome, 64, stdin);
                    jogadoresNovoIni[1].nome[strlen(jogadoresNovoIni[1].nome) - 1] = '\0';

                    while (!validaNomePlayer2(jogadoresNovoIni[0].nome, jogadoresNovoIni[1].nome)) // Validação do nome do player 2
                    {
                        printf("Digite o nome do jogador 2:");
                        fgets(jogadoresNovoIni[1].nome, 64, stdin);
                        jogadoresNovoIni[1].nome[strlen(jogadoresNovoIni[1].nome) - 1] = '\0';
                    }
                }
                else // 1 player
                {
                    strcpy(jogadoresNovoIni[1].nome, "Computador"); // Player 2 = Computador
                }
                // Inicializa arquivo
                int nJogadoresNovos = 2;
                jogadoresNovoIni[0].vitorias = 0;
                jogadoresNovoIni[0].empates = 0;
                jogadoresNovoIni[0].derrotas = 0;
                jogadoresNovoIni[1].vitorias = 0;
                jogadoresNovoIni[1].empates = 0;
                jogadoresNovoIni[1].derrotas = 0;

                FILE *arquivoIni = fopen("velha.ini", "r+"); // Gravação dos primeiros dados do .ini recém criado
                fprintf(arquivoIni, "%d\n", nJogadoresNovos);
                for (int i = 0; i < 2; i++)
                {
                    fprintf(arquivoIni, "%s\n", jogadoresNovoIni[i].nome);
                    fprintf(arquivoIni, "%d %d %d\n", jogadoresNovoIni[i].vitorias, jogadoresNovoIni[i].empates, jogadoresNovoIni[i].derrotas);
                }
                fclose(arquivoIni);

                // Rodada do game

                int vitoriaNew = 0; // Variável que determinará se houve vitória ou não
                int empateNew = 0;  // Variável que determinará se houve empate ou não
                int coordenadaLinhaNew, coordenadaColunaNew;

                char **matriz;
                matriz = criaMatriz(3, 3);
                inicializaMatriz(&matriz, 3, 3);
                imprimeMatriz(matriz, 3, 3);

                int contRodadaNew = 1;                                                                                                                                                                                                             // Contará o número de rodadas e servirá para determinar quem joga
                jogoMultiplayerArquivoIniNovo(matriz, jogadoresNovoIni, contRodadaNew, nJogadoresNovos, &matrizJogoAtual, jogadoresTempJogoAtual, &posicaoPlayer1JogoAtual, &posicaoPlayer2JogoAtual, &contRodadaJogoAtual, &nJogadoresJogoAtual); // Função que roda o game
            }

            else // Arquivo .ini existente
            {
                Jogador *jogadoresTemp = malloc(2 * sizeof(Jogador)); // Vetor temporário parar armazenar dados dos players, que, posteriormente, serão incorporados ao vetor principal *jogadores
                printf("Digite o nome do jogador 1:");
                fgets(jogadoresTemp[0].nome, 64, stdin);
                jogadoresTemp[0].nome[strlen(jogadoresTemp[0].nome) - 1] = '\0'; // Removendo \n

                // Validação do nome do primeiro player
                while (!validaNomePlayer1(jogadoresTemp[0].nome))
                {
                    printf("Digite o nome do jogador 1:");
                    fgets(jogadoresTemp[0].nome, 64, stdin);
                    jogadoresTemp[0].nome[strlen(jogadoresTemp[0].nome) - 1] = '\0'; // Removendo \n
                }
                if (nJogadoresRodadaConvertido == 2) // 2 players
                {
                    printf("Digite o nome do jogador 2:");
                    fgets(jogadoresTemp[1].nome, 64, stdin);
                    jogadoresTemp[1].nome[strlen(jogadoresTemp[1].nome) - 1] = '\0'; // Removendo \n

                    // Validação do nome do segundo player
                    while (!validaNomePlayer2(jogadoresTemp[0].nome, jogadoresTemp[1].nome))
                    {
                        printf("Digite o nome do jogador 2:");
                        fgets(jogadoresTemp[1].nome, 64, stdin);
                        jogadoresTemp[1].nome[strlen(jogadoresTemp[1].nome) - 1] = '\0'; // Removendo \n
                    }
                }
                else // 1 player
                {
                    strcpy(jogadoresTemp[1].nome, "Computador"); // Player 2 = Computador
                }

                // Verificando se os players informados já estão no .ini
                int posicaoPlayer1, posicaoPlayer2;
                posicaoPlayer1 = verificaNomeNoVetorPrincipal(jogadores, jogadoresTemp[0].nome, nJogadores); // Retorna a posição do player no ini, caso exista, senão, retorna -1
                posicaoPlayer2 = verificaNomeNoVetorPrincipal(jogadores, jogadoresTemp[1].nome, nJogadores);

                // Caso em que o nome não está no ini
                if (posicaoPlayer1 == -1) // Nome do player 1 não está no .ini
                {
                    adicionaNovoPlayer(jogadores, jogadoresTemp, &nJogadores, &posicaoPlayer1, 0);
                }

                if (posicaoPlayer2 == -1) // Nome do player 2 não está no .ini
                {
                    adicionaNovoPlayer(jogadores, jogadoresTemp, &nJogadores, &posicaoPlayer2, 1);
                }

                char **matriz;
                matriz = criaMatriz(3, 3);
                inicializaMatriz(&matriz, 3, 3);
                imprimeMatriz(matriz, 3, 3);

                int contRodada = 1;                                                                                                                                                                                                                                                  // Contará o número de rodadas e servirá para determinar quem joga
                jogoMultiplayer(matriz, jogadoresTemp, jogadores, posicaoPlayer1, posicaoPlayer2, contRodada, nJogadoresRodadaConvertido, &matrizJogoAtual, jogadoresTempJogoAtual, &posicaoPlayer1JogoAtual, &posicaoPlayer2JogoAtual, &contRodadaJogoAtual, &nJogadoresJogoAtual); // Função que roda o game
            }

            break;
        case '2': // Continuar um jogo salvo
            printf("Digite o nome do arquivo que contém o jogo salvo: ");
            char nomeArquivo[128];
            fgets(nomeArquivo, 128, stdin);
            int tamanhoNomeArquivo = strlen(nomeArquivo);
            nomeArquivo[tamanhoNomeArquivo - 1] = '\0';

            // Validação do nome do arquivo
            while (!validaNomeArquivo(nomeArquivo))
            {
                printf("Digite o nome do arquivo que contém o jogo salvo: ");
                fgets(nomeArquivo, 128, stdin);
                int tamanhoNomeArquivo1 = strlen(nomeArquivo);
                nomeArquivo[tamanhoNomeArquivo1 - 1] = '\0';
            }

            // Variáveis que serão extraídas do arquivo
            char **matrizJogoCarregado;
            matrizJogoCarregado = criaMatriz(3, 3);
            Jogador *jogadoresTempJogoCarregado = malloc(2 * sizeof(Jogador));
            int posicaoPlayer1JogoCarregado, posicaoPlayer2JogoCarregado = -1, contRodadaJogoCarregado, nJogadoresJogoCarregado;

            lerArquivo(nomeArquivo, &matrizJogoCarregado, jogadoresTempJogoCarregado, &contRodadaJogoCarregado, &nJogadoresJogoCarregado);

            posicaoPlayer1JogoCarregado = verificaNomeNoVetorPrincipal(jogadores, jogadoresTempJogoCarregado[0].nome, nJogadores); // Retorna a posição do player no ini, caso exista, senão, retorna -1
            posicaoPlayer2JogoCarregado = verificaNomeNoVetorPrincipal(jogadores, jogadoresTempJogoCarregado[1].nome, nJogadores);

            // Caso em que o nome não está no ini
            if (posicaoPlayer1JogoCarregado == -1) // Nome do player 1 não está no .ini
            {
                adicionaNovoPlayer(jogadores, jogadoresTempJogoCarregado, &nJogadores, &posicaoPlayer1JogoCarregado, 0);
            }

            if (posicaoPlayer2JogoCarregado == -1) // Nome do player 2 não está no .ini
            {
                adicionaNovoPlayer(jogadores, jogadoresTempJogoCarregado, &nJogadores, &posicaoPlayer2JogoCarregado, 1);
            }

            imprimeMatriz(matrizJogoCarregado, 3, 3);
            jogoMultiplayer(matrizJogoCarregado, jogadoresTempJogoCarregado, jogadores, posicaoPlayer1JogoCarregado, posicaoPlayer2JogoCarregado, contRodadaJogoCarregado, nJogadoresJogoCarregado, &matrizJogoAtual, jogadoresTempJogoAtual, &posicaoPlayer1JogoAtual, &posicaoPlayer2JogoAtual, &contRodadaJogoAtual, &nJogadoresJogoAtual);

            printf("NUMERO DE JOGADORES = %d\n\n", nJogadores);
            break;

        case '3': // Continuar o jogo atual

            if (posicaoPlayer2JogoAtual != -1) // Caso em que algum jogo foi iniciado, ou seja, o valor da variável posicaoPlayer2JogoAtual é diferente de -1, que é o valor que foi atribuido no início do programa
            {
                imprimeMatriz(matrizJogoAtual, 3, 3);
                jogoMultiplayer(matrizJogoAtual, jogadoresTempJogoAtual, jogadores, posicaoPlayer1JogoAtual, posicaoPlayer2JogoAtual, contRodadaJogoAtual, nJogadoresJogoAtual, &matrizJogoAtual, jogadoresTempJogoAtual, &posicaoPlayer1JogoAtual, &posicaoPlayer2JogoAtual, &contRodadaJogoAtual, &nJogadoresJogoAtual);
            }
            else // Caso em que nenhum jogo foi iniciado
            {
                printf("\nErro - Nenhum jogo foi iniciado, portanto, não há como continuar jogo atual.\n\n");
            }
            break;

        case '4': // Exibir o ranking
            
            exibeRanking(jogadores, nJogadores);
            break;
        default:
            break;
        }
    }
    return 0;
}
