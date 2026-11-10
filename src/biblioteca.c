#include "../include/biblioteca.h"

void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

//ADICIONA UM LIVRO NOVO AO ACERVO (PELO TECLADO)
int adicionar_livro(Livro *livro, patricia *arvore, int *proximoId){
    printf("Adicione um livro novo: \n");

    printf("Titulo: ");
    fgets(livro->titulo, M, stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livro->autor, M, stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0';

    printf("Ano de publicacao: ");
    scanf("%d", &livro->ano);

    printf("Quantidade de exemplares: ");
    scanf("%d", &livro->quantidade);

    livro->total = livro->quantidade;

    livro->id = gerar_id(proximoId);
    return inserir_patricia(arvore, livro);
}

//REMOVER UM LIVRO DO ACERVO
int remover_livro(patricia *arvore, Chave id){
    Livro *livro = buscar_patricia(arvore, id);
    //LIVRO NAO EXISTE NO ACERVO
    if(livro == NULL){
        printf("Livro nao existe no acervo.\n");
        return 0;
    }

    //SE HA EXEMPLARES ALUGADOS
    if(livro->quantidade < livro->total){
        printf("Nao e possivel remover: %d exemplar(es) ainda estao alugados.\n", livro->total - livro->quantidade);
        return 0;
    }

    printf("Removendo o livro:\n");
    imprimir_livro(livro);

    if(!remover_patricia(arvore, id)){
        printf("Erro ao remover o livro.\n");
        return 0;
    }

    printf("Livro removido com sucesso.\n");
    return 1;
}

//IMPRIME TODOS OS LIVROS
void listar_acervo(patricia *arvore){
    printf("====================== LIVROS NO ACERVO DA BIBLIOTECA ======================\n");
    imprimir_patricia(arvore);
}

//ALGUGAR LIVRO
int alugar_livro(patricia *arvore, Chave id){
    Livro *livro = buscar_patricia(arvore, id);

    if(livro == NULL){
        printf("Livro nao encontrado.\n");
        return 0;             
    }
    
    //SE O LIVRO NÃO EXISTIR NO ACERVO DA BIBLIOTECA
    if(livro == NULL){
        printf("Livro nao existe no acervo. \n");
        return 0;
    }

    //SE LIVRO ESTIVER ESGOTADO
    if(!registrar_emprestimo(livro)){
        printf("Todas as copias deste livro ja foram alugadas. \n");
        return 0;
    }else{
        //LIVRO ALUGADO 
        printf("Livro alugado com sucesso!\n");
        imprimir_livro(livro);
        return 1;
    }
}

//IMPRIME UM LIVRO EM ESPECIFICO
void imprime_especifico(patricia *arvore, int id){
    Livro *livro = buscar_patricia(arvore, id);

    if(livro == NULL){
        printf("Livro nao encontrado.\n");
    }

    imprimir_livro(livro);
}

//DEVOLVER LIVRO
int devolver_livro(patricia *arvore, Chave id){
    Livro *livro = buscar_patricia(arvore, id);

    //SE O LIVRO NÃO EXISTIR NO ACERVO DA BIBLIOTECA
    if(livro == NULL){
        printf("Livro nao existe no acervo. \n");
        return 0;
    }

    //NÃO CONSEGUE RESGISTRAR A DEVOLUÇÃO
    if(!registrar_devolucao(livro)){
        printf("Nao foi possivel registrar a devolução. \n");
        return 0;
    }

    printf("Livro devolvido com sucesso!\n");
    imprimir_livro(livro);
    return 1;
}
