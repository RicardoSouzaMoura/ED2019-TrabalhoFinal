#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "formas_geometricas.h"
#include "arvore_generica.h"

TAG* split_string(char* sFrase, TAG* arv_gen);
TAG* ler(char* path, TAG* arv_gen);


// metodo que recebe uma linha do arquiv0
// separa as informacoes e cria um elemento
// da arvore generica
TAG* split_string(char* sFrase, TAG* arv_gen){
    char *psRetorno;
    int codItem;
    int codPai;
    char aux;
    char *tipo;
    int dim[10];
    
    psRetorno=strtok(sFrase, "/");

    codItem=atoi(psRetorno);

    psRetorno=strtok('\0', "/");

    codPai=atoi(psRetorno);
    //printf("item: %d e Pai: %d\n",codItem,codPai);
    int j=0;
    int cont=2;
    do {
      //printf("%c\n",psRetorno);
      psRetorno=strtok('\0', " ");

      if(psRetorno){
         if(cont==2) {
            tipo=psRetorno;
         }
         if(cont>2){
             dim[j]=atoi(psRetorno);
             j=j+1;
         }
         cont=cont+1;
      }
    } while(psRetorno);

    if(strcmp("RET",tipo) == 0){
        TR*ret = criaRetangulo(dim[0], dim[1]);
        arv_gen = insere_AG(arv_gen, codItem, "RET", ret, codPai);
    }
    else if(strcmp("QUA",tipo) == 0){
        TQ*qua = criaQuadrado(dim[0]);
        arv_gen = insere_AG(arv_gen, codItem, "QUA", qua, codPai);
    }
    else if(strcmp("TRA",tipo)==0){
        TZ*tra = criaTrapezio(dim[0], dim[1], dim[2]);
        arv_gen = insere_AG(arv_gen, codItem, "TRA", tra, codPai);
    }
    else if(strcmp("CIR",tipo)==0){
        TC*cir = criaCirculo(dim[0]);
        arv_gen = insere_AG(arv_gen, codItem, "CIR", cir, codPai);
    }
    else if(strcmp("TRI",tipo)==0){
        TT*tri = criaTriangulo(dim[0], dim[1]);
        arv_gen = insere_AG(arv_gen, codItem, "TRI", tri, codPai);
    }

    return arv_gen;
}

// Metodo que faz a leitura de um arquivo cujo caminho é path
// para uma arvore arq_gen
TAG* ler(char* path, TAG* arv_gen){

    int i = 0;
    int numPalavras = 0;
    char* palavras[500];
    char line[500];

    FILE *arquivo;
    arquivo = fopen(path,"r");

    if (arquivo){
        while(fgets(line, sizeof(line), arquivo) != NULL){
            palavras[i] = strdup(line);

            arv_gen = split_string(palavras[i],arv_gen);
            //split_string(palavras[i],arv_gen);
            numPalavras++;
        }

        fclose(arquivo);
    }
    else{
        printf("Erro ao abrir o arquivo %s", path);
    }
    return arv_gen;
}
