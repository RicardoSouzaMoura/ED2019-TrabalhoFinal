#ifndef FILE_AG_SEEN
#define FILE_AG_SEEN

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


TAG * altera_dim (TAG *pAg, int pCodItem, void* pItem);

TAG *cria_elem_AG(int pCodItem, char* pTipoItem, void *info);

TAG *insere_AG(TAG* pAg, int pCodItem, char* tipoItem, void* pItem, int pCodPai);

TAG *busca_AG(TAG *pAg, int pCodItem);

TAG *remove_AG(TAG *pAg, int pCodItem);


TAG * busca_pai (TAG * a, int pCodItem);

void libera_elem(TAG * p);

void destroi_AG(TAG * p);

void imprime_AG(TAG *pAg, funcaoImpItem *func);

void imprime_elem_AG(TAG *pAg, funcaoImpItem *func);

void imprime_repres_AG(TAG *pAg, int andar);

void imprime_repres_AG(TAG *pAg, int andar){
    if (pAg){
        TAG *aux1 = pAg->filho;
        int j=0;
        while(aux1){
            imprime_repres_AG(aux1->irmao, andar + 1);
            for(j=0; j<=andar; j++) printf("   ");
            printf("%d\n", aux1->cod);
            aux1 = aux1->irmao;
        }
    }
}

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

// Inserir com possibilidade de inserir irmao na raiz
// TODO: Nao permitir inserir item com mesmo codigo
/*TAG * insere_AG(TAG *pAg, int pCodItem, char* pTipoItem, void* pItem, int pCodPai){
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
}*/

// Inserir sem deixar raiz ter irmao
TAG * insere_AG(TAG *pAg, int pCodItem, char* pTipoItem, void* pItem, int pCodPai){
    // lista vazia. A insercao tem que ser da raiz
    if (!pAg){
        if (pCodPai == 0){
            return cria_elem_AG(pCodItem, pTipoItem, pItem);
        }
        printf("Erro ao inserir codItem: %d com codPai: %d. Lista ainda vazia !!!\n", pCodItem, pCodPai);
        return pAg;
    }

    // se a lista nao esta vazia entao já tem no raiz
    if (pCodPai == 0){
        printf("Erro ao inserir codItem: %d !! Nó raiz (pai == 0) ja existe !!\n", pCodItem);
        return pAg;
    }

    // busca o item, pois nao pode inserir o mesmo duas vezes
    TAG *item = busca_AG(pAg, pCodItem);
    // item encontrado
    if (item){
        printf("Erro ao inserir codItem: %d !! Já existe !!\n", pCodItem);
        return pAg;
    }
    else{
        // buscando o pai que vai receber o novo filho
        TAG *pai = busca_AG(pAg, pCodPai);
        // erro se o pai nao existir ainda
        if (!pai){
            printf("Erro ao inserir codItem: %d !! Pai %d nao encontrado.\n", pCodItem, pCodPai);
            return pAg;
        }
        else{
            // adicionando na lista de filhos ao final da lista de irmaos
            // verifica se e o primeiro filho
            TAG *lFilho = pai->filho;
            if (!lFilho){
                pai->filho = cria_elem_AG(pCodItem, pTipoItem, pItem);
                return pAg;
            }
            while(lFilho->irmao){
                lFilho = lFilho->irmao;
            }
            lFilho->irmao = cria_elem_AG(pCodItem, pTipoItem, pItem);
            return pAg;
        }
    }
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

#endif /* !FILE_AG_SEEN */
