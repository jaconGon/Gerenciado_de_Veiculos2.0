/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "arvore.h"

using namespace std;
/**
 * 
 * @return Retorna o cabeçalho da lista principal
 * 
 */
tLista *inicia_lista() {
  tLista *tmp = new (tLista);
  tmp->tam = 0;
  tmp->lista = NULL;
  return tmp;
}
/**
 * 
 * @param ptlista lista principal que é criada a partir do banco de dados
 */
void inicia_BD(tLista *ptlista) {
  ifstream myfile ("BD_veiculos_2.txt");
  if(myfile.is_open()){
    no * ant;
    no *atual = new(no);
    atual->car = new(carro);
    myfile >> atual->car->modelo;
    myfile >> atual->car->marca;
    myfile >> atual->car->tipo;
    myfile >> atual->car->ano;
    myfile >> atual->car->km;
    myfile >> atual->car->potencia;
    myfile >> atual->car->combustivel;
    myfile >> atual->car->cambio;
    myfile >> atual->car->direcao;
    myfile >> atual->car->cor;
    myfile >> atual->car->portas;
    myfile >> atual->car->placa;
    myfile >> atual->car->valor;
    ptlista->lista=atual;
    ant = atual;
    ptlista->tam++;  
    while( !myfile.eof()){
        atual = new(no);
        atual->car = new(carro);
        myfile >> atual->car->modelo;
        myfile >> atual->car->marca;
        myfile >> atual->car->tipo;
        myfile >> atual->car->ano;
        myfile >> atual->car->km;
        myfile >> atual->car->potencia;
        myfile >> atual->car->combustivel;
        myfile >> atual->car->cambio;
        myfile >> atual->car->direcao;
        myfile >> atual->car->cor;
        myfile >> atual->car->portas;
        myfile >> atual->car->placa;
        myfile >> atual->car->valor;
        ant->prox = atual;
        ant = ant->prox;
        ptlista->tam++;
        }    
    myfile.close();
    ptlista->tam--;
    delete(ant->car);
    delete(ant);
    ant = ptlista->lista;
    for(int i = 0;i < ptlista->tam-1; i ++)
        ant = ant->prox;
    ant->prox = NULL;
    }else{
      cout << "Erro ao abrir arquivo";
    }
}

/**
 * 
 * @param raiz Raiz a ser percorrida
 * @param placa Placa a ser buscada
 * @return Ponteiro para o nó encontrado
 */
folha * busca(folha * raiz,string pla){
    if(raiz == NULL || raiz->car->placa == pla)
        return raiz;
    if(raiz->car->placa > pla)
        return busca(raiz->esq,pla);
    else
        return busca(raiz->dir,pla);
}

/**
 * 
 * @param topo Nó da lista para o ponteiro irá apontar
 * @return retorna a raiz criada
 */
folha * inicia_arv(no *  topo){
    folha * raiz = new(folha);
    raiz->car = topo->car;
    raiz->esq = NULL;
    raiz->dir = NULL;
    return raiz;
}

/**
 * 
 * @param raiz Arvore binaria a ser criada
 * @param topo Lista principal para onde os ponteiros da binaria irão apontar
 * @return Retorna a arvore criada
 */
folha * insere(folha * raiz,no * topo){
    if(raiz == NULL)
        return inicia_arv(topo);
    if(raiz->car->placa > topo->car->placa ){
        raiz->esq = insere(raiz->esq,topo);
    }else
        raiz->dir = insere(raiz->dir,topo);
    return raiz;
}

/**
 * 
 * @param ptlista Cabeçalho da lista principal
 * @param raiz Arvore binaria a ser criada
 * @return retorna a arvore binaria criada
 */
folha * cria_arv(tLista * ptlista,folha * raiz){
    no * topo = ptlista->lista;
    while(topo != NULL){
        if(topo->car->cambio == "Manual")
           raiz = insere(raiz,topo);
        topo = topo->prox;
    }
    in_alt(raiz);
    return raiz;
}

/**
 * 
 * @param n nó a ser printada
 */
void printa(folha * n){
    cout << n->car->modelo << " ";
    cout << n->car->marca << " ";
    cout << n->car->tipo << " ";
    cout << n->car->ano << " ";
    cout << n->car->km<< " ";
    cout << n->car->potencia << " ";
    cout << n->car->combustivel << " ";
    cout << n->car->cambio << " ";
    cout << n->car->direcao << " ";
    cout << n->car->cor << " ";
    cout << n->car->portas << " ";
    cout << n->car->placa << " ";
    cout << n->car->valor << " ";
    cout << "// Altura do nó: " << n->alt-1 << " " << endl;
}

/**
 * 
 * @param q nó a ser desalocado
 */
void desaloc(folha * q){     
    delete(q);
    //cout << "\nnó desalocado";    
}

/**
 * 
 * @param raiz Imprime em pre ordem
 */
void pre_ord(folha * raiz){
    printa(raiz);
    if(raiz->esq != NULL){
        pre_ord(raiz->esq);
    }
    if(raiz->dir != NULL){
        pre_ord(raiz->dir);
    }
}

void in_ord(folha * raiz){
    if(raiz->esq != NULL){
        in_ord(raiz->esq);
    }
    printa(raiz);
    if(raiz->dir != NULL){
        in_ord(raiz->dir);
    }
}

/**
 * 
 * @param raiz raiz a ser contada
 * @param i numero de nós
 * @return retorna numero total de nós
 */
int conta_no(folha * raiz, int  i){
    if(raiz->esq != NULL){
       i = conta_no(raiz->esq,i);
    }
    if(raiz->dir != NULL){
        i = conta_no(raiz->dir,i);
    }
    i++;
    return i;
}

void pos_ord(folha * raiz){
    if(raiz->esq != NULL){
        pos_ord(raiz->esq);
    }
     if(raiz->dir != NULL){
        pos_ord(raiz->dir);
    }
   printa(raiz);
}

/**
 * 
 * @param raiz a ser encerrada
 */
void encerra_arv(folha * raiz){
    if(raiz->esq != NULL){
        encerra_arv(raiz->esq);
    }
    if(raiz->dir != NULL){
        encerra_arv(raiz->dir);
    }
    desaloc(raiz);
}

/**
 * 
 * @param raiz a ser percorrida
 * @param pla filho a ser achado
 * @return pai do nó placa
 */
folha * busca_pai(folha * raiz,string pla){
    if(raiz != NULL){
        if(raiz->dir != NULL && raiz->dir->car->placa == pla)
            return raiz;
        if(raiz->esq != NULL && raiz->esq->car->placa == pla)
            return raiz;
        if(raiz->car->placa == pla){
            cout << "O carro encontrado é a raiz" << endl;
            return NULL;
        }
        if(raiz->car->placa > pla)
            return busca_pai(raiz->esq,pla);
        else
            return busca_pai(raiz->dir,pla);
    }
    return NULL;
}    

/**
 * 
 * @param raiz a ser removida
 * @return raiz atualizada
 */
folha * remove_raiz(folha * raiz){
    folha * pont;
    folha * ant;
    if(raiz->esq != NULL){
        pont = raiz->esq;
        while(pont->dir != NULL){
            ant = pont;
            pont = pont->dir;
        }
        ant->dir = pont->esq;
        pont->esq=raiz->esq;
        pont->dir=raiz->dir;
        ant = raiz;
        raiz = pont;
        ant->dir = NULL;
        ant->esq = NULL;
        cout<<"Carro removido: "<< ant->car->placa << endl;
        delete(ant);
        return raiz;
    }else{
        if(raiz->dir != NULL){
            pont = raiz->dir;
            while(pont->esq != NULL){
                ant = pont;
                pont = pont->esq;
            }
            ant->esq = pont->dir;
            pont->dir=raiz->dir;
            pont->esq=raiz->esq;
            ant = raiz;
            raiz = pont;
            ant->dir = NULL;
            ant->esq = NULL;
            cout<<"Carro removido: "<< ant->car->placa << endl;
            delete(ant);
            return raiz;
        }
        else{
            delete(raiz);
            return NULL;
        }            
    }
}    
    
/**
 * 
 * @param raiz raiz a ser calculada a altura
 */
void altura(folha* raiz){
    int alt1 = 0,alt2 = 0;
    if(raiz->esq != NULL)
        alt1 = (raiz->esq->alt);
    else
        alt1= 0;
    if(raiz->dir != NULL)
        alt2 = (raiz->dir->alt);
    else
        alt2 = 0;
    if(alt1 > alt2 )
        raiz->alt = alt1 +1;
    else
        raiz->alt = alt2 +1;
}

/**
 * 
 * @param raiz Raiz principal a ser percorrida
 */
void in_alt(folha * raiz){
    if(raiz->esq != NULL){
        in_alt(raiz->esq);
    }
    if(raiz->dir != NULL){
        in_alt(raiz->dir);
    }
    altura(raiz);
}

/**
 * 
 * @param raiz Raiz a ser percorrida
 * @param pla Placa a ser removida
 * @return Retorna a raiz atualizada
 */
folha * removeNo(folha * raiz, string pla){
    folha * aux = busca(raiz, pla);
    if (aux != NULL) {        
        folha * pai = busca_pai(raiz, pla);
        if (pai != NULL) { 
            if (pai->dir->car->placa == pla)
                pai->dir = remove_raiz(aux);
            else 
                pai->esq = remove_raiz(aux);
        } else 
            raiz = remove_raiz(aux);
    }else
        cout << "Carro não encontrado na árvore" << endl;
    in_alt(raiz);
    return raiz;
}

/**
 * 
 * @param ptlista Cabeçalho da lista principal
 * @param raiz Arvore binaria
 * @return Retorna arvore principal com novo nó incluído
 * Insere um carro manualmente na lista principal e caso seja manual também insere na binaria
 */
no * inclui(tLista * ptlista, folha * raiz){
    no * p = ptlista->lista;
    while(p->prox != NULL )
        p = p->prox;
    p->prox = new(no);
    p->prox->car = new(carro);
    p = p->prox;
    cout << "\nInforme\nModelo: ";
    cin >> p->car->modelo;
    cout << "\nMarca: ";
    cin >> p->car->marca;
    cout << "\nTipo: ";
    cin >> p->car->tipo;
    cout << "\nAno: ";
    cin >> p->car->ano;
    cout << "\nKm: ";
    cin >> p->car->km;
    cout << "\nPotência: ";
    cin >> p->car->potencia;
    cout << "\nCombustível: ";
    cin >> p->car->combustivel;
    cout << "\nCâmbio: ";
    cin >> p->car->cambio;
    cout << "\nDireção: ";
    cin >> p->car->direcao;
    cout << "\nCor: ";
    cin >> p->car->cor;
    cout << "\nPortas: ";
    cin >> p->car->portas;
    cout << "\nPlaca: ";
    cin >> p->car->placa;
    cout << "\nValor: ";
    cin >> p->car->valor;
    p->prox = NULL;
    ptlista->tam++;
    if(p->car->cambio == "Manual"){
        insere(raiz, p);
        in_alt(raiz);
    }
    cout << "inserção bem sucedida" << endl << endl;
    return p;
}

/**
 * 
 * @param ptlista Imprime lista principal
 */
void imprime_lista(tLista *ptlista) {
  if (ptlista->tam == 0) {
    printf("Lista vazia!\n");
  } else {
    no *pont = ptlista->lista;
    for (int i = 0; i < ptlista->tam; i++) {
        cout << pont->car->modelo << " ";
        cout << pont->car->marca << " ";
        cout << pont->car->tipo << " ";
        cout << pont->car->ano << " ";
        cout << pont->car->km<< " ";
        cout << pont->car->potencia << " ";
        cout << pont->car->combustivel << " ";
        cout << pont->car->cambio << " ";
        cout << pont->car->direcao << " ";
        cout << pont->car->cor << " ";
        cout << pont->car->portas << " ";
        cout << pont->car->placa << " ";
        cout << pont->car->valor << " " << endl;
        pont = pont->prox;
    }
  }
  cout << endl;
}

/**
 * 
 * @param cabeca Cabeçalho da lista principal
 * @param placa Placa a ser buscada na lista principal
 * @return Retorna o ponteiro do nó que tem a placa a ser procurada
 */
no * busca_lista(tLista * cabeca , string placa){
    no *pont = cabeca->lista;
    for(int i = 0;i < cabeca->tam;i++){
        if(pont->car->placa==placa){
           return pont; 
        }else
            pont = pont->prox;
    }
    return NULL;
}

/**
 * 
 * @param ptlista Lista principal a ser percorrida
 * @param alvo Nó a ser removido da lista
 */
void remove_lista(tLista * ptlista,no * alvo){
    no * aux = ptlista->lista;
    while(aux->prox != alvo)
        aux = aux->prox;
    aux->prox = alvo->prox;
    alvo->prox = NULL;
    delete(alvo->car);
    delete(alvo);
    ptlista->tam--;
}

/**
 * 
 * @param lista Lista a ser desalocada
 */
void desalocalista(tLista * lista)
{
    no * ant;
    no * pont;
    pont = lista->lista;
    ant = pont;
    while(pont!=NULL)
    {
        pont = pont->prox;
        delete(ant->car);
        delete(ant);
        ant = pont;
    }
    delete (lista);
}