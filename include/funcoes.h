/*
 * Autor: Danillo Neves Souza
 */

 #include <stdio.h>

/*
* Cabeçalhos das funções.
*/

typedef struct node {
     int valor;
     char *pergunta;
     struct node *sim;   /* Nó da Esquerda */
     struct node *nao;   /* Nó da Direita */
 } tree;

void clearScreen();

tree* newNode(char* pergunta, int valor);

tree* deleteTree(tree *del);

void saveTree(tree *save, FILE *fp);

tree* loadTree(tree **save, tree **anterior, FILE *fp, int posicao, int lado);

//void createGame(tree **atual, tree **anterior, int altura);

tree* createGame(tree **atual, tree **anterior, int altura, int *deleted_position, FILE *fp);

void playGame(tree **atual, int altura);

tree* chooseMenu(tree *load, int *selecao);
