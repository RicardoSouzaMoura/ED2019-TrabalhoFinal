#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_b.h"
#include "leitura_arquivo.h"

int main(void){

    char path[]="/home/ricardo/Documents/mestrado/ED/ED2019-TrabalhoFinal/exemplo_AG.txt";

    TAG *arv_gen = NULL;
    arv_gen=ler(path,arv_gen);

    imprime_repres_AG(arv_gen, 0);
    printf("\n");
    printf("Finalizada AG \n");

    TAB *arv_b = NULL;
    arv_b = transforma_AG_AB(arv_gen, 3);
    printf("Finalizada AB \n");
    imprime_AB(arv_b, 0);
}
