#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_bbb.h"

void imprimeItem(void *pItem, char* pTipoItem);

int main(void){
    TQ *qua1 = criaQuadrado(10);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 20, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 22, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 16, "QUA", qua1, 20);
    arv_gen = insere_AG(arv_gen, 21, "QUA", qua1, 22);
    arv_gen = insere_AG(arv_gen, 24, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 23, "QUA", qua1, 24);

    imprime_AG(arv_gen, imprimeItem);
    printf("\nImprimindo pos rse\n");
    arv_gen = rse(arv_gen);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    arv_gen = remove_AG(arv_gen, 20);
    arv_gen = remove_AG(arv_gen, 22);
    arv_gen = remove_AG(arv_gen, 16);
    arv_gen = remove_AG(arv_gen, 21);
    arv_gen = remove_AG(arv_gen, 24);
    arv_gen = remove_AG(arv_gen, 23);

    arv_gen = insere_AG(arv_gen, 20, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 22, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 16, "QUA", qua1, 20);
    arv_gen = insere_AG(arv_gen, 12, "QUA", qua1, 16);
    arv_gen = insere_AG(arv_gen, 18, "QUA", qua1, 20);
    arv_gen = insere_AG(arv_gen, 10, "QUA", qua1, 12);

    imprime_AG(arv_gen, imprimeItem);
    printf("\nImprimindo pos rsd\n");
    arv_gen = rsd(arv_gen);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    arv_gen = remove_AG(arv_gen, 20);
    arv_gen = remove_AG(arv_gen, 22);
    arv_gen = remove_AG(arv_gen, 16);
    arv_gen = remove_AG(arv_gen, 12);
    arv_gen = remove_AG(arv_gen, 18);
    arv_gen = remove_AG(arv_gen, 10); 

    arv_gen = insere_AG(arv_gen, 13, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 20, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 15, "QUA", qua1, 20);

    imprime_AG(arv_gen, imprimeItem);
    printf("\nImprimindo pos rde\n");
    arv_gen = rde(arv_gen);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n");   

    arv_gen = remove_AG(arv_gen, 13);
    arv_gen = remove_AG(arv_gen, 20);
    arv_gen = remove_AG(arv_gen, 15);

    arv_gen = insere_AG(arv_gen, 30, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 14, "QUA", qua1, 30);
    arv_gen = insere_AG(arv_gen, 35, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 12, "QUA", qua1, 14);
    arv_gen = insere_AG(arv_gen, 20, "QUA", qua1, 30);
    arv_gen = insere_AG(arv_gen, 33, "QUA", qua1, 35);
    arv_gen = insere_AG(arv_gen, 37, "QUA", qua1, 0);
    arv_gen = insere_AG(arv_gen, 11, "QUA", qua1, 12);
    arv_gen = insere_AG(arv_gen, 18, "QUA", qua1, 20);
    arv_gen = insere_AG(arv_gen, 22, "QUA", qua1, 30);
    arv_gen = insere_AG(arv_gen, 21, "QUA", qua1, 22);

    imprime_AG(arv_gen, imprimeItem);
    printf("\nImprimindo pos red\n");
    arv_gen = red(arv_gen);
    imprime_AG(arv_gen, imprimeItem);
    printf("\n"); 

    destroi_AG(arv_gen);
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