/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/
#include "funcoes.h"

int main(int argc, char const *argv[])
{
    // Arquivo .ini
    printNomeDoJogo();
    printf("Bora jogar um jogo da velha?\n\n");
    while (1)
    {
        int condArquivo;
        int nJogadores;
        Jogador *jogadores = malloc(11 * sizeof(Jogador)); // Um a mais que o limite de jogadores
        if (verificaArquivoExistente("velha.ini"))
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
        scanf("%c", &op); // Lê a opção do usuário
        limpaBuffer();

        while (op != '0' && op != '1' && op != '2' && op != '3' && op != '4') // Valida a opção do usuário
        {
            printf("\n\nERRO - Opção inválida\n\n");
            printMenu();
            printf("Digite uma opção válida: ");
            scanf("%c", &op);
            limpaBuffer();
        }

        switch (op)
        {
        case '0': // Sair do jogo

            break;

        case '1': // Começar um novo jogo
            printf("\nDigite o número de jogadores (1 ou 2): ");
            char nJogadoresRodada;
            scanf("%c", &nJogadoresRodada);
            limpaBuffer();

            while (nJogadoresRodada != '1' && nJogadoresRodada != '2') // Valida o número de jogadores
            {
                printf("Erro - Valor inválido!\nDigite novamente o número de jogadores (1 ou 2):");
                scanf("%c", &nJogadoresRodada);
                limpaBuffer();
            }

            int nJogadoresRodadaConvertido = converteCharPraInt(nJogadoresRodada); // Convertendo para int

            if (condArquivo == 0) // Arquivo .ini acabou de ser criado
            {
                Jogador *jogadoresNovoIni = malloc(2 * sizeof(Jogador)); // Vetor para os primeiros jogadores, uma vez que o ini acabou de ser criado

                printf("Digite o nome do jogador 1:");
                fgets(jogadoresNovoIni[0].nome, 64, stdin);
                jogadoresNovoIni[0].nome[strlen(jogadoresNovoIni[0].nome) - 1] = '\0'; // Removendo \n
                if (nJogadoresRodadaConvertido == 2)                                   // 2 players
                {
                    printf("Digite o nome do jogador 2:");
                    fgets(jogadoresNovoIni[1].nome, 64, stdin);
                    jogadoresNovoIni[1].nome[strlen(jogadoresNovoIni[1].nome) - 1] = '\0';
                }
                else // 1 player
                {
                    strcpy(jogadoresNovoIni[1].nome, "Computador"); // Player 2 = Computador
                }
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
            }

            else // Arquivo .ini existente
            {
                Jogador *jogadoresTemp = malloc(2 * sizeof(Jogador)); // Vetor temporário parar armazenar dados dos players, que, posteriormente, serão incorporados ao vetor principal *jogadores
                printf("Digite o nome do jogador 1:");
                fgets(jogadoresTemp[0].nome, 64, stdin);
                jogadoresTemp[0].nome[strlen(jogadoresTemp[0].nome) - 1] = '\0'; // Removendo \n
                if (nJogadoresRodadaConvertido == 2)                             // 2 players
                {
                    printf("Digite o nome do jogador 2:");
                    fgets(jogadoresTemp[1].nome, 64, stdin);
                    jogadoresTemp[1].nome[strlen(jogadoresTemp[1].nome) - 1] = '\0'; // Removendo \n
                }
                else // 1 player
                {
                    strcpy(jogadoresTemp[1].nome, "Computador"); // Player 2 = Computador
                }

                // Verificando se os players informados já estão no .ini
                int posicaoPlayer1, posicaoPlayer2;
                posicaoPlayer1 = verificaPlayerNoIni(jogadoresTemp[0].nome, nJogadores); // Retorna a posição do player no ini, caso exista, senão, retorna -1
                posicaoPlayer2 = verificaPlayerNoIni(jogadoresTemp[1].nome, nJogadores);

                // Caso em que o nome não está no ini
                if (posicaoPlayer1 == -1) // Nome do player 1 não está no .ini
                {
                    adicionaNovoPlayer(jogadores, jogadoresTemp, &nJogadores, &posicaoPlayer1, 0);
                }

                if (posicaoPlayer2 == -1) // Nome do player 2 não está no .ini
                {
                    adicionaNovoPlayer(jogadores, jogadoresTemp, &nJogadores, &posicaoPlayer2, 1);
                }

                // Rodada do game
                int vitoria = 0; // Variável que determinará se houve vitória ou não
                int empate = 0;  // Variável que determinará se houve empate ou não
                int coordenadaLinha, coordenadaColuna;
                char **matriz;
                matriz = criaMatriz(3, 3);
                int contRodada = 1;         // Contará o número de rodadas e servirá para determinar quem joga
                while (!vitoria && !empate) // O jogo roda enquanto não houver vitoria ou empate
                {
                    char comandoGeral[64], comandoPrincipal[6], parametroDoComandoPrincipal[64];

                    if (contRodada % 2 != 0) // Vez do player 1
                    {
                        printf("%s, digite o comando: ", jogadoresTemp[0].nome);
                        fgets(comandoGeral, 64, stdin);
                        captaComando(comandoGeral, comandoPrincipal, parametroDoComandoPrincipal);

                        if(validaComando(comandoPrincipal, parametroDoComandoPrincipal, comandoGeral, jogadoresTemp, 0) && (validaParametroDoMarcar(parametroDoComandoPrincipal, &coordenadaLinha, &coordenadaColuna, comandoPrincipal) || validaParametroDoSalvar(parametroDoComandoPrincipal, comandoPrincipal) || validaParametroDoVoltar(parametroDoComandoPrincipal, comandoPrincipal)) ) //Valida comando principal - marcar, voltar e salvar
                        {
                          printf("X = %d \n\n Y = %d \n", coordenadaLinha, coordenadaColuna);  
                        }
                        
                    }
                }
            }

            break;

        case '2': // Continuar um jogo salvo

            break;

        case '3': // Continuar o jogo atual

            break;

        case '4': // Exibir o ranking

            break;
        default:
            break;
        }
    }
    return 0;
}
