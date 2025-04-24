#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) return NULL;

    int T, N;
    if (fscanf(fp, "%d", &T) != 1 || T < 3 || T > 1000000) {
        fclose(fp);
        return NULL;
    }

    if (fscanf(fp, "%d", &N) != 1 || N < 2 || N > 10000) {
        fclose(fp);
        return NULL;
    }

    // Aloca estrutura principal
    Estrada *e = malloc(sizeof(Estrada));
    if (!e) {
        fclose(fp);
        return NULL;
    }

    e->T = T;
    e->N = N;
    e->C = malloc(N * sizeof(Cidade));
    if (!e->C) {
        free(e);
        fclose(fp);
        return NULL;
    }

    int *posicoes = malloc(N * sizeof(int));
    if (!posicoes) {
        free(e->C);
        free(e);
        fclose(fp);
        return NULL;
    }

    // Leitura das cidades
    for (int i = 0; i < N; i++) {
        int pos;
        char nome[256];
        if (fscanf(fp, "%d %[^\n]", &pos, nome) != 2 || pos <= 0 || pos >= T) {
            free(posicoes);
            free(e->C);
            free(e);
            fclose(fp);
            return NULL;
        }

        // Verifica se a posição já foi usada
        for (int j = 0; j < i; j++) {
            if (posicoes[j] == pos) {
                free(posicoes);
                free(e->C);
                free(e);
                fclose(fp);
                return NULL;
            }
        }

        posicoes[i] = pos;
        e->C[i].Posicao = pos;
        strcpy(e->C[i].Nome, nome);
    }

    free(posicoes);
    fclose(fp);
    return e;
}
