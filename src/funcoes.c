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
tree* deleteTree(tree *del){

    if(del != NULL){
      deleteTree(del->nao);
      deleteTree(del->sim);
      free(del);
    }
    return NULL;
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

}

/*
*  Função que cria uma árvore do zero ou edita uma árvore existente,
   desde que o ponteiro raiz dessa árvore seja passada corretamente.
*/
tree* createGame(tree **atual, tree **anterior, int altura, int *deleted_position, FILE *fp){

    int resposta;
    char *pergunta;

    pergunta = (char*) malloc(51*sizeof(char));

    do{
        clearScreen();
        printf("\n**********************************\n");
        printf("PERGUNTA ATUAL: %s\n", (*atual)->pergunta);
        printf("\n MENU DO JOGO\n");
        printf("\n 1: Essa pergunta/resposta nao faz sentido! (REMOVER E VOLTAR PRO INICIO DA ARVORE)");
        printf("\n 2: Positivo ");
        printf("\n 3: Negativo ");
        printf("\n 4: Parar o jogo \n");
        printf("**********************************\n");
        printf("Selecione uma das alternativas: \n");
        scanf("%d", &resposta);
        getchar();
    }while(resposta != 1 && resposta != 2 && resposta != 3 && resposta != 4 && resposta != 5);

    switch(resposta){
        case 1:

            deleted_position[0] = (*atual)->valor;

            if((*atual)->valor % 2 == 0)
              (*anterior)->sim = NULL;
            else  (*anterior)->nao = NULL;

            *atual = deleteTree(*atual);
            break;
        case 2:
            if(altura == 20){
                printf("\nVoce nao pode criar mais perguntas!\n");
            }

            if((*atual)->sim == NULL){
                printf("\nDigite a nova pergunta (sim): \n");
                fgets(pergunta, 50, stdin);
                strtok(pergunta, "\n");
                (*atual)->sim = newNode(pergunta, ((*atual)->valor) * 2);
            }

            createGame(&(*atual)->sim, &(*atual), altura++, deleted_position, fp);
            break;
        case 3:
            if(altura == 20){
                printf("\nVoce nao pode criar mais perguntas!\n");
            }

            if((*atual)->nao == NULL){
                printf("\nDigite a nova pergunta (nao): \n");
                fgets(pergunta, 50, stdin);
                strtok(pergunta, "\n");
                (*atual)->nao = newNode(pergunta, (((*atual)->valor * 2) + 1));
            }

            createGame(&(*atual)->nao, &(*atual), altura++, deleted_position, fp);
            break;
        case 4:
            printf("\n%d\n", (*atual)->valor);
  	        printf("%s\n", (*atual)->pergunta);
            fp = fopen("savedTree.txt","w");
            if (fp == NULL) {
                printf("\n  Erro ao abrir o arquivo! Desligando...\n");
                exit(-55);
            }
            saveTree(*atual, (fp));
            fclose(fp);
            deleted_position[0] = 0;
            break;
    }

    if((*atual) != NULL){
        fp = fopen("savedTree.txt","w");
        if (fp == NULL) {
            printf("\n  Erro ao abrir o arquivo! Desligando...\n");
            exit(-55);
        }
        saveTree(*atual, fp);
    }

if (fp != NULL)
  fclose(fp);

return *anterior;
}

/*
*  Função simplificada de createGame();
*  Nessa função. não existe a opção de criar mais perguntas.
*  Passado o ponteiro correto, é possível apenas jogar o jogo.
*/
void playGame(tree **atual, int altura){

    int aux;

    do{
      printf("**********************************");
      printf("\nPERGUNTA ATUAL: %s\n", (*atual)->pergunta);
      printf("\n1: Sim ");
      printf("\n2: Nao ");
      printf("\n3: Sair");
      printf("\nSelecione uma das alternativas: \n");
      printf("**********************************\n");
      scanf("%d", &aux);
    }while(aux != 1 && aux != 2 && aux != 3);

    switch(aux){
        case 1:
          if( ((*atual)->sim == NULL && (*atual)->nao == NULL) || altura == 20){
            printf("\nAha! Ganhei!\n");
            printf("O que deseja fazer agora?\n");
            return;
          }
          if((*atual)->sim != NULL){
            playGame(&(*atual)->sim, altura++);
          } else {
            printf("\n A pergunta seguinte (sim) nao existe. \n");
            playGame(&(*atual), altura);
          }

          break;

        case 2:
          if( ((*atual)->sim == NULL && (*atual)->nao == NULL) || altura == 20){
            printf("\nAh, fala serio... Perdi!\n");
            printf("O que deseja fazer agora?\n");
            return;
          }
          if((*atual)->nao != NULL){
            playGame(&(*atual)->nao, altura++);
          } else {
            printf("\n A pergunta seguinte (nao) nao existe. \n");
            playGame(&(*atual), altura);
          }
          break;

        case 3:
          break;
    }
}

/*
*  Função do menu principal do jogo.
* Caso 1: Criar um jogo. Chama a função createGame();
* Caso 2: Carregar um jogo. Chama a função loadGame();
* Caso 3: Sair do jogo. Fecha o programa.
* Há sempre a opção de salvar a árvore antes de sair e
  de jogar o jogo carregado ou criado logo após tais eventos.
*/
tree* chooseMenu(tree *load, int *selecao){

    int inicio;
    int aux;

    do{
        clearScreen();
        printf("**********************************");
        printf("\n MENU PRINCIPAL\n");
        printf("\n 1: Criar um jogo");
        printf("\n 2: Carregar um jogo ");
        printf("\n 3: Sair \n");
        printf("**********************************\n");
        printf("Selecione uma das alternativas: \n");
        scanf("%d", &inicio);
        getchar();
    }while(inicio != 1 && inicio != 2 && inicio != 3);

    char *txt, *pergunta, *numero;

    tree *write_tree;

    txt = (char*) malloc(16*sizeof(char));
    numero = (char*) malloc(4*(sizeof(char)));
    pergunta = (char*) malloc(51*(sizeof(char)));

    int *deleted_position = (int*) malloc(sizeof(int));

    FILE *fp = NULL;

    switch(inicio){
        case 1:
            if(load != NULL){
                do{
                  printf("**********************************");
                  printf("\nEncontramos um jogo carregado. \nDeseja edita-lo?");
                  printf("\n1: Sim ");
                  printf("\n2: Nao \n");
                  printf("Selecione uma das alternativas: \n");
                  scanf("%d", &aux);
                }while(aux != 1 && aux!= 2);
            }

            if(aux == 1) {
              deleted_position[0] == 0;
              load = createGame(&load, &load, 1, deleted_position, fp);
            } else {
              printf("\nEntao digite a primeira pergunta: \n");
              fgets(txt, 15, stdin);
              strtok(txt, "\n");

              load = newNode(txt,1);

              deleted_position[0] == 0;

              load = createGame(&load, &load, 1, deleted_position, fp);

              while(deleted_position[0] != 0){
                /* Entra aqui caso o usuário tenha deletado alguma pergunta */
                printf("\nDELETED POSITION: %d\n", deleted_position[0]);
                deleted_position[0] == 0;
                printf("\nComeço da árvore!");
                load = createGame(&load, &load, 1, deleted_position, fp);
              }

              free(deleted_position);
            }

            do{
              printf("**********************************");
              printf("\nDeseja jogar agora?");
              printf("\n1: Sim ");
              printf("\n2: Nao \n");
              printf("Selecione uma das alternativas: \n");
              scanf("%d", &aux);
            }while(aux != 1 && aux!= 2);

            if(aux == 1){
              clearScreen();
              printf("\nENTRANDO EM MODO DE JOGO!");
              printf("\nNeste modo, nada pode ser editado!");
              printf("\nPara editar, selecione a alternativa <1> no MENU PRINCIPAL\n");
              playGame(&load, 1);
            }

            printf("\n**********************************");
            printf("\nSALVANDO SEU JOGO...\n");
            printf("**********************************\n");

            fp = fopen("savedTree.txt","w");
            if (fp == NULL) {
                printf("\n  Erro ao abrir o arquivo! Desligando...\n");
                exit(-55);
            }
            if(load != NULL){
              saveTree(load, fp);
            } else {
              printf("\nA arvore nao existe!\n");
            }

            free(pergunta);
            free(numero);
            fclose(fp);
            selecao[0] = 1;
            return load;
            break;

        case 2:
            printf("\nDigite o nome do arquivo: \n");
            fgets(txt, 15, stdin);
            strtok(txt, "\n");

            fp = fopen(txt, "r");

            if(fp == NULL){
                printf("\nErro ao ler o arquivo! Desligando... \n");
                exit(-55);
            } else {
                printf("\nArquivo encontrado! Processando seu pedido... \n");
            }

            fscanf(fp, "%4[^.].", numero);

            fscanf(fp, "%50[^\n]\n", pergunta);

            load = newNode(pergunta,1);

            load = loadTree(&load->sim, &load, fp, 2 , 1);

            printf("\nArvore carregada com sucesso! \n");

            do{
              printf("**********************************");
              printf("\nDeseja jogar agora?");
              printf("\n1: Sim ");
              printf("\n2: Nao \n");
              printf("Selecione uma das alternativas: \n");
              scanf("%d", &aux);
            }while(aux != 1 && aux!= 2);

            if(aux == 1){
              clearScreen();
              printf("\nENTRANDO EM MODO DE JOGO!");
              printf("\nNeste modo, nada pode ser editado!");
              printf("\nPara editar, selecione a alternativa <1> no MENU PRINCIPAL.\n");
              playGame(&load, 1);
            }

            printf("\n**********************************");
            printf("\nSALVANDO SEU JOGO...\n");
            printf("**********************************\n");

	          fp = fopen("savedTree.txt","w");
            if (fp == NULL) {
                printf("\n  Erro ao abrir o arquivo! Desligando...\n");
                exit(-55);
            }
            if(load != NULL){
              saveTree(load, fp);
            } else {
              printf("\nA arvore nao existe!\n");
            }

            free(txt);
            free(pergunta);
            free(numero);
            fclose(fp);
            selecao[0] = 2;
            return load;
            break;

        case 3:
          if(fp != NULL)
            fclose(fp);
          free(pergunta);
          free(numero);
          free(txt);
          selecao[0] = 3;
          return load;
          break;
    }

    free(txt);
    free(pergunta);
    free(numero);
    if(fp != NULL)
      fclose(fp);
}
