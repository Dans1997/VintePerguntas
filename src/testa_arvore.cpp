#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "string.h"
#include "funcoes.h"

TEST_CASE("Create Game", "Testar se a funcao de cria uma arvore corretamente"){
	tree* node;
	FILE *fp;
	char* aux = (char*) malloc(51*(sizeof(char)));
	int *selecao = (int*) malloc(sizeof(int));

	strcpy(aux, "E uma fruta?");
	node = newNode(aux, 1);
	createGame(&node, &node, 1, selecao, fp);

	REQUIRE(node->sim != NULL);
}


/*
*  Testa a função newNode();
*/
TEST_CASE("New Node", "Testar se o no foi criado e preenchido corretamente"){
	tree* node;
	char* aux = (char*) malloc(51*(sizeof(char)));
	strcpy(aux, "E uma fruta?");
	node = newNode(aux, 1);

	REQUIRE(node != NULL);
	REQUIRE(node->sim == NULL);
	REQUIRE(node->nao == NULL);
	REQUIRE(node->valor == 1);
}

/*
*  Testa a função saveTree();
*/
TEST_CASE("Save Tree", "Testar se a arvore - ou subarvore - foi salva corretamente"){
	FILE* fp = fopen("savedTreeTest.txt", "w");;
	char* aux = (char*) malloc(51*(sizeof(char)));
	strcpy(aux, "E uma fruta?");
	tree* node = newNode(aux, 1);
	strcpy(aux, "E verde?");
	node->sim = newNode(aux, 2);
	strcpy(aux, "E um objeto?");
	node->nao = newNode(aux, 3);

	saveTree(node, fp);

	REQUIRE(node != NULL);
	REQUIRE(fp != NULL);
}

/*
*  Testa a função loadTree();
*/
TEST_CASE("Load Tree", "Testar se a arvore - ou subarvore - foi carregada corretamente"){
	printf("\nCASO DE TESTE LOAD\n");
	printf("**********************************\n");

	FILE* fp;
	tree* node;

	char *txt, *pergunta, *numero;
	txt = (char*) malloc(16*sizeof(char));
	numero = (char*) malloc(4*(sizeof(char)));
	pergunta = (char*) malloc(51*(sizeof(char)));

	printf("\nDigite o nome do arquivo: \n");
	fgets(txt, 15, stdin);
	strtok(txt, "\n");

	fp = fopen(txt, "r");
	fscanf(fp, "%4[^.].", numero);
	fscanf(fp, "%50[^\n]\n", pergunta);

	node = newNode(pergunta,1);

	node = loadTree(&(node->sim), &node, fp, 2, 1);

	REQUIRE(node->sim != NULL);
	REQUIRE(fp != NULL);
}

/*
*  Testa a função playGame();
*/
TEST_CASE("Play Game", "Testar se a funcao percorre a arvore corretamente"){
	printf("\nCASO DE TESTE PLAY GAME\n");
	printf("**********************************\n");

	char* aux = (char*) malloc(51*(sizeof(char)));
	strcpy(aux, "E uma fruta?");
	tree* node = newNode(aux, 1);
	strcpy(aux, "E verde?");
	node->sim = newNode(aux, 2);
	strcpy(aux, "E um objeto?");
	node->nao = newNode(aux, 3);
	playGame(&node, 1);

	REQUIRE(node != NULL);
}

/*
*  Testa a função chooseMenu() para o caso 2;
*/

/*
*  Testa a função chooseMenu() para o caso 3;
*/
TEST_CASE("Choose Menu 3", "Testar se o menu sai do jogo corretamente (caso 3)"){
	printf("\nCASO DE TESTE CHOOSE MENU - CASO 3\n");
	printf("**********************************\n");

	FILE *fp = NULL;
	int *selecao = (int*) malloc(sizeof(int));
	selecao[0] = 0;
	tree *caso_tres;
	chooseMenu(caso_tres, selecao);

	REQUIRE(caso_tres == NULL);
	REQUIRE(fp == NULL);
	REQUIRE(selecao[0] == 3);
}

// TODO: Dando erro! //

/*
* Testa a função deleteTree();
*/
TEST_CASE("Delete Tree", "Testar se a arvore - ou subarvore - foi deletada corretamente"){
	tree* node = (tree*) malloc(sizeof(tree));
	node = deleteTree(node);
	REQUIRE(node == NULL);
}
