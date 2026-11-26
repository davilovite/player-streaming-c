#ifndef PILHA_H
#define PILHA_H

#include "musica.h"

// Nó da pilha encadeada
typedef struct NoPilha {
    Musica dados;
    struct NoPilha *abaixo;
} NoPilha;

// Estrutura de controle da Pilha
typedef struct {
    NoPilha *topo;
    int tamanho;
} Pilha;

// Protótipos das funções essenciais
Pilha* criar_pilha();
int pilha_vazia(Pilha *p);
int empilhar(Pilha *p, Musica m);           // push: adiciona no topo do histórico
int desempilhar(Pilha *p, Musica *saida);   // pop: remove do topo para voltar música
int consultar_topo(Pilha *p, Musica *saida); // top: espia a última música tocada
void exibir_pilha(Pilha *p);
void liberar_pilha(Pilha *p);

#endif