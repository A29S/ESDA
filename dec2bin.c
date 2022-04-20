#include <stdio.h>
#include "pilha.h"
#include "conversor.h"

/* Para compilar: gcc -g -Wall dec2bin.c conversor.c pilha.c -o dec2bin */

int main()
{
  pilha *p = pilha_nova();

  if (dec2bin(p, get_dec()))
    print_bin(p);

  pilha_apaga(p);

  return 0;
}
