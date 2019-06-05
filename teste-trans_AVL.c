#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_bbb.h"
#include "leitura_arquivo.h"

int main(void){

    char path[]="/home/arthur/learning/data-structure/ED2019-TrabalhoFinal/exemplo_AG.txt";

    TAG *arv_gen = NULL;
    arv_gen=ler(path,arv_gen);

    imprime_repres_AG(arv_gen, 0);
    printf("\n");
    printf("Finalizada AG \n");

    TAG *arv_avl = NULL;
    arv_avl = AG_2_AVL(arv_gen, arv_avl);
    printf("Finalizada AVL \n");
    imprime_repres_ABBB(arv_avl, 0);

    TAG *arv_avl1 = NULL;
    arv_avl1 = AG_2_AVL(arv_gen, arv_avl1);
    printf("Finalizada AVL2 \n");
    imprime_repres_ABBB(arv_avl1, 0);
}
