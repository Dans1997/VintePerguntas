/*
 * Autor: Danillo Neves Souza
 */

 #include <stdio.h>

typedef struct node {
     int valor;
     char *pergunta;
     struct node *sim;   /* Nó da Esquerda */
     struct node *nao;   /* Nó da Direita */
 } tree;

void clearScreen();

tree* newNode(char* pergunta, int valor);

