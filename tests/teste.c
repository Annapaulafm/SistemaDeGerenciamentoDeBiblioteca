#include "teste.h"

static int passou = 0;
static int falhou = 0;

static void verificar(int condicao, const char *nome){
    if(condicao){
        printf("[OK]    %s\n", nome);
        passou ++;
    }else{
        printf("[FALHA]     %s\n", nome);
        falhou++;
    }
}

//IMPRIME RESULTADO FINAL
static int resultado_final(){
    printf("%d verificacoes = %d OK | %d FALHA\n", passou + falhou, passou, falhou);
    if(falhou == 0){
        printf("TESTE APROVADO!\n");
    }else{
        printf("TESTE REPROVADO!\n");
    }

    return falhou != 0;
}

//CRIA UM LIVRO TESTE
static Livro novo_livro(int id){
    Livro livro;
    livro.id = id;
    strcpy(livro.titulo, "Titulo de teste");
    strcpy(livro.autor, "Autor teste");
    livro.ano = 2000;
    livro.quantidade = 2;
    livro.total = 2;
    return livro;
}

//TESTE DAS FUNÇÕES DA PATRICIA
static void teste_patricia(){
    patricia *arvore = cria_patricia();  
    Livro livro = novo_livro(1);        
    Livro repetido = novo_livro(1);

    verificar(inserir_patricia(arvore, &livro) == 1, "inserir livro novo");
    verificar(inserir_patricia(arvore, &repetido) == 0, "id repetido e recusado");
    verificar(buscar_patricia(arvore, 1) != NULL, "buscar id existente");
    verificar(buscar_patricia(arvore, 99) == NULL, "buscar id inexistente");
    destruir_patricia(arvore);
}

//TESTE DE ALGUEL E DEVOLUÇÃO
static void teste_aluguel_devolucao(){
    patricia *arvore = cria_patricia();
    Livro livro = novo_livro(1);

    verificar(inserir_patricia(arvore, &livro) == 1, "inserir livro novo");

    verificar(alugar_livro(arvore, 1) == 1, "alugar com livro disponivel");
    verificar(buscar_patricia(arvore, 1)->quantidade == 1, "quantidade caiu para 1");
    verificar(alugar_livro(arvore, 1) == 1, "alugar o ultimo exemplar");
    verificar(buscar_patricia(arvore, 1)->quantidade == 0, "quantidade caiu para 0");
    verificar(alugar_livro(arvore, 1) == 0, "alugar livro esgotado e recusado");
    verificar(buscar_patricia(arvore, 1)->quantidade == 0, "quantidade continua 0");

    verificar(devolver_livro(arvore, 1) == 1, "devolver um livro");
    verificar(buscar_patricia(arvore, 1)->quantidade == 1, "quantidade aumentou para 1");
    verificar(devolver_livro(arvore, 1) == 1, "devolver o outro livro");
    verificar(buscar_patricia(arvore, 1)->quantidade == 2, "quantidade voltou para 2");
    verificar(devolver_livro(arvore, 1) == 0, "devolver com tudo na biblioteca e recusado");
    verificar(buscar_patricia(arvore, 1)->quantidade == 2, "quantidade continua 2");

    verificar(alugar_livro(arvore, 99) == 0, "alugar id inexistente");
    verificar(devolver_livro(arvore, 99) == 0, "devolver id inexistente");

    destruir_patricia(arvore);
}

int rodar_testes(void){
    teste_patricia();
    teste_aluguel_devolucao();
    return resultado_final();
}