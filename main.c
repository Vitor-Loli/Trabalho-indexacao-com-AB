#include <stdio.h>
#include <stdlib.h>

#include "mapa.h"
#include "arvore.h"

static void menu(void) {
    printf("\n=== MENU ===\n");
    printf("1 - Inserir produto\n");
    printf("2 - Buscar por ID\n");
    printf("3 - Remover por ID\n");
    printf("4 - Atualizar preco\n");
    printf("5 - Listar produtos por faixa de preco\n");
    printf("6 - Buscar vizinho mais proximo\n");
    printf("7 - Mostrar arvore por ID\n");
    printf("8 - Mostrar arvore por Preco\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int main(void) {
    Sistema *s = sistema_criar();

    sistema_inserir(s, 50, "Mouse", 100);
    sistema_inserir(s, 30, "Teclado", 150);
    sistema_inserir(s, 70, "Monitor", 900);
    sistema_inserir(s, 20, "Mousepad", 50);
    sistema_inserir(s, 40, "Headset", 250);
    sistema_inserir(s, 60, "Webcam", 300);
    sistema_inserir(s, 80, "Notebook", 3500);

    int opcao;

    do {
        menu();

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            break;
        }

        switch (opcao) {
            case 1: {
                int id;
                char nome[64];
                float preco;

                printf("ID: ");
                scanf("%d", &id);
                printf("Nome: ");
                scanf(" %63[^\n]", nome);
                printf("Preco: ");
                scanf("%f", &preco);

                sistema_inserir(s, id, nome, preco);
                break;
            }

            case 2: {
                int id;
                printf("ID: ");
                scanf("%d", &id);

                Produto *p = sistema_buscar_por_id(s, id);
                if (p != NULL) {
                    printf("Encontrado -> ID: %d | Nome: %s | Preco: %.2f\n",
                           p->id, p->nome, p->preco);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                break;
            }

            case 3: {
                int id;
                printf("ID: ");
                scanf("%d", &id);
                sistema_remover(s, id);
                break;
            }

            case 4: {
                int id;
                float novo_preco;

                printf("ID: ");
                scanf("%d", &id);
                printf("Novo preco: ");
                scanf("%f", &novo_preco);

                sistema_atualizar_preco(s, id, novo_preco);
                break;
            }

            case 5: {
                float min, max;

                printf("Preco minimo: ");
                scanf("%f", &min);
                printf("Preco maximo: ");
                scanf("%f", &max);

                printf("\nProdutos na faixa:\n");
                sistema_listar_faixa_preco(s, min, max);
                break;
            }

            case 6: {
                float preco;

                printf("Preco de referencia: ");
                scanf("%f", &preco);

                Produto *p = sistema_vizinho_mais_proximo(s, preco);
                if (p != NULL) {
                    printf("Vizinho mais proximo -> ID: %d | Nome: %s | Preco: %.2f\n",
                           p->id, p->nome, p->preco);
                } else {
                    printf("Sistema vazio.\n");
                }
                break;
            }

            case 7:
                printf("\nÁrvore por ID:\n");
                sistema_mostrar_por_id(s);
                break;

            case 8:
                printf("\nÁrvore por Preco:\n");
                sistema_mostrar_por_preco(s);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    sistema_destruir(s);
    return 0;
}