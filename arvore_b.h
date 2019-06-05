#include <stdlib.h>
#include <stdio.h>

typedef struct AB {
    int nch, folha, *cod;
    struct info **nos;
    //void *info;
    struct AB **filho;
}TAB;


TAB * inicializa_AB();

TAB *cria(int t);

TAB *Libera_AB(TAB *a, int t);

TAB *insere_AB(TAB* pAg, int t,int pCodItem, char* pTipoItem, void *info);

TAB *ins_nao_compl(TAB *pAg,int t, int pCodItem, char* pTipoItem,void *info);

TAB * divisao(TAB * pai,int i,TAB * pAg, int t);

TAB *Busca_AB(TAB* pAg, int cod);
TNO *buscaNo_AB(TAB *pAb, int pCodItem);

void imprime_AB(TAB *a, int andar);

TAB * transforma_AG_AB(TAG * l, int t);

TAB * insere_filhos_irmaos(TAB * resp, int t, TAG * l);

TAB * inicializa_AB(){
    return NULL;
}

TAB *cria(int t){
    TAB * novo = (TAB *)malloc(sizeof(TAB));
    novo->folha = 1;
    novo->nch = 0;
    novo->cod = (int*)malloc(sizeof(int)*(2*t-1));
    novo->nos = (TNO**)malloc(sizeof(TNO*)*(2*t-1));
    novo->filho = (TAB**)malloc(sizeof(TAB*)*(2*t));
    int i;
    for(i=0;i<2*t;i++){
        novo->filho[i]= NULL;
        
        if (i!=(2*t-1)){
            novo->nos[i]=(TNO*)malloc(sizeof(TNO));
            novo->nos[i]->tipoItem = (char*)malloc(sizeof(char)*3);
        }
    }
    return novo;
}
TAB *Libera_AB(TAB *a, int t){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nch; i++) Libera_AB(a->filho[i], t);
    }

    int i;
    
    for(i=0; i < (2*t-1);i++){
        free(a->nos[i]->tipoItem);
        free(a->nos[i]);        
    }
    
    free(a->nos);
    free(a->cod);
    free(a->filho);//como não tenho que liberar nenhuma das estruturas apontadas pelos ponteiros, free direto
    free(a);
    return NULL;
  }
}
TAB *insere_AB(TAB* pAg, int t,int pCodItem, char* pTipoItem, void *info){
    if(!pAg){
        pAg = cria(t);
        pAg->nch++;
        pAg->cod[0]=pCodItem;
        strcpy(pAg->nos[0]->tipoItem, pTipoItem);
        pAg->nos[0]->info = info;        
        return pAg;
    }
    if(pAg->nch==(2*t-1)){
        TAB * novo = cria(t);
        novo->folha=0;
        novo->filho[0]= pAg;
        novo=divisao(novo,0,pAg,t);//0 é o index do filho a ser dividido
        novo = ins_nao_compl(novo,t,pCodItem, pTipoItem, info);
        return novo;
    }
    pAg=ins_nao_compl(pAg,t,pCodItem,pTipoItem, info);
    return pAg;

}

TAB *ins_nao_compl(TAB *pAg,int t, int pCodItem, char* pTipoItem,void *info){
    int i = pAg->nch-1;
    if(pAg->folha){// é folha
        while(i>=0&&pAg->cod[i]>pCodItem){
            pAg->cod[i+1]=pAg->cod[i];
            strcpy(pAg->nos[i+1]->tipoItem, pAg->nos[i]->tipoItem);
            pAg->nos[i+1]->info = pAg->nos[i]->info;
            i--;
        }
        pAg->cod[i+1]=pCodItem;
        strcpy(pAg->nos[i+1]->tipoItem, pTipoItem);
        pAg->nos[i+1]->info = info;
        pAg->nch++;
        return pAg;
    }
    else{
        while(i>=0&&pAg->cod[i]>pCodItem) i--;
        if(pAg->filho[i+1]->nch==(2*t-1)){
            pAg=divisao(pAg,i+1,pAg->filho[i+1],t);//0 é o index do filho a ser dividido
            if(pAg->cod[i+1]< pCodItem) i++;
        }
        pAg->filho[i+1]=ins_nao_compl(pAg->filho[i+1], t, pCodItem, pTipoItem, info);
        return pAg;
    }
}
TAB * divisao(TAB * pai,int i,TAB * pAg, int t){// i é o número do filho que será dividido
    TAB * novo = cria(t);
    novo->nch = t-1;
    novo->folha = pAg->folha;// só tinha no da professora
    int j;
    for(j=0;j<t-1;j++){// Copy the last (t-1) keys of pAg to novo 
        novo->cod[j] = pAg->cod[t+j];
        strcpy(novo->nos[j]->tipoItem, pAg->nos[t+j]->tipoItem);
        novo->nos[j]->info = pAg->nos[t+j]->info;
    }
    if(!pAg->folha){
        for(j=0;j<t;j++)// Copy the last (t) children of pAg to novo 
            novo->filho[j] = pAg->filho[t+j];
            pAg->filho[t+j] = NULL;
    }
    pAg->nch = t-1;
    for (j=pai->nch;j>=i+1;j--){
        pai->filho[j+1]=pai->filho[j];//igual código professora
    }
    pai->filho[i+1]=novo;
    for(j=pai->nch-1;j>=i;j--){
        pai->cod[j+1]=pai->cod[j];
        strcpy(pai->nos[j+1]->tipoItem, pai->nos[j]->tipoItem);
        pai->nos[j+1]->info = pai->nos[j]->info;
    }  
    pai->cod[i]=pAg->cod[t-1];
    strcpy(pai->nos[i]->tipoItem, pAg->nos[t-1]->tipoItem);
    pai->nos[i]->info = pAg->nos[t-1]->info;
    pai->nch++;
    return pai;
}

TNO *buscaNo_AB(TAB *pAb, int pCodItem){
    int *cod = pAb->cod;
    int i=0;
    for (; i < pAb->nch; i++){
        if (cod[i] == pCodItem){
            return pAb->nos[i];
        }
    }
    return NULL;
}

TAB *Busca_AB(TAB* pAg, int cod){
  TAB *resp = NULL;
  if(!pAg) return resp;
  int i = 0;
  while(i < pAg->nch && cod > pAg->cod[i]) i++;
  if(i < pAg->nch && cod == pAg->cod[i]) return pAg;
  if(pAg->folha) return resp;
  return Busca_AB(pAg->filho[i], cod);
}

void imprime_AB(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nch-1; i++){
        imprime_AB(a->filho[i], andar +1);
        for(j=0; j<=andar; j++) printf("   ");
        printf("%d\n", a->cod[i]);
    }
    imprime_AB(a->filho[i], andar +1);
  }
}
TAB * transforma_AG_AB(TAG * l, int t){
    TAB * resp = NULL;
    if(!l) return resp;
    return insere_filhos_irmaos(resp, t, l);
}
TAB * insere_filhos_irmaos(TAB * resp, int t, TAG * l){
    resp = insere_AB(resp, t, l->cod,l->no->tipoItem, l->no->info);
    if(l->filho) resp = insere_filhos_irmaos(resp, t, l->filho);
    if(l->irmao)  resp = insere_filhos_irmaos(resp, t, l->irmao);
    return resp;
}