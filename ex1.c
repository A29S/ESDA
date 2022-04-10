/***********************************************************/
/*      PL2 - Listas Ligadas | ESDA | L.EEC | 2021/22      */
/***********************************************************/

//FAZER A LISTA ORGANIZA   

/* Para compilar: gcc -g -Wall ex1.c -o ex1 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_STR 100
#define LISTA_INICIO 0
#define LISTA_FIM 1

/*
 * Registo para armazenar elementos de uma lista duplamente ligada.
 *   Este registo contém uma string e apontadores para o próximo e
 *   anterior elementos da lista.
 */
typedef struct _l_elemento {
	// string armazenada
	char *str;
	// apontadores para os elementos vizinhos
    struct _l_elemento *proximo;
    struct _l_elemento *anterior;
} l_elemento;

typedef struct {
	l_elemento *inicio;
	l_elemento *fim;
	int tamanho;
} lista;

/******* Funções já implementadas *******/
void lista_imprime(lista *lst);
l_elemento* novo_elemento(const char *valor);

/******* Funções a implementar *******/

/*
 * Cria uma nova lista ligada vazia.
 *  > retorno: apontador para a lista; se a lista não foi criada retorna NULL
 */
lista* lista_nova()
{
	lista *v;
    v=(lista*)malloc(sizeof(lista));
    if(v==NULL)
        return NULL;

    v->tamanho=0;
    v->inicio=NULL;
    v->fim=NULL;

    return v;

}

/*
 * Insere um elemento no fim da lista.
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'str': string a inserir
 *  > retorno: apontador para novo elemento inserido na lista ou NULL se ocorrer um erro
 *  - obs: testar onde deve se pretende colocar o elemento
 */
l_elemento* lista_insere(lista *lst, const char *str)
{
	/* b) inserir elemento na lista (dica: recorra também à função novo_elemento) */

    if (lst==NULL||str==NULL)
        return NULL;


    l_elemento *curr, *aux;
        
    curr=novo_elemento(str);
    if(curr==NULL)
        return NULL;

    lst->tamanho++;


    if (lst->inicio==NULL)
        lst->inicio=lst->fim=curr;

    

    else {
        aux=lst->inicio;
        while (aux->proximo!=NULL)
            aux=aux->proximo;
        
        aux->proximo=curr;
        aux->proximo->anterior=aux; 
        lst->fim=aux->proximo;

    }

    return aux->proximo;}

/*
 * Elimina uma lista, libertando toda a memória ocupada.
 *  > parâmetro 'lst': apontador para a lista
 *  - obs: se lst é NULL, não há operações a realizar
 */
void lista_apaga(lista *lst)
{
	/* c) apagar lista */
   	
	if (lst==NULL)
        return;
    
    l_elemento *curr;

    curr=lst->fim;

    while (curr!=lst->inicio){

        free(curr->str);
        curr=curr->anterior;
        free(curr->proximo);
        lst->fim=curr;
              
    }    

    if (lst->tamanho>0){    
    free(lst->inicio->str);
    free(lst->inicio);}

    
    free(lst);
    
    
    return;
}
    
    
    

/*
 * Ordena uma lista por ordem alfabética.
 *  > parâmetro 'lst': apontador para a lista
 *  > retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
 */
int lista_ordena(lista *lst)
{
    /* e) ordenar lista */

    if (lst==NULL)
        return -1;

    if (lst->tamanho==0)
        return 0;

    l_elemento *curr, *aux;
    
    curr=lst->inicio;
    
    char str[100];

    //insertion sort 

    while (curr!=NULL){
        strcpy(str,curr->str);
        //printf("1\n");
        for (aux=curr; aux!=lst->inicio && strcmp(aux->anterior->str,str)>0; aux=aux->anterior){
            
            aux->str=(char*)realloc (aux->str,(strlen(aux->anterior->str)+1)*sizeof(char));
            strcpy(aux->str,aux->anterior->str);
            aux->anterior->str=(char*)realloc (aux->anterior->str,(strlen(str)+1)*sizeof(char));
            strcpy(aux->anterior->str,str);}


    curr=curr->proximo;
    }
    



            
    return 0;

    }    
 




/*
 * Remove o elemento especificado.
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'pos': elemento que se pretende remover
 *  > retorno: apontador para o elemento seguinte ao que foi removido ou NULL se ocorrer um erro
 */
l_elemento* lista_remove(lista *lst, l_elemento *pos)
{
	/* g) remover elemento da lista */

    if (lst==NULL||pos==NULL)
        return NULL;

    lst->tamanho--;

    l_elemento *curr;

    if(pos->anterior==NULL){
        free(pos->str);
        lst->inicio=pos->proximo;
        free (pos);
        return lst->inicio;
    }

    else if (pos->proximo==NULL){
        free(pos->str);
      
        lst->fim=pos->anterior;
        curr=pos->proximo;
        free(pos);
        return curr;
    }

    else{
        free(pos->str);
        curr=pos->proximo;
        pos->proximo->anterior=pos->anterior;
        pos->anterior->proximo=pos->proximo;
        free(pos);}




    return curr;


}

/*
 * Devolve a posição do primeiro elemento da lista que contém a string especificada
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'str': string a pesquisar
 *  > parâmetro 'init': apontador para elemento onde a pesquisa é iniciada
 *  > parâmtero 'sentido': pesquisa efetuada a partir do início (LISTA_INICIO) ou a partir do fim (LISTA_FIM)
 *  > retorno: elemento encontrado ou NULL (caso não encontre o elemento ou caso ocorra um erro)
 */
l_elemento* lista_pesquisa(lista *lst, const char *str, l_elemento *init, int sentido)
{
	/* h) pesquisar a lista */

    if (lst==NULL||str==NULL||init==NULL||(sentido!=1 && sentido!=0))
        return NULL;


    

    while (init!=NULL){

        /*if (strstr(init->str,str)!=NULL){
            return init;

        }*/

        if (strcmp(init->str,str)==0){
            return init;
        }
    
        if(sentido==LISTA_INICIO)
            init=init->proximo;

        else 
            init=init->anterior;


    }
     return NULL;   
}

int main()
{
    char f_nome[] = "arquivo.txt";
    FILE *ficheiro;
    ficheiro = fopen(f_nome, "r");
    if (ficheiro == NULL) {
        printf("Erro a abrir %s.\n", f_nome);
        exit(0);
    }

    lista *lst_jogos = lista_nova();
    
    /* d) preencher a lista com a informação do ficheiro */

    char aux[100];

    while (fgets(aux,100,ficheiro)!=NULL){
       //esta linha de codigo resolve um problema com o \r\n do windows, mas por alguma razão só funciona algumas vezes
        aux[strlen(aux)-1]='\0';
       // aux[strlen(aux)]='\0';
        if(lista_insere(lst_jogos,aux)==NULL){
            printf("ERRO\n");
            exit (1);}

    }

    

    fclose(ficheiro);

    printf("Foram carregados %d jogos:\n", lst_jogos->tamanho);
    lista_imprime(lst_jogos);
    printf("\n");

    /* f) ordenar a lista */
    printf("Lista ordenada:\n");
    lista_ordena(lst_jogos);
    lista_imprime(lst_jogos);
    printf("\n");



    l_elemento *pr=lista_pesquisa(lst_jogos,"Pac-Man Party 3D (3DS)", lst_jogos->inicio,LISTA_INICIO);
    
    printf ("\n\n%s\n\n", pr->str);

    
	/* i) pesquisar jogos PS2 e removê-los da lista */

    l_elemento *curr;

    curr=lst_jogos->inicio;

    while (curr!=NULL){
        if(strstr(curr->str, "PS2")!=NULL){
            if (curr->anterior!=NULL){
            curr=curr->anterior;
            lista_remove(lst_jogos,curr->proximo);}

            else if (curr->proximo!=NULL && curr->anterior==NULL){
                  curr=curr->proximo;
            lista_remove(lst_jogos,curr->anterior);   
            }

        }

        curr=curr->proximo;

    }

    printf("Após remoção de jogos PS2 a lista tem %d jogos.\n", lst_jogos->tamanho);
    lista_imprime(lst_jogos);
    printf("\n");
   
	
    lista_apaga(lst_jogos);


    

    return 0;
}

/*
 * Imprime os elementos de uma lista.
 *  > parâmetro 'lst': apontador para a lista
 */
void lista_imprime(lista *lst)
{
    if (lst != NULL && lst->tamanho != 0) {
        l_elemento *l_elem = lst->inicio;
        for (int i = 0; i < lst->tamanho; i++) {
            printf("Pos %d -> %s\n", i, l_elem->str);
            l_elem = l_elem->proximo;
        }
    }
}

/*
 * Cria novo elemento.
 *  > parâmetro 'valor': string
 *  > retorno: apontador para o elemento criado ou NULL se ocorrer um erro
 */
l_elemento* novo_elemento(const char *valor)
{
	// alocar memória para a estrutura l_elemento
	l_elemento *item = (l_elemento*)malloc(sizeof(l_elemento));
	if (item == NULL) return NULL;

	// alocar memória para string
    item->str = (char*)malloc((strlen(valor) + 1) * sizeof(char));
	if(item->str == NULL) {
		free(item);
		return NULL;
	}

	// copiar valor
	strcpy(item->str, valor);

	// item ainda não tem próximo
    item->proximo = NULL;
    item->anterior = NULL;

	return item;
}