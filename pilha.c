#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/**
 * Aloca e inicializa uma nova pilha vazia.
 */
Pilha* criar_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
        p->tamanho = 0;
    }
    return p;
}

/**
 * Verifica se a pilha está vazia.
 * Retorna 1 se vazia, 0 caso contrário.
 */
int pilha_vazia(Pilha *p) {
    return (p == NULL || p->topo == NULL);
}

/**
 * Insere uma música no topo da pilha de histórico (Push).
 * Retorna 1 em caso de sucesso, 0 em caso de erro de alocação.
 */
int empilhar(Pilha *p, Musica m) {
    if (p == NULL) return 0;

    NoPilha *novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) return 0; // Falha de memória

    novo->dados = m;
    novo->abaixo = p->topo;
    p->topo = novo;
    p->tamanho++;
    return 1;
}

/**
 * Remove a música do topo da pilha e copia seus dados para 'saida' (Pop).
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int desempilhar(Pilha *p, Musica *saida) {
    if (pilha_vazia(p)) return 0;

    NoPilha *removido = p->topo;
    if (saida != NULL) {
        *saida = removido->dados;
    }

    p->topo = removido->abaixo;
    free(removido);
    p->tamanho--;
    return 1;
}

/**
 * Consulta a música no topo da pilha sem removê-la (Top).
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int consultar_topo(Pilha *p, Musica *saida) {
    if (pilha_vazia(p) || saida == NULL) return 0;
    *saida = p->topo->dados;
    return 1;
}

/**
 * Exibe todo o histórico de músicas tocadas (da mais recente para a mais antiga).
 */
void exibir_pilha(Pilha *p) {
    if (pilha_vazia(p)) {
        printf("  [Historico vazio]\n");
        return;
    }

    NoPilha *atual = p->topo;
    int pos = 1;
    while (atual != NULL) {
        int min = atual->dados.duracao_segundos / 60;
        int seg = atual->dados.duracao_segundos % 60;
        printf("  %d. %s - %s (%02d:%02d)\n", 
               pos++, atual->dados.titulo, atual->dados.artista, min, seg);
        atual = atual->abaixo;
    }
}

/**
 * Libera toda a memória alocada para os nós e para a própria pilha.
 */
void liberar_pilha(Pilha *p) {
    if (p == NULL) return;
    while (!pilha_vazia(p)) {
        desempilhar(p, NULL);
    }
    free(p);
}