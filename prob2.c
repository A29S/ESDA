#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bst.h"
#include "avl.h"


int main(int argc, char **argv){
    
    if(argc>2){
        perror("Demasiados argumentos\n");
        exit(-1);}

    else if (argc<2){
        perror("Poucos argumentos-->Fazer ./a.out paises.txt\n");
        exit(-1);}

    FILE *p;


    p=fopen(argv[1],"r");
    if(p==NULL){
        perror("Não abriu\n");
        return -1;}


arvore_avl *nova=avl_nova();
if(nova==NULL)
    return -1;

char str[500], *token, pais[200];

    while(fgets(str,500,p)!=NULL){
        token=strtok(str,",");
        while(token!=NULL){
          token=strtok(NULL,",");

          if(token!=NULL){
            if(strstr(token,"\n"))
               token[strlen(token)-1]='\0';
            strcpy(pais,token);}}
        
        avl_insere(nova,pais);}

avl_imprime(nova);

return 0;}