#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26

typedef struct {
    int states[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
    int numStates;
    int numSymbols;
    int initialState;
    int numFinalStates;
    int finalStates[MAX_STATES];
} NFA;

void initializeNFA(NFA *nfa) {
    for (int i = 0; i < MAX_STATES; ++i) {
        for (int j = 0; j < MAX_SYMBOLS; ++j) {
            for (int k = 0; k < MAX_STATES; ++k) {
                nfa->states[i][j][k] = -1;
            }
        }
    }
    nfa->numStates = 0;
    nfa->numSymbols = 0;
    nfa->initialState = 0;
    nfa->numFinalStates = 0;
}

void addTransition(NFA *nfa, int from, char symbol, int to) {
    int symbolIndex = symbol - 'a';
    nfa->states[from][symbolIndex][to] = to;
}

bool isFinalState(NFA *nfa, int state) {
    for (int i = 0; i < nfa->numFinalStates; ++i) {
        if (nfa->finalStates[i] == state) {
            return true;
        }
    }
    return false;
}

bool processInput(NFA *nfa, char *input) {
    int currentStates[MAX_STATES];
    int numCurrentStates = 1;
    currentStates[0] = nfa->initialState;
    
    for (int i = 0; input[i] != '\0'; ++i) {
        int symbolIndex = input[i] - 'a';
        int nextStates[MAX_STATES];
        int numNextStates = 0;
        
        for (int j = 0; j < numCurrentStates; ++j) {
            int currentState = currentStates[j];
            for (int k = 0; k < nfa->numStates; ++k) {
                if (nfa->states[currentState][symbolIndex][k] != -1) {
                    nextStates[numNextStates++] = nfa->states[currentState][symbolIndex][k];
                }
            }
        }
        
        if (numNextStates == 0) {
            return false;
        }
        
        numCurrentStates = numNextStates;
        for (int j = 0; j < numCurrentStates; ++j) {
            currentStates[j] = nextStates[j];
        }
    }
    
    for (int i = 0; i < numCurrentStates; ++i) {
        if (isFinalState(nfa, currentStates[i])) {
            return true;
        }
    }
    
    return false;
}

int main() {
    NFA nfa;
    initializeNFA(&nfa);

    int numStates;
    scanf("%d", &numStates);
    nfa.numStates = numStates;

    int numSymbols;
    scanf("%d", &numSymbols);
    nfa.numSymbols = numSymbols;

    char symbols[MAX_SYMBOLS];
    for (int i = 0; i < numSymbols; ++i) {
        scanf(" %c", &symbols[i]);
    }

    for (int i = 0; i < numStates * numSymbols; ++i) {
        int from, numDestinations;
        char symbol;
        scanf("%d %c %d", &from, &symbol, &numDestinations);
        for (int j = 0; j < numDestinations; ++j) {
            int to;
            scanf("%d", &to);
            addTransition(&nfa, from, symbol, to);
        }
    }

    scanf("%d", &nfa.initialState);

    scanf("%d", &nfa.numFinalStates);
    for (int i = 0; i < nfa.numFinalStates; ++i) {
        scanf("%d", &nfa.finalStates[i]);
    }

    char input[MAX_STATES];
    scanf("%s", input);

    if (processInput(&nfa, input)) {
        printf("Aceito\n");
    } else {
        printf("Rejeito\n");
    }

    return 0;
}

