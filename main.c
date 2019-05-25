#include <stdlib.h>
#include <stdio.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeMenu();

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
            TT *tri = criaTriangulo(10, 4);
            printf("area: %f\n", tri->area);
            arv_gen = insere_AG(arv_gen, 1, tri, 0);
            break;

        case 3:;
            arv_gen = busca_AG(arv_gen, 1);
            printf("%d", arv_gen->cod);
            TT *triangulo = (TT*)arv_gen->info;
            printf("area: %f\n", triangulo->area);
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
}