#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct quadrado{
    int lado;
    float area;
}TQ;

typedef struct circulo{
    int raio;
    float area;
}TC;

typedef struct retangulo{
    int ladoGrande;
    int ladoPequeno;
    float area;
}TR;

typedef struct triangulo{
    int base;
    int altura;
    float area;
}TT;

typedef struct trapezio{
    int baseGrande;
    int basePequena;
    int altura;
    float area;
}TZ;

TQ *criaQuadrado(int pLado);
TR *criaRetangulo(int pLadoGrande, int pLadoPequeno);
TT *criaTriangulo(int pBase, int pAltura);
TC *criaCirculo(int pRaio);
TZ *criaTrapezio(int pBaseGrande, int pBasePequena, int pAltura);

TQ *criaQuadrado(int pLado){
    TQ *quad = (TQ*)malloc(sizeof(TQ));
    quad->lado = pLado;
    quad->area = pLado * pLado;
    return quad;
}

TR *criaRetangulo(int pLadoGrande, int pLadoPequeno){
    TR *retang = (TR*)malloc(sizeof(TR));
    retang->ladoGrande = pLadoGrande;
    retang->ladoPequeno = pLadoPequeno;
    retang->area = pLadoPequeno * pLadoGrande;
    return retang;
}

TT *criaTriangulo(int pBase, int pAltura){
    TT *triang = (TT*)malloc(sizeof(TT));
    triang->base = pBase;
    triang->altura = pAltura;
    triang->area = pAltura * pBase;
    return triang;
}

TC *criaCirculo(int pRaio){
    TC *circ = (TC*)malloc(sizeof(TC));
    circ->raio = pRaio;
    circ->area = M_PI * (pRaio * pRaio);
    return circ;
}

TZ *criaTrapezio(int pBaseGrande, int pBasePequena, int pAltura){
    TZ *trap = (TZ*)malloc(sizeof(TZ));
    trap->baseGrande = pBaseGrande;
    trap->basePequena = pBasePequena;
    trap->area = ((pBaseGrande + pBasePequena) * pAltura) / 2;
    return trap;
}