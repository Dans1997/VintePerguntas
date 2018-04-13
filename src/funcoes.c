/*
 * Autor: Danillo Neves Souza
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>

 typedef struct node {
      int valor;
      char *pergunta;
      struct node *sim;   /* Nó da Esquerda */
      struct node *nao;   /* Nó da Direita */
  } tree;

void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

tree* newNode(char* pergunta, int valor){

    tree* newNode = (tree*) malloc((sizeof(tree)));
    newNode->pergunta = pergunta;
    newNode->valor = valor;
    newNode->nao = NULL;
    newNode->sim = NULL;
    return newNode;
}
