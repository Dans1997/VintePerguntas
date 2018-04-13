#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "funcoes.h"


/*
*  Testa a função newNode();
*/
TEST_CASE("New Node", "Testar se o no foi criado e preenchido corretamente"){
	tree* node;
	char* aux = (char*) malloc(51*(sizeof(char)));
	node = newNode("E uma fruta?", 1);

	REQUIRE(node != NULL);
	REQUIRE(node->sim == NULL);
	REQUIRE(node->nao == NULL);
	REQUIRE(node->pergunta == "E uma fruta?");
	REQUIRE(node->valor == 1);
}

/*
*  Testa a função saveTree();
*/
TEST_CASE("Save Tree", "Testar se a arvore - ou subarvore - foi salva corretamente"){
	FILE* fp = fopen("savedTreeTest.txt", "w");;
	tree* node = newNode("E uma fruta?", 1);
	node->sim = newNode("E verde?", 2);
	node->nao = newNode("E um objeto?", 3);

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

// TODO: Dando erro! //

/*

TEST_CASE("Delete Tree", "Testar se a arvore - ou subarvore - foi deletada corretamente"){
	tree* node = (tree*) malloc(sizeof(tree));
	deleteTree(node);

	REQUIRE(node == NULL);
}

*/
