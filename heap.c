/*****************************************************************/
/*   Fila de prioridade / min-heap | ESDA | L.EEC | 2021/22     */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

int menor_que(elemento * e1, elemento * e2);

int pesquisa_aresta_heap(heap *h, aresta_grafo *aresta);


heap* heap_nova(int capacidade)
{
    heap * h = (heap *) malloc(sizeof(heap));

    if (!h)
        return NULL;

    h->tamanho = 0;
    h->capacidade = capacidade;
    h->elementos = (elemento **) calloc(capacidade+1, sizeof(elemento *));


    if (!h->elementos) {
        free(h);
        return NULL;
    }
    for (int i=0;i<=capacidade;i++)
h->elementos[i]=NULL;
    return h;
}

void heap_apaga(heap *h)
{
    int i;

    if(!h)
        return;

    /* apaga todos os elementos e respetivas strings */
    for(i=RAIZ; i<=h->tamanho; i++)
    {
    //    free(h->elementos[i]->no);
        free(h->elementos[i]);
        h->elementos[i]=NULL;
    }

    free(h->elementos);
    free(h);
}


elemento * elemento_novo(double prioridade, no_grafo * no, aresta_grafo *aresta)
{
	if(!no && !aresta)
	return NULL;   

	elemento * elem = (elemento *) malloc(sizeof(elemento));

    if (!elem)
        return NULL;


    elem->no=no;
    elem->aresta=aresta;
    elem->prioridade = prioridade;

    return elem;
}


int heap_insere(heap * h,  no_grafo* no,aresta_grafo *aresta, double prioridade)
{
    elemento * aux=NULL, * elem;
    int i=0;

    /* se heap esta' cheia, nao insere elemento */
    if (h->tamanho >= h->capacidade)
        return 0;

    elem = elemento_novo(prioridade,no, aresta);
    if (!elem)
        return 0;

    /* coloca elemento no fim da heap */
    h->tamanho++;
    i = h->tamanho;
    h->elementos[i] = elem;

     /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
    while (i != RAIZ && menor_que(h->elementos[i], h->elementos[PAI(i)]))
    {
        aux = h->elementos[PAI(i)];
        h->elementos[PAI(i)] = h->elementos[i];
        h->elementos[i] = aux;
        i = PAI(i);
    }
    return 1;
}

no_grafo * heap_remove(heap * h)
{
    int i, filho_maior;
    elemento * aux;
    no_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->no;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


aresta_grafo * heap_remove_aresta(heap * h)
{
    int i, filho_maior;
    elemento * aux;
   aresta_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->aresta;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


int menor_que(elemento * e1, elemento * e2)
{
    if (e1 == NULL || e2 == NULL)
    {
        return 0; 
    }

    return e1->prioridade < e2->prioridade;
}

heap *heap_carrega(grafo *g, int capacidade)
{
    if(g==NULL || capacidade<=0)
        return NULL;

    if(g->tamanho==0)
        return NULL;
                                                                    //min heap-->a raiz é a que tem prioridade menor
heap *nova=heap_nova(capacidade);
if(nova==NULL)
    return NULL;       

int aux;
for(int i=0; i<g->tamanho; i++){
    for(int j=0; j<g->nos[i]->tamanho && g->nos[i]->tamanho!=0; j++){

        if((aux=pesquisa_aresta_heap(nova,g->nos[i]->arestas[j]))==1)
            continue;

        if(aux==-1){
            heap_apaga(nova);
            return NULL;}


        if(heap_insere(nova,NULL,g->nos[i]->arestas[j], g->nos[i]->arestas[j]->inspecao)==0){
            heap_apaga(nova);
            return NULL;}}}    


   return nova;
}

aresta_grafo **inspecao_trocos (heap *h, int dias, int *n)
{
    if(h==NULL||dias<=0||n==NULL)
        return NULL;

    if(h->tamanho==0)
        return NULL;

    aresta_grafo **aux=NULL;
    *n=0;
    int round;
    

    while(h->tamanho!=0){

        //ver se arredondo ou não
       round=h->elementos[1]->aresta->distancia/10000;

        if(h->elementos[1]->aresta->distancia%10000!=0)
            round+=1;

        //se o valor da raiz da heap for superior ao nº de dias não fazer nada 
        if(round>dias)
            break;
        
        dias=dias-round;

        //fazer alguma coisa....
        if(*n==0){
            *n+=1;

            aux=(aresta_grafo**)malloc(sizeof(aresta_grafo*));
            if(aux==NULL){
                *n=0;
                return NULL;}

           if((aux[0]=heap_remove_aresta(h))==NULL){
               free(aux);
               *n=0;
               return NULL;}
                
            continue;}

            //n!=0
            *n+=1;

            aux=(aresta_grafo**)realloc(aux,sizeof(aresta_grafo*)*(*n));

            //não deve retornar NULL,porem.....
            if((aux[*n-1]=heap_remove_aresta(h))==NULL){
                free(aux);
                *n=0;
                return NULL;}        
      
            }


  return aux;}


//pesquisar se a aresta ja existe na heap
int pesquisa_aresta_heap(heap *h, aresta_grafo *aresta){
    if(h==NULL || aresta==NULL)
        return -1;

    for(int i=1; i<=h->tamanho; i++){
        if(strcmp(aresta->codigo, h->elementos[i]->aresta->codigo)==0)
            return 1;}

    return 0;}


