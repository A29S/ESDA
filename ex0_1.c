#include <stdio.h>
#include <stdlib.h>

void imprime_vetor(int *v, int n)
{
    
    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);
    
    return;
}

int main()
{
    int n, *v;
    // (a) pede ao utilizador o número de elementos do vetor
        printf ("Nº de elementos: ");
        scanf("%d", &n);

    
    // (b) cria um vetor de forma dinâmica (dica: calloc)
    v=(int*)malloc(sizeof(int)*n);
    if (v==NULL){
        printf("ERRO\n");
        exit (1);
    }
    
    // (c) pede ao utilizador números inteiros e preenche o vetor com os mesmos    
        printf ("Valores:\n");

        for (int i=0; i<n; i++)
            scanf("%d", &v[i]);

    
    // (d) no final chama a função imprime_vetor que te é fornecida
    imprime_vetor(v,n);
    
    return 0;
}