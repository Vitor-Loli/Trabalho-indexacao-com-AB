#ifndef ARVORE_H
#define ARVORE_H

#include "mapa.h"

struct NoId {
    Produto *produto;
    NoId *esq;
    NoId *dir;
};

struct NoPreco {
    Produto *produto;
    NoPreco *esq;
    NoPreco *dir;
};

struct Sistema {
    NoId *raiz_id;
    NoPreco *raiz_preco;
};

#endif