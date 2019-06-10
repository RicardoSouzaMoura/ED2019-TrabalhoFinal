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
    arv_avl = insere_ABBB(arv_avl, 20, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 14, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 30, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 12, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 18, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 22, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 35, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 11, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 21, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 33, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 37, "QUA", qua1);

    imprime_repres_ABBB(arv_avl, 0);

    arv_avl = remove_ABBB(arv_avl, 20);

    printf("################################\n");
    imprime_repres_ABBB(arv_avl, 0);

    arv_avl = insere_ABBB(arv_avl, 13, "QUA", qua1);
    arv_avl = insere_ABBB(arv_avl, 36, "QUA", qua1);

    printf("################################\n");
    imprime_repres_ABBB(arv_avl, 0);

    arv_avl = remove_ABBB(arv_avl, 12);
    printf("################################\n");
    imprime_repres_ABBB(arv_avl, 0);

    arv_avl = remove_ABBB(arv_avl, 35);
    printf("################################\n");
    imprime_repres_ABBB(arv_avl, 0);

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