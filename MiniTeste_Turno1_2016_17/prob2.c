#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
int avalia_expressoes(FILE *ficheiro, vetor *expressoes)
{
int h=0;
char ok[50];

	//exercicio resolvido sem pilha... prefiro este metodo...
 /* for(int i=0; i<vetor_tamanho(expressoes);i++){
	strcpy(ok,expressoes->elementos[i].str);
	for(int j=0; j<strlen(expressoes->elementos[i].str)+1; j++){
	if(expressoes->elementos[i].str[j]=='(' || expressoes->elementos[i].str[j]==')')
		h++;}

	if(h%2==0){
	strcat(ok," --> OK\n");
	fputs(ok,ficheiro);
	h=0;}
	
	else{
	strcat(ok," --> NOK\n");
	fputs(ok,ficheiro);
	h=0;}}*/

//exercicio resolvido com uma pilha...
pilha *aux=pilha_nova();
if(aux==NULL)
	return -1;

for(int i=0; i<vetor_tamanho(expressoes);i++){
	strcpy(ok,expressoes->elementos[i].str);

	if(pilha_vazia(aux)!=1){
		printf ("%d\n",i);
		while(pilha_vazia(aux)!=1)
			pilha_pop(aux);}

	for(int j=0; j<strlen(expressoes->elementos[i].str)+1;j++){
		
		if(expressoes->elementos[i].str[j]=='(')
			pilha_push(aux,"(");
			

		if(expressoes->elementos[i].str[j]==')' && pilha_vazia(aux)!=1){ //-->voltar a fazer este simplesmente pra me lembrar antes do teste para pensar em todos
			pilha_pop(aux);												  // os casos que um exercicio pode ter...
			continue;}															
			
			
		if(expressoes->elementos[i].str[j]==')' && pilha_vazia(aux)==1)
			pilha_push(aux,")");}
	
	if(pilha_vazia(aux)==1){
		strcat(ok,"-> OK\n");
		if(fputs(ok,ficheiro)==EOF)
			return -1;}

	else{
		strcat(ok,"-> NOK\n");
		if(fputs(ok,ficheiro)==EOF)
			return -1;}}

pilha_apaga(aux);

return 1;}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

vetor* lerFicheiro(FILE *ficheiro)
{
	char buffer[BUFFER], *charptr;
	vetor *v;
	v = vetor_novo();
	while(fgets(buffer, BUFFER, ficheiro) != NULL)
	{
		charptr = strchr(buffer, '\n');
		if(charptr) *charptr = '\0';
		charptr = strchr(buffer, '\t');
		if(charptr) *charptr = '\0';
		if(strcmp(charptr+1, "infixa") == 0)
			vetor_insere(v, buffer, v->tamanho);
	}
	return v;
}

int main()
{
	FILE *fin, *fout;
	vetor *expressoes=NULL;

	fin = fopen("expressoes.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	fout = fopen("avaliacao.txt", "w");
	if(fout == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	expressoes = lerFicheiro(fin);
	if(!expressoes)
	{
		printf("Erro ao ler ficheiro de expressoes.\n");
		return 1;
	}
	int h;
	if((h=avalia_expressoes(fout, expressoes)) == 1)
		printf("Funcao terminou corretamente - verificar ficheiro avaliacao.txt\n");
		
	else
		printf("Funcao retornou erro.\n");

printf("%d\n",h);
	fclose(fin);
	fclose(fout);

	return 0;
}
