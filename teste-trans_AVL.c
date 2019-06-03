#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_bbb.h"




int main(void){

    char path[]="/Users/sergiojunior/ED2019-TrabalhoFinal/exemplo_AG.txt";

    TAG *arv_gen = NULL;
    arv_gen=ler(path,arv_gen);

    imprime_AG(arv_gen, imprimeItem);
    printf("\n");

    imprime_repres_AG(arv_gen, 0);
    printf("Finalizada AG \n");

    TAG *arv_avl = NULL;
    arv_avl=Ag2Avl(arv_gen,arv_avl);
    printf("Finalizada AVL \n");
    imprime_AG(arv_avl, imprimeItem);
    printf("\n\n");
    imprime_repres_ABBB(arv_avl,0);


}
