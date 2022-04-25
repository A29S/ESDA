#include <stdio.h>
#include "bst.h"
#include "avl.h"

int main()
{
  // ALINEA a)

  arvore_bst *bst = bst_nova();
  if(bst==NULL)
    return -1;

bst_insere(bst, "G");
bst_insere(bst, "C");
bst_insere(bst, "A");
bst_insere(bst, "F");
bst_insere(bst, "L");
bst_insere(bst, "J");
bst_insere(bst, "V");
bst_insere(bst, "M");
bst_insere(bst, "N");
bst_insere(bst, "O");


  

  // ALINEA b)
   printf("A altura da arvore é: %d\n",bst_altura(bst->raiz));
 
  // ALINEA c)
    bst_imprime(bst);  


  // ALINEA e)
    arvore_avl *avl =avl_nova();
    if(avl==NULL)
        return -1;
  
avl_insere(avl, "G");
avl_insere(avl, "C");
avl_insere(avl, "A");
avl_insere(avl, "F");
avl_insere(avl, "L");
avl_insere(avl, "J");
avl_insere(avl, "V");
avl_insere(avl, "M");
avl_insere(avl, "N");
avl_insere(avl, "O");

avl_imprime(avl);
  // ALINEA f)
printf("%d\n",avl_altura(avl->raiz));
 
  //representação arvore avl

 /*            G
        C              N       
     A     F       L       V
                 J   M   O         */
  // ALINEA g)

  avl_remove(avl,"N");
  
  avl_imprime(avl);

//Não é necessário fazer rotação-->isto é estranho a arvore original não esta balanceada sendo right heavy, retirando o N o O passa pra essa posição e arvore mantem-se rigth heavy
//não esta balanceada porém mantem se right heavy será por isto que não é necessário trocar??\\ 

//é assim a arvore em geral é right heavy a sub-arvore esquerda ta balanceada e a direita esta inicialmente balanceada ,tirar o L faz o O subsitui lo e a sub arvore direita fica left heavy
//não sei o porque de não rodar mas não há rotações...

  // ALINEA h)

avl_remove(avl,"V");

avl_imprime(avl);

//aqui não tirar o V torna a sub-arvore direita em (0-2=-2-->left) logo faz-se um rotação á direita na sub arvore direita pra compensar e fica 2-1=-1 right heavy
  return 0;
}
