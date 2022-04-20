/*****************************************************************/
/*      Conversao Base Numerica | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#ifndef DECBIN_H
#include "pilha.h"

// /**
//  *  \brief converte decimal para binario
//  *  \param p apontador para a pilha
//  *  \param n inteiro (decimal) a converter (binário)
//  *	 \return 1, se converteu com sucesso. 0, caso contrario
//  */
int dec2bin(pilha *p, int n);

// /**
//  *  \brief converte binario para decimal
//  *  \param p apontador para a pilha
//  *	 \return numero (em decimal), se converteu com sucesso. 0, caso contrario
//  */
int bin2dec(pilha *p);

// /**
//  *  \brief captura numero decimal
//  *	 \return numero decimal
//  */
int get_dec(void);

// /**
//  *  \brief captura numero binario e armazena na pilha
//  *  \param p apontador para a pilha
//  *	 \return 1 em caso de sucesso. 0, caso contrario. 
//  */
int get_bin(pilha *p);

// /**
//  *  \brief imprime a representacao binaria do numero na pilha
//  *  \param p apontador para a pilha
//  */
void print_bin(pilha *p);

// /**
//  *  \brief imprime a representacao decimal do numero na pilha
//  *  \param p apontador para a pilha
//  */
void print_dec(pilha *p);

#define DECBIN_H
#endif
