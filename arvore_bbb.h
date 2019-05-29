#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "arvore_generica.h";

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

int maior(int pNum1, int pNum2){
    if (pNum1 > pNum2) return pNum1;
    return pNum2;
}

int altura (TAG *pABBB){
    if (!pABBB) return -1;
    return maior(altura(pABBB->filho),altura(pABBB->irmao)) + 1;
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

TAG *insere_ABBB(TAG* pAg, int pCodItem, char* tipoItem, void* pItem){

}