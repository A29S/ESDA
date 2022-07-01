#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "componentes.hpp"

using namespace std;

/* --------------- */ 
/*    Componente   */ 
/* --------------- */ 

// Constructors

Componente::Componente()
{  preco=0;

   quantidade=0;

}

Componente::Componente(string c_id, string c_nome, int c_quantidade, float c_preco, string c_categoria)
{   

    id=c_id;

    nome=c_nome;

    if(c_quantidade<0)
        quantidade=0;

    if(c_quantidade>=0)
      quantidade=c_quantidade;
    

    if(c_preco<0)
       preco=0;
    
    if(c_preco>=0)
      preco=c_preco;
    
    categoria=c_categoria;
}

// Get Methods

string Componente::getId() const
{
    return id;

}

string Componente::getNome() const
{   
    return nome;

}

string Componente::getCategoria() const
{
    return categoria;

}

float Componente::getPreco() const
{
    return preco;

}

int Componente::getQuantidade() const
{
    return quantidade;

}

// Set Methods

void Componente::setId(string c_id)
{
    if(c_id.empty())
        return;

    id=c_id;

}

void Componente::setNome(string c_nome)
{   
    if(c_nome.empty())
        return;

    nome=c_nome;

}

void Componente::setQuantidade(int c_quantidade)
{
    if(c_quantidade<0)
        return;

    quantidade=c_quantidade;

}

void Componente::setPreco(float c_preco)
{
    if(c_preco<0)
        return;

    preco=c_preco;

}

void Componente::setCategoria(string c_categoria)
{
    if(c_categoria.empty())
        return;

    categoria=c_categoria;
       
}

// Friend Fucntion

bool comparaComponentes(const Componente *c1, const Componente *c2) 
{                                                                  
    if(c1->getPreco()<c2->getPreco())
        return true;

    else if(c1->getPreco()==c2->getPreco()){
        if(c1->getId().compare(c2->getId())<0)
            return true;

        else //c1>c2
            return false;}
        

    else  //caso c1>c2    
    return false;

}

/* --------------- */ 
/*     Armazém     */ 
/* --------------- */

// Constructor

Armazem::Armazem()
{
    if(!componentes.empty())
        componentes.clear();
                             

}

// Destructor

Armazem::~Armazem()
{
    
     for(int i=0; !componentes.empty() && i<componentes.size();i++)
        delete componentes[i];

    componentes.clear();

}

// Get Methods

vector<Componente*> Armazem::getComponentes() const
{   
    //criação do vetor
    vector <Componente*> aux; 

    for(int i=0;!componentes.empty() && i<componentes.size();i++)
        aux.push_back(componentes[i]);

    return aux;}



size_t Armazem::getTamanho() const
{
    return componentes.size();

}

// Other Methods

int Armazem::componenteInsere(Componente *c)
{

    //ver se o componente ja existe e se o vetor não esta vazio
    for(int i=0; !componentes.empty() && i<componentes.size();i++){
        if(componentes[i]->getId().compare(c->getId())==0){
            //atualizar quantidade
            componentes[i]->setQuantidade(componentes[i]->getQuantidade()+c->getQuantidade());

            //atualizar preco
            componentes[i]->setPreco(c->getPreco());

            //apagar o componente c
            delete c;

            return 1;
        }}

   //componente não existe ou vetor vazio
    
    componentes.push_back(c);


    return 0;
}

Componente* Armazem::componenteRemove(const string nome)
{
    
     Componente *aux;
 
     //procurar o componente
    for(int i=0; !componentes.empty() && i<componentes.size(); i++){
        if(componentes[i]->getNome().compare(nome)==0){
            aux=componentes[i];

            componentes.erase(componentes.begin()+i);

            return aux;
        }}

    //componente não existe
    return NULL;
}

int Armazem::importa(const string nome_ficheiro)
{
    ifstream pfile(nome_ficheiro); 

    if(!pfile.is_open())
        return -1;

   string line, id, nome,cat, preco, quantidade;   

    while(!pfile.eof()){
     
     getline(pfile,line); 

     if(line.empty()==true)
        continue;

    stringstream aux(line);

    //dividir em tokens 
    getline(aux,id,',');     
   // cout<<id<<endl;

    getline(aux,nome,',');
    //cout<<nome<<"\n";

    getline(aux,cat,',');
    //cout<<cat<<"\n";

    getline(aux,quantidade,',');
    //cout<<stoi(quantidade)<<"\n";
    
    getline(aux,preco);//->vai ate ao '\n'
    //cout<<stof(preco)<<endl;
    
    Componente *c=new Componente(id,nome,stoi(quantidade),stof(preco),cat); 

    componenteInsere(c);}


    return 0;
}

vector<int> Armazem::pesquisaCategoria(const string categoria)
{ 

    vector<int> aux; 
    
    for(int i=0; !componentes.empty() && i<componentes.size(); i++){
        if(componentes[i]->getCategoria().compare(categoria)==0)
            aux.push_back(i);}

    
    return aux;}


void Armazem::ordena()
{
    if(componentes.empty())
        return;

     sort(componentes.begin(),componentes.end(),comparaComponentes);   


}