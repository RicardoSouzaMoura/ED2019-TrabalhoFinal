#include <stdlib.h>

typedef struct AG {
    int cod;
    struct AG *filho, *irmao;
}TAG;

typedef struct info{
    int tipo;
    void *info;
}TNO;

TAG *criaArvoreGenerica();
