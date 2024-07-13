#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

const char* keywords[] = {
    //puxei na ordem do enunciado de lexico
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

int verifica_palavra_chave(const char* str) {
    //passaremos por todas as palavras chaves verificando
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// verificaremos se uma linha contem uma palavra-chave especifica
int contem_palavra_chave(const char *linha, const char *keyword) {
    return strstr(linha, keyword) != NULL;
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

void remove_comentarios(char *linha) {
    char *inicio = strstr(linha, "{");
    while (inicio != NULL) {
        char *fim = strstr(inicio, "}");
        if (fim != NULL) {
            memmove(inicio, fim + 1, strlen(fim + 1) + 1);
            inicio = strstr(linha, "{");
        } else {
            *inicio = '\0';
            break;
        }
    }
    inicio = strstr(linha, "(*");
    while (inicio != NULL) {
        char *fim = strstr(inicio, "*)");
        if (fim != NULL) {
            memmove(inicio, fim + 2, strlen(fim + 2) + 1);
            inicio = strstr(linha, "(*");
        } else {
            *inicio = '\0';
            break;
        }
    }
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

// verificando se uma variavel foi declarada
int verifica_variavel_declarada(const char* variavel, char declaradas[][256], int num_declaradas) {
    for (int i = 0; i < num_declaradas; i++) {
        if (strcmp(variavel, declaradas[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

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
    int during_comment = 0;
    int is_last_char = 0;
    
    //leremos todos os caracteres ate o fim do arquivo (EOF)
    while (!is_last_char && (caracter = fgetc(file)) != EOF) { 
    
        if (fgetc(file) == EOF) {
            is_last_char = 1;
            printf("Cheguei no final\n");
            if (inside_comment == 1) {
                count->keyword += count_aux->keyword;
                count->identifier += count_aux->identifier;
                count->number += count_aux->number;
                count->operator += count_aux->operator;
                count->compound_operator += count_aux->compound_operator;
                count->delimiter += count_aux->delimiter;
                count->comments += count_aux->comments;
                count->unknown += count_aux->unknown;
            }
            printf("Count de KW: %d\n", count->keyword);

        } else {
            fseek(file, -1, SEEK_CUR);

            if (inside_comment == 1) {
            // printf("Estou em um comentário\n");
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
                } else { // Dentro de um "comentário" mas ainda sem fechamento | inside_comment = 1
                    count_aux->keyword++;
                    printf("Count_aux KW: %s\n", buffer);
                }

            } else if (verifica_identificador(buffer)) {
                if (inside_comment == 0) {
                    count->identifier++;
                } else {
                    printf("Count_aux de ident: %d\n", count_aux->identifier);
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

            // printf("Caracter atual: %c\n", op[0]);
            // printf("Próximo caracter: %c\n", op[1]);

            // Verificando operador Composto
            if ((verifica_operador(op[0]) == 0) && (verifica_operador(op[1]) == 0)) {
                if (inside_comment == 0) {
                    count->compound_operator++;
                } else {
                    count_aux->compound_operator++;
                }
          
                // printf("COMPOSTO: %d\n", count->compound_operator);
            } else {
                // Operador Comum
                ungetc(proximo_caracter, file);
                if (inside_comment == 0) {
                    count->operator++;
                } else {
                    count_aux->compound_operator++;
                }
                // printf("NORMAL: %d\n", count->operator);
            }
            // printf("Op: %s\n", op);
        } else if (caracter == '(') {
            char proximo_caracter = fgetc(file);
            if (proximo_caracter == '*') {
                inside_comment = 1;
                during_comment = 1;
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
                // printf("Op (Delimitador): %s\n", op);
            } else {
                ungetc(proximo_caracter, file);
                if (inside_comment == 0) {
                        count->delimiter++;
                } else {
                    count_aux->delimiter++;
                }
                // printf("Delimitadores: %c\n", caracter);
            }
            
        } else if (!isspace(caracter)) {
            if (inside_comment == 0) {
                     count->unknown++;
                } else {
                    count_aux->unknown++;
                }
            // printf("Unknown: %c \n", caracter);
        }
        } 
    }

    fclose(file);
}

// vamos analisar o arquivo pascal e fazer a analise lexica
int analise_sintatica(FILE *file) {

    char linha[256];
    //vamos armazenar quando acharmos a palavra program
    int program = 0;
    //vamos armazenar quando acharmos a palavra begin
    int begin = 0;
    //vamos armazenar quando acharmos a palavra end
    int end = 0;
    //como no enunciado pede para recusarmos variaveis nao declaradas vamos armazenar
    char declaradas[100][256];
    //vamos guardar o numero de variaveis utilizadas para saber se n foi usado algo que n foi declarado antes
    int num_declaradas = 0;

    int dentro_var = 0;
    

    //vamos verificar linha por linha se encontramos essas 3 variaveis e vamos coloca-las como 1 se acharmos
    while (fgets(linha, sizeof(linha), file)) {
        //vamos remover comentarios
        remove_comentarios(linha);

        if (contem_palavra_chave(linha, "program")) {
            if(program == 0 && begin == 0 && end == 0 ){
                //  printf("Encontrado: program\n");
                  program == 1;
                  continue;
            } else{
                return 0;
                
            }
            
          
        }

        if (contem_palavra_chave(linha, "begin")) {
            if (program == 1 && begin == 0 && end ==0 ){
                begin = 1;
             //  printf("Encontrado: begin\n");
             continue;
            } else {
                return 0;
            }
            
        }

        if (contem_palavra_chave(linha, "end.")) {
            if (program == 1 && begin == 1 && end == 0) {

                 end = 1;
                //printf("Encontrado: end\n");
                continue;
            } else {
                return 0;
            }
           
        }

        if (contem_palavra_chave(linha, "var")) {
            dentro_var = 1;
            continue;
        }

        if (dentro_var && contem_palavra_chave(linha, "begin")) {
            dentro_var = 0;
        }

         if (dentro_var == 0) {
            char *token = strtok(linha, " ,;");
            while (token != NULL) {
                if (verifica_identificador(token)) {
                    strcpy(declaradas[num_declaradas++], token);
                }
                token = strtok(NULL, " ,;");
            }
        } else {
            char *token = strtok(linha, " ");
            while (token != NULL) {
                if (verifica_identificador(token)) {
                    if (!verifica_variavel_declarada(token, declaradas, num_declaradas) && !verifica_palavra_chave(token)) {
                        return 0; // Variável não declarada
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }

    

    // se acharmos as 3 vamos poder aceitar senao vamos recusar
    if (program == 1 && begin == 1 && end == 1) {
        return 1;
        //printf("Encontrei as 3 palavras chaves \n"); 
    } else {
        return 0; 
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s arquivo.pas\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    if (analise_sintatica(file)) {
        printf("Aceito\n");
    } else {
        printf("Rejeito\n");
    }

    fclose(file);
    return 0;
}
