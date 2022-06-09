#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_VERTICES 5

int numeroDeArestas(grafo *g, int verticeId)
{
	if(g==NULL|| verticeId<0 || verticeId>=g->tamanho)
		return -1;

 int n_arestas=g->adjacencias[verticeId].tamanho;

lista_no *curr;

for(int i=0; i<g->tamanho; i++){
	if(g->adjacencias[i].tamanho!=0 && i!=verticeId){
		curr=g->adjacencias[i].inicio;
		while(curr!=NULL){
			if(curr->vertice==verticeId){
				n_arestas++;
				break;}

			curr=curr->proximo;}}}

return n_arestas;}


grafo *uniao(grafo *g1, grafo *g2)
{

	if(!g1 || !g2)
		return NULL;

	grafo *g;

	if(g1->tamanho==g2->tamanho)
		g=grafo_novo((g1->tamanho), DIGRAFO);

	else 
	    g=grafo_novo((g1->tamanho+g2->tamanho), DIGRAFO);

	
	if(!g)
	 return NULL;			

lista_no *curr,*aux;

	//adicionar g1...
	for(int i=0;i<g1->tamanho;i++){
		if(g1->adjacencias[i].tamanho!=0){
			curr=g1->adjacencias[i].inicio;
			while(curr!=NULL){
				grafo_adiciona(g,i,curr->vertice);	
			curr=curr->proximo;}}}

	//adicionar g2...
	for(int i=0;i<g2->tamanho;i++){
		if(g2->adjacencias[i].tamanho!=0){
			curr=g2->adjacencias[i].inicio;
			while(curr!=NULL){
            grafo_adiciona(g,i,curr->vertice);	
			curr=curr->proximo;}}}



	return g;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	grafo *g1 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *g2 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *g3 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *gproposto = NULL;

	// Grafo gf (uniao de g1 e g2)
	grafo_adiciona(g3, 0, 4);
	grafo_adiciona(g3, 0, 1);
	grafo_adiciona(g3, 1, 3);
	grafo_adiciona(g3, 3, 4);
	grafo_adiciona(g3, 3, 1);
	grafo_adiciona(g3, 3, 0);
	grafo_adiciona(g3, 4, 3);
	grafo_adiciona(g3, 4, 0);

	// Grafo 1
	grafo_adiciona(g1, 3, 0);
	grafo_adiciona(g1, 3, 1);
	grafo_adiciona(g1, 4, 0);
	grafo_adiciona(g1, 4, 3);

	// Grafo 2
	grafo_adiciona(g2, 0, 4);
	grafo_adiciona(g2, 0, 1);
	grafo_adiciona(g2, 1, 3);
	grafo_adiciona(g2, 3, 4);
	

	
	printf("Grafo 3:\n");
	grafo_imprime(g3);

	// Pergunta 2.1
	printf("\n\nAlinea 2.1\n");
	printf("Numero de arestas do no 3: %d\n", numeroDeArestas(g3, 3));
	printf("Numero de arestas do no 2: %d\n", numeroDeArestas(g3, 2));
	printf("Numero de arestas do no 4: %d\n", numeroDeArestas(g3, 4));

	
	// Pergunta 2.2
	printf("\n\n\nAlinea 2.2\n");
	printf("==========================\n");
	printf("Grafo 1:\n");
	grafo_imprime(g1);
	printf("==========================\n");
	printf("Grafo 2:\n");
	grafo_imprime(g2);
	printf("==========================\n");
	printf("Grafo UNIAO:\n");
	gproposto = uniao(g1, g2);
	if (gproposto == NULL)
	  printf("NULL\n");
	else
	  grafo_imprime(gproposto);
	printf("==========================\n");

	grafo_apaga(g1);
	grafo_apaga(g2);
	grafo_apaga(g3);
	grafo_apaga(gproposto);

	return 0;
}
