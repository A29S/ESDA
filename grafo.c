/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2018/19    */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;
    
    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(n, sizeof(int));
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
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(g==NULL || origem<0 || dest<0 || origem>=g->tamanho ||dest>=g->tamanho)
        return -1;

    if(g->tamanho==0)
        return -1;

    //ver se origem==dest
    if(origem==dest)
        return -1;

    //verficar se ja tem ou não
    if(g->adjacencias[origem][dest]==1)
        return 1;

    g->adjacencias[origem][dest]=1;
        return 0;

    }


/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(g==NULL || origem<0 ||origem>=g->tamanho || dest<0 || dest>=g->tamanho)
        return -1;

    if(g->tamanho==0)
        return -1;

    if(origem==dest)
        return 0;

    //verficar se ja tem ou não
    if(g->adjacencias[origem][dest]==1){
        g->adjacencias[origem][dest]=0;
        return 1;}


        return 0;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
     /* alinea 1.1 */
    if(g==NULL||origem<0||dest<0||origem>=g->tamanho||dest>=g->tamanho)
        return -1;

    if(g->tamanho==0)
        return -1;

    if(g->adjacencias[origem][dest]==1)
        return 1;

    return 0;
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    /* alinea 1.2 */
    if(adjacencias==NULL || n_arestas<0|| n_arestas%2!=0)
        return NULL;

    int max=0;
    for(int i=0; i<n_arestas*2;i++){
        if(adjacencias[i]>adjacencias[max])
            max=i;}

    grafo *novo=grafo_novo(adjacencias[max]+1);
    if(novo==NULL)
        return NULL;
    
    for(int i=0; i<n_arestas*2;i+=2){
        grafo_adiciona(novo,adjacencias[i],adjacencias[i+1]); }


    return novo;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    /* alinea 1.3 */
    if(g==NULL||i<0||i>=g->tamanho)
        return NULL;

    if(g->tamanho==0)
        return NULL;

    vetor *aux=vetor_novo();
    if(aux==NULL)
        return NULL;

    for(int j=0; j<g->tamanho; j++){
        if(g->adjacencias[i][j]==1)
            vetor_insere(aux,j,-1);}




    return aux;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
    /* alinea 1.3 */

    if(g==NULL||i<0||i>=g->tamanho)
        return NULL;

    if(g->tamanho==0)
        return NULL;

    vetor *aux=vetor_novo();
    if(aux==NULL)
        return NULL;

    for(int j=0; j<g->tamanho; j++){
        if(g->adjacencias[j][i]==1)
            vetor_insere(aux,j,-1);}




    return aux;}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    /* alinea 1.4 */
    if(g==NULL)
        return -1;

    for(int i=0; i<g->tamanho; i++){
        if(grafo_arestasEntrada(g,i)->tamanho!=g->tamanho-1 || grafo_arestasSaida(g,i)->tamanho!=g->tamanho-1)
            return 0;}

    return 1;
}

/* verifica se o vertice i do grafo g e' uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o vertice for uma celebridade e 0 se nao o for */
int grafo_eCelebridade(grafo* g, int i)
{
    /* alinea 1.5 */ 
    if(g==NULL || i<0 ||i>=g->tamanho)
        return -1;

    if(g->tamanho==0)
        return -1;

    if(grafo_arestasSaida(g,i)->tamanho!=0)
        return 0;

    if(grafo_arestasEntrada(g,i)->tamanho!=g->tamanho-1)
        return 0;

  

    return 1;
}

/* verifica se o grafo g tem pelo menos uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se existir uma celebridade e 0 se nao existir */
int grafo_temCelebridade(grafo* g)
{
    /* alinea 1.5 */ 
    if(g==NULL)
        return -1;

    if(g->tamanho==0)
        return -1;

    for(int j=0; j<g->tamanho; j++){
       if(grafo_eCelebridade(g,j)==1)
            return 1;}


    return 0;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 0; i < g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < g->tamanho; j++)
        {
            if(g->adjacencias[i][j] != 0)
                printf("%d ", j);
        }
        printf("\n");
    }
}

