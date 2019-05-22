#include <stdlib.h>

typedef struct AG {
    int cod;
    struct AG *filho, *irmao;
}TAG;

typedef struct info{
    int tipo;
    void *info;
}TNO;

TAG *cria();

TAG *insere(TAG* ag, void* item);

TAG *remove(TAG *ag, void* item);

void imprime(TAG *ag);
