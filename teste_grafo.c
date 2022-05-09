#include "grafo.h"
#include <stdio.h>

int main()
{

	/* teste da alinea 1.1 */
	printf("\n=== Alinea 1.1 ===\n");

	grafo *g11 = grafo_novo(6);

	// grafo_adiciona
	if (grafo_adiciona(g11, 1, 2) != -1 && grafo_adiciona(g11, 1, 3) != -1 &&
			grafo_adiciona(g11, 1, 4) != -1 && grafo_adiciona(g11, 2, 5) != -1 &&
			grafo_adiciona(g11, 3, 5) != -1 && grafo_adiciona(g11, 4, 5) != -1)
	{
		printf("Teste grafo_adiciona:\n");
		grafo_imprime(g11);
	}

	// grafo_remove
	if (grafo_remove(g11, 2, 5) != -1 && grafo_remove(g11, 3, 5) != -1 && grafo_remove(g11, 4, 5) != -1)
	{
		printf("\nTeste grafo_remove:\n");
		grafo_imprime(g11);
	}

	// grafo_aresta
	int a12 = grafo_aresta(g11, 1, 2);
	if (a12 == 1)
	{
		printf("\nTeste grafo_aresta:\n");
		printf("Aresta (1,2): %d\n", a12);
	}
	
	grafo_apaga(g11);

	/* teste da alinea 1.2 */
	printf("\n=== Alinea 1.2 ===\n");

	int adj[] = {1,2,1,3,1,4,2,5,3,5,4,5};
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
	grafo_apaga(g12);

	/* teste da alinea 1.3 */
	grafo *g = grafo_deLista(adj, 6);

	printf("\n=== Alinea 1.3 ===\n");
	printf("arestasSaida(1) = {");
    vetor *s1 = grafo_arestasSaida(g, 1);
    for(int i = 0; i < s1->tamanho; i++)
        printf("%d,", vetor_elemento(s1, i));
    printf("}\n");

	printf("arestasEntrada(5) = {");
    vetor *e5 = grafo_arestasEntrada(g, 5);
    for(int i = 0; i < e5->tamanho; i++)
        printf("%d,", vetor_elemento(e5, i));
    printf("}\n");
    vetor_apaga(s1);
    vetor_apaga(e5);
    printf("\n");

	/* teste da alínea 1.4 */
    printf("\n=== Alinea 1.4 ===\n");
	printf("g completo: %d\n\n", grafo_completo(g));
    grafo_adiciona(g, 0, 1);
    printf("aresta 0->1 adicionada\n");
    grafo_adiciona(g, 0, 2);
    printf("aresta 0->2 adicionada\n");
    grafo_adiciona(g, 0, 3);
    printf("aresta 0->3 adicionada\n");
    grafo_adiciona(g, 0, 4);
    printf("aresta 0->4 adicionada\n");
    grafo_adiciona(g, 0, 5);
    printf("aresta 0->5 adicionada\n");
    grafo_adiciona(g, 1, 5);
    printf("aresta 1->5 adicionada\n");
    grafo_adiciona(g, 2, 3);
    printf("aresta 2->3 adicionada\n");
    grafo_adiciona(g, 3, 4);
    printf("aresta 3->4 adicionada\n");
    grafo_adiciona(g, 4, 2);
    printf("aresta 4->2 adicionada\n");
    grafo_imprime(g);
    printf("g completo: %d\n\n", grafo_completo(g));

    grafo_apaga(g);

	printf("\nFIM\n");

	return 0;
}
