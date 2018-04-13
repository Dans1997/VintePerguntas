/*
 * Autor: Danillo Neves Souza
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>

/*
* Definição do nó da árvore.
*/
 typedef struct node {
      int valor;          /* Posição da pergunta na árvore */
      char *pergunta;     /* Pergunta do nó */
      struct node *sim;   /* Sim -> Esquerda */
      struct node *nao;   /* Não -> Direita */
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

void deleteTree(tree *del){

    if(del != NULL){
      deleteTree(del->nao);
      deleteTree(del->sim);
      free(del);
    }
}

void saveTree(tree *save, FILE *fp){

    char *aux;

    if (save == NULL) {
        printf("\nA arvore nao existe!\n");
        exit(-56);
    }

    aux = (char*) malloc(4*(sizeof(char)));
    sprintf( aux, "%d", save->valor );    /* Converte a posição do nó para ASC */

    fprintf(fp, "%s", aux);
    fprintf(fp, "%c", '.');   /* Separador da pergunta e da posição */
    fprintf(fp, "%s", save->pergunta);
    fprintf(fp, "%c", '\n'); /* Nova linha é o separados entre nós */

    if(save->sim != NULL){
        saveTree(save->sim, fp);
    }

    if(save->nao != NULL){
        saveTree(save->nao, fp);
    }

    free(aux);
}
