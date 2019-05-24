#include <stdlib.h>
#include <stdio.h>

typedef struct AG {
    int cod;
    struct info *no;
    struct AG *filho, *irmao;
}TAG;

typedef struct info{
    int tipo;
    void *info;
}TNO;

TAG *cria_AG();

TAG *insere_AG(TAG* pAg, void* pItem, int pCodPai);

TAG *remove_AG(TAG *pAg, void* pItem);

void imprime_AG(TAG *pAg);

TAG *cria_AG(){
    TAG *ag = (TAG*)malloc(sizeof(TAG));
    ag->no = NULL;
    ag->filho = NULL;
    ag->irmao = NULL;
    ag->cod = -1;
    return ag;
}

TAG *insere_TAG(TAG *pAg, void* pItem){

}
