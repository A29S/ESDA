#include "grafo.h"
#include <stdio.h>

int main()
{

	//ex 1.1

	grafo *aux=grafo_novo(4);

	grafo_adiciona(aux,0,1);
	grafo_adiciona(aux,0,2);
	grafo_adiciona(aux,0,3);
	grafo_adiciona(aux,1,2);
	grafo_adiciona(aux,1,3);
	grafo_adiciona(aux,1,0);
	grafo_adiciona(aux,2,1);
	grafo_adiciona(aux,2,3);
	grafo_adiciona(aux,2,0);
	grafo_adiciona(aux,3,1);
	grafo_adiciona(aux,3,2);
	grafo_adiciona(aux,3,0);
	
	grafo_imprime(aux);

	grafo_remove(aux,0,2);
	grafo_remove(aux,0,3);
	grafo_remove(aux,1,3);
	

	printf("\n");
	grafo_imprime(aux);

	printf("\nA aresta 0-1 tem valor:%d\n", grafo_aresta(aux,0,1));
	printf("A aresta 0-3 tem valor:%d\n\n", grafo_aresta(aux,0,3));

	grafo_apaga(aux);

	/* exemplo da alinea 1.2 */
	int adj[] = {1,2,1,3,1,4,2,5,3,5,4,5};
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
	//grafo_apaga(g12);

	/* outros testes */

	printf("\n");

	vetor *vec=grafo_arestasSaida(g12,1);

	printf("Arestas Saida NÓ 1:");
	for(int i=0; i<vec->tamanho;i++)
		printf("%d ",vec->elementos[i]);
	
	printf("\n");

	 vec=grafo_arestasEntrada(g12,5);

	printf("Arestas Entrada NÓ 5:");
	for(int i=0; i<vec->tamanho;i++)
		printf("%d ",vec->elementos[i]);
	
	printf("\n");

	grafo_apaga(g12);

	//teste 1.4	
	
	grafo *g14=grafo_novo(3);

	grafo_adiciona(g14,0,1);		
	grafo_adiciona(g14,0,2);
	grafo_adiciona(g14,1,0);		
	grafo_adiciona(g14,1,2);
	grafo_adiciona(g14,2,0);		
	grafo_adiciona(g14,2,1);	

	if(grafo_completo(g14)==1)
		printf("\nÈ um grafo completo\n\n");

	else 
		printf("\nNão é ou parametros invalidos\n\n");
	
	grafo_apaga(g14);
	
	//teste da 1.5 

	grafo *g15=grafo_novo(5);
	if(g15==NULL)
		return -1;

	grafo_adiciona(g15,0,4);		
	grafo_adiciona(g15,1,4);
	grafo_adiciona(g15,2,4);
	grafo_adiciona(g15,3,4);
	//grafo_adiciona(g15,4,3); -->serve pra testar se não é...

	if(grafo_temCelebridade(g15)==1)
		printf("TEM!\n");

	else 
		printf("Não tem ou valores de entrada invalidos\n");

	grafo_apaga(g15);


	printf("\nFIM\n");

	return 0;
}
