#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "arvore_generica.h"

// difere da arvore generica pois pode ser otimizada
// devido a estar balanceada e ordenada
TAG* busca_ABBB(TAG *pABBB, int pCodItem);

// libera pode ser a mesma da AG

// inserir muda pois precisa estar balanceada e ordenada
// quebra a ideia de pai e filho ja que ordena por codItem
TAG *insere_ABBB(TAG* pAg, int pCodItem, char* tipoItem, void* pItem);

// remover muda pois otimiza e precisa rebalancear
TAG *remove_ABBB(TAG *pAg, int pCodItem);

// imprimir pode ser a mesma da AG

// inicializa pode ser a mesma da AG

// funcao que me devolve o peso do no da arvore
// ou seja, a diferenca da altura das suas subarvores.
// Para estar balanceada todos os nos precisam
// estar entre {-1, 0, 1}
// Esta funcao é utilizada no insere e remove para saber se
// está balanceada ou nao
int altura (TAG *pABBB);

// Maior entre dois numeros. Mesmo que fmax da math.h
// Para evitar incompatibilidade de compilador resolvi recriar
int maior(int pNum1, int pNum2);

// calcula o fator de balanco de um determinado elemento da arvore
// para isso leva em consideracao o calculo das alturas
int fatorBalanco(TAG *pABBB);

//FB(P) = -2
//FB(D) <= 0
TAG *rse(TAG *pABBB);

// FB(P) = 2
// FB(E) >=0
TAG *rsd(TAG* pABBB);

// FB(P) = -2
// FB(D) > 0
TAG *rde(TAG *pABBB);

// FB(P) = 2
// FB(E) < 0
TAG *red(TAG *pABBB);

void imprime_repres_ABBB(TAG *pAg, int andar);

// converte AG para AVL
TAG* AG_2_AVL(TAG *pAg, TAG *pAvl);

// balanceia a arvore
TAG* balanceia_ABBB(TAG *pABBB);

// imprime os nos em profundidade da esquerda para direita
// os filhos sao os que estao a direita em cima de cada no
// de cima para baixo os nos filhos entram da esquerda para direita
void imprime_repres_ABBB(TAG *pAg, int andar){
    if (pAg){
        int j=0;
        imprime_repres_ABBB(pAg->filho, andar + 1);
        for(j=0; j<=andar; j++) printf("   ");
        printf("%d\n", pAg->cod);
        imprime_repres_ABBB(pAg->irmao, andar + 1);
    }
}

TAG *rse(TAG *pABBB){
    TAG *p = pABBB;
    TAG *d = p->irmao;
    p->irmao = d->filho;
    d->filho = p;
    return d;
}

TAG *rsd(TAG* pABBB){
    TAG *p = pABBB;
    TAG *e = p->filho;
    p->filho = e->irmao;
    e->irmao = p;
    return e;
}

TAG *rde(TAG *pABBB){
    pABBB->irmao = rsd(pABBB->irmao);
    return rse(pABBB);
}

TAG *red(TAG *pABBB){
    pABBB->filho = rse(pABBB->filho);
    return rsd(pABBB);
}

int maior(int pNum1, int pNum2){
    if (pNum1 > pNum2) return pNum1;
    return pNum2;
}

int altura (TAG *pABBB){
    if (!pABBB) return -1;
    return maior(altura(pABBB->filho),altura(pABBB->irmao)) + 1;
}

int fatorBalanco(TAG *pABBB){
    if (pABBB){
      return altura(pABBB->filho) - altura(pABBB->irmao);
    }
    return altura(pABBB);
}

TAG* busca_ABBB(TAG *pABBB, int pCodItem){
    if (!pABBB || pABBB->cod == pCodItem){
        return pABBB;
    }
    if (pABBB->cod > pCodItem){
        return busca_ABBB(pABBB->filho, pCodItem);
    }
    return busca_ABBB(pABBB->irmao, pCodItem);
}


TAG *insere_ABBB(TAG* pABBB, int pCodItem, char* pTipoItem, void* pItem){

    // primeiramente insere o item conforme uma arvore binaria normal
    if (!pABBB){
        return cria_elem_AG(pCodItem, pTipoItem, pItem);
    }
    if (pABBB->cod > pCodItem){
        pABBB->filho = insere_ABBB(pABBB->filho, pCodItem, pTipoItem, pItem);
    }
    else if (pABBB->cod < pCodItem){
      pABBB->irmao = insere_ABBB(pABBB->irmao, pCodItem, pTipoItem, pItem);
    }
    else{
        printf("\n Warning !!! Item %d já existe na arvore\n", pCodItem);
    }

    return balanceia_ABBB(pABBB);
}

TAG* balanceia_ABBB(TAG *pABBB){
    // aqui comeca o rebalanceamento
    int lFB_P = fatorBalanco(pABBB);
    int lFB_E = fatorBalanco(pABBB->filho);
    int lFB_D = fatorBalanco(pABBB->irmao);

    // apos calcular os fatores usa as regras
    // conforme explicado pela professora
    // tabela que sera dada no dia da prova
    if (lFB_P == -2 && lFB_D <=0){
        pABBB = rse(pABBB);
    }
    else if (lFB_P == 2 && lFB_E >=0){
        pABBB = rsd(pABBB);
    }
    else if (lFB_P == -2 && lFB_D > 0){
        pABBB = rde(pABBB);
    }
    else if (lFB_P == 2 && lFB_E < 0){
        pABBB = red(pABBB);
    }
    return pABBB;
}

TAG* AG_2_AVL(TAG *pAg, TAG *pAvl){
    if (!pAg) return NULL;

    pAvl = insere_ABBB(pAvl, pAg->cod, pAg->no->tipoItem, pAg->no->info);

    if (pAg->irmao){
        pAvl = AG_2_AVL(pAg->irmao, pAvl);
    }

    if (pAg->filho){
        pAvl = AG_2_AVL(pAg->filho, pAvl);
    }
    
    return pAvl; 

}

TAG *remove_ABBB(TAG *pAg, int pCodItem){
    if (!pAg){
        return pAg;
    }
    if (pAg->cod > pCodItem){
        pAg->filho = remove_ABBB(pAg->filho, pCodItem);
        pAg = balanceia_ABBB(pAg);
    }
    else if (pAg->cod < pCodItem){
        pAg->irmao = remove_ABBB(pAg->irmao, pCodItem);
        pAg = balanceia_ABBB(pAg);
    }
    else{
        if (!pAg->filho && !pAg->irmao){
            // folha
            free(pAg);
            return NULL;
        }
        if (!pAg->filho || !pAg->irmao){
            TAG *f;
            if (!pAg->filho){
                f = pAg->irmao;
            }
            else{
                f = pAg->filho;
            }
            free(pAg);
            return f;
        }
        else{
            TAG *f = pAg->filho;
            while(f->irmao){
                f = f->irmao;
            }
            pAg->cod = f->cod;
            f->cod = pCodItem;
            pAg->filho = remove_ABBB(pAg->filho, pCodItem);
            pAg = balanceia_ABBB(pAg);
        }
    }
    return pAg;
}

//convertendo arvore generica em AVL

/*TQ* buildQuadrado(TQ *pQua){
    TQ*qua=NULL;
    qua=criaQuadrado(pQua->lado);
    return qua;

}

TR* buildRetangulo(TR *pret){
    TR*ret=NULL;
    ret=criaRetangulo(pret->base,pret->altura);
    return ret;

}

TT* buildTriangulo(TT *pTri){
    TT*tri=NULL;
    tri=criaTriangulo(pTri->base,pTri->altura);
    return tri;

}

TC* buildCirculo(TC *pCir){
    TC*cir=NULL;
    cir=criaCirculo(pCir->raio);
    return cir;

}

TZ* buildTrapezio(TZ *pTz){
    TZ*trz=NULL;
    trz=criaTrapezio(pTz->baseMenor,pTz->baseMaior,pTz->altura);
    return trz;

}

TAG* build(TAG*pAg,TAG*pAvl,void *pItem, char* pTipoItem){
    if (strcmp(pTipoItem, "QUA") == 0){
        TQ*x=NULL;
        x=buildQuadrado((TQ*)pItem);
        pAvl=insere_ABBB(pAvl,pAg->cod,pAg->no->tipoItem,x);

        return pAvl;
    }
    if (strcmp(pTipoItem, "TRI") == 0){
        TT*x=NULL;
        x=buildTriangulo((TT*)pItem);
        pAvl=insere_ABBB(pAvl,pAg->cod,pAg->no->tipoItem,x);

        return pAvl;
    }
    if (strcmp(pTipoItem, "RET") == 0){
        TR*x=NULL;
        x=buildRetangulo((TR*)pItem);
        pAvl=insere_ABBB(pAvl,pAg->cod,pAg->no->tipoItem,x);

        return pAvl;
    }
    if (strcmp(pTipoItem, "TRA") == 0){
        TZ*x=NULL;
        x=buildTrapezio((TZ*)pItem);
        pAvl=insere_ABBB(pAvl,pAg->cod,pAg->no->tipoItem,x);
        return pAvl;
    }
    if (strcmp(pTipoItem, "CIR") == 0){
        TC*x=NULL;
        x=buildCirculo((TC*)pItem);
        pAvl=insere_ABBB(pAvl,pAg->cod,pAg->no->tipoItem,x);
        return pAvl;
    }
}


TAG * Ag2Avl(TAG *pAg, TAG *pAvl){
    if (pAg){
        pAvl = build(pAg, pAvl, pAg->no->info, pAg->no->tipoItem);

        pAvl = Ag2Avl(pAg->filho, pAvl);

        pAvl = Ag2Avl(pAg->irmao, pAvl);
        return pAvl;
    }
}*/

