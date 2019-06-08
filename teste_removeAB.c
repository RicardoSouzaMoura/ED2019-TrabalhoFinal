#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_b.h"

void imprimeItem(void *pItem, char* pTipoItem);

int main(void){
    TQ *qua = criaQuadrado(10);
    TT *tri = criaTriangulo(10, 2);
    TC *cir = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    TQ *qua1 = criaQuadrado(10);
    TT *tri1 = criaTriangulo(10, 2);
    TC *cir1 = criaCirculo(30);
    TZ *tra1 = criaTrapezio(40, 20, 2);
    TR *ret1 = criaRetangulo(50, 2);

    TAB *arv_b = NULL;
    
    arv_b = insere_AB(arv_b, 2, 1, "QUA", qua);    
    arv_b = insere_AB(arv_b, 2, 2, "TRI", tri);
    arv_b = insere_AB(arv_b, 2, 3, "CIR", cir);
    arv_b = insere_AB(arv_b, 2, 4, "TRA", tra);
    arv_b = insere_AB(arv_b, 2, 5, "RET", ret);

    arv_b = insere_AB(arv_b, 2, 10, "QUA", qua1);    
    arv_b = insere_AB(arv_b, 2, 20, "TRI", tri1);
    arv_b = insere_AB(arv_b, 2, 300, "CIR", cir1);
    arv_b = insere_AB(arv_b, 2, 8, "TRA", tra1);
    arv_b = insere_AB(arv_b, 2, 9, "RET", ret1);
    
    imprime_AB(arv_b,0);
    printf("\n");

    arv_b = retira(arv_b,20,2);
    imprime_AB(arv_b,0);
    //printf("%d\n",arv_b->filho[2]->cod[2]);
    //printf("%s\n",arv_b->nos[2]->tipoItem);

    arv_b = retira(arv_b,300,2);
    imprime_AB(arv_b,0);
    printf("\n");

    arv_b = retira(arv_b,4,2);
    imprime_AB(arv_b,0);
    printf("\n");
    arv_b = retira(arv_b,5,2);
    imprime_AB(arv_b,0);
    //printf("%s\n",arv_b->filho[0]->nos[0]->tipoItem);
    


    arv_b = Libera_AB(arv_b,2);
    imprime_AB(arv_b,0);
    
    //free(arv_b->filho[0]->nos[0]); o Libera_AB já deu free em tudo!

    /*
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
    */
    
    //imprime_AG(arv_gen, imprimeItem); se não comentar depois que eu destruo dá segmantation default


    //TAG * pai = busca_pai (arv_gen,1);
    //if(!pai) printf("NULL");
    //printf("pai do circulo %d", pai->cod);


    free(qua);
    free(tri);
    free(cir);
    free(tra);
    free(ret);
    

    //free(arv_gen);
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