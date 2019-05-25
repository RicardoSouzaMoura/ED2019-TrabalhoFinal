#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeItem(TAG *arv_gen);

int main(void){
    TQ *qua = criaQuadrado(10);
    TT *tri = criaTriangulo(10, 2);
    TC *cir = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 1, "QUA", qua, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 0);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);
    arv_gen = insere_AG(arv_gen, 4, "TRA", tra, 0);
    arv_gen = insere_AG(arv_gen, 5, "RET", ret, 2);

    imprime_AG(arv_gen, imprimeItem);

    free(qua);
    free(tri);
    free(cir);
    free(tra);
    free(ret);

    free(arv_gen);
}

void imprimeItem(TAG *arv_gen){
    char *lTipoItem = arv_gen->no->tipoItem;
    printf("Imprindo forma geometrica %s...", lTipoItem);
    if (strcmp(lTipoItem, "QUA") == 0){
        imprimeQuadrado((TQ*)arv_gen->no->info);
        return;
    }
    if (strcmp(lTipoItem, "TRI") == 0){
        imprimeTriangulo((TT*)arv_gen->no->info);
        return;
    }
    if (strcmp(lTipoItem, "RET") == 0){
        imprimeRetangulo((TR*)arv_gen->no->info);
        return;
    }
    if (strcmp(lTipoItem, "TRA") == 0){
        imprimeTrapezio((TZ*)arv_gen->no->info);
        return;
    }
    if (strcmp(lTipoItem, "CIR") == 0){
        imprimeCirculo((TC*)arv_gen->no->info);
        return;
    }
}