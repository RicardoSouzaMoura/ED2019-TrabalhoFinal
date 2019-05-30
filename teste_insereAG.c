#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeItem(TAG *arv_gen);

int convert_string(char*text){
    int dim=strlen(text);
    int acm=0;
    int i=0;
    //printf("dimensao: %d\n", dim);
    if(dim==1){
        return atoi(text);
    }
    if(dim>1){
        for(i=0;dim-1-i>=0;i++){
            printf("digito: %d\n",atoi(text[i]));
            acm=acm+atoi(text[i])*pow(10,dim-1-i);
        }
    }
    return acm;
}

TAG* split_string(char*sFrase,TAG*arv_gen)
{
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
   do
   {
      //printf("%c\n",psRetorno);
      psRetorno=strtok('\0', " ");


      if(psRetorno)
      {
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

    if(strcmp("RET",tipo)==0){
        TR*ret = criaRetangulo(dim[0], dim[1]);
        arv_gen = insere_AG(arv_gen, codItem, "RET", ret, codPai);
    }

   if(strcmp("QUA",tipo)==0){
        //printf("QQQQQQ\n");
        TQ*qua = criaQuadrado(dim[0]);
        arv_gen = insere_AG(arv_gen, codItem, "QUA", qua, codPai);
   }
   if(strcmp("TRA",tipo)==0){
        TZ*tra = criaTrapezio(dim[0], dim[1], dim[2]);
        arv_gen = insere_AG(arv_gen, codItem, "TRA", tra, codPai);
   }
   if(strcmp("CIR",tipo)==0){
        TC*cir = criaCirculo(dim[0]);
        arv_gen = insere_AG(arv_gen, codItem, "CIR", cir, codPai);
   }
   if(strcmp("TRI",tipo)==0){
        TT*tri = criaTriangulo(dim[0], dim[1]);
        arv_gen = insere_AG(arv_gen, codItem, "TRI", tri, codPai);
   }

    return arv_gen;
}


TAG* ler(char*path,TAG*arv_gen){

    int i = 0;
    int numPalavras = 0;
    char* palavras[500];
    char line[500];

    FILE *arquivo;
    arquivo = fopen(path,"r");

    while(fgets(line, sizeof(line), arquivo) != NULL)
    {
        palavras[i] = strdup(line);

        arv_gen=split_string(palavras[i],arv_gen);
        //split_string(palavras[i],arv_gen);
        numPalavras++;
    }

    fclose(arquivo);
    return arv_gen;
}

int main(void){
    char path[]="/Users/sergiojunior/ED2019-TrabalhoFinal/exemplo_AGII.txt";

    //convert_string("50");

    TAG *arv_gen = NULL;
    arv_gen=ler(path,arv_gen);


    /*TQ *qua = criaQuadrado(10);
    TT *tri = criaTriangulo(10, 2);
    TC *cir = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    //alterando dimensao
    TR *ret2 = criaRetangulo(11, 11);
    TZ *tra3 = criaTrapezio(11, 11, 2);
    TQ *qua2 = criaQuadrado(11);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 1, "QUA", qua, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 0);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);
    arv_gen = insere_AG(arv_gen, 4, "TRA", tra, 0);
    arv_gen = insere_AG(arv_gen, 5, "RET", ret, 2);
    arv_gen = insere_AG(arv_gen, 6, "RET", ret, 5);*/

    imprime_AG(arv_gen, imprimeItem);

    //executando alteracao
    /*arv_gen = altera_dim(arv_gen, 1, qua2);
    arv_gen = altera_dim(arv_gen, 4, tra3);
    printf("\n\n");*/

    //imprimindo nova arvore com dimensao nova
    //imprime_AG(arv_gen, imprimeItem);

    //free(qua);
    //free(tri);
    //free(cir);
    //free(tra);
    //free(ret);

    //free(arv_gen);
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
