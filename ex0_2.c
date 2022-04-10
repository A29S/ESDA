#include <stdio.h>
#include <stdlib.h>

int vetor_tem_impares(int *vetor, int n)
{
    if (vetor==NULL){
        printf("ERRO\n");
        return 0;}

    for (int i=0; i<n; i++){
        if (vetor[i]%2!=0)
            return 1;}
    
    return 0;

}

int main()
{
    // testes:
    int a[] = {0, 2, 8, 6};
    printf("devia retornar 0: %d\n", vetor_tem_impares(a, 4));
    int b[] = {0, 2, 7, 6};
    printf("devia retornar 1: %d\n", vetor_tem_impares(b, 4));
    return 0;
}