#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Keywords in C
const char *keywords[] = {
    "int", "float", "char", "double", "return", "void", "if", "else", "while", "for", "break", "continue", "string", NULL
};

// Operators in C
const char operators[] = "+-*/=%<>!&|";

// Punctuation symbols in C
const char punctuation[] = "(),;{}[]";

// Check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a character is an operator
int isOperator(char ch) {
    return strchr(operators, ch) != NULL;
}

// Check if a character is a punctuation symbol
int isPunctuation(char ch) {
    return strchr(punctuation, ch) != NULL;
}

// Tokenize input string
void tokenize(const char *line) {
    char buffer[MAX];
    int i = 0, j = 0;

    while (line[i] != '\0') {
        if (isspace(line[i])) {
            i++; // Skip whitespaces
            continue;
        }

        // Check for keywords, identifiers, or constants
        if (isalpha(line[i]) || line[i] == '_') {
            while (isalnum(line[i]) || line[i] == '_') {
                buffer[j++] = line[i++];
            }
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
        }
        // Check for numbers (constants)
        else if (isdigit(line[i])) {
            while (isdigit(line[i])) {
                buffer[j++] = line[i++];
            }

            if (isalpha(line[i])) { // Detect invalid lexemes like 7H
                buffer[j++] = line[i++];
                while (isalnum(line[i])) {
                    buffer[j++] = line[i++];
                }
                buffer[j] = '\0';
                printf("Error: Invalid lexeme '%s'\n", buffer);
            } else {
                buffer[j] = '\0';
                printf("Constant: %s\n", buffer);
            }
            j = 0;
        }
        // Check for string literals
        else if (line[i] == '"' || line[i] == '\'') {
            char quote = line[i++];
            while (line[i] != quote && line[i] != '\0') {
                buffer[j++] = line[i++];
            }
            if (line[i] == quote) {
                i++; // Skip closing quote
                buffer[j] = '\0';
                printf("String: '%s'\n", buffer);
            } else {
                printf("Error: Unterminated string\n");
            }
            j = 0;
        }
        // Check for operators
        else if (isOperator(line[i])) {
            printf("Operator: %c\n", line[i]);
            i++;
        }
        // Check for punctuation
        else if (isPunctuation(line[i])) {
            printf("Punctuation: %c\n", line[i]);
            i++;
        }
        // Anything else is an error
        else {
            printf("Error: Invalid character '%c'\n", line[i]);
            i++;
        }
    }
}

int main() {
    char sourceCode[MAX];
    sourceCode[0] = '\0'; // Initialize empty source code string

    printf("Enter your C code (type 'END' to finish input):\n");
    
    while (1) {
        char input[MAX];
        if (fgets(input, MAX, stdin) == NULL) {
            break;
        }

        // Check if the input is "END" to stop reading
        if (strcmp(input, "END\n") == 0) {
            break;
        }

        strcat(sourceCode, input);
    }

    printf("\n--- TOKENS ---\n");
    tokenize(sourceCode);

    return 0;
}