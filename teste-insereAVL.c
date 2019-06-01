#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_bbb.h"

void imprimeItem(void *pItem, char* pTipoItem);

int main(void){
    TQ *qua1 = criaQuadrado(10);

    TAG *arv_avl = NULL;
    arv_avl = insere_ABBB(arv_avl, 5, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 7, "QUA", qua1);

    imprime_repres_ABBB(arv_avl, 0);
    printf("\nInserindo o 15\n");
    arv_avl = insere_ABBB(arv_avl, 15, "QUA", qua1);
    imprime_repres_ABBB(arv_avl, 0);
    printf("################################\n");

    destroi_AG(arv_avl);
    arv_avl = NULL;

    arv_avl = insere_ABBB(arv_avl, 25, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 20, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 30, "QUA", qua1);

    arv_avl = insere_ABBB(arv_avl, 16, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 22, "QUA", qua1);

    arv_avl = insere_ABBB(arv_avl, 29, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 31, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 21, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 24, "QUA", qua1);
    
    imprime_repres_ABBB(arv_avl, 0);
    printf("\nInserindo o 23\n");
    arv_avl = insere_ABBB(arv_avl, 23, "QUA", qua1);
    imprime_repres_ABBB(arv_avl, 0);
    printf("\n");

    printf("################################\n");

    destroi_AG(arv_avl);
    arv_avl = NULL;

    arv_avl = insere_ABBB(arv_avl, 25, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 20, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 16, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 12, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 18, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 22, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 30, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 29, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 31, "QUA", qua1);
    
    imprime_repres_ABBB(arv_avl, 0);
    printf("\nInserindo o 10\n");
    arv_avl = insere_ABBB(arv_avl, 10, "QUA", qua1);
    imprime_repres_ABBB(arv_avl, 0);
    printf("\n");

    printf("################################\n");

    destroi_AG(arv_avl);
    arv_avl = NULL;

    arv_avl = insere_ABBB(arv_avl, 12, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 10, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 13, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 8, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 11, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 20, "QUA", qua1);

    imprime_repres_ABBB(arv_avl, 0);
    printf("\nInserindo o 15\n");
    arv_avl = insere_ABBB(arv_avl, 15, "QUA", qua1);
    imprime_repres_ABBB(arv_avl, 0);
    printf("\n");

    printf("################################\n");

    destroi_AG(arv_avl);
    arv_avl = NULL;

    arv_avl = insere_ABBB(arv_avl, 30, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 14, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 35, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 12, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 20, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 33, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 37, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 11, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 18, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 22, "QUA", qua1);

    imprime_repres_ABBB(arv_avl, 0);
    printf("\nInserindo o 21\n");
    arv_avl = insere_ABBB(arv_avl, 21, "QUA", qua1);
    imprime_repres_ABBB(arv_avl, 0);
    printf("\n");

    destroi_AG(arv_avl);
}

void imprimeItem(void *pItem, char* pTipoItem){
    printf("Imprindo forma geometrica %s...", pTipoItem);
    if (strcmp(pTipoItem, "QUA") == 0){
        imprimeQuadrado((TQ*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "TRI") == 0){
        imprimeTriangulo((TT*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "RET") == 0){
        imprimeRetangulo((TR*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "TRA") == 0){
        imprimeTrapezio((TZ*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "CIR") == 0){
        imprimeCirculo((TC*)pItem);
        return;
    }
}