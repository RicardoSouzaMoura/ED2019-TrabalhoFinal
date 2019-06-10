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

TAG* implementaMenuInsereAG(TAG* arv_gen);
TAG* implementaMenuInsereABBB(TAG* arv_avl);
TAB* implementaMenuInsereAB(TAB* arv_b, int pT);
void implementaMenuBuscaElemPorId(TAG *pAg, int pTipoAG);
void implementaMenuBuscaElemABPorId(TAB *pAb);

void implementaMenuAlteraDim(TAG* arv_gen, int pTipoItem);
void decideMenuAlteraDim(char* pTipoItem, void* pInfo);
void* criaFormaPorMenu(char * pTipoItem);
TAG* implementaMenuRemoverPorId(TAG *pAg, int pTipoAG);
TAB* implementaMenuRemover_arv_b(TAB * arv_b, int t);

int main(void){
    int lOpcao = -1;
    int lOpcaoArvore = 0;

    printf("Bem vindo !!!\n");

    TAG *arv_gen = NULL;
    TAG *arv_avl = NULL;
    TAB *arv_b = NULL;
    int t = 0;

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

            if (opt == 1 || opt == 2) {
                char path[151];
                printf("Caminho do arquivo: ");
                scanf(" %150[^\n]", path);

                if (opt == 1) {
                    destroi_AG(arv_gen);
                    arv_gen = NULL;
                }
                arv_gen = ler(path, arv_gen);

            }

            break;

        case 2:;
            arv_gen = implementaMenuInsereAG(arv_gen);
            break;

        case 3:;
            if (arv_gen){
                implementaMenuBuscaElemPorId(arv_gen, 1);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 4:;
            if (arv_gen){
                printf("Imprimindo arvore...\n");
                imprime_repres_AG(arv_gen, 0);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 5:;
            if (arv_gen){
                arv_gen = implementaMenuRemoverPorId(arv_gen, 1);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 6:;
            if (arv_gen){
                printf("destruindo arvore AG...\n");
                destroi_AG(arv_gen);
                arv_gen = NULL;
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 7:;
            if (arv_gen){
                implementaMenuAlteraDim(arv_gen, 1);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 8:;
            if (arv_gen){
                lOpcaoArvore = 10;
                arv_avl = AG_2_AVL(arv_gen, arv_avl);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 9:;
            if (arv_gen){
                lOpcaoArvore = 20;
                printf("\nInforme o grau mínimo (t): ");
                scanf("%d", &t);
                arv_b = transforma_AG_AB(arv_gen, t);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 12:;
            arv_avl = implementaMenuInsereABBB(arv_avl);
            break;

        case 13:;
            if (arv_gen){
                implementaMenuBuscaElemPorId(arv_avl, 0);
            }
            else{
                printf("\nABBB está vazia");
            }
            break;

        case 14:;
            imprime_repres_ABBB(arv_avl, 0);
            break;

        case 15:;
            if (arv_avl){
                arv_avl = implementaMenuRemoverPorId(arv_avl, 0);
            }
            else{
                printf("\nAG está vazia");
            }
            break;

        case 16:;
            printf("destruindo arvore ABBB...\n");
            destroi_AG(arv_avl);
            arv_avl = NULL;
            lOpcaoArvore = 0;
            break;

        case 17:;
            if (arv_avl){
                implementaMenuAlteraDim(arv_avl, 0);
            }
            else{
                printf("\nABBB está vazia");
            }
            break;

        case 18:;
            lOpcaoArvore = 0;
            destroi_AG(arv_avl);
            arv_avl = NULL;
            break;

        case 22:;
            arv_b = implementaMenuInsereAB(arv_b, t);
            break;

        case 23:;
            if (arv_gen){
                implementaMenuBuscaElemABPorId(arv_b);
            }
            else{
                printf("\nABBB está vazia");
            }
            break;

        case 24:;
            imprime_AB(arv_b, 0);
            break;

        case 25:;
            if (arv_b){
                arv_b = implementaMenuRemover_arv_b(arv_b, t);
            }
            else{
                printf("\nÁrvore B está vazia");
            }
            break;

        case 26:;
            printf("destruindo arvore AB...\n");
            Libera_AB(arv_b, t);
            arv_b = NULL;
            lOpcaoArvore = 0;
            break;

        case 27:;
            if (arv_gen){
                implementaMenuAlteraDim(arv_gen, 1);
            }
            else{
                printf("\nAG está vazia");
            }
            break;


        case 28:;
            lOpcaoArvore = 0;
            Libera_AB(arv_b, t);
            arv_b = NULL;
            break;

        default:
            break;
        }
    }

    printf("\nLiberando estruturas...");

    destroi_AG(arv_gen);
    destroi_AG(arv_avl);
    Libera_AB(arv_b, t);

    printf("\nBye");
}

void implementaMenuBuscaElemABPorId(TAB *pAb){
    int lIdItem = -1;
    printf("Qual id quer buscar:");
    scanf("%d", &lIdItem);

    TAB *lElemento = Busca_AB(pAb, lIdItem);
    if (lElemento){
        TNO* no = buscaNo_AB(lElemento, lIdItem);
        if (no){
            imprimeItem(no->info, no->tipoItem);
        }
        else{
            printf("Erro !!!metodo buscaNo_AB mal implementado. Tinha que ter encontrado cod %d", lIdItem);
        }
    }
    else{
        printf("Erro !!!Não existe nó com cod. %d na arvore B", lIdItem);
    }
}

TAB * implementaMenuRemover_arv_b(TAB *arv_b, int t){
    int lIdItem = -1;
    printf("Qual id quer remover:");
    scanf("%d", &lIdItem);
    retira(arv_b, lIdItem, t);
    return arv_b;
}

TAG *implementaMenuRemoverPorId(TAG *pAg, int pTipoAG){
    int lIdItem = -1;
    printf("Qual id quer remover:");
    scanf("%d", &lIdItem);
    if (pTipoAG == 1){
      pAg = remove_AG(pAg, lIdItem);
    }
    else{
      pAg = remove_ABBB(pAg, lIdItem);
    }
    return pAg;
}

void implementaMenuBuscaElemPorId(TAG *pAg, int pTipoAG){
    int lIdItem = -1;
    printf("Qual id quer buscar:");
    scanf("%d", &lIdItem);
    TAG *lElem = NULL;
    // fazendo a busca de maneira diferenciada, embora nos dois casos
    // retornasse o mesmo resultado. A busca na ABBB tem uma melhor performance
    // pois a complexidade do algoritmo é de uma ordem inferior
    if (pTipoAG == 1){
        // busca em arvore generica
        lElem = busca_AG(pAg, lIdItem);
    }
    else{
        // busca em arvore BBB
        lElem = busca_ABBB(pAg, lIdItem);
    }
    if (lElem){
        imprime_elem_AG(lElem, imprimeItem);
    }
    else {
        printf("\nElemento com id %d nao encontrado", lIdItem);
    }

}

void imprimeMenuAG(){
    printf("\n#######################################################################\n");
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
    printf("\n#######################################################################\n");
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(2) Inserir figura na ABBB\n");
    printf("(3) Buscar figura pelo id na ABBB\n");
    printf("(4) Imprimir representacao da ABBB\n");
    printf("(5) Retirar elemento da ABBB\n");
    printf("(6) Destruir ABBB\n");
    printf("(7) Alterar dimensao de figura na ABBB\n");
    printf("(8) Voltar Menu para AG\n");
}

void imprimeMenuAB(){
    printf("\n#######################################################################\n");
    printf("\nDigite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(2) Inserir figura na AB\n");
    printf("(3) Buscar figura pelo id na AB\n");
    printf("(4) Imprimir representacao da AB\n");
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

void implementaMenuAlteraDim(TAG* pAg, int pTipoAG){
    int lCod;
    printf("\nQual codigo: ");
    scanf("%d", &lCod);
    // fazendo a busca de maneira diferenciada, embora nos dois casos
    // retornasse o mesmo resultado. A busca na ABBB tem uma melhor performance
    // pois a complexidade do algoritmo é de uma ordem inferior
    TAG *lElem = NULL;
    if (pTipoAG == 1){
        // busca em arvore generica
        lElem = busca_AG(pAg, lCod);
    }
    else{
        // busca em arvore BBB
        lElem = busca_ABBB(pAg, lCod);
    }
    if (lElem){
        decideMenuAlteraDim(lElem->no->tipoItem, lElem->no->info);
    }
    else{
        printf("Warning !! Elemento com cod %d nao existe", lCod);
    }
}

TAB* implementaMenuInsereAB(TAB* arv_b, int pT){
    char* lTipoItem = (char*)malloc(sizeof(char)*3);
    int lCod = -1;
    printf("Qual tipo de figura (QUA, TRI, TRA, CIR, RET): ");
    scanf(" %3[^\n]", lTipoItem);
    printf("\nQual codigo: ");
    scanf("%d", &lCod);

    TAB *lElemento = Busca_AB(arv_b, lCod);
    if (!lElemento) {
        void *info = criaFormaPorMenu(lTipoItem);
        if (!info) {
            printf("\nErro !!! Tipo de figura %s não definida", lTipoItem);
            return arv_b;
        }
        arv_b = insere_AB(arv_b, pT, lCod, lTipoItem, info);
    }
    else{
        TNO* no = buscaNo_AB(lElemento, lCod);
        if (no){
            int opt;
            printf("Item %d do tipo %s ja existente. Gostaria de atualizar suas dimensoes? [y-1/n-0]", lCod, no->tipoItem);
            scanf("%d",&opt);
            if(opt==1) {
                decideMenuAlteraDim(no->tipoItem, no->info);
            }
        }
        else{
            printf("Erro !!!Não existe nó com cod. %d neste ramo da arvore B", lCod);
        }
    }
    // posso dar free pois na forma o valor é copiado para outro ponteiro
    free(lTipoItem);
    return arv_b;
}

TAG* implementaMenuInsereABBB(TAG* arv_avl){
    char* lTipoItem = (char*)malloc(sizeof(char)*3);
    int lCod = -1;
    printf("Qual tipo de figura (QUA, TRI, TRA, CIR, RET): ");
    scanf(" %3[^\n]", lTipoItem);
    printf("\nQual codigo: ");
    scanf("%d", &lCod);

    TAG *lElemento = busca_ABBB(arv_avl, lCod);
    if (!lElemento) {
        void *info = criaFormaPorMenu(lTipoItem);
        if (!info) {
            printf("\nErro !!! Tipo de figura %s não definida", lTipoItem);
            return arv_avl;
        }
        arv_avl = insere_ABBB(arv_avl, lCod, lTipoItem, info);
    }
    else{
        int opt;
        printf("Item %d do tipo %s ja existente. Gostaria de atualizar suas dimensoes? [y-1/n-0]", lCod, lElemento->no->tipoItem);
        scanf("%d",&opt);
        if(opt==1) {
            decideMenuAlteraDim(lElemento->no->tipoItem, lElemento->no->info);
        }
    }
    // posso dar free pois na forma o valor é copiado para outro ponteiro
    free(lTipoItem);
    return arv_avl;
}

TAG* implementaMenuInsereAG(TAG* arv_gen){
    char* lTipoItem = (char*)malloc(sizeof(char)*3);
    int lCod = -1;
    int lCodPai = -1;
    printf("Qual tipo de figura (QUA, TRI, TRA, CIR, RET): ");
    scanf(" %3[^\n]", lTipoItem);
    printf("\nQual codigo: ");
    scanf("%d", &lCod);
    printf("\nQual codigo do pai (0 == raiz): ");
    scanf("%d", &lCodPai);

    TAG *lElemento = busca_AG(arv_gen, lCod);
    if (!lElemento) {
        void *info = criaFormaPorMenu(lTipoItem);
        if (!info) {
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
            decideMenuAlteraDim(lElemento->no->tipoItem, lElemento->no->info);
        }
    }
    // posso dar free pois na forma o valor é copiado para outro ponteiro
    free(lTipoItem);
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

void* criaFormaPorMenu(char * pTipoItem){
    void *info = NULL;
    if (strcmp(pTipoItem, "QUA") == 0){
        info = criaQuadradoViaMenu();
    }
    else if (strcmp(pTipoItem, "TRI") == 0){
        info = criaTrianguloViaMenu();
    }
    else if (strcmp(pTipoItem, "RET") == 0){
        info = criaRetanguloViaMenu();
    }
    else if (strcmp(pTipoItem, "TRA") == 0){
        info = criaTrapezioViaMenu();
    }
    else if (strcmp(pTipoItem, "CIR") == 0){
        info = criaCirculoViaMenu();
    }
    return info;
}

void decideMenuAlteraDim(char* pTipoItem, void* pInfo){
    if (strcmp(pTipoItem, "QUA") == 0){
        alteraQuadradoViaMenu(pInfo);
    }
    else if (strcmp(pTipoItem, "TRI") == 0){
        alteraTrianguloViaMenu(pInfo);
    }
    else if (strcmp(pTipoItem, "RET") == 0){
        alteraRetanguloViaMenu(pInfo);
    }
    else if (strcmp(pTipoItem, "TRA") == 0){
        alteraTrapezioViaMenu(pInfo);
    }
    else if (strcmp(pTipoItem, "CIR") == 0){
        alteraCirculoViaMenu(pInfo);
    }
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
