#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "heap.h"

//apenas para ver como se calcula a altura da arvore...(Já é fornecido na biblioteca)...
int bst_h (no_bst *no){

if(no==NULL)
    return -1;

int left=0,right=0;    

right=1+bst_h(no->direita);
left=1+bst_h(no->esquerda);

if(right>left)   
    return right;

 return left;}


//contar a quantidade de nos ate ao "no"(incluindo este)
int bst_quantidade(no_bst *no){
if(no==NULL)
      return 0;

    int right=0,left=0;

right=bst_quantidade(no->direita);
left=bst_quantidade(no->esquerda);



return (1+right+left);}



int bst_cheia(no_bst *no)
{
if(no==NULL)                                           
    return -1;                                 /*                   A 
                                                                B       C  -->arvore cheia...
                                                              D   E   F   G */


//arvores cheia numero par de nos excluindo a raiz...
int right=0, left=0;

//contar o numero de nos na subarvore direita...
right=bst_quantidade(no->direita);

//contar o numero de nos na subarvore esquerda...
left=bst_quantidade(no->esquerda);

//verificar se é par...
if((right+left)%2==0)
    return  1;

return 0;}


int altera_prioridade(heap *h, char *valor, int nova_prioridade)
{
    if(h==NULL||valor==NULL||nova_prioridade<0)
        return -1;

    int aux=-1;

    for(int i=1; i<=h->tamanho;i++){
        if(strcmp(valor,h->elementos[i]->valor)==0){
            h->elementos[i]->prioridade=nova_prioridade;
            aux=i;
            break;}}

    if(aux==-1)
        return -1;

    elemento *tmp;

    while (aux!=1 && h->elementos[aux]->prioridade<h->elementos[aux/2]->prioridade){
            tmp=h->elementos[aux];
            h->elementos[aux]=h->elementos[aux/2];
            aux=aux/2;
            h->elementos[aux]=tmp;}
   

return 0;}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    // Pergunta 1.1
    printf("Alinea 1.1\n");
    arvore_bst *bst1 = bst_nova();
    arvore_bst *bst2 = bst_nova();

    char strs[5][2] = {"D", "B", "C", "F", "A"};
    for (int i = 0; i < 5; i++)
        bst_insere(bst1, strs[i]);

    if (bst_cheia(bst1->raiz) == 1)
        printf("bst1 e' uma arvore cheia (OK)\n");
    else
        printf("bst1 nao e' uma arvore cheia (ERRO)\n");

    char novas_strs[6][2] = {"D", "B", "C", "E", "A", "F"};
    for (int i = 0; i < 6; i++)
        bst_insere(bst2, novas_strs[i]);

    if (bst_cheia(bst2->raiz) == 1)
        printf("bst2 e' uma arvore cheia (ERRO)\n");
    else
        printf("bst2 nao e' uma arvore cheia (OK)\n");

    bst_apaga(bst1);
    bst_apaga(bst2);

    // Pergunta 1.2
    printf("\n\nAlinea 1.2\n");
    heap *h = heap_nova(6);
    for (int i = 0; i < 6; i++)
        heap_insere(h, novas_strs[i], novas_strs[i][0]);

    printf("Heap original\n");
    heap_imprime(h, 1);

    altera_prioridade(h, "C", 60);
    altera_prioridade(h, "D", 75);
    altera_prioridade(h, "X", 0);
    printf("\n\n\nHeap apos alteracoes\n");
    heap_imprime(h, 1);

    heap_apaga(h);
}