/*****************************************************************/
/*   Grafo direcionado | ESDA | L.EEC | 2021/22      */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"

//para a função heap update
#define RAIZ 		(1)
#define PAI(x) 		(x/2)


double infinito=__DBL_MAX__;

//funções aux para a função trajeto_mais_rapido
int heap_carrega_no(grafo *g, heap *h);

int heap_update (heap *h, int pos);

int elemento_menor(elemento * e1, elemento * e2);

grafo *grafo_novo()
{

grafo *novo=(grafo*)malloc(sizeof(grafo));
if(novo==NULL) 
  return NULL;

 novo->nos=NULL;

 novo->tamanho=0;   


    return novo;
}

no_grafo *no_novo(char *estacao, char *distrito)
{   
    if(estacao==NULL||distrito==NULL)
        return NULL;

no_grafo *no=(no_grafo*)malloc(sizeof(no_grafo));
if(no==NULL)
  return NULL; 

//nomes

no->estacao=(char*)malloc(sizeof(char)*(strlen(estacao)+1));
if(no->estacao==NULL){
  free(no);
  return NULL;}

strcpy(no->estacao,estacao);



strcpy(no->distrito,distrito);



//o resto
no->anterior=NULL;
no->arestas=NULL;
no->tamanho=0;
no->p_acumulado=0;



   return no;
}


no_grafo *no_remove(grafo *g, char *estacao)
{
    if(g==NULL||estacao==NULL)
        return NULL;


no_grafo *aux=NULL;

//procurar o no 

for(int i=0; i<g->tamanho && g->tamanho!=0; i++){
    if(strcmp(g->nos[i]->estacao,estacao)==0){
        aux=g->nos[i];
        
        //puxar as posições dos nós uma posição pra tras...
        for(int j=i+1; j<g->tamanho; j++)
            g->nos[j-1]=g->nos[j];

        g->tamanho--;

        g->nos=(no_grafo**)realloc(g->nos,sizeof(grafo*)*g->tamanho);

        break;}}

    if(aux==NULL)
      return NULL;

//retirar as arestas com este no como destino
for(int i=0; i<g->tamanho && g->tamanho!=0; i++){

    for(int j=0; j<g->nos[i]->tamanho && g->nos[i]->tamanho!=0;j++){
        
        if(strcmp(g->nos[i]->arestas[j]->destino->estacao,aux->estacao)==0){
              
              aresta_apaga(g->nos[i]->arestas[j]);
           
            //puxar as posições das arestas uma posição pra tras...
            for(int s=j+1; s<g->nos[i]->tamanho;s++){
                g->nos[i]->arestas[s-1]=g->nos[i]->arestas[s];}

                g->nos[i]->tamanho--;

                g->nos[i]->arestas=(aresta_grafo**)realloc(g->nos[i]->arestas,sizeof(aresta_grafo*)*g->nos[i]->tamanho);   
                
                j--;
               //break;-->talvez acha mais arestas com codigo diferente para a mesma estação     
                }}}


return aux;}

int aresta_apaga(aresta_grafo *aresta)
{   
    if(aresta==NULL)
        return -1;


    free(aresta->codigo);

    free(aresta->linha);

    free(aresta);


    return 0;
}

int no_apaga(no_grafo *no)
{
    if(no==NULL)
        return -1;

    if(no->tamanho!=0){
        for(int i=0; i<no->tamanho; i++)
            aresta_apaga(no->arestas[i]);
       
        free(no->arestas);}

     free(no->estacao);

     free(no);   
   
     return 0;}


int grafo_apaga(grafo *g)
{
    if(g==NULL)
        return -1;

    if(g->tamanho!=0){
        for(int i=0; i<g->tamanho;i++)
            no_apaga(g->nos[i]);
       
        free(g->nos);}

    free(g);

  
    return 0;}


int no_insere(grafo *g, no_grafo *no)
{
  if(g==NULL||no==NULL)
    return -1;


//tamanho do grafo=0
if(g->tamanho==0){

g->nos=(no_grafo**)malloc(sizeof(no_grafo*));
if(g->nos==NULL)
    return -1;

g->nos[0]=no;

g->tamanho++;

return 0;}


//tamanho do grafo!=0
for(int i=0;i<g->tamanho;i++){
    if(strcmp(g->nos[i]->estacao,no->estacao)==0)
        return 1;}

g->tamanho++;

g->nos=(no_grafo**)realloc(g->nos,sizeof(no_grafo*)*g->tamanho);

g->nos[g->tamanho-1]=no;


    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *linha, int distancia, int ano)
{
    if(origem==NULL||destino==NULL||codigo==NULL||linha==NULL||distancia<=0||ano<=0)
        return -1;

    //se a origem corresponder ao destino-->erro
    if(strcmp(origem->estacao,destino->estacao)==0)
        return -1;


if(origem->tamanho==0){
 
 origem->tamanho++;

origem->arestas=(aresta_grafo**)malloc(sizeof(aresta_grafo*));
if(origem->arestas==NULL){
    origem->tamanho--;
    return -1;}

origem->arestas[0]=(aresta_grafo*)malloc(sizeof(aresta_grafo));
if(origem->arestas[0]==NULL){
    free(origem->arestas);
    origem->tamanho--;
     return -1;}

origem->arestas[0]->destino=destino;

origem->arestas[0]->distancia=distancia;

origem->arestas[0]->inspecao=ano;


//linha
origem->arestas[0]->linha=(char*)malloc(sizeof(char)*(strlen(linha)+1));
if(origem->arestas[0]->linha==NULL){
    free(origem->arestas[0]);
    free(origem->arestas);
    origem->tamanho--;
    return -1;}

strcpy(origem->arestas[0]->linha,linha);



//codigo
origem->arestas[0]->codigo=(char*)malloc(sizeof(char)*(strlen(codigo)+1));
if(origem->arestas[0]->codigo==NULL){
    free(origem->arestas[0]->linha);
    free(origem->arestas[0]);
    free(origem->arestas);
    origem->tamanho--;
    return -1;}

strcpy(origem->arestas[0]->codigo,codigo);


return 0;}

//tamanho!=0

for(int i=0; i<origem->tamanho;i++){
    if(strcmp(origem->arestas[i]->codigo,codigo)==0 && strcmp(origem->arestas[i]->destino->estacao,destino->estacao)==0) 
        return 1;}


//não encontrou
origem->tamanho++;

origem->arestas=(aresta_grafo**)realloc(origem->arestas,sizeof(aresta_grafo*)*origem->tamanho);

origem->arestas[origem->tamanho-1]=(aresta_grafo*)malloc(sizeof(aresta_grafo));
if(origem->arestas[origem->tamanho-1]==NULL){
    origem->tamanho--;
    //falhar dar realloc pro valor anterior
    origem->arestas=(aresta_grafo**)realloc(origem->arestas,sizeof(aresta_grafo*)*origem->tamanho);
    return -1;}



origem->arestas[origem->tamanho-1]->destino=destino;
origem->arestas[origem->tamanho-1]->distancia=distancia;
origem->arestas[origem->tamanho-1]->inspecao=ano;



//linha
origem->arestas[origem->tamanho-1]->linha=(char*)malloc(sizeof(char)*(strlen(linha)+1));
if(origem->arestas[origem->tamanho-1]->linha==NULL){
    free(origem->arestas[origem->tamanho-1]);
    origem->tamanho--;
    origem->arestas=(aresta_grafo**)realloc(origem->arestas,sizeof(aresta_grafo*)*origem->tamanho);
    return -1;}

strcpy(origem->arestas[origem->tamanho-1]->linha,linha);


//codigo
origem->arestas[origem->tamanho-1]->codigo=(char*)malloc(sizeof(char)*(strlen(codigo)+1));
if(origem->arestas[origem->tamanho-1]->codigo==NULL){
    free(origem->arestas[origem->tamanho-1]->linha);
    free(origem->arestas[origem->tamanho-1]);
    origem->tamanho--;
    origem->arestas=(aresta_grafo**)realloc(origem->arestas,sizeof(aresta_grafo*)*origem->tamanho);
    return -1;}

strcpy(origem->arestas[origem->tamanho-1]->codigo,codigo);


return 0;}


no_grafo **pesquisa_avancada(grafo *g, char *destino, int *n)
{
    if(g==NULL || destino==NULL|| n==NULL)
        return NULL;

    if(g->tamanho==0)
        return NULL;

no_grafo **aux=NULL;        
*n=0;

    for(int i=0; i<g->tamanho; i++){
        for(int j=0; j<g->nos[i]->tamanho && g->nos[i]->tamanho!=0 && strcmp(g->nos[i]->estacao,destino)!=0; j++){
            if(strcmp(g->nos[i]->arestas[j]->destino->estacao, destino)==0){
                if(*n==0){
                    *n+=1;
                    aux=(no_grafo**)malloc(sizeof(no_grafo*));
                    if(aux==NULL){
                        *n=0;
                        return NULL;}
                        
                    aux[0]=g->nos[i];

                    break;}
                    
                  *n+=1;

                  aux=(no_grafo**)realloc(aux,sizeof(no_grafo*)*(*n));

                  aux[*n-1]=g->nos[i];
                  break;}}}



    
    return aux;}



no_grafo **estacoes_distrito (grafo *g, char *distrito, int *n)
{   if(g==NULL || distrito==NULL || n==NULL)
        return NULL;

    if(g->tamanho==0)
        return NULL;

no_grafo **aux=NULL;
*n=0;


for(int i=0; i<g->tamanho; i++){
   if(strcmp(g->nos[i]->distrito,distrito)==0){
       if(*n==0){
         *n+=1;

         aux=(no_grafo**)malloc(sizeof(no_grafo*));
         if(aux==NULL){
            *n=0;
            return NULL;}
            
         aux[0]=g->nos[i];

         continue;}

        *n+=1;

        aux=(no_grafo**)realloc(aux,sizeof(no_grafo*)*(*n));

        aux[*n-1]=g->nos[i];}}


return aux;}

no_grafo **estacoes_linha (grafo *g, char *estacao, char *linha, int *n) 
{                                                                         
    if(g==NULL|| estacao==NULL||linha==NULL||n==NULL)
        return NULL;

    if(g->tamanho==0)
        return NULL;

no_grafo **aux=NULL, *rec;
*n=0;

//encontrar estação
if((rec=encontra_no(g,estacao))==NULL)
    return NULL;

*n+=1;

aux=(no_grafo**)malloc(sizeof(no_grafo*));
if(aux==NULL){
    *n=0;
    return NULL;}

aux[0]=rec;


for(int i=0; i<aux[*n-1]->tamanho && aux[*n-1]->tamanho!=0; i++){
    //no origem
    if(strcmp(aux[*n-1]->arestas[i]->linha,linha)==0 && *n==1){
        
        *n+=1;

        aux=(no_grafo**)realloc(aux,sizeof(no_grafo*)*(*n));

        // colocar no vetor a proxima estação
        aux[*n-1]=aux[*n-2]->arestas[i]->destino;

        
        i=-1;
        continue;}

        //outro no que nao a origem
       if(strcmp(aux[*n-1]->arestas[i]->linha,linha)==0 && strcmp(aux[*n-2]->estacao, aux[*n-1]->arestas[i]->destino->estacao)!=0 && *n!=1){

         *n+=1;

        aux=(no_grafo**)realloc(aux,sizeof(no_grafo*)*(*n));

        // colocar no vetor a proxima estação
        aux[*n-1]=aux[*n-2]->arestas[i]->destino;

        
        i=-1;}}

    //caso não tenha encontrado nenhuma aresta na origem que pertença à linha
    if(*n==1){
        free(aux);
        return NULL;}



    return aux;}


int metros_linha (grafo *g, char *linha, char *origem) 
{   if (g==NULL || origem==NULL || linha==NULL)
       return -1;

    if(g->tamanho==0)
       return -1; 

int n=0,metros=0;
no_grafo **aux=estacoes_linha(g,origem,linha,&n);
if(aux==NULL)
    return -1;



for(int i=2; i<=n;i++){
    for(int j=0; j<aux[i-2]->tamanho;j++){
        if(strcmp(aux[i-2]->arestas[j]->destino->estacao,aux[i-1]->estacao)==0){
        metros=metros+aux[i-2]->arestas[j]->distancia;
        break;}}}

free(aux);

return metros;
}


no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, int *n)
{
    if (g==NULL || origem==NULL || destino==NULL || n==NULL)
        return NULL;

    //grafo sem arestas... ou a estação de destino é igual à estação de origem
    if(g->tamanho==0 || strcmp(origem,destino)==0) 
        return NULL;


//vetor a ser devolvido
no_grafo **aux=NULL, *ret_origem, *ret_destino;
*n=0;  

//verificar se o no de origem existe    
if((ret_origem=encontra_no(g,origem))==NULL)
    return NULL;

//verificar se o no de destino existe
if((ret_destino=encontra_no(g,destino))==NULL)
    return NULL;    

//adicionar o no de origem ao vetor
*n+=1;

aux=(no_grafo**)malloc(sizeof(no_grafo*));
if(aux==NULL){
    *n=0;
    return NULL;}

//encontrar o no origem 
aux[0]=ret_origem;


//verficar se tem arestas
if(aux[0]->tamanho==0){
    free(aux);
    return NULL;}

//algoritmo:

//colocar o peso nos nós
for(int i=0; i<g->tamanho; i++){
    if(strcmp(aux[0]->estacao,g->nos[i]->estacao)==0){
        g->nos[i]->p_acumulado=0;
        g->nos[i]->anterior=NULL;
        continue;}
        
    g->nos[i]->p_acumulado=infinito;
    g->nos[i]->anterior=NULL;}

     

//heap aux
heap *h=heap_nova(g->tamanho);
if(h==NULL){
    free(aux);
    return NULL;}


if(heap_carrega_no(g,h)==-1){
 heap_apaga(h);
 free(aux);
 return NULL;}


//operações na heap
no_grafo *tmp;

//ciclo infinito para atualizar os pesos
while(1){
  
tmp=heap_remove(h);

if(h->tamanho==0)
    break;

for(int i=0; i<tmp->tamanho;i++){
    for(int j=1; j<=h->tamanho; j++){
        if(strcmp(tmp->arestas[i]->destino->estacao,h->elementos[j]->no->estacao)==0){
            //ver se faço update ou não
          if(h->elementos[j]->no->p_acumulado>tmp->p_acumulado+tmp->arestas[i]->distancia){             
              //update do peso 
              h->elementos[j]->no->p_acumulado=tmp->p_acumulado+tmp->arestas[i]->distancia;
              //update da prioridade
              h->elementos[j]->prioridade=h->elementos[j]->no->p_acumulado;
              //apontador pro nó anterior
              h->elementos[j]->no->anterior=tmp;
             // printf("%f--%s\n",h->elementos[j]->no->p_acumulado, h->elementos[j]->no->estacao);
              //fazer update da posição do elemento na heap
              if(heap_update(h,j)==-1){
                  free(aux);
                  heap_apaga(h);
                  return NULL;}}
                  break;}
    }}
    
}
//algoritmo terminou voltar ao vetor...


//adicionar ao vetor

while(ret_destino->anterior!=NULL){
    *n+=1;
    ret_destino=ret_destino->anterior;}

aux=(no_grafo**)realloc(aux,sizeof(aresta_grafo*)*(*n));

//só por segurança
if((ret_destino=encontra_no(g,destino))==NULL){
    free(aux);
    *n=0;    
    return NULL;}

for(int i=*n-1;i>0;i--,ret_destino=ret_destino->anterior)
    aux[i]=ret_destino;


heap_apaga(h);

    return aux;
}

no_grafo *encontra_no(grafo *g, char *estacao)
{
    if(g==NULL ||estacao==NULL)
        return NULL;   

    no_grafo *aux=NULL;

    for(int i=0; i<g->tamanho && g->tamanho!=0; i++){
        if(strcmp(g->nos[i]->estacao,estacao)==0){
            aux=g->nos[i];
            break;}}


    return aux;}


no_grafo *encontra_troco(grafo *g, char *codigo, int *aresta_pos)  
{
    if(g==NULL || codigo==NULL || aresta_pos==NULL)
        return NULL;

    if(g->tamanho==0)
        return NULL;   

no_grafo *aux=NULL;    

for(int i=0; i<g->tamanho; i++){
    for(int j=0; j<g->nos[i]->tamanho && g->nos[i]->tamanho!=0;j++){
        if(strcmp(g->nos[i]->arestas[j]->codigo,codigo)==0){
            
            //caso no que encontrei seja mais baixo do que o outro no
            if(strcmp(g->nos[i]->arestas[j]->destino->estacao,g->nos[i]->estacao)>0){
                aux=g->nos[i];
                *aresta_pos=j;
                return aux;}

            //caso não seja
            for(int s=0; s<g->nos[i]->arestas[j]->destino->tamanho; s++){
                 if(strcmp(g->nos[i]->arestas[j]->destino->arestas[s]->codigo,codigo)==0){
                     aux=g->nos[i]->arestas[j]->destino;
                     *aresta_pos=s;
                     return aux;}}}

   }}



    return NULL;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, linha[40] = {0}, distritoorigem[40], distritodestino[40];
    int distancia = 0;
    int ano=0;
    int existearesta=0;
    

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ";");
        if (!token)
            break;
        strcpy(codigo, token);
   
        token = strtok(NULL, ";");
        strcpy(linha, token);

        token = strtok(NULL, ";");
        strcpy(origem, token);

        token = strtok(NULL, ";");
        strcpy(distritoorigem, token);

        token = strtok(NULL, ";");
        strcpy(destino, token);

        token = strtok(NULL, ";");
        strcpy(distritodestino, token);
   
        token = strtok(NULL, ";");
        distancia = atoi(token);


        token = strtok(NULL, ";");
        ano = atoi(token);
      
      //  printf("%s - %s - %s -%s - %s -%s -%d -%d",codigo,linha,origem,distritoorigem,destino,distritodestino,distancia,ano);
        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {
           no_origem = no_novo(origem,distritoorigem);
       

            if (no_insere(g, no_origem)==-1)
            {
                fclose(f);

                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
           
           no_destino = no_novo(destino,distritodestino);
        

            if (no_insere(g, no_destino)==-1)
            {
                fclose(f);

                return NULL;
            }
        }


    
    existearesta=0;
    //pesquisa em todas as arestas se existe
    for (int i = 0; i < no_origem->tamanho; i++)
    {

        if ((no_origem->arestas[i]->destino == no_destino) && ((strcmp(no_origem->arestas[i]->codigo, codigo) == 0)))
            existearesta=1;
    }
        if (existearesta == 0)
        {
            
            ret = cria_aresta(no_origem, no_destino, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
             ret = cria_aresta(no_destino,no_origem, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}


//FUNÇÕES AUXILIARES
int heap_carrega_no(grafo *g, heap *h){
    if(g==NULL || h==NULL)
        return -1;

    for (int i=0; i<g->tamanho; i++){
        if(heap_insere(h,g->nos[i],NULL,g->nos[i]->p_acumulado)==0)
            return -1;}

    return 0;

}


int heap_update (heap *h, int pos){
    if(pos<=0||h==NULL)
        return -1;


elemento *aux=NULL;


 while (pos != RAIZ && elemento_menor(h->elementos[pos], h->elementos[PAI(pos)]))
    {   
        aux = h->elementos[PAI(pos)];
        h->elementos[PAI(pos)] = h->elementos[pos];
        h->elementos[pos] = aux;
        pos = PAI(pos);
    }

return 0;}

int elemento_menor(elemento * e1, elemento * e2)
{
    if (e1 == NULL || e2 == NULL)
    {
        return 0; 
    }

    return e1->prioridade < e2->prioridade;
}