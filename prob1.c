#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/*** problema 1 ***/
char* avl_maiorstring(no_avl *no)
{
	/* complexidade do algoritmo: ________________ */
    if(no==NULL)
        return "\0";
char *aux, *right, *left;

aux=no->str;


left=avl_maiorstring(no->esquerda);
right=avl_maiorstring(no->direita);


if(strlen(left)>strlen(right) && strlen(aux)<strlen(left))
    aux=left;

else if(strlen(right)>strlen(left) && strlen(aux)<strlen(right)) 
aux=right;

else 
    return aux;

return aux;

}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *str;

	arvore_avl *arv;
	puts("* Problema 1 *");
	arv = avl_nova();
	while(fgets(str_aux,MAX_STR,fp) != NULL)
	{
		if(str_aux[strlen(str_aux)-1] == '\n')
			str_aux[strlen(str_aux)-1] = '\0';
		avl_insere(arv, str_aux);
	}
	str = avl_maiorstring(arv->raiz);
	printf("Maior string: ");
	if(str != NULL)
		puts(str);
	else
		puts("(null)");
	avl_apaga(arv);

	fclose(fp);
	return 0;
}
