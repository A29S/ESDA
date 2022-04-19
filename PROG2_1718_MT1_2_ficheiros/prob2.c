#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest);
/*** problema 2 ***/
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{	if(vrem==NULL||vdest==NULL)
		return NULL;
	
vetor *novo=vetor_novo();
if(novo==NULL)
	return NULL;

int count=0;

for(int i=0,FLAG=0; i<vetor_tamanho(vrem);i++){
	
	if(novo->tamanho!=0){
		for(int s=0; s<novo->tamanho; s++){
			if(strcmp(novo->elementos[s].str,vrem->elementos[i].str)==0){
				FLAG=1;
				break;}}}

		if(FLAG==1){
			FLAG=0;
			continue;}
					

	for (int j=0;j<vetor_tamanho(vrem);j++){
			if(strcmp(vrem->elementos[i].str,vrem->elementos[j].str)==0)
				count++;}

	for (int j=0;j<vetor_tamanho(vdest);j++){
			if(strcmp(vrem->elementos[i].str,vdest->elementos[j].str)==0)
				count++;}	
	
	vetor_insere(novo,vrem->elementos[i].str,-1);

	printf("%s: %d cartas\n", vrem->elementos[i].str, count);

	count=0;}


	for(int i=0,FLAG=0; i<vetor_tamanho(vdest);i++){
		
		
	if(novo->tamanho!=0){
		for(int s=0; s<novo->tamanho; s++){
			if(strcmp(novo->elementos[s].str,vdest->elementos[i].str)==0){
				FLAG=1;
				break;}}}

		if(FLAG==1){
			FLAG=0;
			continue;}
			

		for(int j=0;j<vetor_tamanho(vdest);j++){
			if(strcmp(vdest->elementos[i].str,vdest->elementos[j].str)==0)
				count++;}

			vetor_insere(novo,vdest->elementos[i].str,-1);
			printf("%s: %d cartas\n", vdest->elementos[i].str, count);
			count=0;}



		return novo;}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor* vrem;
	vetor* vdest;
	vetor *vcp_dest;
	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_remetente_destinatario(vrem, vdest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else {
		printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);

	return 0;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}
