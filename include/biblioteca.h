#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>

#include "patricia.h"

enum menu_opcoes{
    SAIR = 0,
    CADASTRAR_LIVRO,
    REMOVER_LIVRO,
    LISTAR_ACERVO,
    IMPRIMIR_LIVRO,
    ALUGAR_LIVRO,
    DEVOLVER_LIVRO
};

void limpar_buffer(void);
int adicionar_livro(Livro *livro, patricia *arvore, int *proximoId);
int remover_livro(patricia *arvore, Chave id);
void listar_acervo(patricia *arvore);
void imprime_especifico(patricia *arvore, int id);
int alugar_livro(patricia *arvore, Chave id);
int devolver_livro(patricia *arvore, Chave id);

//CADASTRO DE CLIENTE 
//LIMITE DE LIVROS ALUGADOS POR CLIENTE

#endif