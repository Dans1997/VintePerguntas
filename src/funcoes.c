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

/*
*  Função que limpa a janela do terminal.
*  Melhora experiência de impressão dos menus do jogo ao rodar o programa.
*/
void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

/*
*  Função que cria um novo nó na árvore.
*/
tree* newNode(char* pergunta, int valor){

    tree* newNode = (tree*) malloc((sizeof(tree)));
    newNode->pergunta = pergunta;
    newNode->valor = valor;
    newNode->nao = NULL;
    newNode->sim = NULL;
    return newNode;
}

/*
*  Função que deleta recursivamente uma árvore ou sub árvore.
*/
void deleteTree(tree *del){

    if(del != NULL){
      deleteTree(del->nao);
      deleteTree(del->sim);
      free(del);
    }
}

/*
*  Função que salva uma árvore ou sub árvore em um arquivo .txt.
*/
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

/*
*  Função que carrega uma árvore ou sub árvore de um arquivo .txt.
*  POSICAO_SCAN testa a posição achada no txt com a
   posição que está sendo procurada na iteração atual
*  Se a posição sendo procurada é achada
   no arquivo, pega-se a pergunta dessa mesma linha
   e cria-se um novo nó com esses valores.
*  Depois, chama-se a função com o próximo ponteiro da esquerda.
*  O ponteiro da direita só é chamado quando a posição sendo
   procurada não existe no arquivo. Tal escolha é decidida pela
   variável LADO.
*/
tree* loadTree(tree **save, tree **anterior, FILE *fp, int posicao, int lado){

    int posicao_scan;
    char *aux, *numero, *pergunta;

    rewind(fp);

    numero = (char*) malloc(4*(sizeof(char)));
    pergunta = (char*) malloc(51*(sizeof(char)));
    aux = (char*) malloc(2*(sizeof(char)));

    while(!feof(fp)){

        fscanf(fp, "%4[^.].", numero);

        posicao_scan = atoi(numero);

        if(posicao_scan == posicao){

            fscanf(fp, "%50[^\n]\n", pergunta);

            *save = newNode(pergunta, posicao);

            loadTree(&(*save)->sim, save, fp, (((*save)->valor)*2), 1);

        } else {
            fscanf(fp, "%50[^\n]\n", aux);
        }
    }

    if(lado == 1) {
        loadTree(&(*anterior)->nao, anterior, fp, ((((*anterior)->valor)*2) + 1) , 0);
    }

    free(aux);
    free(numero);
    return *anterior;

}d
