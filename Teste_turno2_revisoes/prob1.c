#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
int* troca(int * cromos1, int n1, int * cromos2, int n2, int *tam)
{
	/***  Responder ao problema 1.1 aqui  ***/
	if(cromos1==NULL||cromos2==NULL||n1<=0||n2<0||tam==NULL)
		return NULL;


int *v=(int*)malloc(sizeof(int));
if(v==NULL)
	return NULL;
*tam=0;

//add cromos repetidos do vetor cromos1
for (int i=0,Flag=0; i<n1; i++){
	for(int j=0; j<n1; j++){
		if(cromos1[i]==cromos1[j] && i!=j){
			if(*tam==0){
				*tam=*tam+1;
				v[0]=cromos1[i];
				break;}

			for(int s=0; s<*tam; s++){
				if(v[s]==cromos1[i])
					Flag=1;}
			
			if(Flag==1){
				Flag=0;
				break;}

			*tam=*tam+1;
			v=(int*)realloc(v,sizeof(int)*(*tam));
			v[*tam-1]=cromos1[i];
			break;}}}

//verificar se nenhum desses cromos tão no vetor cromos2
for(int i=0; i<n2; i++){
	for(int j=0; j<*tam; j++){
		if (v[j]==cromos2[i]){
			for(int aux=j+1; aux<*tam;aux++)
				v[aux-1]=v[aux];
				*tam=*tam-1;
				v=(int*)realloc(v,sizeof(int)*(*tam));}}}


	return v;
}

/*** problema 1.2 ***/

void retirar_cromos(pilha *cromos, int *retirar, int nr)

{
		/***  Responder ao problema 1.2 aqui  ***/
		if (cromos==NULL||retirar==NULL||nr<=0)
			return;
	
pilha *aux=pilha_nova();
if(aux==NULL)
	return;
	

	for(int i=0; i<nr; i++){
		
		while(pilha_vazia(cromos)!=1){	
			if(cromos->raiz->elemento!=retirar[i])
				pilha_push(aux, cromos->raiz->elemento);

				pilha_pop(cromos);}

		while(pilha_vazia(aux)!=1){
			pilha_push(cromos,aux->raiz->elemento);
			pilha_pop(aux);}}
			
pilha_apaga(aux);

return;}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/


int main()
{
	
	/* testes */
	int colecao1[] = {2,4,5,6,5,4,10,11,10,10};
	int colecao2[] = {3,4,6,9,12};
	int tam1=10,tam2=5;
	int total=0;
	int *ve;

	/* inicio teste prob1.1 */
	ve = troca(colecao1, tam1, colecao2, tam2, &total);
	if(ve) { 
		if (total==4) printf("\nNúmero de cromos trocados: 4 (Certo)\n");
		else printf("\nNúmero de cromos trocados errado : (tamanho: %d; esperado: 4)\n",total);
		printf("Cromos trocados: [");
		for (int i=0;i<(total-1);i++)
		printf("%d,",ve[i]);
		printf("%d]\n",ve[total-1]);
		free(ve);
		
	} else
		printf("\ntroca retornou NULL\n"); 
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	pilha *cro=pilha_nova();
	if (cro == NULL)
		{  	printf("\nSem espaço de memoria\n");
			return 0;}

	pilha_push(cro,24);
	pilha_push(cro,5);
	pilha_push(cro,35);
	pilha_push(cro,25);
	pilha_push(cro,34);
	pilha_push(cro,11);
	pilha_push(cro,6);
	pilha_push(cro,5);
	pilha_push(cro,2);
	int repetidos[] = {5,34,25};
	int nr=3;
	pilhaItem *item;
	int erro1=0,erro2=0,erro3=0, errototal=0;
	
	retirar_cromos(cro, repetidos, nr);
	
		item=cro->raiz;
		while (item) {
			if (item->elemento==5)
			erro1=1;
			if (item->elemento==34)
			erro2=1;
			if (item->elemento==25)
			erro3=1;
			item=item->proximo;
		}
		if (erro1==1) {
				printf("\nO cromo numero 5 não foi retirado da pilha\n");
				errototal++;

		} 
		if (erro2==1) {
				printf("\nO cromo numero 34 não foi retirado da pilha\n");
				errototal++;

		} 
		if (erro3==1) {
				printf("\nO cromo numero 25 não foi retirado da pilha\n");
				errototal++;

		} 

	if(pilha_tamanho(cro)==5)
	{
	
		if (errototal==0) {
				printf("\nOs cromos foram todos retirados corretamente\n"); 
		}
				
	}
	else
		printf("\npilha com tamanho errado (tamanho: %d; esperado: 5)\n",pilha_tamanho(cro));
		printf("Cromos: [");
		item=cro->raiz;
		for (int i=0;i<pilha_tamanho(cro)-1;i++) {
		printf("%d,",item->elemento);
		item=item->proximo;
		}
		printf("%d]\n",item->elemento);
		pilha_apaga(cro);
	/* fim teste prob1.2 */


	return 0;
}
