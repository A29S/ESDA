#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
void trocar(fila *f, int pos1, int pos2)
{
	/*** Responder ao problema 2.1 aqui ***/
	if(f==NULL||pos1<0||pos2<0)
		return;

	if(pos2>=fila_tamanho(f)||pos1>=fila_tamanho(f)){
		printf("A pessoa na posição %d não trocou com a pessoa na posição %d\n",pos1,pos2);
		return;}


filaItem *aux, *curr, *troca;

aux=curr=f->cabeca;


	for(int i=0,Flag; i<fila_tamanho(f); i++){
		if (i==pos1){
			
			for(int j=0; j<fila_tamanho(f);j++){
				if (j==pos2){
					troca=curr;
					curr=aux;
					aux=troca;
					Flag=1;
					break;}
			curr=curr->proximo;
			}}	

		if(Flag==1)
			break;		

	aux=aux->proximo;}


	printf("A pessoa na posição %d trocou com a pessoa na posição %d\n",pos1,pos2);


}

/*** problema 2.2 ***/

lista *sublista_apelido(fila *f, const char *apelido)
{
	/*** Responder ao problema 2.2 aqui ***/
	if (f==NULL||apelido==NULL)
		return NULL;

	if (fila_vazia(f)==1)
		return NULL;	
	
lista *nova=lista_nova();
if(nova==NULL)
	return NULL;
filaItem *aux;
aux=f->cabeca;

	while (aux!=NULL){
		if(strstr(aux->string," ")!=NULL && strstr(aux->string,apelido)!=NULL){
		if(lista_insere(nova,aux->string,NULL)==NULL)
			return NULL;}

		aux=aux->proximo;}

	
	return nova;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	fila *fila1 = fila_nova();
	int pos1 = 3, pos2 = 5;

	lista *nomes;
	l_elemento *ptr;

	const char *str = "Costa";

	/* preenche a fila 1 */
	if (fila_push(fila1, "João Teixeira") == -1)
		return -1;
	if (fila_push(fila1, "Júlia Costa") == -1)
		return -1;
	if (fila_push(fila1, "Pedro") == -1)
		return -1;
	if (fila_push(fila1, "Henrique") == -1)
		return -1;
	if (fila_push(fila1, "Paulo") == -1)
		return -1;
	if (fila_push(fila1, "Susana") == -1)
		return -1;
	if (fila_push(fila1, "Teresa Santos") == -1)
		return -1;
	if (fila_push(fila1, "Afonso Costa") == -1)
		return -1;

	/* início do teste de prob2.1 */

	trocar(fila1, 3, 5); // caso em que as posições existem

	trocar(fila1, 3, 15); // caso em que pelo menos uma posição NÃO existe

	/* fim do teste de prob2.1 */

	/* início do teste de prob2.2 */

	nomes = sublista_apelido(fila1, str);

	if (nomes != NULL)
	{
		ptr = nomes->inicio;

		while (ptr)
		{
			printf("%s\n", ptr->str);
			ptr = ptr->proximo;
		}
	}
	/* fim do teste de prob2.2 */

	fila_apaga(fila1);

	lista_apaga(nomes);

	return 0;
}
