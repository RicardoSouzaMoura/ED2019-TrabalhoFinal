#include <stdlib.h>
#include <stdio.h>

void imprimeMenu();

int main(void){
    int opcao = -1;

    printf("Bem vindo !!!\n");
    
    while(opcao != 0){
        imprimeMenu();
        scanf("%d", &opcao);

        printf("Opcao escolhida: %d\n", opcao);
    }
    
}

void imprimeMenu(){
    printf("Digite uma opcao do menu: \n");
    printf("(0) Sair\n");
    printf("(1) Ler Arquivo inicial\n");
    
}