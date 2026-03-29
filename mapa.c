#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "mapa.h"
#include "arvore.h"

static Produto* produto_criar(int id, const char* nome, float preco) {
    Produto *p = (Produto*)malloc(sizeof(Produto));
    if (p == NULL) return NULL;

    p->id = id;
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->preco = preco;
    return p;
}

static NoId* noid_criar(Produto *produto) {
    NoId *n = (NoId*)malloc(sizeof(NoId));
    if (n == NULL) return NULL;
    n->produto = produto;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

static NoPreco* nopreco_criar(Produto *produto) {
    NoPreco *n = (NoPreco*)malloc(sizeof(NoPreco));
    if (n == NULL) return NULL;
    n->produto = produto;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

Sistema* sistema_criar(void) {
    Sistema *s = (Sistema*)malloc(sizeof(Sistema));
    if (s == NULL) return NULL;
    s->raiz_id = NULL;
    s->raiz_preco = NULL;
    return s;
}

static NoId* inserir_id(NoId *raiz, Produto *produto) {
    if (raiz == NULL) return noid_criar(produto);

    if (produto->id < raiz->produto->id) {
        raiz->esq = inserir_id(raiz->esq, produto);
    } else if (produto->id > raiz->produto->id) {
        raiz->dir = inserir_id(raiz->dir, produto);
    }
    return raiz;
}

static NoPreco* inserir_preco(NoPreco *raiz, Produto *produto) {
    if (raiz == NULL) return nopreco_criar(produto);

    if (produto->preco < raiz->produto->preco ||
       (produto->preco == raiz->produto->preco && produto->id < raiz->produto->id)) {
        raiz->esq = inserir_preco(raiz->esq, produto);
    } else {
        raiz->dir = inserir_preco(raiz->dir, produto);
    }
    return raiz;
}

static Produto* buscar_id_no(NoId *raiz, int id) {
    while (raiz != NULL) {
        if (id < raiz->produto->id) {
            raiz = raiz->esq;
        } else if (id > raiz->produto->id) {
            raiz = raiz->dir;
        } else {
            return raiz->produto;
        }
    }
    return NULL;
}

static void mostrar_in_id(NoId *raiz) {
    if (raiz == NULL) return;
    mostrar_in_id(raiz->esq);
    printf("ID: %d | Nome: %s | Preco: %.2f\n",
           raiz->produto->id, raiz->produto->nome, raiz->produto->preco);
    mostrar_in_id(raiz->dir);
}

static void mostrar_in_preco(NoPreco *raiz) {
    if (raiz == NULL) return;
    mostrar_in_preco(raiz->esq);
    printf("Preco: %.2f | ID: %d | Nome: %s\n",
           raiz->produto->preco, raiz->produto->id, raiz->produto->nome);
    mostrar_in_preco(raiz->dir);
}

static void listar_faixa(NoPreco *raiz, float minimo, float maximo) {
    if (raiz == NULL) return;

    if (raiz->produto->preco > minimo) {
        listar_faixa(raiz->esq, minimo, maximo);
    }

    if (raiz->produto->preco >= minimo && raiz->produto->preco <= maximo) {
        printf("ID: %d | Nome: %s | Preco: %.2f\n",
               raiz->produto->id, raiz->produto->nome, raiz->produto->preco);
    }

    if (raiz->produto->preco < maximo) {
        listar_faixa(raiz->dir, minimo, maximo);
    }
}

static Produto* vizinho_rec(NoPreco *raiz, float preco, Produto *melhor, float *melhor_diff) {
    if (raiz == NULL) return melhor;

    float diff = fabsf(raiz->produto->preco - preco);
    if (diff < *melhor_diff ||
        (diff == *melhor_diff && raiz->produto->preco < melhor->preco)) {
        *melhor_diff = diff;
        melhor = raiz->produto;
    }

    if (preco < raiz->produto->preco) {
        return vizinho_rec(raiz->esq, preco, melhor, melhor_diff);
    } else if (preco > raiz->produto->preco) {
        return vizinho_rec(raiz->dir, preco, melhor, melhor_diff);
    }

    return raiz->produto;
}

static NoPreco* encontrar_min_preco(NoPreco *raiz) {
    while (raiz != NULL && raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

static NoPreco* remover_preco_no(NoPreco *raiz, float preco, int id) {
    if (raiz == NULL) return NULL;

    if (preco < raiz->produto->preco ||
       (preco == raiz->produto->preco && id < raiz->produto->id)) {
        raiz->esq = remover_preco_no(raiz->esq, preco, id);
    } else if (preco > raiz->produto->preco ||
              (preco == raiz->produto->preco && id > raiz->produto->id)) {
        raiz->dir = remover_preco_no(raiz->dir, preco, id);
    } else {
        if (raiz->esq == NULL) {
            NoPreco *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoPreco *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        NoPreco *menor = encontrar_min_preco(raiz->dir);
        raiz->produto = menor->produto;
        raiz->dir = remover_preco_no(raiz->dir, menor->produto->preco, menor->produto->id);
    }
    return raiz;
}

static NoId* encontrar_min_id(NoId *raiz) {
    while (raiz != NULL && raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

static NoId* remover_id_no(NoId *raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->produto->id) {
        raiz->esq = remover_id_no(raiz->esq, id);
    } else if (id > raiz->produto->id) {
        raiz->dir = remover_id_no(raiz->dir, id);
    } else {
        if (raiz->esq == NULL) {
            NoId *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoId *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        NoId *menor = encontrar_min_id(raiz->dir);
        raiz->produto = menor->produto;
        raiz->dir = remover_id_no(raiz->dir, menor->produto->id);
    }
    return raiz;
}

void sistema_inserir(Sistema* s, int id, const char* nome, float preco) {
    if (s == NULL || nome == NULL) return;

    if (buscar_id_no(s->raiz_id, id) != NULL) {
        printf("Erro: ja existe produto com ID %d\n", id);
        return;
    }

    Produto *produto = produto_criar(id, nome, preco);
    if (produto == NULL) {
        printf("Erro: memoria insuficiente\n");
        return;
    }

    s->raiz_id = inserir_id(s->raiz_id, produto);
    s->raiz_preco = inserir_preco(s->raiz_preco, produto);
}

Produto* sistema_buscar_por_id(Sistema* s, int id) {
    if (s == NULL) return NULL;
    return buscar_id_no(s->raiz_id, id);
}

void sistema_remover(Sistema* s, int id) {
    if (s == NULL) return;

    Produto *produto = buscar_id_no(s->raiz_id, id);
    if (produto == NULL) {
        printf("Produto com ID %d nao encontrado\n", id);
        return;
    }

    s->raiz_id = remover_id_no(s->raiz_id, id);
    s->raiz_preco = remover_preco_no(s->raiz_preco, produto->preco, produto->id);
    free(produto);
}

void sistema_atualizar_preco(Sistema* s, int id, float novo_preco) {
    if (s == NULL) return;

    Produto *produto = buscar_id_no(s->raiz_id, id);
    if (produto == NULL) {
        printf("Produto com ID %d nao encontrado\n", id);
        return;
    }

    s->raiz_preco = remover_preco_no(s->raiz_preco, produto->preco, produto->id);
    produto->preco = novo_preco;
    s->raiz_preco = inserir_preco(s->raiz_preco, produto);
}

void sistema_listar_faixa_preco(Sistema* s, float minimo, float maximo) {
    if (s == NULL) return;
    if (minimo > maximo) {
        float tmp = minimo;
        minimo = maximo;
        maximo = tmp;
    }
    listar_faixa(s->raiz_preco, minimo, maximo);
}

Produto* sistema_vizinho_mais_proximo(Sistema* s, float preco) {
    if (s == NULL || s->raiz_preco == NULL) return NULL;

    Produto *raiz_produto = s->raiz_preco->produto;
    float melhor_diff = fabsf(raiz_produto->preco - preco);
    return vizinho_rec(s->raiz_preco, preco, raiz_produto, &melhor_diff);
}

void sistema_mostrar_por_id(Sistema* s) {
    if (s == NULL) return;
    mostrar_in_id(s->raiz_id);
}

void sistema_mostrar_por_preco(Sistema* s) {
    if (s == NULL) return;
    mostrar_in_preco(s->raiz_preco);
}

static void destruir_id(NoId *raiz) {
    if (raiz == NULL) return;
    destruir_id(raiz->esq);
    destruir_id(raiz->dir);
    free(raiz);
}

static void destruir_preco(NoPreco *raiz) {
    if (raiz == NULL) return;
    destruir_preco(raiz->esq);
    destruir_preco(raiz->dir);
    free(raiz);
}

void sistema_destruir(Sistema* s) {
    if (s == NULL) return;

    destruir_id(s->raiz_id);
    destruir_preco(s->raiz_preco);
    free(s);
}