#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "formas_geometricas.h"
#include "arvore_generica.h"
#include "arvore_bbb.h"
#include "arvore_b.h"
#include "leitura_arquivo.h"

void imprimeMenuAG();
void imprimeMenuABBB();
void imprimeMenuAB();
TQ *criaQuadradoViaMenu();
TR *criaRetanguloViaMenu();
TZ *criaTrapezioViaMenu();
TT *criaTrianguloViaMenu();
TC *criaCirculoViaMenu();

void alteraQuadradoViaMenu(TQ* pQuad);
void alteraRetanguloViaMenu(TR *pRet);
void alteraTrapezioViaMenu(TZ *pTrap);
void alteraTrianguloViaMenu(TT *pTri);
void alteraCirculoViaMenu(TC *pCirc);

void imprimeItem(void *pItem, char* pTipoItem);

TAG* implementaMenuInsere(TAG* arv_gen);
void implementaMenuBuscaElemPorId(TAG *pAg);

int main(void){
    int lOpcao = -1;
    int lOpcaoArvore = 0;

    printf("Bem vindo !!!\n");

    TAG *arv_gen = NULL;
    
    while(lOpcao != 0 && lOpcao != 10 && lOpcao != 20){
        if (lOpcaoArvore == 0){
            imprimeMenuAG();
        }
        else if (lOpcaoArvore == 10){
            imprimeMenuABBB();
        }
        else if (lOpcaoArvore == 20){
            imprimeMenuAB();
        }
        scanf("%d", &lOpcao);
        printf("Opcao escolhida: %d\n", lOpcao);
        // estou somando aqui pois os menus para
        // cada arvore tera um incrementador diferente
        // embora para o usuario permaneca igual.
        // AG lOpcaoArvore = 0 (case do 0 ao 9)
        // ABBB lOpcaoArvore = 10 (case do 10 ao 19)
        // AB lOpcaoArvore = 20 (case do 20 ao 29)
        lOpcao = lOpcao + lOpcaoArvore;
        switch (lOpcao)
        {
        case 1:;
            int opt = 1;
            if (arv_gen){
                printf("A AG já está preenchida. É possível recriá-la ou inserir novos items (itens existentes serão rejeitados). [recriar: 1/inserir: 2/cancelar: !=(1,2)]");
                scanf("%d", &opt);
            }
            char *path;
            printf("Nome do arquivo: ");
            scanf(" %30[^\n]", path);
            
            if (opt == 1){
                destroi_AG(arv_gen);
                arv_gen = NULL;
            }
            arv_gen = ler(path, arv_gen);
            break;

        case 2:;
            arv_gen = implementaMenuInsere(arv_gen);
            break;

        case 3:;
            implementaMenuBuscaElemPorId(arv_gen);
            break;

        case 4:;
            printf("Imprimindo arvore...\n");
            imprime_repres_AG(arv_gen, 0);
            break;

        case 8:;
            lOpcaoArvore = 10;
            break;

        case 9:;
            lOpcaoArvore = 20;
            break;

        case 18:;
            lOpcaoArvore = 0;
            break;

        case 28:;
            lOpcaoArvore = 0;
            break;
        
        default:
            break;
        }        
    }

    printf("\nLiberando estruturas...");
    // TODO: Liberar toda a arvore binaria
    // TODO: Liberar toda a arvore bbb
    // TODO: Liberar toda a arvore B
    printf("\nBye");
}

void implementaMenuBuscaElemPorId(TAG *pAg){
    int lIdItem = -1;
    printf("Qual id quer buscar:");
    scanf("%d", &lIdItem);
    TAG *lElem = busca_AG(pAg, lIdItem);
    if (lElem){
        imprime_elem_AG(lElem, imprimeItem);
    }
    else {
        printf("\nElemento com id %d nao encontrado", lIdItem);
    }
    
}

void imprimeMenuAG(){
    printf("\n#######################################################################3\n");
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(1) Ler Arquivo inicial para AG\n");
    printf("(2) Inserir figura na AG\n");
    printf("(3) Buscar figura pelo id na AG\n");
    printf("(4) Imprimir Representação de AG\n");
    printf("(5) Retirar elemento da AG\n");
    printf("(6) Destruir AG\n");
    printf("(7) Alterar dimensao de figura na AG\n");
    printf("(8) Transformar AG em ABBB\n");
    printf("(9) Transformar AG em AB\n");
}

void imprimeMenuABBB(){
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(1) Inserir figura na ABBB\n");
    printf("(3) Buscar figura pelo id na ABBB\n");
    printf("(4) Imprimir ABBB\n");
    printf("(5) Retirar elemento da ABBB\n");
    printf("(6) Destruir ABBB\n");
    printf("(7) Alterar dimensao de figura na ABBB\n");
    printf("(8) Voltar Menu para AG\n");
}

void imprimeMenuAB(){
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(1) Inserir figura na AB\n");
    printf("(3) Buscar figura pelo id na AB\n");
    printf("(4) Imprimir AB\n");
    printf("(5) Retirar elemento da AB\n");
    printf("(6) Destruir AB\n");
    printf("(7) Alterar dimensao de figura na AB\n");
    printf("(8) Voltar Menu para AG\n");
}

void imprimeItem(void *pItem, char* pTipoItem){
    printf("Imprindo forma geometrica %s...", pTipoItem);
    if (strcmp(pTipoItem, "QUA") == 0){
        imprimeQuadrado((TQ*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "TRI") == 0){
        imprimeTriangulo((TT*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "RET") == 0){
        imprimeRetangulo((TR*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "TRA") == 0){
        imprimeTrapezio((TZ*)pItem);
        return;
    }
    if (strcmp(pTipoItem, "CIR") == 0){
        imprimeCirculo((TC*)pItem);
        return;
    }
}

TAG* implementaMenuInsere(TAG* arv_gen){
    char* lTipoItem;
    int lCod;
    int lCodPai;
    printf("Qual tipo de figura (QUA, TRI, TRA, CIR, RET): ");
    scanf(" %3[^\n]", lTipoItem);
    printf("\nQual codigo: ");
    scanf("%d", &lCod);
    printf("\nQual codigo do pai (0 == raiz): ");
    scanf("%d", &lCodPai);

    TAG *lElemento = busca_AG(arv_gen, lCod);
    if (!lElemento) {
        void *info = NULL;
        if (strcmp(lTipoItem, "QUA") == 0){
            info = criaQuadradoViaMenu();
        }
        else if (strcmp(lTipoItem, "TRI") == 0){
            info = criaTrianguloViaMenu();
        }
        else if (strcmp(lTipoItem, "RET") == 0){
            info = criaRetanguloViaMenu();
        }
        else if (strcmp(lTipoItem, "TRA") == 0){
            info = criaTrapezioViaMenu();
        }
        else if (strcmp(lTipoItem, "CIR") == 0){
            info = criaCirculoViaMenu();
        } else {
            printf("\nErro !!! Tipo de figura %s não definida", lTipoItem);
            return arv_gen;
        }
        arv_gen = insere_AG(arv_gen, lCod, lTipoItem, info, lCodPai);
    }
    else{
        int opt;
        printf("Item %d do tipo %s ja existente. Gostaria de atualizar suas dimensoes? [y-1/n-0]", lCod, lElemento->no->tipoItem);
        scanf("%d",&opt);
        if(opt==1) {
            if (strcmp(lElemento->no->tipoItem, "QUA") == 0){
                alteraQuadradoViaMenu(lElemento->no->info);
            }
            else if (strcmp(lElemento->no->tipoItem, "TRI") == 0){
                alteraTrianguloViaMenu(lElemento->no->info);
            }
            else if (strcmp(lElemento->no->tipoItem, "RET") == 0){
                alteraRetanguloViaMenu(lElemento->no->info);
            }
            else if (strcmp(lElemento->no->tipoItem, "TRA") == 0){
                alteraTrapezioViaMenu(lElemento->no->info);
            }
            else if (strcmp(lElemento->no->tipoItem, "CIR") == 0){
                alteraCirculoViaMenu(lElemento->no->info);
            }
        }
    }
    return arv_gen;
}

TQ *criaQuadradoViaMenu(){
    int lLado;
    printf("\nQual o lado: ");
    scanf("%d", &lLado);
    return criaQuadrado(lLado);
}

TT *criaTrianguloViaMenu(){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaTriangulo(lBase, lAltura);
}

TR *criaRetanguloViaMenu(){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaRetangulo(lBase, lAltura);
}

TZ *criaTrapezioViaMenu(){
    int lBaseMaior, lBaseMenor, lAltura;
    printf("\nQual a base maior: ");
    scanf("%d", &lBaseMaior);
    printf("\nQual a base menor: ");
    scanf("%d", &lBaseMenor);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    return criaTrapezio(lBaseMenor, lBaseMaior, lAltura);
}

TC *criaCirculoViaMenu(){
    int lRaio;
    printf("\nQual o raio: ");
    scanf("%d", &lRaio);
    return criaCirculo(lRaio);
}

void alteraQuadradoViaMenu(TQ * pQuad){
    int lLado;
    printf("\nQual o lado: ");
    scanf("%d", &lLado);
    altera_dim_TQ(pQuad, lLado);
}

void alteraTrianguloViaMenu(TT* pTri){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    altera_dim_TT(pTri, lBase, lAltura);
}

void alteraRetanguloViaMenu(TR *pRet){
    int lBase, lAltura;
    printf("\nQual a base: ");
    scanf("%d", &lBase);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    altera_dim_TR(pRet, lBase, lAltura);
}

void alteraTrapezioViaMenu(TZ *pTrap){
    int lBaseMaior, lBaseMenor, lAltura;
    printf("\nQual a base maior: ");
    scanf("%d", &lBaseMaior);
    printf("\nQual a base menor: ");
    scanf("%d", &lBaseMenor);
    printf("\nQual a altura: ");
    scanf("%d", &lAltura);
    altera_dim_TZ(pTrap, lBaseMenor, lBaseMaior, lAltura);
}

void alteraCirculoViaMenu(TC *pCirc){
    int lRaio;
    printf("\nQual o raio: ");
    scanf("%d", &lRaio);
    altera_dim_TC(pCirc, lRaio);
}