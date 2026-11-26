#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/**
 * Aloca e inicializa uma nova fila vazia.
 */
Fila* criar_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

/**
 * Verifica se a fila está vazia.
 * Retorna 1 se vazia, 0 caso contrário.
 */
int fila_vazia(Fila *f) {
    return (f == NULL || f->inicio == NULL);
}

/**
 * Insere uma música no final da fila (Enqueue).
 * Retorna 1 em caso de sucesso, 0 em caso de erro de alocação.
 */
int enfileirar(Fila *f, Musica m) {
    if (f == NULL) return 0;

    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) return 0; // Falha de memória

    novo->dados = m;
    novo->proximo = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }

    f->fim = novo;
    f->tamanho++;
    return 1;
}

/**
 * Remove a música do início da fila e copia seus dados para 'saida' (Dequeue).
 * Retorna 1 em caso de sucesso, 0 se a fila estiver vazia.
 */
int desenfileirar(Fila *f, Musica *saida) {
    if (fila_vazia(f)) return 0;

    NoFila *removido = f->inicio;
    if (saida != NULL) {
        *saida = removido->dados;
    }

    f->inicio = removido->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL; // A fila ficou vazia
    }

    free(removido);
    f->tamanho--;
    return 1;
}

/**
 * Consulta a música no início da fila sem removê-la (Front).
 * Retorna 1 em caso de sucesso, 0 se a fila estiver vazia.
 */
int consultar_frente(Fila *f, Musica *saida) {
    if (fila_vazia(f) || saida == NULL) return 0;
    *saida = f->inicio->dados;
    return 1;
}

/**
 * Exibe todas as músicas na fila de reprodução.
 */
void exibir_fila(Fila *f) {
    if (fila_vazia(f)) {
        printf("  [Fila de reproducao vazia]\n");
        return;
    }

    NoFila *atual = f->inicio;
    int pos = 1;
    while (atual != NULL) {
        int min = atual->dados.duracao_segundos / 60;
        int seg = atual->dados.duracao_segundos % 60;
        printf("  %d. %s - %s (%02d:%02d)\n", 
               pos++, atual->dados.titulo, atual->dados.artista, min, seg);
        atual = atual->proximo;
    }
}

/**
 * Libera toda a memória alocada para os nós e para a própria fila.
 */
void liberar_fila(Fila *f) {
    if (f == NULL) return;
    while (!fila_vazia(f)) {
        desenfileirar(f, NULL);
    }
    free(f);
}