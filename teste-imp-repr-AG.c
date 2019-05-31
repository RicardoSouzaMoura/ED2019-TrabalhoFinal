#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeItem(void *pItem, char* pTipoItem);

int main(void){

    TQ *qua = criaQuadrado(10);
    TT *tri = criaTriangulo(10, 2);
    TC *cir = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 10, "QUA", qua, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 10);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 10);
    arv_gen = insere_AG(arv_gen, 5, "TRA", tra, 10);
    arv_gen = insere_AG(arv_gen, 1, "RET", ret, 2);
    arv_gen = insere_AG(arv_gen, 8, "QUA", qua, 3);
    arv_gen = insere_AG(arv_gen, 7, "TRI", tri, 3);
    arv_gen = insere_AG(arv_gen, 9, "CIR", cir, 3);
    arv_gen = insere_AG(arv_gen, 12, "TRA", tra, 5);
    arv_gen = insere_AG(arv_gen, 6, "RET", ret, 5);
    arv_gen = insere_AG(arv_gen, 11, "CIR", cir, 5);
    arv_gen = insere_AG(arv_gen, 13, "TRA", tra, 3);
    arv_gen = insere_AG(arv_gen, 14, "RET", ret, 13);
    arv_gen = insere_AG(arv_gen, 15, "QUA", qua, 13);
    arv_gen = insere_AG(arv_gen, 16, "TRI", tri, 13);
    arv_gen = insere_AG(arv_gen, 17, "CIR", cir, 13);

    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    imprime_repres_AG(arv_gen, 0);
    printf("\n");

    destroi_AG(arv_gen);
    arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 1, "QUA", qua, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 1);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);
    arv_gen = insere_AG(arv_gen, 4, "TRA", tra, 2);
    arv_gen = insere_AG(arv_gen, 5, "RET", ret, 3);
    arv_gen = insere_AG(arv_gen, 6, "QUA", qua, 3);
    arv_gen = insere_AG(arv_gen, 7, "TRI", tri, 4);
    arv_gen = insere_AG(arv_gen, 8, "CIR", cir, 4);
    arv_gen = insere_AG(arv_gen, 9, "TRA", tra, 5);
    arv_gen = insere_AG(arv_gen, 10, "RET", ret, 6);
    arv_gen = insere_AG(arv_gen, 11, "TRA", tra, 10);
    arv_gen = insere_AG(arv_gen, 12, "RET", ret, 8);
    arv_gen = insere_AG(arv_gen, 13, "RET", ret, 1);

    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    imprime_repres_AG(arv_gen, 0);
    printf("\n");
    
    destroi_AG(arv_gen);

    free(qua);
    free(tri);
    free(cir);
    free(tra);
    free(ret);
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