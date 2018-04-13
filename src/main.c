/*
 * Autor: Danillo Neves Souza
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <funcoes.h>

/*
*  Função main.
* Chama o menu até que o usuário queira sair do jogo (caso 3).
*/
int main(){

    tree *raiz = NULL;
    int *selecao = (int*) malloc(sizeof(int));

    while(1){
        raiz = chooseMenu(raiz, selecao);
        if(selecao[0] == 3){
          free(selecao);
          if(raiz != NULL)
            deleteTree(raiz);
          return 0;
        }
    }
}
