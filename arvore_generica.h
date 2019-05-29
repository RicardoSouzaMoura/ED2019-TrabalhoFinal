#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AG {
    int cod;
    struct info *no;
    struct AG *filho, *irmao;
}TAG;

typedef struct info{
    char* tipoItem;
    void *info;
}TNO;

typedef void (funcaoImpItem)(void* item, char* tipoItem);

TAG * inicializa();

TAG *cria_elem_AG(int pCodItem, char* pTipoItem, void *info);

TAG *insere_AG(TAG* pAg, int pCodItem, char* tipoItem, void* pItem, int pCodPai);

TAG *busca_AG(TAG *pAg, int pCodItem);

TAG *remove_AG(TAG *pAg, int pCodItem);


TAG * busca_pai (TAG * a, int pCodItem);

void libera_elem(TAG * p);

void destroi_AG(TAG * p);

void imprime_AG(TAG *pAg, funcaoImpItem *func);

void imprime_elem_AG(TAG *pAg, funcaoImpItem *func);

TAG * inicializa(){
    return NULL;
}

TAG *cria_elem_AG(int pCodItem, char* pTipoItem, void *info){
    TAG *ag = (TAG*)malloc(sizeof(TAG));
    TNO *no = (TNO*)malloc(sizeof(TNO));
    no->tipoItem = (char*)malloc(sizeof(char)*3);
    no->info = info;
    strcpy(no->tipoItem, pTipoItem);
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
    if (pCodPai == 0){
        if (!pAg){
            return cria_elem_AG(pCodItem, pTipoItem, pItem);
        }
        else{
            pAg->irmao = insere_AG(pAg->irmao, pCodItem, pTipoItem, pItem, pCodPai);
        }
    }
    else{
        TAG *pai = busca_AG(pAg, pCodPai);
        if (!pai){
            printf("Erro !! Pai %d nao encontrado.\n", pCodPai);
            return pAg;
        }
        else{
            pai->filho = insere_AG(pai->filho, pCodItem, pTipoItem, pItem, 0);
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
TAG *remove_AG(TAG *pAg, int pCodItem){
    TAG * p = busca_AG(pAg, pCodItem);
    if (!p) return pAg;
    TAG * pai = busca_pai(pAg, pCodItem);
    if(pai){
        if(pai->filho == p){//nó a ser removido é o filho mais velho
            if(p->irmao){// vejo se o nó a ser removido tem irmao
                pai->filho = p->irmao;
                TAG * aux = p->irmao->filho;
                if(!aux) p->irmao->filho = p->filho;
                else{
                    while (aux->irmao) aux = aux->irmao;
                    aux->irmao = p->filho;
                }
            }
            else{ // quando não tiver irmao
                pai->filho = p->filho;
            }
        }
        else{// nó a ser removido não é o filho mais velho
            TAG * aux = pai->filho->filho;
            if(!aux) pai->filho->filho = p->filho;
            else{
                while (aux->irmao) aux = aux->irmao;
                aux->irmao = p->filho;
            }
            aux = pai->filho;
            while(aux->irmao!=p) aux=aux->irmao;
            aux->irmao = p->irmao;
        }
    }
    else{// quando o pai for NULL
        if(p->cod == pAg->cod){
            if(!p->irmao) pAg=pAg->filho;// caso em que só há um nó na primeira camada;
            else{// caso que existem mais de um nó na primeira camada
                TAG * aux = p->irmao->filho;
                if(!aux){
                    p->irmao->filho = p->filho;
                    pAg = pAg->irmao;
                } 
                else{
                    while (aux->irmao) aux = aux->irmao;
                    aux->irmao = p->filho;
                    pAg = pAg->irmao;
                }

            }
        }
        else{
            TAG * aux = pAg;
            while(aux->irmao!=p) aux=aux->irmao;
            aux->irmao = p->irmao;
            TAG * q = aux;
            aux = aux->filho;
            if(!aux) q->filho = p->filho;
            else{
                while(aux->irmao) aux = aux->irmao;
                aux->irmao = p->filho;
            }
        }
    }
    libera_elem(p);
    return pAg;
}
TAG * busca_pai (TAG * a, int pCodItem){
    if(!a) return a;
    TAG * p = a->filho;
    while(p&&(p->cod!=pCodItem)) p=p->irmao;
    if (!p){
        TAG * esq = busca_pai(a->filho, pCodItem);
        if (esq) return esq;
        return busca_pai(a->irmao, pCodItem);
    }
    else return a;
}
void libera_elem(TAG * p){
    free(p->no);
    free(p);
}

void destroi_AG(TAG * p){
    if(p){
        destroi_AG(p->filho);
        destroi_AG(p->irmao);
        libera_elem(p);
    }
}

// percorrimento pré-ordem  (profundidade)
// RAIZ FILHO IRMAO
void imprime_AG(TAG *pAg, funcaoImpItem *func){
    if (pAg){
        imprime_elem_AG(pAg, func);

        imprime_AG(pAg->filho, func);
        
        imprime_AG(pAg->irmao, func);
    }
}

// imprime apenas o primeiro elemento da arvore sem
// fazer percorrimento.
// Esta funcao é usada no menu de busca elemento por id.
// tambem é utilizada na impressao da arvore inteira
void imprime_elem_AG(TAG *pAg, funcaoImpItem *func){
     if (pAg){
        printf("%d/", pAg->cod);
        func(pAg->no->info, pAg->no->tipoItem);
        printf("\n");
     }
     else{
         printf("Elemento NULO\n");
     }
}
