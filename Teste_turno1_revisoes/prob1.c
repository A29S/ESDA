#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
int *junta_colecoes(int *cromos1, int n1, int *cromos2, int n2, int *tam)
{
	/*** Responder ao 1.1 aqui ***/
if (cromos1==NULL || cromos2==NULL || n1<0||n2<0||tam==NULL)
	return NULL;

if (n2==0 && n1==0)
	return NULL;

int *novo=(int*)malloc(sizeof(int));
if(n1!=0)
novo[0]=cromos1[0];

if (n2!=0 && n1==0)
novo[0]=cromos2[0];

*tam=1;


//add os cromos do primeiro vetor e certificar que não add repetidos
	for(int i=1,Flag=0; i<n1; i++){
		for (int j=0; j<*tam; j++){
			if(novo[j]==cromos1[i]){
				Flag=1;
				break;}}
	
		if(Flag!=1){
		*tam=*tam+1;
		novo=realloc(novo,sizeof(int)*(*tam));
		novo[*tam-1]=cromos1[i];}
		
	if (Flag==1){
		Flag=0;
		continue;}}
	
	
//add os cromos do 2 vetor e certificar que não add repetidos
	for (int i=0,Flag=0; i<n2; i++){
		for (int j=0; j<*tam; j++){
			if(novo[j]==cromos2[i]){
				Flag=1;
				break;}}

		if (Flag==1){
			Flag=0;
			continue;}
		
		if (Flag!=1){
			*tam=*tam+1;
			novo=realloc(novo,sizeof(int)*(*tam));
			novo[*tam-1]=cromos2[i];}}


	return novo;
}

/*** problema 1.2 ***/

void juntar_repetidos(pilha *cromos, int *acrescentar, int ac)
{
	/*** Responder ao 1.2 aqui ***/
	if (cromos==NULL|| acrescentar==NULL || ac<=0)
		return;

	if(pilha_vazia(cromos)==1)
		return;

pilha *aux=pilha_nova();
if(aux==NULL)
	return;

	while (pilha_vazia(cromos)!=1){
		pilha_push(aux,cromos->raiz->elemento);
		pilha_pop(cromos);}

	int i=0;
	short FLAG=0;

	while (i<ac && pilha_vazia(aux)!=1){
		for (int j=0; j<ac; j++){
			//isto só funciona caso dentro do vetor acrescentar não haja cromos repetidos entre si
			if(aux->raiz->elemento==acrescentar[j]){
				pilha_push(cromos,aux->raiz->elemento);
				pilha_push(cromos,acrescentar[j]);
				pilha_pop(aux);
				FLAG=1;
				break;}}
		
		if (FLAG==1){
			FLAG=0;
			continue;}

		if(FLAG!=1){
			pilha_push(cromos,aux->raiz->elemento);
			pilha_pop(aux);}}
	
	
	pilha_apaga(aux);


	return;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	int colecao1[] = {2, 4, 5, 6, 5, 4, 10, 11, 10, 10};
	int colecao2[] = {3, 4, 6, 9, 12};
	int tam1 = 10, tam2 = 5;
	int total = 0;
	int *ve;

	/* inicio teste prob1.1 */
	ve = junta_colecoes(colecao1, tam1, colecao2, tam2, &total);
	if (ve)
	{
		if (total == 9)
			printf("\nNúmero de cromos na nova coleção: 9 (Certo)\n");
		else
			printf("\nNúmero de cromos na nova coleção : %d (errado, tem que dar 9)\n", total);
		printf("Lista da nova coleção: [");
		for (int i = 0; i < (total - 1); i++)
			printf("%d,", ve[i]);
		printf("%d]\n", ve[total - 1]);
		free(ve);
	}
	else
		printf("\njunta_colecoes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	pilha *cro = pilha_nova();
	if (cro == NULL)
	{
		printf("\nSem espaço de memoria\n");
		return 0;
	}

	pilha_push(cro, 24);
	pilha_push(cro, 5);
	pilha_push(cro, 35);
	pilha_push(cro, 11);
	pilha_push(cro, 6);
	pilha_push(cro, 2);
	int repetidos[] = {5, 34, 24};
	int nr = 3;
	pilhaItem *item;

	juntar_repetidos(cro, repetidos, nr);

	if (pilha_tamanho(cro) == 8)
	{
		item = cro->raiz->proximo->proximo->proximo->proximo;
		if (item->elemento != 5 || item->proximo->elemento != 5)
		{
			printf("\nO cromo numero 5 não foi inserido no local correto\n");
		}
		else
		{
			item = item->proximo->proximo;
			if (item->elemento != 24 || item->proximo->elemento != 24)
			{
				printf("\nO cromo numero 24 não foi inserido no local correto\n");
			}
			else
			{
				printf("\nOs cromos foram inseridos nos locais corretos\n");
			}
		}
	}
	else
		printf("\npilha com tamanho errado (tamanho: %d; esperado: 8)\n", pilha_tamanho(cro));
	printf("Cromos: [");
	item = cro->raiz;
	for (int i = 0; i < pilha_tamanho(cro) - 1; i++)
	{
		printf("%d,", item->elemento);
		item = item->proximo;
	}
	printf("%d]\n", item->elemento);
	pilha_apaga(cro);
	/* fim teste prob1.2 */

	return 0;
}
