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
    int base;
    int altura;
    float area;
}TR;

typedef struct triangulo{
    int base;
    int altura;
    float area;
}TT;

typedef struct trapezio{
    int baseMaior;
    int baseMenor;
    int altura;
    float area;
}TZ;

TQ *criaQuadrado(int pLado);
TR *criaRetangulo(int pLadoGrande, int pLadoPequeno);
TT *criaTriangulo(int pBase, int pAltura);
TC *criaCirculo(int pRaio);
TZ *criaTrapezio(int pBaseMenor, int pBaseMaior, int pAltura);

TQ *criaQuadrado(int pLado){
    TQ *quad = (TQ*)malloc(sizeof(TQ));
    quad->lado = pLado;
    quad->area = pLado * pLado;
    return quad;
}

TR *criaRetangulo(int pBase, int pAltura){
    TR *retang = (TR*)malloc(sizeof(TR));
    retang->base = pBase;
    retang->altura = pAltura;
    retang->area = pBase * pAltura;
    return retang;
}

TT *criaTriangulo(int pBase, int pAltura){
    TT *triang = (TT*)malloc(sizeof(TT));
    triang->base = pBase;
    triang->altura = pAltura;
    triang->area = (pAltura * pBase)/2;
    return triang;
}

TC *criaCirculo(int pRaio){
    TC *circ = (TC*)malloc(sizeof(TC));
    circ->raio = pRaio;
    circ->area = M_PI * (pRaio * pRaio);
    return circ;
}

TZ *criaTrapezio(int pBaseMenor, int pBaseMaior, int pAltura){
    TZ *trap = (TZ*)malloc(sizeof(TZ));
    trap->baseMaior = pBaseMaior;
    trap->baseMenor = pBaseMenor;
    trap->area = ((pBaseMaior + pBaseMenor) * pAltura) / 2;
    return trap;
}