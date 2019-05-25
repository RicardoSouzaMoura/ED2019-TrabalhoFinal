#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeMenu();
TQ *criaQuadradoViaMenu();
TR *criaRetanguloViaMenu();
TZ *criaTrapezioViaMenu();
TT *criaTrianguloViaMenu();
TC *criaCirculoViaMenu();

void imprimeItem(TAG *arv_gen);

TAG* implementaMenuInsere(TAG* arv_gen);

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
            arv_gen = implementaMenuInsere(arv_gen);
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
    printf("(2) Inserir figura na AG\n");
    printf("(3) Buscar figura pelo id na AG\n");
    printf("(4) Imprimir arvore AG\n");
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

TAG* implementaMenuInsere(TAG* arv_gen){
    char* lTipoItem;
    int lCod;
    int lCodPai;
    printf("Qual tipo de figura (QUA, TRI, TRA, CIR, RET): ");
    scanf(" %3[^\n]", lTipoItem);
    printf("\nQual codigo: ");
    scanf("%d", &lCod);
    printf("\nQual codigo do pai (0 == raiz): ");
    scanf("%d", &lCodPai);

    void *info = NULL;
    if (strcmp(lTipoItem, "QUA") == 0){
        info = criaQuadradoViaMenu();
    }
    else if (strcmp(lTipoItem, "TRI") == 0){
        info = criaTrianguloViaMenu();
    }
    else if (strcmp(lTipoItem, "RET") == 0){
        info = criaRetanguloViaMenu();
    }
    else if (strcmp(lTipoItem, "TRA") == 0){
        info = criaTrapezioViaMenu();
    }
    else if (strcmp(lTipoItem, "CIR") == 0){
        info = criaCirculoViaMenu();
    }

    arv_gen = insere_AG(arv_gen, lCod, lTipoItem, info, lCodPai);
    return arv_gen;
}

TQ *criaQuadradoViaMenu(){
    int lLado;
    printf("\nQual o lado: ");
    scanf("%d", &lLado);
    return criaQuadrado(lLado);
}

TT *criaTrianguloViaMenu(){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaTriangulo(lBase, lAltura);
}

TR *criaRetanguloViaMenu(){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaRetangulo(lBase, lAltura);
}

TZ *criaTrapezioViaMenu(){
    int lBaseMaior, lBaseMenor, lAltura;
    printf("\nQual a base maior: ");
    scanf("%d", &lBaseMaior);
    printf("\nQual a base menor: ");
    scanf("%d", &lBaseMenor);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaTrapezio(lBaseMenor, lBaseMaior, lAltura);
}

TC *criaCirculoViaMenu(){
    int lRaio;
    printf("\nQual o raio: ");
    scanf("%d", &lRaio);
    return criaCirculo(lRaio);
}