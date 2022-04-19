#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
int contar_apelidos(fila *f)
{
	
	/*** Responder ao 2.1 aqui ***/
	if (f==NULL)
		return -1;

	if(fila_vazia(f)==1)
		return 0;

	int count=0;
	filaItem *aux;
	aux=f->cabeca;

	while(aux!=NULL){
		if(strstr(aux->string," ")!=NULL)
			count++;
		
		aux=aux->proximo;}
	
//outra forma que me lembrei, mas requer mais trabalho do que a outra...	
	
	/*int count=0;
	fila *aux=fila_nova();
	filaItem *curr;
	curr=f->cabeca;

	while(curr!=NULL){
		fila_push(aux,curr->string);
		curr=curr->proximo;} 

	while(fila_vazia(aux)!=1){
	 if(strstr(aux->cabeca->string," ")!=NULL)
		count++;
		fila_pop(aux);}
		
		//apagar a fila aux no final*/

	
	return count;
}

/*** problema 2.2 ***/

lista *lista_a_j(fila *f)
{
	/*** Responder ao 2.2 aqui ***/
	if (f==NULL)
		return NULL;

 lista *nova=lista_nova();
 if (nova==NULL)
	return NULL;

filaItem *curr;
curr=f->cabeca;

while(curr!=NULL){
	if(curr->string[0]<='J' && curr->string[0]>='A'){
		if(lista_insere(nova,curr->string,NULL)==NULL)
			return NULL;}

	curr=curr->proximo;}

return nova;

}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	fila *fila1 = fila_nova();

	lista *nomes_A_J;
	l_elemento *ptr;

	/* preenche a fila 1 */
	if (fila_push(fila1, "Maria") == -1)
		return -1;
	if (fila_push(fila1, "João Teixeira") == -1)
		return -1;
	if (fila_push(fila1, "Júlia Costa") == -1)
		return -1;
	if (fila_push(fila1, "Henrique") == -1)
		return -1;
	if (fila_push(fila1, "Afonso Costa") == -1)
		return -1;
	if (fila_push(fila1, "Nuno Antunes") == -1)
		return -1;

	/* início do teste de prob2.1 */

	printf("Número de pessoas com apelido: %d\n", contar_apelidos(fila1));

	/* fim do teste de prob2.1 */

	/* início do teste de prob2.2 */

	nomes_A_J = lista_a_j(fila1);
	if (nomes_A_J != NULL)
	{

		ptr = nomes_A_J->inicio;

		while (ptr)
		{
			printf("%s\n", ptr->str);
			ptr = ptr->proximo;
		}
	}

	/* fim do teste de prob2.2 */

	lista_apaga(nomes_A_J);

	fila_apaga(fila1);

	return 0;
}
