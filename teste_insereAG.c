#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formas_geometricas.h"
#include "arvore_generica.h"

void imprimeItem(void *pItem, char* pTipoItem);

TAG * insere_AG(TAG *pAg, int pCodItem, char* pTipoItem, void* pItem, int pCodPai){
    int opt;
    if (pCodPai == 0){
        if (!pAg){
            return cria_AG(pCodItem, pTipoItem, pItem);
        }
        else{
            TAG*check=busca_AG(pAg,pCodItem);
            if (check){
                printf("Item %d ja existente. Gostaria de atualizar suas dimensoes? [y-1/n-0]",pCodItem);
                scanf("%d",&opt);

                if(opt==1) pAg = altera_dim(pAg,pCodItem,pItem);
                return pAg;
            }else{
                pAg->irmao = insere_AG(pAg->irmao, pCodItem, pTipoItem, pItem, pCodPai);
            }
        }
    }
    else{
        TAG *pai = busca_AG(pAg, pCodPai);
        if (!pai){
            printf("Erro !! Pai %d nao encontrado.\n", pCodPai);
            return pAg;
        }
        else{
            TAG*check=busca_AG(pAg,pCodItem);
            if (check){
                printf("Item %d ja existente. Gostaria de atualizar suas dimensoes? [y-1/n-0]",pCodItem);
                scanf("%d",&opt);
                if(opt==1) pAg = altera_dim(pAg,pCodItem,pItem);
                return pAg;
            }else{
                pai->filho = insere_AG(pai->filho, pCodItem, pTipoItem, pItem, 0);
            }

        }
    }
    return pAg;
}


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


    TC *cir = criaCirculo(666);
    /*TT *tri = criaTriangulo(10, 2);
    TC *cir = criaCirculo(30);
    TZ *tra = criaTrapezio(40, 20, 2);
    TR *ret = criaRetangulo(50, 2);

    //alterando dimensao
    TR *ret2 = criaRetangulo(11, 11);
    TZ *tra3 = criaTrapezio(11, 11, 2);
    TQ *qua2 = criaQuadrado(11);

    TAG *arv_gen = NULL;
    arv_gen = insere_AG(arv_gen, 1, "QUA", qua, 0);
    arv_gen = insere_AG(arv_gen, 2, "TRI", tri, 1);
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);
    arv_gen = insere_AG(arv_gen, 4, "TRA", tra, 0);
    arv_gen = insere_AG(arv_gen, 5, "RET", ret, 2);*/
    arv_gen = insere_AG(arv_gen, 3, "CIR", cir, 1);

    imprime_AG(arv_gen, imprimeItem);
    printf("\n");
    
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
    //imprime_AG(arv_gen, imprimeItem); se não comentar depois que eu destruo dá segmantation default


    //TAG * pai = busca_pai (arv_gen,1);
    //if(!pai) printf("NULL");
    //printf("pai do circulo %d", pai->cod);

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