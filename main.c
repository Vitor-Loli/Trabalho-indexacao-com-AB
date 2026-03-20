#include <stdio.h>
#include <limits.h>
#include "mapa.h"
#include "arvore.h"

int dados (int chave) {
    /* inventa dados associados a uma chave */
    return 2*chave;
}

Mapa* preenche (Mapa* m, int inicio, int fim) {
    int meio;
    if (inicio>fim) return m;
    meio = (fim+inicio)/2;
    m = insere (m, meio, dados(meio));
    m = preenche (m, inicio, meio-1);
    m = preenche (m, meio+1, fim);
    return m;
}

int main () {

    int i, res, tammapa;

    tammapa = 5;
    Mapa *meumapa = cria();
    meumapa = insere(meumapa, 1, 2);
    meumapa = insere(meumapa, 2, 10);
    meumapa = insere(meumapa, 3, 3);
    meumapa = insere(meumapa, 4, 12);
    meumapa = insere(meumapa, 5, 45);
    meumapa = insere(meumapa, 6, 5);
    meumapa = insere(meumapa, 7, 9);
    meumapa = insere(meumapa, 8, 1);
    printf("%d",altura (meumapa));
    printf ("\n");
    mostra(meumapa);


    // for (i=0;i<tammapa;i++) meumapa = insere(meumapa, i, dados(i));
    // printf("Primeiro mapa -------------- \n");
    // printf("implementacao: ");
    // mostra(meumapa);
    // printf("\n");
    // printf("altura: %d \n", altura(meumapa));
    //
    // for (i=0; i<=(tammapa+1); i++) {
    //     printf("busca %d\n", i);
    //     res = busca(meumapa, i);
    //     printf ("achou? %s\n", (res!=INT_MIN)?"sim":"nao");
    // }

    //
    // Mapa *outromapa = cria();
    // outromapa = preenche (outromapa, 0, tammapa-1);
    //
    // printf("outro mapa ------------ \n");
    // printf("implementacao: ");
    // mostra(outromapa);
    // printf("\n");
    // printf("altura: %d \n", altura(outromapa));
    //
    // for (i=0; i<=(tammapa+1); i++) {
    //     printf("busca %d\n", i);
    //     res = busca(outromapa, i);
    //     printf ("achou? %s\n", (res!=INT_MIN)?"sim":"nao");
    // }

    //destroi(meumapa);

    // destroi(outromapa);

    return 0;}
