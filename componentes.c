/*****************************************************************/
/*       Biblioteca componentes | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#include "componentes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int vetor_organiza_capacidade(armazem *a,int *vetor_pos_c, int tam);

componente *componente_novo(const char *ID, char *nome, int quantidade, float preco, const char *categoria){
  
  if (ID==NULL || nome==NULL || categoria==NULL)
    return NULL;
  
 componente *novo=malloc(sizeof(componente));
 if (novo==NULL)
    return NULL;

//colocar ID
strcpy(novo->ID,ID);

//colocar nome
novo->nome=(char*)malloc(sizeof(char)*(strlen(nome)+1));
if(novo->nome==NULL){
    free(novo);
    novo=NULL;
    return NULL;}

strcpy(novo->nome,nome);


//colocar quantidade
novo->quantidade=quantidade;

//colocar preço
novo->preco=preco;

//colocar categoria
strcpy(novo->categoria,categoria);
  
  
    return novo;
}

armazem *armazem_novo(){
  
armazem *novo=malloc(sizeof(armazem));
    if(novo==NULL)
        return NULL;

novo->tamanho=0;
novo->componentes=NULL;

    return novo;
}

int componente_insere(armazem *a,componente *c){
    

        if (a==NULL || c==NULL)
         return -1;

    //alocar memoria para um componente
        if(a->tamanho==0){
           a->componentes=(componente**)malloc(sizeof(componente*));
           if(a->componentes==NULL)
            return -1;}

    //procurar no vetor e adicionar caso encontre...
      for (int i=0; i<a->tamanho && a->tamanho!=0; i++){
        if (strcmp(a->componentes[i]->ID, c->ID)==0){
            a->componentes[i]->quantidade=a->componentes[i]->quantidade+c->quantidade;
            a->componentes[i]->preco=c->preco;
            return 1;}}

    // componente não estava presente

     a->tamanho++;
    
       
   if(a->tamanho!=1)
     a->componentes=(componente**)realloc(a->componentes,sizeof(componente*)*a->tamanho);

    a->componentes[a->tamanho-1]=c;    

    
    return 0;
}

armazem *armazem_importa(const char *nome_ficheiro){
    
    if (nome_ficheiro==NULL)
        return NULL;

    FILE *p;

    p=fopen(nome_ficheiro,"r");
      if(p==NULL)
        return NULL;

    armazem *novo=armazem_novo();
        if (novo==NULL){
            fclose(p);
            p=NULL;
            return NULL;}
    
    componente *aux;
    
    char str[500],*nome, ID[10], categoria[MAX_CHAR], *token;
    float preco;
    int quantidade;
    short FLAG;
    
    while (fgets(str,500,p)!=NULL){
        

        token=strtok(str, ",");
        strcpy(ID,token);
       

        token=strtok(NULL,",");
        nome=token;
        

        token=strtok(NULL,",");
        strcpy(categoria,token);

        token=strtok(NULL,",");
        quantidade=atoi(token);

        token=strtok(NULL,"\n");
        preco=atof(token);


        aux=componente_novo(ID,nome,quantidade,preco,categoria);
        if(aux==NULL){
            fclose(p);
            return NULL;}
        
       FLAG=componente_insere(novo,aux);
       
        if(FLAG==-1){
            fclose(p);
            componente_apaga(aux);
            return NULL;}
          
         if (FLAG==1)
             componente_apaga(aux);}

    fclose(p);
    p=NULL;
    
    return novo;
}

componente *componente_remove(armazem *a,  char *nome){
    
    if (a==NULL||nome==NULL||a->tamanho==0)
        return NULL;
    
     componente *aux;
    

      for (int i=0;i<a->tamanho;i++){
        if (strcmp(a->componentes[i]->nome,nome)==0){
            
           aux=a->componentes[i];
            
            //ultima posição
            if(i==a->tamanho-1){
                
                a->tamanho--;
                a->componentes=(componente**)realloc(a->componentes,sizeof(componente*)*a->tamanho);
                
                return aux;
            }
            
            //qualquer outra 
                                 
                  for (int j=i+1; j<a->tamanho;j++){
                      
                 a->componentes[j-1]=a->componentes[j];}
                 
                 a->tamanho--;
                 
                 a->componentes=(componente**)realloc(a->componentes,sizeof(componente*)*a->tamanho);  
                  
                 return aux;}}

    

    return NULL;
}

int componente_apaga(componente *c){

	    if (c==NULL)
        return -1;

    free(c->nome);
    c->nome=NULL;

    free(c);
    c=NULL;
    
    
    return 0;
}

int armazem_apaga(armazem *a){
	
	if (a==NULL)
      return -1;


    if (a->tamanho==0){
        free(a);
        a=NULL;
        return 0;}

    
    for (int i=0; i<a->tamanho; i++){
         if(componente_apaga(a->componentes[i])==-1)
           return -1;}
    
    free(a->componentes);
    free(a);
    a=NULL;

    return 0;

    
}

int *armazem_pesquisa_categoria(armazem *a, const char *categoria, int *tam){
   
    if (a==NULL||categoria==NULL||a->tamanho==0||tam==NULL)
        return NULL;

    *tam=0;
    int *v=(int*)malloc(sizeof(int));
    if(v==NULL)
        return NULL;

    for (int i=0; i<a->tamanho; i++){
        if (strcmp(a->componentes[i]->categoria,categoria)==0){
            *tam=*tam+1;
           if (*tam>1)
            v=(int*)realloc(v,sizeof(int)*(*tam));
             v[*tam-1]=i;
        }

    }


    //tam=0
   if (*tam==0){
       free(v);
       v=NULL;
       return NULL;}


   
	return v;
}

int *armazem_pesquisa_nome(armazem *a, char *nome, int *tam){
	
    if (a==NULL||nome==NULL||a->tamanho==0||tam==NULL)
        return NULL;

    *tam=0;
    int *v=malloc(sizeof(int));

    for (int i=0; i<a->tamanho; i++){
        if (strstr(a->componentes[i]->nome,nome)!=NULL){
            *tam=*tam+1;
            if(*tam>1)
            v=(int*)realloc(v,sizeof(int)*(*tam));
            v[*tam-1]=i;}}        

    
  //tam=0
  if (*tam==0){
       free(v);
       v=NULL;
       return NULL;
   }
  

	return v;
}

int  vetor_ordena(armazem *a, int *vetor_pos_c, int tam){
   
    if (a==NULL||vetor_pos_c==NULL||a->tamanho==0||tam==0)
        return -1;




//insertion sort
    int aux;

    for (int i=1; i<tam; i++){
        aux=vetor_pos_c[i];
        for(int j=i;j>0 && ((a->componentes[aux]->preco<a->componentes[vetor_pos_c[j-1]]->preco)||((a->componentes[aux]->preco==a->componentes[vetor_pos_c[j-1]]->preco)&&strcmp(a->componentes[aux]->ID,a->componentes[vetor_pos_c[j-1]]->ID)<0));j--){
            vetor_pos_c[j]=vetor_pos_c[j-1];
            vetor_pos_c[j-1]=aux;}}


    return 0;
}


fatura *fatura_nova(){

fatura *nova=malloc(sizeof(fatura));
 
 if(nova==NULL)
    return NULL;

nova->inicio=NULL;
nova->n_parcelas=0;
nova->preco_total=0;

    return nova;
}

parcela *parcela_nova (const char *ID, int quantidade,   float preco ){
    
 if (ID==NULL)
   return NULL;

 parcela *nova=(parcela*)malloc(sizeof(parcela));
    if(nova==NULL)
        return NULL;

  strcpy(nova->ID,ID);
  
  nova->preco=preco;
  nova->quantidade=quantidade;

    return nova; 
}

int insere_parcela_fatura(fatura *f, parcela  *p){

    if(p==NULL||f==NULL)
        return -1;

    parcela *aux;

if(f->n_parcelas==0){
        
    f->inicio=p;
   
    f->inicio->proximo=NULL;
    f->n_parcelas++;
    f->preco_total=f->inicio->preco*f->inicio->quantidade;
    return 0;}



  aux=f->inicio;
//testar isto
   while (aux->proximo!=NULL){
       if (strcmp(aux->ID,p->ID)==0){
        f->preco_total=f->preco_total+(p->quantidade*p->preco);
        aux->quantidade=p->quantidade+aux->quantidade;
        aux->preco=p->preco;
        return 1;}
       
    aux=aux->proximo;}
    
     if (strcmp(aux->ID,p->ID)==0){
        f->preco_total=f->preco_total+(p->quantidade*p->preco);
        aux->quantidade=p->quantidade+aux->quantidade;
        aux->preco=p->preco;
        return 1;}


    aux->proximo=p;
    aux->proximo->proximo=NULL; 
 
    f->n_parcelas++;
    f->preco_total=f->preco_total+(aux->proximo->preco*aux->proximo->quantidade);
    
    
    return 0;  


    
}

int parcela_apaga(parcela *p){ 
  
    if (p==NULL)
        return -1;

    free (p);
    p=NULL;
    
    return 0;
}

fatura *cria_fatura(armazem *a, const char *f){
  
    if (a==NULL||f==NULL||a->tamanho==0)
        return NULL;

    FILE *p;
    
    p=fopen(f, "r");
    if(p==NULL)
        return NULL;


    fatura *fat=fatura_nova();
     if (f==NULL){
        fclose(p);
        return NULL;}

    parcela *tmp;

    char str[100], des[MAX_CHAR], t,*token;
    int quant, *v, tam;
   

    while (fgets(str,100,p)!=NULL){
     

        token=strtok(str,",");
        t=*token;

        token=strtok(NULL,",");
        strcpy(des,token);

        token=strtok(NULL,"\n");
        quant=atoi(token);

        //se a quatidade pedida for 0 para um comp então vamos pro proximo
        if (quant==0)
            continue;
       
        

        //caso c
        if(t=='C'){
            
            short FLAG;
            v=armazem_pesquisa_categoria(a,des,&tam);
            if(v==NULL){
                fclose(p);
                return NULL;}

            if (vetor_ordena(a,v,tam)==-1){
                free(v);
                v=NULL;
                fclose(p);
                return NULL;}

            // ja ordenado 

            //pesquisar pra ver se algum tem a quantidade pedida
            for (int i=0; i<tam; i++){
                if(a->componentes[v[i]]->quantidade>=quant){
                    //meter lá 
                  
                
                tmp=parcela_nova(a->componentes[v[i]]->ID,quant,a->componentes[v[i]]->preco);
                if (tmp==NULL){
                    free(v);
                    v=NULL;
                    fclose(p);
                    return NULL;}
               
               FLAG=insere_parcela_fatura(fat,tmp);
                if(FLAG==-1){
                    free(v);
                    v=NULL;
                    fclose(p);
                    return NULL;}

                if (FLAG==1)
                    parcela_apaga(tmp);
                
                  a->componentes[v[i]]->quantidade=a->componentes[v[i]]->quantidade-quant;
                 
                  quant=0;
                  
                  break;
                }}



            if (quant!=0){
                
            //pesquisou mas nenhum tem a totalidade do que se pede 
            for (int i=0; i<tam && quant!=0; i++){
                   //começar a adicionar e certificar que não há quantidades ==0 
                if (a->componentes[v[i]]->quantidade==0)
                    continue;
                    
                    //senão for zero adicionar
                   quant=quant-a->componentes[v[i]]->quantidade;
                   
                   //se quant_componentes for superior à quantidade restante então vou subtrair o quant ao quant_componente 
                   if (quant<0){
                    tmp=parcela_nova(a->componentes[v[i]]->ID,a->componentes[v[i]]->quantidade+quant,a->componentes[v[i]]->preco);
                    if(tmp==NULL){
                        free(v);
                        v=NULL;
                        fclose(p);
                        return NULL;}

                      a->componentes[v[i]]->quantidade=-quant;
                 
                   
                    FLAG=insere_parcela_fatura(fat,tmp);
                    if (FLAG==-1){
                         free(v);
                         v=NULL;
                         parcela_apaga(tmp);
                         fclose(p);
                        return NULL;}

                        if (FLAG==1)
                        parcela_apaga(tmp);

                        quant=0;                
                        break;}
                    
                    
                    
                  
                     //se quant=0 ou quant>0 continuar neste ciclo
                
                    tmp=parcela_nova(a->componentes[v[i]]->ID,a->componentes[v[i]]->quantidade,a->componentes[v[i]]->preco);
                      if(tmp==NULL){
                        free(v);
                        v=NULL;
                        fclose(p);
                        return NULL;}

                    a->componentes[v[i]]->quantidade=0;  

                   FLAG=insere_parcela_fatura(fat,tmp); 
                   if (FLAG==-1){
                    free(v);
                    v=NULL;
                    parcela_apaga(tmp);
                    fclose(p);
                    return NULL;}

                    if(FLAG==1)
                        parcela_apaga(tmp); 
                    
                    //se chegar ao ultimo componente e quant>0 então terminar o ciclo porque não ha comps suficientes 
                    if (a->componentes[v[tam-1]]->quantidade==0 && quant>0){
                        break;}
                    }}
                    free(v);
                    v=NULL;}

         //caso N
        else if (t=='N'){
            
            int FLAG;

            v=armazem_pesquisa_nome(a,des,&tam);
            if(v==NULL){
                fclose(p);
                return NULL;}
            
            if(vetor_ordena(a,v,tam)==-1){
                free(v);
                v=NULL;
                fclose(p);
                return NULL;}
            
        //procurar se há algum comp com com_quant>=quant
            for (int i=0; i<tam; i++){
                if(a->componentes[v[i]]->quantidade>=quant){
                    tmp=parcela_nova(a->componentes[v[i]]->ID,quant,a->componentes[v[i]]->preco);
                    if (tmp==NULL){
                        free(v);
                        v=NULL;
                        fclose(p);
                        return NULL;}

                    FLAG=insere_parcela_fatura(fat,tmp);
                    if (FLAG==-1){
                        free(v);
                        v=NULL;
                        parcela_apaga(tmp);
                        fclose(p);
                        return NULL;}
                    
                    if(FLAG==1)
                        parcela_apaga(tmp);
                    
                    
                    a->componentes[v[i]]->quantidade=a->componentes[v[i]]->quantidade-quant;
                    
                    quant=0;
                     break;
                }}
                //se quant>comp_quant
                if (quant!=0){
                    if (vetor_organiza_capacidade(a,v,tam)==-1){
                        free(v);
                        v=NULL;
                        fclose(p);
                        return NULL;}
                    //caso todos os componentes sejam 0 passar pro proximo produto da lista de compras...
                    if(a->componentes[v[0]]->quantidade==0){
                        free (v);
                        v=NULL;
                        continue;}
                        
               
                    tmp=parcela_nova(a->componentes[v[0]]->ID,a->componentes[v[0]]->quantidade,a->componentes[v[0]]->preco);
                    if(tmp==NULL){
                        free(v);
                        v=NULL;
                        fclose(p);
                        return NULL;}

                    FLAG=insere_parcela_fatura(fat,tmp);    
                    if(FLAG==-1){
                        free(v);
                        v=NULL;
                        parcela_apaga(tmp);
                        fclose(p);
                        return NULL;}

                    if(FLAG==1)
                        parcela_apaga(tmp);
                    
                    a->componentes[v[0]]->quantidade=0;}
                    free(v);
                    v=NULL;}
                                                            

        //caso I
        else if (t=='I'){
                    short FLAG=1,j;
                    //procurar ID
                    for (int i=0; i<a->tamanho; i++){
                       
                       FLAG=strcmp(a->componentes[i]->ID,des);
                        if (FLAG==0){

                            //quant do comp é zero logo não se cria....
                            if (a->componentes[i]->quantidade==0)
                                break;
                            
                            //quant<=quant_comp
                            if(a->componentes[i]->quantidade>=quant){
                                tmp=parcela_nova(a->componentes[i]->ID,quant,a->componentes[i]->preco);
                                if(tmp==NULL){
                                    fclose(p);
                                    return NULL;}
                                    
                                    j=insere_parcela_fatura(fat,tmp);
                                    if(j==-1){
                                        parcela_apaga(tmp);
                                        fclose(p);
                                        return NULL;}

                                    if(j==1)
                                        parcela_apaga(tmp);

                                   a->componentes[i]->quantidade=a->componentes[i]->quantidade-quant;
                                   quant=0; 
                                     break;}

                              //quant>quant_comp
                            
                                tmp=parcela_nova(a->componentes[i]->ID,a->componentes[i]->quantidade,a->componentes[i]->preco);
                                if(tmp==NULL){
                                    fclose(p);
                                    return NULL;}

                                j=insere_parcela_fatura(fat,tmp);
                                if(j==-1){
                                    parcela_apaga(tmp);
                                    fclose(p);
                                    return NULL;}

                                if(j==1)
                                    parcela_apaga(tmp);
                                    
                                a->componentes[i]->quantidade=0;
                                
                                break; }}

                                //comp com o ID mandado não existe no armazem
                                if (FLAG!=0)
                                    continue;
                                }

        //nenhum caso..
        else {
        fclose(p);
        return NULL;}}
   
    fclose(p);
    return fat;
}

int fatura_apaga(fatura *f){
 
    if(f==NULL)
        return -1;

    if (f->n_parcelas==0){
        free (f);
        f=NULL;
        return 0;}
    
 parcela *next,*curr;
 curr=f->inicio;

 //todas as parcelas tirando a ultima
   while (curr->proximo!=NULL){
    next=curr->proximo;
    parcela_apaga(curr);
    curr=next;}

    //ultima parcela
    parcela_apaga(curr);
 
    free(f);
    f=NULL;
    return 0;
}

//organiza por capacidade maior e 2 criterio preço
int vetor_organiza_capacidade(armazem *a,int *vetor_pos_c, int tam){
    if (a==NULL||vetor_pos_c==NULL||a->tamanho==0||tam==0)
        return -1;
    
    int aux;

    for (int i=1; i<tam; i++){
        aux=vetor_pos_c[i];
        for(int j=i;j>0 && ((a->componentes[aux]->quantidade>a->componentes[vetor_pos_c[j-1]]->quantidade)||((a->componentes[aux]->quantidade==a->componentes[vetor_pos_c[j-1]]->quantidade)&&a->componentes[aux]->preco<a->componentes[vetor_pos_c[j-1]]->preco));j--){
            vetor_pos_c[j]=vetor_pos_c[j-1];
            vetor_pos_c[j-1]=aux;}}


    return 0;}