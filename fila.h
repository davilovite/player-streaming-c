#ifndef FILA_H
#define FILA_H

#include "musica.h"

// Nó da fila encadeada
typedef struct NoFila {
    Musica dados;
    struct NoFila *proximo;
} NoFila;

// Estrutura de controle da Fila
typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} Fila;

// Protótipos das funções essenciais
Fila* criar_fila();
int fila_vazia(Fila *f);
int enfileirar(Fila *f, Musica m);            // enqueue: adiciona no fim
int desenfileirar(Fila *f, Musica *saida);    // dequeue: remove do início
int consultar_frente(Fila *f, Musica *saida); // front: espia a próxima sem remover
void exibir_fila(Fila *f);
void liberar_fila(Fila *f);

#endif