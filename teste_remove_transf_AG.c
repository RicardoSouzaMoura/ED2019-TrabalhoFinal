#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_b.h"

void imprimeItem(void *pItem, char* pTipoItem);


int main(void){

    TC *cir = criaCirculo(666);
    TT *tri = criaTriangulo(10, 2);
    TC *cir2 = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    //alterando dimensao
    TR *ret2 = criaRetangulo(11, 11);
    TZ *tra2 = criaTrapezio(11, 11, 2);
    TQ *qua2 = criaQuadrado(11);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 1, "CIR", cir2, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 1);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);
    arv_gen = insere_AG(arv_gen, 4, "TRA", tra, 1);
    arv_gen = insere_AG(arv_gen, 5, "RET", ret, 2);
    arv_gen = insere_AG(arv_gen, 3, "QUA", qua2, 1);

    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    TAB * teste = transforma_AG_AB(arv_gen,2);
    
    imprime_AB(teste,0);
    teste = Libera_AB(teste, 2);
    if(!teste) printf("POnteiro da arv_b está NULL pois ela foi removida\n");

    
    arv_gen = remove_AG(arv_gen, 1);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");
    arv_gen = remove_AG(arv_gen, 2);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");
    arv_gen = remove_AG(arv_gen, 3);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");
    arv_gen = remove_AG(arv_gen, 4);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");
    arv_gen = remove_AG(arv_gen, 5);
    imprime_AG(arv_gen, imprimeItem);
    destroi_AG(arv_gen);
    //imprime_AG(arv_gen, imprimeItem); //se não comentar depois que eu destruo dá segmantation default. estrutura da arv_gen foi destruida.

    free(qua2);
    free(tri);
    free(cir);
    free(tra);
    free(ret);
    free(cir2);
    free(tra2);
    free(ret2);
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