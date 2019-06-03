#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore_generica.h"
#include "leitura_arquivo.h"

void imprimeItem(void *pItem, char* pTipoItem);

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

int main(void){
    char *path;
    printf("Nome do arquivo: ");
    scanf(" %30[^\n]", path);

    TAG *arv_gen = NULL;
    arv_gen = ler(path, arv_gen);

    imprime_repres_AG(arv_gen, 0);

    imprime_AG(arv_gen, imprimeItem);
}