/*
Discente: Nicolas Expedito Lana Mendes
Matricula: 22.1.4028
*/
#include "funcoes.h"

int main(int argc, char const *argv[])
{
    printNomeDoJogo();
    printf("Bora jogar um jogo da velha?\n\n");
    while(1)
    {
        printMenu();
        printf("Escolha uma opção: ");
        char op;
        scanf("%c", &op); // Lê a opção do usuário
        limpaBuffer();

        while (op != '0' && op != '1' && op != '2' && op != '3' && op != '4') //Valida a opção do usuário
        {
            printf("\n\nERRO - Opção inválida\n\n");
            printMenu();
            printf("Digite uma opção válida: ");
            scanf("%c", &op);
            limpaBuffer();
        }

        
    }
    return 0;
}
