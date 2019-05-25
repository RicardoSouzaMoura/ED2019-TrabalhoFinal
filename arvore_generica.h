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
    if (!pAg) return pAg;
    if (pAg->cod == pCodItem) return pAg;

    pAg = busca_AG(pAg->filho, pCodItem);
    if (pAg) return pAg;
    pAg = busca_AG(pAg->irmao, pCodItem);
}

TAG * insere_AG(TAG *pAg, int pCodItem, char* pTipoItem, void* pItem, int pCodPai){
    TAG *item = busca_AG(pAg, pCodItem);
    if (item){
        printf("Warning !!! codItem %d ja existe.\n", pCodItem);
        return pAg;
    }
    if (pCodPai !=0 && !pAg){
        printf("Erro !! Tentativa de inserir um no nao pai em uma arvore vazia.\n");
        exit(1);
    }
    if (pCodPai != 0){
        TAG *pai = busca_AG(pAg, pCodPai);
        if (pai){
            TAG *filho = pai->filho;
            // percorrendo ate chegar no ultimo irmao
            while(filho->irmao) filho = filho->irmao;
            TAG* novoFilho = cria_AG(pCodItem, pTipoItem, pItem);
            filho->irmao == novoFilho;
        }
        else{
            printf("Warning !!! Pai %d nao encontrado.\n", pCodPai);
        }
        return pAg;
    }
    
    return cria_AG(pCodItem, pTipoItem, pItem);    
}

// o filho mais antigo (primeiro da lista) ocupara o lugar do pai
// seus irmaos entraram como filho dele no final da lista de filhos dele
// TODO- ainda esta incompleto
TAG *remove_AG(TAG *pAg, int pCodItem){
    TAG *item = busca_AG(pAg, pCodItem);
    TAG *novoPai = item->filho;
    // caso o item a ser retirado tenha filhos
    // precisa pegar o filho mais antigo para
    // virar novo pai
    if (novoPai){
        TAG *filhosNovoPai = novoPai->filho;
        // percorrendo os filhos do novo pai
        while(filhosNovoPai->irmao) filhosNovoPai = filhosNovoPai->irmao;
    }
}

// percorrimento pré-ordem  (profundidade)
// RAIZ FILHO IRMAO
void imprime_AG(TAG *pAg, funcao *func){
    if (pAg){
        printf("%d/", pAg->cod);
        func(pAg);

        imprime_AG(pAg->filho, func);
        
        imprime_AG(pAg->irmao, func);
    }
}
