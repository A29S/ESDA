#include <stdio.h>
#include <math.h>
#include "pilha.h"
#include "conversor.h"

/* Para compilar: gcc -g -Wall bin2dec.c conversor.c pilha.c -o bin2dec */

int main()
{
  pilha *p = pilha_nova();

  if (get_bin(p))
    print_dec(p);

  pilha_apaga(p);

  return 0;
}
