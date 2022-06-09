#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "heap.h"

int compara_bsts(no_bst *noA, no_bst *noB)
{
    if(noA==NULL || noB==NULL)
        return -1;

int cmp=1,right=1,left=1;

    if(strcmp(noA->str,noB->str)!=0)
        cmp=0;

right=compara_bsts(noA->direita,noB->direita);
left=compara_bsts(noB->esquerda,noB->esquerda);

if(right==0 || cmp==0 || left==0)
    return 0;

return 1;}


int altera_valor(heap *h, char *valor_original, char *valor_novo)
{
    if(h==NULL || valor_original==NULL || valor_novo==NULL)
        return -1;

    
    int curr=-1;

    //procurar o elemento na heap
    for(int i=1; i<=h->tamanho; i++){
        if(strcmp(h->elementos[i]->valor,valor_original)==0){
            //atualizar o valor do elemento
                h->elementos[i]->valor=(char*)realloc(h->elementos[i]->valor,sizeof(char)*(strlen(valor_novo)+1));
                strcpy(h->elementos[i]->valor,valor_novo);
                curr=i;
                h->elementos[i]->prioridade=valor_novo[0];
                break;}}

    if(curr==-1)
        return -1;


    //fazer update da posição na heap
    elemento *tmp;
      while (curr!=1 && h->elementos[curr]->prioridade<h->elementos[curr/2]->prioridade){
        
        tmp=h->elementos[curr];
        h->elementos[curr]=h->elementos[curr/2];
        curr=curr/2;
        h->elementos[curr]=tmp;}
      

    return 0;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    // Pergunta 1.1
    printf("Alinea 1.1\n");
    arvore_bst *bst1 = bst_nova();
    arvore_bst *bst2 = bst_nova();
    arvore_bst *bst3 = bst_nova();

    char strs[6][2] = {"D", "B", "C", "E", "A", "F"};
    for (int i = 0; i < 6; i++)
    {
        bst_insere(bst1, strs[i]);
        bst_insere(bst2, strs[i]);
    }

    if (compara_bsts(bst1->raiz, bst2->raiz) == 1)
    {
        printf("bst1 e bst2 sao iguais (OK)\n");
    }
    else
        printf("bst1 e bst2 nao sao iguais (ERRO)\n");

    char novas_strs[6][2] = {"D", "B", "C", "F", "A", "E"};
    for (int i = 0; i < 6; i++)
    {
        bst_insere(bst3, novas_strs[i]);
    }
    if (compara_bsts(bst1->raiz, bst3->raiz) == 1)
    {
        printf("bst1 e bst3 sao iguais (ERRO)\n");
    }
    else
        printf("bst1 e bst3 nao sao iguais (OK)\n");

    bst_apaga(bst1);
    bst_apaga(bst2);
    bst_apaga(bst3);

    // Pergunta 1.2
    printf("\n\nAlinea 1.2\n");
    heap *h = heap_nova(6);
    for (int i = 0; i < 6; i++)
        heap_insere(h, strs[i], strs[i][0]);

    printf("Heap original\n");
    heap_imprime(h, 1);

    altera_valor(h, "C", "Cc");
    altera_valor(h, "F", "PROG2");
    altera_valor(h, "X", "-");
    printf("\n\n\nHeap apos alteracoes\n");
    heap_imprime(h, 1);

    heap_apaga(h);
}