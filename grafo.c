/*****************************************************************/
/*   Grafo c/ lista de adjacencias | ESDA | LEEC | 2021/22       */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria no da lista de adjacencias */
lista_no* cria_no(int v)
{
    lista_no* novo = (lista_no*)malloc(sizeof(lista_no));
    if(!novo)
        return NULL;

    novo->vertice = v;
    novo->proximo = NULL;

    return novo;
}

/* cria grafo com n vertices */
grafo* grafo_novo(int n, tipo_grafo tipo)
{
    grafo* g = (grafo*)malloc(sizeof(grafo));
    if(g == NULL)
        return NULL;

    g->tamanho = n;
    g->tipo = tipo;

    /* cria array de listas de adjacencias */
    g->adjacencias = (lista_adj*)calloc(n, sizeof(lista_adj));
    if(g->adjacencias == NULL)
    {
        free(g);
        return NULL;
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
        {
            while (g->adjacencias[v].inicio)
            {
                lista_no* aux = g->adjacencias[v].inicio;
                g->adjacencias[v].inicio = g->adjacencias[v].inicio->proximo;
                free(aux);
            }
        }
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona uma aresta ao grafo*/
void grafo_adiciona(grafo *g, int origem, int dest)
{
    lista_no* novo;

    if (g == NULL || grafo_aresta(g, origem, dest))
        return;

    /* adiciona uma aresta de origem para dest na lista de adjacencias */
    novo = cria_no(dest);
    novo->proximo = g->adjacencias[origem].inicio;
    g->adjacencias[origem].inicio = novo;
    g->adjacencias[origem].tamanho++;

    if(g->tipo == NAODIRECIONADO)
    {
        /* adiciona tambem aresta de dest para origem */
        novo = cria_no(origem);
        novo->proximo = g->adjacencias[dest].inicio;
        g->adjacencias[dest].inicio = novo;
        g->adjacencias[dest].tamanho++;
    }
}

/* remove uma aresta do grafo*/
void grafo_remove(grafo *g, int origem, int dest)
{
    lista_no *aux, *prev;

    if (g == NULL || g->adjacencias[origem].inicio == NULL)
        return;

    aux = g->adjacencias[origem].inicio;
    /* caso especial: primeiro no' da lista */
    if(aux->vertice == dest)
    {
        g->adjacencias[origem].inicio = aux->proximo;
        free(aux);
    }
    else
    {
        prev = aux;
        aux = aux->proximo;
        while(aux != NULL)
        {
            if(aux->vertice == dest)
            {
                prev->proximo = aux->proximo;
                free(aux);
                break;
            }
            prev = aux;
            aux = aux->proximo;
        }
    }

    if(g->tipo == NAODIRECIONADO)
    {
        /* remove tambem aresta de dest para origem */
        /* caso especial: primeiro no' da lista */
        aux = g->adjacencias[dest].inicio;
        if(aux->vertice == origem)
        {
            g->adjacencias[dest].inicio = aux->proximo;
            free(aux);
        }
        else
        {
            prev = aux;
            aux = aux->proximo;
            while(aux != NULL)
            {
                if(aux->vertice == origem)
                {
                    prev->proximo = aux->proximo;
                    free(aux);
                    break;
                }
                prev = aux;
                aux = aux->proximo;
            }
        }
    }

}

/* verifica se existe uma aresta entre os vertices origem e dest */
int grafo_aresta(grafo *g, int origem, int dest)
{
    if (g == NULL)
        return 0;

    lista_no* aux = g->adjacencias[origem].inicio;
    while (aux)
    {
        if(aux->vertice == dest)
            return 1;
        aux = aux->proximo;
    }
    return 0;
}

/* imprime as listas de adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i;
    for (i = 0; i < g->tamanho; i++)
    {
        lista_no* aux = g->adjacencias[i].inicio;
        printf("%d: ", i);
        if(aux)
        {
            printf("%d", aux->vertice);
            aux = aux->proximo;

            while (aux)
            {
                printf("->%d", aux->vertice);
                aux = aux->proximo;
            }
        }
        printf("\n");
    }
}

int* grafo_adjacentes(grafo *g, int v, int* n)
{
	if (g==NULL)
		return NULL;
	if (v>=g->tamanho)
		return NULL;

	lista_adj vertice_adjs = g->adjacencias[v];

	*n = vertice_adjs.tamanho;
	int *res = (int*) malloc(vertice_adjs.tamanho * sizeof(int));
	int i=0;
	lista_no *adj1 = vertice_adjs.inicio;
	while(adj1!=NULL) {
		res[i]=adj1->vertice;
		adj1 = adj1->proximo;
		i++;
	}
	return res;

}
