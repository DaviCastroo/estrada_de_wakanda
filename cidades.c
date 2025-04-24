#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#include "cidades.h"

void selectionSortCidades(Cidade *cidades, int n) {
    for (int i = 1; i < n; i++) {
        Cidade atual = cidades[i];
        int j = i - 1;
        while (j >= 0 && cidades[j].Posicao > atual.Posicao) {
            cidades[j + 1] = cidades[j];
            j--;
        }
        cidades[j + 1] = atual;
    }
}

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
                printf("[DEBUG] Posição duplicada: %d\n", pos);
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

    //ordena as cidades 
    selectionSortCidades(e -> C, e -> N);

    printf("Leitura do arquivo concluída com sucesso.\n");
    
    return e;
}

double calcularMenorVizinhanca (const char *nomeArquivo){
    Estrada *estrada = getEstrada (nomeArquivo);
        if(estrada == NULL){
            return -1.0;
        }
    
    double menor = estrada->T;
    
    for(int i = 0;i < estrada -> N; i++){
        double vizinhanca;
            if( i == 0 ){
                vizinhanca = (estrada -> C[1].Posicao - estrada -> C[0].Posicao) / 2.0 + estrada -> C[0].Posicao;
            }
                else if ( i == estrada -> N-1 ) {
                    vizinhanca = (estrada ->C[i].Posicao - estrada ->C[i - 1].Posicao) /2.0 + (estrada -> T - estrada ->C[i].Posicao);//
                }
                    else{
                        vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i - 1].Posicao) / 2.0;
            }
            if(vizinhanca < menor){
                menor = vizinhanca;
            }
    }
    free(estrada -> C);
    free(estrada);
    return menor;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo){
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL){
        return NULL;
    } 

    double menor = 1e9;
    int indiceMenor = -1;

    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;

        if (i == 0) {
            vizinhanca = (estrada->C[1].Posicao - estrada->C[0].Posicao) / 2.0 + estrada->C[0].Posicao;
        } else if (i == estrada->N - 1) {
            vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0 + (estrada->T - estrada->C[i].Posicao);
        } else {
            vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        }

        if (vizinhanca < menor) {
            menor = vizinhanca;
            indiceMenor = i;
        }
    }

    char *nomeCidade = strdup(estrada->C[indiceMenor].Nome);

    free(estrada->C);
    free(estrada);

    return nomeCidade;
}