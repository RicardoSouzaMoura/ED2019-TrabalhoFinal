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
TAB* remover(TAB* arv, int ch, int t){
    if(!arv) return arv;
    int i;
    printf("Removendo %d...\n", ch);
    for(i = 0; i<arv->nch && arv->cod[i] < ch; i++);
    if(i < arv->nch && ch == arv->cod[i]){ //CASOS 1, 2A, 2B e 2C
        if(arv->folha){ //CASO 1
            printf("\nCASO 1\n");
            int j;
            for(j=i; j<arv->nch-1;j++){
                arv->cod[j] = arv->cod[j+1];
                strcpy(arv->nos[j]->tipoItem, arv->nos[j+1]->tipoItem);
                arv->nos[j]->info = arv->nos[j+1]->info;
            }
            arv->nch--;
            return arv;      
        }
        if(!arv->folha && arv->filho[i]->nch >= t){ //CASO 2A
            printf("\nCASO 2A\n");
            TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
            while(!y->folha) y = y->filho[y->nch];
            int temp = y->cod[y->nch-1];
            char temp_char[4]; 
            strcpy(temp_char, y->nos[y->nch-1]->tipoItem);
            void * temp_info = y->nos[y->nch-1]->info;
            arv->filho[i] = remover(arv->filho[i], temp, t); 
            //Eliminar recursivamente K e substitua K por K' em x
            arv->cod[i] = temp;
            strcpy(arv->nos[i]->tipoItem, temp_char);
            arv->nos[i]->info = temp_info;
            return arv;
        }
        if(!arv->folha && arv->filho[i+1]->nch >= t){ //CASO 2B
            printf("\nCASO 2B\n");
            TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
            while(!y->folha) y = y->filho[0];
            int temp = y->cod[0];
            char temp_char[4];
            strcpy(temp_char, y->nos[0]->tipoItem);
            void * temp_info = y->nos[0]->info;
            y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
            arv->cod[i] = temp;
            strcpy(arv->nos[i]->tipoItem, temp_char);
            arv->nos[i]->info = temp_info;
            return arv;
        }
        if(!arv->folha && arv->filho[i+1]->nch == t-1 && arv->filho[i]->nch == t-1){ //CASO 2C
            printf("\nCASO 2C\n");
            TAB *y = arv->filho[i];
            TAB *z = arv->filho[i+1];
            y->cod[y->nch] = ch;          //colocar ch ao final de filho[i]
            strcpy(y->nos[y->nch]->tipoItem , arv->nos[i]->tipoItem);
            y->nos[y->nch]->info = arv->nos[i]->info;
            int j;
            for(j=0; j<t-1; j++){                //juntar cod[i+1] com cod[i]
                y->cod[t+j] = z->cod[j];
                strcpy (y->nos[t+j]->tipoItem, z->nos[j]->tipoItem);
                y->nos[t+j]->info = z->nos[j]->info;
            }
            for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
                y->filho[t+j] = z->filho[j];
            y->nch = 2*t-1;
            for(j=i; j < arv->nch-1; j++){   //remover ch de arv
                arv->cod[j] = arv->cod[j+1];
                strcpy(arv->nos[j]->tipoItem, arv->nos[j+1]->tipoItem);
                arv->nos[j]->info = arv->nos[j+1]->info;
            }
            for(j=i+1; j <= arv->nch; j++)  //remover ponteiro para filho[i+1]
                arv->filho[j] = arv->filho[j+1];
            arv->filho[j] = NULL; //Campello
            arv->nch--;
            arv->filho[i] = remover(arv->filho[i], ch, t);
            return arv;   
        }
    }

    TAB *y = arv->filho[i], *z = NULL;
    if (y->nch == t-1){ //CASOS 3A e 3B
        if((i < arv->nch) && (arv->filho[i+1]->nch >=t)){ //CASO 3A
            printf("\nCASO 3A: i menor que nch\n");
            z = arv->filho[i+1];
            y->cod[t-1] = arv->cod[i];   //dar a y a cod i da arv
            strcpy(y->nos[t-1]->tipoItem, arv->nos[i]->tipoItem);
            y->nos[t-1]->info = arv->nos[i]->info;
            y->nch++;
            arv->cod[i] = z->cod[0];     //dar a arv uma cod de z
            strcpy(arv->nos[i]->tipoItem, z->nos[0]->tipoItem);
            arv->nos[i]->info = z->nos[0]->info;
            int j;
            for(j=0; j < z->nch-1; j++){  //ajustar chaves de z
                z->cod[j] = z->cod[j+1];
                strcpy(z->nos[j]->tipoItem,z->nos[j+1]->tipoItem);
                z->nos[j]->info,z->nos[j+1]->info;
            }
            //z->cod[j] = 0; Rosseti
            y->filho[y->nch] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
            for(j=0; j < z->nch; j++)       //ajustar filhos de z
                z->filho[j] = z->filho[j+1];
            z->nch--;
            arv->filho[i] = remover(arv->filho[i], ch, t);
            return arv;
        }
        if((i > 0) && (!z) && (arv->filho[i-1]->nch >=t)){ //CASO 3A
            printf("\nCASO 3A: i igual a nch\n");
            z = arv->filho[i-1];
            int j;
            for(j = y->nch; j>0; j--){               //encaixar lugar da nova cod
                y->cod[j] = y->cod[j-1];
                strcpy(y->nos[j]->tipoItem, y->nos[j-1]->tipoItem);
                y->nos[j]->info = y->nos[j-1]->info;
            }
            for(j = y->nch+1; j>0; j--)             //encaixar lugar dos filhos da nova cod
                y->filho[j] = y->filho[j-1];
            y->cod[0] = arv->cod[i-1];              //dar a y a cod i da arv
            strcpy(y->nos[0]->tipoItem, arv->nos[i-1]->tipoItem);
            y->nos[0]->info = arv->nos[i-1]->info;
            y->nch++;
            arv->cod[i-1] = z->cod[z->nch-1];   //dar a arv uma cod de z
            strcpy(arv->nos[i-1]->tipoItem, z->nos[z->nch-1]->tipoItem);
            arv->nos[i-1]->info = z->nos[z->nch-1]->info;
            y->filho[0] = z->filho[z->nch];         //enviar ponteiro de z para o novo elemento em y
            z->nch--;
            arv->filho[i] = remover(y, ch, t);
            return arv;
        }
        if(!z){ //CASO 3B
            if(i < arv->nch && arv->filho[i+1]->nch == t-1){
                printf("\nCASO 3B: i menor que nch\n");
                z = arv->filho[i+1];
                y->cod[t-1] = arv->cod[i];     //pegar cod [i] e coloca ao final de filho[i]
                strcpy(y->nos[t-1]->tipoItem, arv->nos[i]->tipoItem);
                y->nos[t-1]->info = arv->nos[i]->info;
                y->nch++;
                int j;
                for(j=0; j < t-1; j++){
                    y->cod[t+j] = z->cod[j];     //passar filho[i+1] para filho[i]
                    strcpy(y->nos[t+j]->tipoItem, z->nos[j]->tipoItem);
                    y->nos[t+j]->info = z->nos[j]->info;
                    y->nch++;
                }
                if(!y->folha){
                    for(j=0; j<t; j++){
                        y->filho[t+j] = z->filho[j];
                    }
                }
                for(j=i; j < arv->nch-1; j++){ //limpar referências de i
                    arv->cod[j] = arv->cod[j+1];
                    strcpy(arv->nos[j]->tipoItem, arv->nos[j+1]->tipoItem);
                    arv->nos[j]->info = arv->nos[j+1]->info;
                    arv->filho[j+1] = arv->filho[j+2];
                }
                arv->nch--;
                if(arv->nch==0){
                    arv = arv->filho[0];
                }
                arv = remover(arv, ch, t);
                return arv;
            }
            if((i > 0) && (arv->filho[i-1]->nch == t-1)){ 
                printf("\nCASO 3B: i igual a nch\n");
                z = arv->filho[i-1];
                if(i == arv->nch){
                    z->cod[t-1] = arv->cod[i-1]; //pegar cod[i] e poe ao final de filho[i-1]
                    strcpy(z->nos[t-1]->tipoItem, arv->nos[i-1]->tipoItem);
                    z->nos[t-1]->info, arv->nos[i-1]->info;
                }                    
                else{
                    z->cod[t-1] = arv->cod[i];   //pegar cod [i] e poe ao final de filho[i-1]
                    strcpy(z->nos[t-1]->tipoItem, arv->nos[i]->tipoItem);
                    z->nos[t-1]->info = arv->nos[i]->info;
                }                 
                z->nch++;
                int j;
                for(j=0; j < t-1; j++){
                    z->cod[t+j] = y->cod[j];     //passar filho[i+1] para filho[i]
                    strcpy(z->nos[t+j]->tipoItem, y->nos[j]->tipoItem);
                    z->nos[t+j]->info = y->nos[j]->info;
                    z->nch++;
                }
                if(!z->folha){
                    for(j=0; j<t; j++){
                        z->filho[t+j] = y->filho[j];
                    }
                }
                arv->nch--;
                if(arv->nch==0){
                    arv = arv->filho[0];
                }
                //else arv->filho[i-1] = z; totalmente desnecessário
                arv = remover(arv, ch, t);
                return arv;
            }
        }
    }
    arv->filho[i] = remover(arv->filho[i], ch, t);
    return arv;
}
TAB* retira(TAB* arv, int k, int t){
    if(!arv || !Busca_AB(arv, k)) return arv;
    return remover(arv, k, t);
}