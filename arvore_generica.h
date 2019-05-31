#include <stdlib.h>
#include <stdio.h>

typedef struct AG {
    int cod;
    struct info *no;
    //void *info;
    struct AG *filho, *irmao;
}TAG;

typedef struct info{
    char* tipoItem;
    void *info;
}TNO;

typedef void (funcao)(TAG* argumento);

TAG *cria_AG(int pCodItem, char* pTipoItem, void *info);
TAG * altera_dim (TAG *pAg, int pCodItem, void* pItem);

TAG *insere_AG(TAG* pAg, int pCodItem, char* tipoItem, void* pItem, int pCodPai);

TAG *busca_AG(TAG *pAg, int pCodItem);

TAG *remove_AG(TAG *pAg, int pCodItem);

void imprime_AG(TAG *pAg, funcao *func);

TAG *cria_AG(int pCodItem, char* pTipoItem, void *info){
    TAG *ag = (TAG*)malloc(sizeof(TAG));
    TNO *no = (TNO*)malloc(sizeof(TNO));
    no->info = info;
    no->tipoItem = pTipoItem;
    ag->no = no;
    ag->filho = NULL;
    ag->irmao = NULL;
    ag->cod = pCodItem;
    return ag;
}

/*TAG *cria_AG(int pCodItem, void *info){
    TAG *ag = (TAG*)malloc(sizeof(TAG));
    ag->info = info;
    ag->filho = NULL;
    ag->irmao = NULL;
    ag->cod = pCodItem;
    return ag;
}*/

// busca um item pelo codigo
// percorrimento pré-ordem (profundidade)
// RAIZ FILHO IRMAO
TAG *busca_AG(TAG *pAg, int pCodItem){
    if ((!pAg) || pAg->cod == pCodItem) return pAg;
    TAG *pAgFilho = busca_AG(pAg->filho, pCodItem);
    if (pAgFilho) return pAgFilho;
    return busca_AG(pAg->irmao, pCodItem);
}

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

/*TAG * insere_AG2(TAG *pAg, int pCodItem, char* pTipoItem, void* pItem, int pCodPai){
    TAG *item = busca_AG(pAg, pCodItem);
    if (item){
        printf("Warning !!! codItem %d ja existe.\n", pCodItem);
        return pAg;
    }
    if(pCodPai == 0){

    }
    TAG *pai = busca_AG(pAg, pCodPai);
    if (pCodPai !=0 && !pAg){
        printf("Erro !! Tentativa de inserir um no nao pai em uma arvore vazia.\n");
        exit(1);
    }
    if (pCodPai != 0){

        if (pai){
            TAG *filho = pai->filho;
            // primogenito
            if (!filho){
                pai->filho = cria_AG(pCodItem, pTipoItem, pItem);
                return pAg;
            }
            // percorrendo ate chegar no ultimo irmao
            while(filho->irmao) filho = filho->irmao;
            TAG* novoFilho = cria_AG(pCodItem, pTipoItem, pItem);
            filho->irmao == novoFilho;
            return pAg;
        }
        else{
            printf("Warning !!! Pai %d nao encontrado.\n", pCodPai);
        }
        return pAg;
    }

    //codPai == 0
    return cria_AG(pCodItem, pTipoItem, pItem);
}*/

// o filho mais antigo (primeiro da lista) ocupara o lugar do pai
// seus irmaos entraram como filho dele no final da lista de filhos dele
// TODO


// percorrimento pré-ordem  (profundidade)
// RAIZ FILHO IRMAO
void imprime_AG(TAG *pAg, funcao *func){
    if (pAg){
        printf("%d/", pAg->cod);
        func(pAg);
        printf("\n");

        imprime_AG(pAg->filho, func);

        imprime_AG(pAg->irmao, func);
    }
}




TAG * altera_dim (TAG *pAg, int pCodItem, void* pItem){
    TAG *item = busca_AG(pAg, pCodItem);
    if (item==NULL){
        printf("Erro!! item %d nao encontrado.\n", pCodItem);
        return pAg;
    }
    else{
        item->no->info=pItem;
    }
    return pAg;
}
