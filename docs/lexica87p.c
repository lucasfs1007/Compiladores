#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// struct para contagem de cada tipo de token pedido no enunciado
typedef struct {
    int keyword;
    int identifier;
    int number;
    int operator;
    int compound_operator;
    int delimiter;
    int comments;
    int unknown;
} TokenCount;

// lista de palavras reservadas em Pascal
const char* keywords[] = {
    //puxei na ordem do enunciado
   "and", 
   "array", 
   "begin", 
   "div", 
   "do", 
   "else", 
   "end",
   "function", 
   "goto", 
   "if", 
   "label", 
   "not", 
   "of", 
   "or",
   "procedure", 
   "program", 
   "then", 
   "type", 
   "var", 
   "while",
   "read", 
   "write"
};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// verificar se eh palavra-chave
int verifica_palavra_chave(const char* str) {
    //passaremos por todas as palavras chaves verificando
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// verifica se eh operador
int verifica_operador(char caracter) {
    if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '<' || caracter == '>' || caracter == '=')
        return 0;

    return 1;
}

// verifica se eh operador composto
int verifica_operador_composto(const char* str) {
    if ((str[0] == ':' && str[1] == '=') || (str[0] == '<' && str[1] == '=') || (str[0] == '>' && str[1] == '=') || (str[0] == '<' && str[1] == '>'))
        return 0;

    return 1;
    // return strcmp(str, ':=') || strcmp(str, '<=') ||
    //        strcmp(str, '>=') || strcmp(str, '<>');
}

// verifica se eh delimitador
int verifica_delimitador(char caracter) {
    if (caracter == '(' || caracter == ')' || caracter == '[' || caracter == ']' ||
           caracter == ';' || caracter == ':' || caracter == ',' || caracter == '.') {
            return 0;
    }
    
    return 1;
}

//essas duas sao funcoes da biblioteca ctype para ver o tipo de caracter

// verifica se eh identificador
int verifica_identificador(const char* str) {
    if (!isalpha(str[0])) {
        return 0;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            return 0;
        }
    }
    return 1;
}

// verificar se eh digito
int verifica_numero(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// funcao para fazer a Analise lexica de fato
void lexico(const char* filename, TokenCount* count, TokenCount* count_aux) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        //nesse caso n conseguimos abrir o arquivo
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        exit(EXIT_FAILURE);
    }
   
    char buffer[256];
    char caracter;
    int buffer_index = 0;
    int inside_comment = 0;
    
    //leremos todos os caracteres ate o fim do arquivo (EOF)
    while ((caracter = fgetc(file)) != EOF) { 
        //logica para identificar comentario 
        if (inside_comment == 1) {
            if (caracter == '*' && fgetc(file) == ')') {
                inside_comment = 0;
                count->comments++;
            } 
        } else if (isalpha(caracter)) {
            buffer[buffer_index++] = caracter;
            while (isalnum(caracter = fgetc(file))) {
                buffer[buffer_index++] = caracter;
            }
            ungetc(caracter, file);
            buffer[buffer_index] = '\0';
            buffer_index = 0;

            //contagem de palavras chave, identificadores e palavras nao identificadas
            if (verifica_palavra_chave(buffer)) {
                if (inside_comment == 0) {
                    count->keyword++;
                } else { 
                    count_aux->keyword++;
                }

            } else if (verifica_identificador(buffer)) {
                if (inside_comment == 0) {
                    count->identifier++;
                } else {
                    count_aux->identifier++;
                }
            } else {
                if (inside_comment == 0) {
                     count->unknown++;
                } else {
                    count_aux->unknown++;
                }
            }

        } else if (isdigit(caracter)) {
            buffer[buffer_index++] = caracter;
            while (isdigit(caracter = fgetc(file))) {
                buffer[buffer_index++] = caracter;
            }
            ungetc(caracter, file);
            buffer[buffer_index] = '\0';
            buffer_index = 0;

            if (verifica_numero(buffer)) {
                if (inside_comment == 0) {
                    count->number++;
                } else {
                    count_aux->number++;
                }
            } else {
                if (inside_comment == 0) {
                     count->unknown++;
                } else {
                    count_aux->unknown++;
                }
            }
        } else if (verifica_operador(caracter) == 0) {
            char op[3] = {caracter, '\0', '\0'};
            char proximo_caracter = fgetc(file);
            op[1] = proximo_caracter;

            if ((verifica_operador(op[0]) == 0) && (verifica_operador(op[1]) == 0)) {
                if (inside_comment == 0) {
                    count->compound_operator++;
                } else {
                    count_aux->compound_operator++;
                }
            } else {
                ungetc(proximo_caracter, file);
                if (inside_comment == 0) {
                    count->operator++;
                } else {
                    count_aux->compound_operator++;
                }
            }
        } else if (caracter == '(') {
            char proximo_caracter = fgetc(file);
            if (proximo_caracter == '*') {
                inside_comment = 1;
            } else {
                ungetc(proximo_caracter, file);
                count->delimiter++;
            }
        } else if (verifica_delimitador(caracter) == 0) {
            char op[3] = {caracter, '\0', '\0'};
            char proximo_caracter = fgetc(file);
            op[1] = proximo_caracter;
            
            if (caracter == ':' && proximo_caracter == '=') {
                if (inside_comment == 0) {
                    count->compound_operator++;
                } else {
                    count_aux->compound_operator++;
                }
            } else {
                ungetc(proximo_caracter, file);
                if (inside_comment == 0) {
                        count->delimiter++;;
                } else {
                    count_aux->delimiter++;
                }
            }
        } else if (!isspace(caracter)) {
            if (inside_comment == 0) {
                     count->unknown++;
                } else {
                    count_aux->unknown++;
                }
        }
    }

    // Verificação para comentários não fechados
    if (inside_comment) {
        printf("Erro: Comentário não fechado.\n");
        fseek(file, -buffer_index, SEEK_CUR);  // Voltar ao início do comentário
        while (buffer_index-- > 0) {
            caracter = fgetc(file);
            if (caracter == '(') {
                count->delimiter++;
            } else if (caracter == '*') {
                count->operator++;
            } else {
                if (verifica_delimitador(caracter)) {
                    count->delimiter++;
                } else if (verifica_operador(caracter) == 0) {
                    count->operator++;
                } else {
                    count->unknown++;
                }
            }
        }
    }

    fclose(file);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_pascal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //iniciei todos com 0 
    TokenCount count = {0, 0, 0, 0, 0, 0, 0, 0}; 
    TokenCount count_aux = {0, 0, 0, 0, 0, 0, 0, 0}; 
    //chamo a funcao para fazer as verificacoes e contar
    lexico(argv[1], &count, &count_aux); 

    //aqui faco o print de tudo
    printf("KEYWORD: %d\n", count.keyword);
    printf("IDENTIFIER: %d\n", count.identifier);
    printf("NUMBER: %d\n", count.number);
    printf("OPERATOR: %d\n", count.operator);
    printf("COMPOUND OPERATOR: %d\n", count.compound_operator);
    printf("DELIMITER: %d\n", count.delimiter);
    printf("COMMENTS: %d\n", count.comments);
    printf("UNKNOWN: %d\n", count.unknown);

    return EXIT_SUCCESS;
}
