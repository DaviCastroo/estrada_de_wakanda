#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("[DEBUG] Erro ao abrir arquivo!\n");
        return NULL;
    }

    int T, N;                     
    
    if(fscanf(arquivo, "%d", &T) != 1 || T < 3 || T > pow(10,6)){ 
        printf("[DEBUG] Valor de T é inválido: %d\n", T);
        fclose(arquivo);
        return NULL; 
    }

    if(fscanf(arquivo, "%d", &N) != 1 || N < 2 || N > pow(10,4)){ 
        printf("[DEBUG] Valor de N é inválido: %d\n", N);
        fclose(arquivo);
        return NULL; 
    }
    
    //*e= ponteiro que armazena as informações na struct; e= estrutura
    // alocando memória para armazenar os itens na struct/ lista principal 
    Estrada *e = malloc(sizeof(Estrada));
    if(e == NULL){
        printf("[DEBUG] Falha ao alocar memória para lista!\n");
        fclose(arquivo);
        return NULL;
    }

    e->T = T;
    e->N = N;

    // alocação dinamica do vetor de cidades, guardando o número de cidades
    e->C = malloc(N * sizeof(Cidade));
    if(e->C == NULL){
        printf("[DEBUG] Falha ao alocar memória para o vetor de cidades\n");
        free(e);
        fclose(arquivo);
        return NULL;
    }

    // vetor auxiliar que armazena as posições xi lidas, verificando se alguma se repete
    int *posicoes = malloc(N * sizeof(int));
    if(posicoes == NULL){
        printf("[DEBUG] Falha ao alocar memória para vetor auxiliar de posições\n");
        free(e->C);
        free(e);
        fclose(arquivo);
        return NULL;
    }

    for(int i = 0; i < N; i++){
        int pos; // guarda a posição da cidade (distância da fronteira)
        char nome[256]; 
        if (fscanf(arquivo, "%d %[^\n]", &pos, nome) != 2 || pos <= 0 || pos >= T){
            printf("[DEBUG] Erro ao ler cidade %d: posição inválida (%d) ou leitura falhou.\n", i + 1, pos);
            free(posicoes);
            free(e->C);
            free(e);
            fclose(arquivo);
            return NULL;
        }

        for(int j = 0; j < i; j++){
            if(posicoes[j] == pos ){
                printf("[DEBUG] Posição duplicada detectada: %d\n", pos);
                free(posicoes);
                free(e->C);
                free(e);
                fclose(arquivo);
                return NULL;
            }
        }

        posicoes[i] = pos;
        e->C[i].Posicao = pos;
        strcpy(e->C[i].Nome, nome);

        printf("[DEBUG] Cidade %d lida: %s na posição %d\n", i + 1, nome, pos);
    }

    free(posicoes);
    fclose(arquivo);
    printf("[DEBUG] Leitura do arquivo concluída com sucesso.\n");
    
    return e;
}
