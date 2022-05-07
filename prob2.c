                                            //Aplicação de um grafo não dirigido atraves de listas\\                       

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                            //ATENÇÂO!!!\\
//Isto não é bem o problema 2.. pois o enunciado dizia pra alterar as funções do grafo implementado atraves de vetores pra um grafo não dirigido... eu decidi fazer
//o grafo não dirigido recorrendo a listas ligadas...
//Só fiz as funções que se encontram na pergunta 1.1 mais as de criação de grafo e impressão.. falta tambem a de apagar o grafo...


//estruturas
typedef struct elemento{

    int valor;
    struct elemento *proximo;

}l_elemento;


typedef struct lista{
    
 int l_tamanho;
 l_elemento *origem;
       

}lista;


typedef struct grafo{
    
    int g_tamanho;
    lista **no;

}grafo;



//funções relacionadas com as estruturas


//funções das listas
lista* lista_nova(){

lista *nova=malloc(sizeof(lista));
if(nova==NULL)
  return NULL;
     
nova->l_tamanho=0;
nova->origem=NULL;

return nova;}

int lista_adiciona(lista *l, int val){

    if (l==NULL || val<0)
        return -1;


if(l->l_tamanho==0){
    l->l_tamanho++;
   
    l->origem=malloc(sizeof(l_elemento));
    l->origem->valor=val;
    l->origem->proximo=NULL;

    return 1;}

l_elemento *curr;
curr=l->origem;

while(curr->proximo!=NULL){
    if(curr->valor==val)
        return 0;
    curr=curr->proximo;}

if(curr->valor==val)
    return 0;

curr->proximo=malloc(sizeof(l_elemento));
curr->proximo->proximo=NULL;

curr->proximo->valor=val;

l->l_tamanho++;

return 1;}

int lista_remove (lista *l, int dest){
     
    if(l==NULL||dest<0)
        return -1;

    if(l->l_tamanho==0)
        return -1;

l_elemento *curr, *prox;
curr=l->origem;
prox=curr->proximo;

while(prox!=NULL){
    if(prox->valor==dest){
        curr->proximo=prox->proximo;
        free(prox);
        return 1;}

curr=curr->proximo;
prox=prox->proximo;}

return 0;
}

int lista_procura(lista *l, int dest){
    if(l==NULL || dest<0)
        return -1;

l_elemento *curr;
curr=l->origem;

while(curr!=NULL){
    if(curr->valor==dest)
        return 1;
    curr=curr->proximo;}

return 0;}

//funções dos grafos
grafo *grafo_novo(int n_vertices){

grafo *novo=malloc(sizeof(grafo));
if(novo==NULL)
    return NULL;

novo->g_tamanho=n_vertices;

novo->no=malloc(sizeof(lista*)*n_vertices);
for(int i=0; i<novo->g_tamanho; i++){
    novo->no[i]=lista_nova();
    lista_adiciona(novo->no[i],i);}


return novo;}

int grafo_adiciona(grafo *g, int orig, int dest){
    if(g==NULL||dest<0||orig<0||dest==orig||dest>=g->g_tamanho||orig>=g->g_tamanho)
        return -1;


//origem
for(int i=0; i<g->g_tamanho; i++){
    if(g->no[i]->origem->valor==orig){
        lista_adiciona(g->no[i],dest);
        break;}}

//destino
for(int i=0; i<g->g_tamanho; i++){
    if(g->no[i]->origem->valor==dest){
       lista_adiciona(g->no[i],orig);
        return 1;}}

return 0;}

int grafo_remove(grafo *g, int orig, int dest){
    if(g==NULL||orig<0||dest<0 || orig==dest)
        return -1;

    for(int i=0; i<g->g_tamanho;i++){
        if(g->no[i]->origem->valor==orig){
            lista_remove(g->no[i],dest);
            for(int j=0; j<g->g_tamanho; j++){
                if(g->no[j]->origem->valor==dest){
                    lista_remove(g->no[j],orig);
                    return 1;}}}}

    return 0;}

int verifica_aresta(grafo *g, int orig, int dest){
    if(g==NULL||orig<0||dest<0)
        return -1;

    for(int i=0; i<g->g_tamanho; i++){
        if(g->no[i]->origem->valor==orig){
            if(lista_procura(g->no[i],dest)==1)
                return 1;
            else return 0;}}   

return -1;}

void imprime (grafo *g){

l_elemento *curr;

for(int i=0; i<g->g_tamanho;i++){
    
    curr=g->no[i]->origem->proximo;
    printf("%d: ", i);
    while(curr!=NULL){
        printf("%d ", curr->valor);    
        curr=curr->proximo;}
    printf("\n");}

return;
}



int main (int argc, char **argv){
    
    if(argc>1)
        exit(-1);

grafo *g11=grafo_novo(3);
if(!g11){
  perror("Não criou o grafo\n");
  exit(-1);}


grafo_adiciona(g11,0,1);
grafo_adiciona(g11,1,2);
grafo_adiciona(g11,0,2);

imprime(g11);

grafo_remove(g11,0,1);
grafo_remove(g11,1,2);

printf("\n");
imprime(g11);

if(verifica_aresta(g11,0,1)==1)
    printf("\nEstão conectados os 2 nós\n");

else
    printf("\nNão estão conectados os nós\n");


printf("\nFIM\n");
return 0;}
