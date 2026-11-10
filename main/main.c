#include "../include/patricia.h"
#include "../include/biblioteca.h"
#include "../tests/teste.h"

#include <stdio.h>
#include <stdlib.h>

static void imprimir_menu(void)
{
    printf("\n");
    printf("================================\n");
    printf("          BIBLIOTECA\n");
    printf("================================\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Remover livro\n");
    printf("3 - Listar acervo\n");
    printf("4 - Imprimir livro\n");
    printf("5 - Alugar livro\n");
    printf("6 - Devolver livro\n");
    printf("0 - Sair\n");
    printf("================================\n");
    printf("Opcao: ");
}

int main(int argc, char *argv[]){
    //MODO TESTE: biblioteca.exe --teste
    if(argc > 1 && strcmp(argv[1], "--teste") == 0){
        return rodar_testes();
    }

    //CRIA A ÁRVORE E OUTRAS VARIAVEIS
    patricia *arvore = cria_patricia();
    int id = 1;     
    int idAUX;
    Livro livro;

    //ABRE O ARQUIVO LIVROS.TX
    FILE *arq = fopen("data/livros.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    
    //INSERE OS LIVROS DO ARQUIVO NA PATRICIA
    while(criar_livro(arq, &livro, &id)){
        inserir_patricia(arvore, &livro);
    }

    //FECHA ARQUIVO
    fclose(arq);

    //MENU
    int opcao;
    do{
        imprimir_menu();
        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        limpar_buffer();

        switch (opcao)
        {
        //ADICIONA LIVRO NOVO AO ACERVO DA BIBLIOTECA 
        case CADASTRAR_LIVRO:
            adicionar_livro(&livro, arvore, &id);
            printf(" %d | %s | %s | %d | %d | %d\n", livro.id, livro.titulo, livro.autor, livro.ano, livro.quantidade, livro.total);
            break;
        //REMOVE LIVRO DO ACERVO
        case REMOVER_LIVRO:
            printf("Informe o id do livro que deseja remover: ");
            scanf("%d", &idAUX);
            remover_livro(arvore, idAUX);
            break;
        //IMPRIMI TODOS OS LIVROS DO ACERVO
        case LISTAR_ACERVO:
            listar_acervo(arvore);
            break;
        //IMPRIMI APENAS UM LIVRO EM ESPECIFICO
        case IMPRIMIR_LIVRO:
            printf("Informe o id do livro que deseja imprimir: ");
            scanf("%d", &idAUX);
            imprime_especifico(arvore, idAUX);
            break;
        //ALUGAR LIVRO
        case ALUGAR_LIVRO:
            printf("Informe o id do livro que deseja alugar: ");
            scanf("%d", &idAUX);
            alugar_livro(arvore, idAUX);
            break;
        //DEVOLVER LIVRO
        case DEVOLVER_LIVRO:
            printf("Informe o id do livro que deseja devolver: ");
            scanf("%d", &idAUX);
            devolver_livro(arvore, idAUX);
            break;
        }
    }while (opcao != SAIR); 



    //DESTROI ÁRVORE
    destruir_patricia(arvore);

    return 0;
}