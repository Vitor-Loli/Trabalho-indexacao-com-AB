#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mapa.h"

struct smapa {
    int chave;
    int dados;
    Mapa* esq;
    Mapa* dir;
};

Mapa* cria (void) {
    return NULL;
}

static Mapa *cria_no (int c, int d) {
    Mapa *nn = (Mapa *)malloc(sizeof(Mapa));
    if (nn!=NULL) {
        nn->esq = nn->dir = NULL;
        nn->chave =c;
        nn->dados = d;
    }
    return nn;
}

Mapa* insere(Mapa *m, int chave, int d) {
    if(m == NULL) {
        return cria_no(chave, d);
    }

    if(d < m->dados) {
        m->esq = insere(m->esq, chave, d);
    } else {
        m->dir = insere(m->dir, chave, d);
    }

    return m;
}

int busca (Mapa *m, int chave) {
    while (m!=NULL) {
        if (chave < m->chave)
            m = m->esq;
        else if (chave > m->chave)
            m = m->dir;
        else
            return m->dados; /* achou */
    }
    return INT_MIN;
}

void percorre (Mapa* m, funcp f) {
    /* depois discutiremos */
}

void destroi (Mapa *m) {
    if (m==NULL) return;
    destroi (m->esq);
    destroi (m->dir);
    free(m);
}

int altura (Mapa *m) {
    if (m == NULL) {
        return 0;
    }else{
        int alturaEsq = altura (m->esq);
        int alturaDir = altura (m->dir);

        if (alturaEsq > alturaDir) {
            return (alturaEsq + 1);
        }else{
            return (alturaDir + 1);
        }

    }

}

void mostra (Mapa *m) {
    if (m==NULL) {
        printf ("()");
    }else {
        printf ("(");
        printf ("%d", m->dados);
        mostra (m->esq);
        mostra (m->dir);
        printf (")");
    }
}