/* 
 * File:   arvore.h
 * Author: 2022.1.08.040
 *
 * Created on 6 de Dezembro de 2022, 10:30
 */

#ifndef ARVORE_H
#define ARVORE_H

using namespace std;

typedef struct{
    string modelo;
    string marca;
    string tipo;
    string ano;
    string km;
    string potencia;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    string portas;
    string placa;
    float valor;
}carro;

typedef struct no_{
    carro * car;
    no_ * prox;
}no;

typedef struct {
	int tam;            //tamanho da lista
	no * lista; // ponteiro para o próximo nó da lista encadeada
} tLista;

typedef struct no1_{
    carro * car;
    int alt = 0;
    struct no1_ * esq;
    struct no1_ * dir;
}folha;

tLista *inicia_lista();
void inicia_BD(tLista *ptlista);
folha * inicia_arv(no * pont);
folha * busca(folha * raiz,string pla);
void encerra_arv(folha * raiz);
void pre_ord(folha * raiz);
void in_ord(folha * raiz);
void pos_ord(folha * raiz);
folha * remove_raiz(folha * raiz);
folha * removeNo(folha * raiz,string placa);
void in_alt(folha * raiz);
folha * cria_arv(tLista * ptlista,folha * raiz);
folha * busca(folha * raiz,string pla);
no * inclui(tLista * ptlista, folha * raiz);
void imprime_lista(tLista *ptlista);
no * busca_lista(tLista * cabeca , string placa);
void remove_lista(tLista * ptlista,no * alvo);
int conta_no(folha * raiz, int  i);
void desalocalista(tLista * lista);


#endif /* ARVORE_H */

