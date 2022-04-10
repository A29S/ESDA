#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
/**
 *  \brief cria um novo armazem vazio
 *  \param comprimento valor maximo do comprimento da fila de pilhas de contentores
 *  \param altura valor maximo da altura das pilhas de contentores
 *  \return apontador para o armazem ou NULL se erro na alocacao de memoria
 *  \remark a fila de contentores devera ser criada nesta altura, 
 *          ainda que inicialmente fique vazia.
 */
armazem* armazem_novo(int comprimento, int altura)
{

 armazem *novo=(armazem*)malloc(sizeof(armazem));
 if (novo==NULL)
    return NULL;

novo->altura=altura;
novo->comprimento=comprimento;

novo->contentores=fila_nova();
if (novo->contentores==NULL){
	free(novo);
	return NULL;}

	return novo;
}

/* alinea c) */
/**
 *  \brief verifica se o armazem esta' vazio
 *  \param armz apontador para o armazem
 *  \return 1 se armazem vazio; 0 se contem contentores
 */
int armazem_vazio(armazem *armz)
{

 if (armz==NULL)
	return 1;

 if (armz->contentores->tamanho==0)
	return 1;


return 0;
}

/* alinea d) */
/**
 *  \brief verifica se o armazem pode receber mais contentores
 *  \param armz apontador para o armazem
 *  \return 1 se armazem nao pode receber mais contentores; 0 se pode
 *  \remark para um armazem estar cheio, tanto a fila de contentores como a 
 *          ultima pilha da fila devem estar na sua ocupacao maxima
 *          (comprimento da fila e altura da ultima pilha).
 */
int armazem_cheio(armazem *armz)
{
	if (armz==NULL)
		return 0;

	if(fila_tamanho(armz->contentores)==armz->comprimento && fila_back(armz->contentores)->tamanho==armz->altura)
		return 1;


	return 0;
}

/* alinea e) */
/**
 *  \brief empilha contentor no armazem
 *  \param armz apontador para o armazem
 *  \param contr apontador para o contentor
 *  \return 1 se contentor foi descarregado; 0 se armazem cheio
 *  \remark contentor e' carregado na primeira pilha; quando a pilha
 *    esta' completa comeca a empilhar noutra;
 */
int armazenar_contentor(armazem *armz, contentor *contr)
{
if (armz==NULL||contr==NULL)
	return 0;

//esta cheio
if (armazem_cheio(armz)==1)
	return 0;


pilha *aux=pilha_nova();

//esta vazio adicionar pilha no inicio
if (armazem_vazio(armz)==1){
	pilha_push(aux,contr);
	fila_push(armz->contentores,aux);
	return 1;}
// não tá vazio ir ao último elemento da fila e a pilha estiver cheia adicionar nova pilha á fila  
if(fila_back(armz->contentores)->tamanho==armz->altura){
	pilha_push(aux,contr);
	fila_push(armz->contentores,aux);
	return 1;}
 
 //ultima pilha não ta cheia adicionar ai
 pilha_push(fila_back(armz->contentores),contr);	


  return 1;
}

/* alinea f) */
/**
 *  \brief retira um contentor do armazem para o navio
 *  \param armz apontador para o armazem
 *  \return apontador para o contentor retirado ou NULL se armazem vazio
 *  \remark contentor e' retirado da pilha mais proxima do navio
 */
contentor *expedir_contentor(armazem *armz)
{
	if (armz==NULL)
		return NULL;
	
	if (armazem_vazio(armz)==1)
		return NULL;
	

	contentor *aux=contentor_novo(pilha_top(fila_front(armz->contentores))->destino,pilha_top(fila_front(armz->contentores))->valor);
	if(aux==NULL)
		return NULL;

	//tirar da pilha 
	pilha_pop(fila_front(armz->contentores));
	
	//se a pilha ficar vazia puxar a proxima pilha pra cabeça da fila (FIFO)
	if (fila_front(armz->contentores)->tamanho==0)
		fila_pop(armz->contentores);

	
	
	return aux;
}
