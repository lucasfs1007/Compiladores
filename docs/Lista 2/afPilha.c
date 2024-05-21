#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

typedef struct {
    char pilha[MAX_SYMBOLS]; // Definindo a estrutura da pilha
    int topo; // Índice do topo da pilha
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1; // Inicializando o topo da pilha como -1 (pilha vazia)
}

bool estaVazia(Pilha *pilha) {
    return pilha->topo == -1; // Retorna verdadeiro se o topo for -1, indicando pilha vazia
}

bool estaCheia(Pilha *pilha) {
    return pilha->topo == MAX_SYMBOLS - 1; // Retorna verdadeiro se o topo for MAX_SYMBOLS - 1, indicando pilha cheia
}

void empilhar(Pilha *pilha, char simbolo) {
    if (!estaCheia(pilha)) { // Verifica se a pilha não está cheia
        pilha->pilha[++pilha->topo] = simbolo; // Incrementa o topo e insere o símbolo na pilha
    }
}

char desempilhar(Pilha *pilha) {
    if (!estaVazia(pilha)) { // Verifica se a pilha não está vazia
        return pilha->pilha[pilha->topo--]; // Retorna o símbolo no topo da pilha e decrementa o topo
    }
    return '\0'; // Retorna nulo se a pilha estiver vazia
}

void imprimirPilha(Pilha *pilha) {
    if (estaVazia(pilha)) { // Verifica se a pilha está vazia
        printf("nil\n"); // Imprime "nil" se a pilha estiver vazia
    } else {
        for (int i = 0; i <= pilha->topo; i++) {
            printf("%c", pilha->pilha[i]); // Imprime cada símbolo da pilha
        }
        printf("\n");
    }
}

void processarPalavra(char *palavra) {
    Pilha pilha;
    inicializarPilha(&pilha); // Inicializa a pilha

    int tamanho = strlen(palavra);

    for (int i = 0; i < tamanho; i++) {
        char caractereAtual = palavra[i];

        if (estaVazia(&pilha)) {
            if (caractereAtual == 'a') {
                empilhar(&pilha, 'A');
            } else if (caractereAtual == 'b') {
                empilhar(&pilha, 'B');
            }
        } else {
            char simboloTopo = pilha.pilha[pilha.topo];
            if ((caractereAtual == 'a' && simboloTopo == 'B') || (caractereAtual == 'b' && simboloTopo == 'A')) {
                desempilhar(&pilha);
            } else if ((caractereAtual == 'a' && simboloTopo == 'A') || (caractereAtual == 'b' && simboloTopo == 'B')) {
                empilhar(&pilha, simboloTopo);
            }
        }
        imprimirPilha(&pilha);
    }

    if (estaVazia(&pilha)) {
        printf("Aceito\n");
    } else {
        printf("Rejeito\n");
    }
    printf("\n");
}

int main() {
    char palavra[MAX_SYMBOLS];

    bool primeiroCasoDeTeste = true;
    while (scanf("%s", palavra) != EOF) {
        if (!primeiroCasoDeTeste) {
            printf("\n");
        }
        processarPalavra(palavra);
        primeiroCasoDeTeste = false;
    }

    return 0;
}

