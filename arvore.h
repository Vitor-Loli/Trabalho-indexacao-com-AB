#ifndef ARVORE_H
#define ARVORE_H

#include "mapa.h"

int altura (Mapa *m);
Mapa* cria (void);
void mostra (Mapa *m);
Mapa *insere (Mapa *m, int chave, int d);

#endif //ARVORE_H
