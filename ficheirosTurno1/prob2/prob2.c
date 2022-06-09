#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_VERTICES 5

float mediaDeArestasPorVertice(grafo *g)
{ 
    if(g==NULL || g->tamanho==0)
        return -1.0;

 int arestas=0; 

    for(int i=0; i<g->tamanho; i++)
        arestas=arestas+g->adjacencias[i].tamanho;

    
    return (float)arestas/g->tamanho;
}

grafo *complementar(grafo *g)
{
    if(g==NULL || g->tamanho==0)
     return NULL;

grafo *comp=grafo_novo(g->tamanho,DIGRAFO);
if(comp==NULL)
 return NULL;  

lista_no *curr;

for(int i=0,FLAG=0; i<g->tamanho; i++){
    for(int j=0; j<g->tamanho;j++){
        if(j==i)
         continue;

        if(g->adjacencias[i].tamanho!=0){
        curr=g->adjacencias[i].inicio;
        while(curr!=NULL){
            if(curr->vertice==j){
                FLAG=1;
                break;}
       
            curr=curr->proximo;}
        
        if(FLAG==1){
            FLAG=0;
            continue;}}

       grafo_adiciona(comp,i,j);}}


    return comp;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    grafo *gf = grafo_novo(N_VERTICES, DIGRAFO);
    grafo *comp;

    grafo_adiciona(gf, 0, 4);
    grafo_adiciona(gf, 0, 1);
    grafo_adiciona(gf, 1, 3);
    grafo_adiciona(gf, 3, 4);
    grafo_adiciona(gf, 3, 1);
    grafo_adiciona(gf, 3, 0);
    grafo_adiciona(gf, 4, 3);
    grafo_adiciona(gf, 4, 0);

    printf("Grafo original para teste:\n");
    grafo_imprime(gf);

    // Pergunta 2.1
    printf("\n\nAlinea 2.1\n");
    printf("Media de arestas por vertice: %.2f\n", mediaDeArestasPorVertice(gf));


    // Pergunta 2.2
    printf("\n\nAlinea 2.2\n");
    printf("Grafo complementar:\n");

    comp = complementar(gf);

    if (comp == NULL)
        printf("NULL\n\n");
    else
        grafo_imprime(comp);

    grafo_apaga(gf);
    grafo_apaga(comp);

    return 0;
}
