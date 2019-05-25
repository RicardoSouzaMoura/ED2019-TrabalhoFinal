#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeMenu();

void imprimeItem(TAG *arv_gen);

int main(void){
    int opcao = -1;

    printf("Bem vindo !!!\n");

    TAG *arv_gen = NULL;
    
    while(opcao != 0){
        imprimeMenu();
        scanf("%d", &opcao);
        printf("Opcao escolhida: %d\n", opcao);
        switch (opcao)
        {
        case 1:;
            //TODO
            break;

        case 2:;
            TQ *qua = criaQuadrado(10);
            printf("area: %f\n", qua->area);
            arv_gen = insere_AG(arv_gen, 1, "QUA", qua, 0);
            break;

        case 3:;
            arv_gen = busca_AG(arv_gen, 1);
            printf("%d", arv_gen->cod);
            TQ *qua1 = (TQ*)arv_gen->no->info;
            //TT *triangulo = (TT*)arv_gen->info;
            printf("area: %f\n", qua1->area);
            break;

        case 4:;
            printf("Imprimindo arvore...\n");
            imprime_AG(arv_gen, imprimeItem);
            break;
        
        default:
            break;
        }        
    }
}

void imprimeMenu(){
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(1) Ler Arquivo inicial\n");
    printf("(2) Inserir figura\n");
    printf("(3) Buscar figura pelo id\n");
    printf("(4) Imprimir arvore\n");
}

void imprimeItem(TAG *arv_gen){
    char *lTipoItem = arv_gen->no->tipoItem;
    printf("Imprindo forma geometrica %s...", lTipoItem);
    if (strcmp(lTipoItem, "QUA") == 0){
        imprimeQuadrado((TQ*)arv_gen->no->info);
        return;
    }
    if (strcmp(lTipoItem, "TRI") == 0){
        imprimeTriangulo((TR*)arv_gen->no->info);
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