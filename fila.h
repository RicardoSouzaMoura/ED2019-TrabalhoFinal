#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct no_fila{
    void *info;
    struct no_fila *prox;
}TNO_FILA;

typedef struct fila {
    TNO_FILA *ini, *fim;
}TFILA;


TFILA *cria_FILA ();

int vazia_FILA(TFILA *pFila);

void libera_FILA(TFILA *pFila);

void insere_FILA(TFILA *pFila, void *pItem);

void *retira_FILA(TFILA *pFila);

TFILA *cria_FILA (){
    TFILA *lFila = (TFILA*)malloc(sizeof(TFILA));
    lFila->fim = NULL;
    lFila->ini = NULL;
    return lFila;
}

int vazia_FILA(TFILA *pFila){
    return pFila->ini == NULL;
}

void libera_FILA(TFILA *pFila){
    TNO_FILA *q = pFila->ini, *t;
    while(q){
        t = q;
        q = q->prox;
        free(t);
    }
    free(pFila);
}

void insere_FILA(TFILA *f, void * x){
    TNO_FILA *novo = (TNO_FILA *)malloc(sizeof(TNO_FILA));
    novo->info = x;
    novo->prox = NULL;
    if (vazia_FILA(f)){
        f->ini = f->fim = novo;
    }
    else{
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void *retira_FILA(TFILA *f){
    if (vazia_FILA(f));
    void *resp = f->ini->info;
    TNO_FILA *q = f->ini;
    f->ini = f->ini->prox;
    if (!f->ini){
        f->fim = NULL;
    }
    free(q);
    return resp;
}