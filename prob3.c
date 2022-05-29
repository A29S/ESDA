#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "avl.h"


//a lista de amigos funciona do seguinte modo: só contem os amigos não o usuario...
//											   conforme se vai adicionando amigos o ultimo amigo adicionado é colocado na cabeça na lista e não no fim...
//											   o usuario é encontrado no vetor de adjacencias fazendo g->adjacencias[usuario]	

/*** problema 3 ***/
arvore_avl* sugestao_amizade(grafo *g, int u)
{
	if(g==NULL||u<0||u>=g->tamanho)
		return NULL;


int tam=0, *vec, pos;


arvore_avl *recom=avl_nova();		
if(recom==NULL)
	return NULL;

//debug
/*for(lista_no *t=g->adjacencias[u].inicio; t!=NULL;t=t->proximo)
	printf("%d\n",t->vertice);*/

lista_no *curr=g->adjacencias[u].inicio, *aux;

while(curr!=NULL){
	
vec=grafo_adjacentes(g,curr->vertice,&tam);

for(int i=0,FLAG=0; i<tam;i++){
	if(vec[i]==u)
		continue;

	
	aux=g->adjacencias[u].inicio;

	while (aux!=NULL){
		if(aux->vertice==vec[i]){
			FLAG=1;
			break;}
		aux=aux->proximo;}


	if(FLAG==1){
		FLAG=0;
		continue;}

	if(avl_pesquisa(recom,vec[i])!=NULL)
		continue;

	avl_insere(recom,vec[i]);}


curr=curr->proximo;}


	return recom;
}


/********************************************************************/
/********************************************************************/
grafo* init_rede()
{
	grafo* g = grafo_novo(10,NAODIRECIONADO);
	if (!g)
		return NULL;
	grafo_adiciona(g,1,2);
	grafo_adiciona(g,1,3);
	grafo_adiciona(g,2,3);
	grafo_adiciona(g,2,4);
	grafo_adiciona(g,2,5);
	grafo_adiciona(g,3,5);
	grafo_adiciona(g,3,6);
	grafo_adiciona(g,3,7);
	grafo_adiciona(g,7,6);
	return g;
}

	
int main ()
{
	puts("* Problema 3 *");

	grafo *rede = init_rede();
	arvore_avl *sugestoes =NULL;
	
	sugestoes = sugestao_amizade(rede,2);
	if (sugestoes==NULL)
		printf("\nUtilizador '2' ou rede nao existe\n");
	else{
		printf("\nSugestoes de amizade para '2': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	sugestoes = sugestao_amizade(rede,12);
	if (sugestoes==NULL)
		printf("\nUtilizador '12' ou rede nao existe\n");
	else{
		printf("\nSugestoes de amizade para '9': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	grafo_apaga(rede);
	return 1;
}
