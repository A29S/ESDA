/*****************************************************************/
/*      Conversao Base Numerica | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#include "conversor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h"

int dec2bin(pilha *p, int n)
{
  /* ALINEA a) */

    if(p==NULL)
      return 0;


    while (n!=0){
        
        pilha_push(p,n%2);
        n=n/2;
    }


return 1;}

int bin2dec(pilha *p)
{
  /* ALINEA b) */
if (p==NULL)
return -1;

int aux=0;

   while(p->tamanho!=0){
    aux=aux+pow(2,p->tamanho-1)*pilha_top(p);
    pilha_pop(p);}



  return aux;
}

int get_dec(void)
{
  int input;

  printf("Introduza o número decimal: ");
  scanf("%d", &input);

  return input;
}

int get_bin(pilha *p)
{
  if (p == NULL)
    return 0;  

  int input, lsb;

  printf("Introduza o número binário: ");
  scanf("%d", &input);

  while (input != 0)
  {
    lsb = input % 10;

    if (!((lsb == 0) || (lsb == 1)))
      return 0;

    pilha_push(p, lsb);
    input = input / 10;
  }

  return 1;
}

void print_bin(pilha *p)
{
  if (p == NULL)
    return;

  if (pilha_vazia(p))
  {
    printf("Representação binária em 1 bit: 0\n");
    return;
  }

  printf("Representação binária em %d bits: ", pilha_tamanho(p));
  
  while (!pilha_vazia(p))
  {
    printf("%d ", pilha_top(p));
    pilha_pop(p);
  }

  printf("\n");
}

void print_dec(pilha *p)
{
  if (p == NULL)
    return;

  printf("Representação decimal: %d\n", bin2dec(p));
}
