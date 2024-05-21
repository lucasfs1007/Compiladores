#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ESTADOS 100
#define MAX_SIMBOLOS 100

typedef struct {
    int tabela_transicao[MAX_ESTADOS][MAX_SIMBOLOS];
    int estado_inicial;
    int estados_finais[MAX_ESTADOS];
    int num_estados;
    int num_simbolos;
    int num_estados_finais;
} AFD;

void inicializar_AFD(AFD *automato) {
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_SIMBOLOS; j++) {
            automato->tabela_transicao[i][j] = -1;
        }
    }
    automato->num_estados = 0;
    automato->num_simbolos = 0;
    automato->num_estados_finais = 0;
}

void ler_transicoes(AFD *automato) {
    int origem, destino;
    char simbolo;

    for (int i = 0; i < automato->num_estados * automato->num_simbolos; i++) {
        scanf("%d %c %d", &origem, &simbolo, &destino);
        automato->tabela_transicao[origem][simbolo - 'a'] = destino;
    }
}

bool processar_palavra(AFD *automato, char *palavra) {
    int estado_atual = automato->estado_inicial;
    int comprimento = strlen(palavra);

    for (int i = 0; i < comprimento; i++) {
        char simbolo = palavra[i];
        int indice_simbolo = simbolo - 'a';
        estado_atual = automato->tabela_transicao[estado_atual][indice_simbolo];
        if (estado_atual == -1) return false;
    }

    for (int i = 0; i < automato->num_estados_finais; i++) {
        if (automato->estados_finais[i] == estado_atual) return true;
    }

    return false;
}

int main() {
    AFD automato;
    inicializar_AFD(&automato);

    scanf("%d", &automato.num_estados);

    scanf("%d", &automato.num_simbolos);
    for (int i = 0; i < automato.num_simbolos; i++) {
        char simbolo;
        scanf(" %c", &simbolo);
    }

    ler_transicoes(&automato);

    scanf("%d", &automato.estado_inicial);

    scanf("%d", &automato.num_estados_finais);
    for (int i = 0; i < automato.num_estados_finais; i++) {
        scanf("%d", &automato.estados_finais[i]);
    }

    char palavra[MAX_ESTADOS];
    scanf("%s", palavra);

    if (processar_palavra(&automato, palavra)) {
        printf("Aceito\n");
    } else {
        printf("Rejeito\n");
    }

    return 0;
}

