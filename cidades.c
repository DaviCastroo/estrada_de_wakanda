#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

Estrada *getEstrada(const char *nomeArquivo){
    FILE *arquivo=fopen(nomeArquivo, "r");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo!\n");
            fclose(arquivo);
            return NULL
        }
    int T, N;                       // != 1 é a verificação se o arquivo foi aberto corretamente                
    if(fscanf(arquivo, "%d", &T) != 1  T <=3 || T <= pow(10,6)){ 
        printf("Valor de E é invalido!");
        fclose(arquivo);
        return NULL; 
    }
    if(fscanf(arquivo, "%d", &N) != 1  N <=2 || N <= pow(10,4)){ 
        printf("Valor de N é invalido!");
        fclose(arquivo);
        return NULL; 
    }
}