#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>

typedef struct Produto {
    int id;
    char nome[64];
    float preco;
} Produto;

typedef struct NoId NoId;
typedef struct NoPreco NoPreco;
typedef struct Sistema Sistema;

Sistema* sistema_criar(void);
void sistema_inserir(Sistema* s, int id, const char* nome, float preco);
Produto* sistema_buscar_por_id(Sistema* s, int id);
void sistema_remover(Sistema* s, int id);
void sistema_atualizar_preco(Sistema* s, int id, float novo_preco);

void sistema_listar_faixa_preco(Sistema* s, float minimo, float maximo);
Produto* sistema_vizinho_mais_proximo(Sistema* s, float preco);

void sistema_mostrar_por_id(Sistema* s);
void sistema_mostrar_por_preco(Sistema* s);
void sistema_destruir(Sistema* s);

#endif