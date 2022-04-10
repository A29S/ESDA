// Para compilar: gcc -Wall ex1_2.c vector.c -o ex1_2

#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 1. Criar um novo vetor vazio.
		vetor *v, *v1;
		char *str;
		str=(char*)malloc(sizeof(char)*50);
		if(str==NULL){
			printf ("ERRO\n");
			exit (1);}



		v=vetor_novo();
		if (v==NULL) {
			printf ("ERRO\n");
			exit(1);}

    // 2. Solicitar ao utilizador 5 strings para inserir no vetor.
	 for (int i=0; i<5; i++){
		 gets(str);
		 if(vetor_insere(v,str,-1)==-1){
		 	printf("ERRO\n");
			 exit(1);}}
    
    // 3. Imprimir o conteúdo do vetor.
		for (int i=0; i<v->tamanho; i++)
			printf("%s\n", v->elementos[i].str);

			printf ("%d\n",v->tamanho );



		v1=vetor_novo();
		if (v1==NULL) {
			printf ("ERRO\n");
			exit(1);}


		for (int i=0; i<5; i++){
		 gets(str);
		 if(vetor_insere(v1,str,-1)==-1){
		 	printf("ERRO\n");
			 exit(1);}}
    
    
		for (int i=0; i<v1->tamanho; i++)
			printf("%s\n", v1->elementos[i].str);


    
   //  4. Solicitar ao utilizador uma string; se essa string existir no vetor, apagar a string.
	
		gets (str);
		


		int pos=vetor_pesquisa(v, str);

		if (pos==-1) {
			printf("ERRO\n");
			exit (1);}
		
		if (vetor_remove(v,pos)!=0) {
			printf ("ERRO\n");
			exit(1);}
			

    
    // 5. Imprimir o conteúdo do vetor.
	for (int i=0; i<v->tamanho; i++)
			printf("%s\n", v->elementos[i].str);
    
    // 6. Ordenar o vetor.
    
    if(vetor_ordena(v)==-1){
		printf("ERRO\n");
		exit (1);};
    // 7. Imprimir o conteúdo do vetor.
    
   for (int i=0; i<v->tamanho; i++)
		printf("%s\n", v->elementos[i].str);



//1.3 vetor concatena teste 
	printf("\n");
	vetor *res;


	res=vetor_concatena (v, v1);

	if(res==NULL)
		printf("Erro vetor concatena\n");

	for (int i=0; i<res->tamanho; i++)
		printf("%s\n", res->elementos[i].str);

//1.3 vetor inverte teste
	printf ("\n");
	if(vetor_inverte(res)==-1)
		printf("ERRO vetor insere\n");

	for (int i=0; i<res->tamanho; i++)
		printf("%s\n", res->elementos[i].str);


    return 0;
}
