%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

/* Define regular expressions for token categories */
KEYWORD    "int"|"char"|"return"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT   [0-9]+[Hh]?
STRING     ".*?"|'.'
PUNCTUATION [(){};,]
OPERATOR   [=+*/-]
COMMENT    "//".*|/\*([^*]|\*+[^*/])*\*+/
WHITESPACE [ \t\n]+

%%
{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{IDENTIFIER}   { printf("Identifier: %s\n", yytext); }
{CONSTANT}     { if(strchr(yytext, 'H') || strchr(yytext, 'h'))
                     printf("Lexical Error: Invalid constant %s\n", yytext);
                  else
                     printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{PUNCTUATION}  { printf("Punctuation: %s\n", yytext); }
{OPERATOR}     { printf("Operator: %s\n", yytext); }
{WHITESPACE}   { /* Ignore white spaces */ }
.              { printf("Lexical Error: Unrecognized token %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}