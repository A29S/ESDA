#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "grafo.h"


/*** problema 1.1 ***/
char* avl_maiorstring(no_avl *no)
{
	/* complexidade do algoritmo: ________________ */
	if(no==NULL)
		return "\0";

char *right, *left;



left=avl_maiorstring(no->esquerda);
right=avl_maiorstring(no->direita);

if(strlen(right)>strlen(left) && strlen(right)>strlen(no->str))
	return right;

if(strlen(left)>strlen(right) && strlen(left)>strlen(no->str))
	return left;

	return no->str;
}

/*** problema 1.2 ***/
int grafo_maisdistante(grafo *g, int origem, int *distancia)
{
	if(g==NULL||origem<0||origem>=g->tamanho||distancia==NULL)
		return -1;

*distancia=0;

int update=0, maior=-1; 

lista_no *curr=g->adjacencias[origem].inicio, *aux;

for(int i=0; i<g->tamanho; i++){
	if(i==origem)
		continue;

	grafo_bfs(g,origem,i,&update);

	if(update>*distancia){
		maior=i;
		*distancia=update-1;}}


	return maior;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *str;

	/* teste problema 1.1 */
	{
		arvore_avl *arv;
		puts("* Problema 1.1 *");
		arv = avl_nova();
		while(fgets(str_aux,MAX_STR,fp) != NULL)
		{
			if(str_aux[strlen(str_aux)-1] == '\n')
				str_aux[strlen(str_aux)-1] = '\0';
			avl_insere(arv, str_aux);
		}
		str = avl_maiorstring(arv->raiz);
		printf("Maior string: ");
		if(str != NULL)
		 	puts(str);
		else
			puts("(null)");
		avl_apaga(arv);
	}

	/* teste problema 1.2 */
	{
		grafo *g;
		int vertice, comprimento;
		puts("\n* Problema 1.2 *");
		g = grafo_novo(8, DIGRAFO);
		grafo_adiciona(g,0,4);
		grafo_adiciona(g,1,0);
		grafo_adiciona(g,1,5);
		grafo_adiciona(g,2,1);
		grafo_adiciona(g,3,2);
		grafo_adiciona(g,4,3);
		grafo_adiciona(g,5,4);
		grafo_adiciona(g,6,3);
		grafo_adiciona(g,7,2);
		grafo_adiciona(g,7,6);

		vertice = grafo_maisdistante(g, 1, &comprimento);
		if(vertice != -1)
			printf("Mais distante do vertice 1: %d (distancia %d)\n", vertice, comprimento);
		vertice = grafo_maisdistante(g, 6, &comprimento);
		if(vertice != -1)
			printf("Mais distante do vertice 6: %d (distancia %d)\n", vertice, comprimento);

		grafo_apaga(g);
	}

	fclose(fp);
	return 0;
}
