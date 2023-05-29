/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   avl.h
 * Author: 2022.1.08.040
 *
 * Created on 1 de Fevereiro de 2023, 10:27
 */

#ifndef AVL_H
#define AVL_H
#include "arvore.h"
using namespace std;


typedef struct aux {
    carro * car;
    struct aux *esq;
    struct aux *dir;
    int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} NO, *PONT;



PONT criarNovoNo(no * topo);
int max(int a, int b);
int altura(PONT  p);
void exibirArvoreEmOrdem(PONT   raiz);
void exibirArvorePreOrdem(PONT   raiz);
void exibirArvorePosOrdem(PONT  raiz);
int atualizarBalanceamentoTotal(PONT raiz);
PONT rotacaoL(PONT p);
PONT rotacaoR(PONT p);
void inserirAVL(PONT* pp, no * ch, bool* alterou);
PONT buscaBinaria(PONT ch, PONT raiz);
PONT buscaNo(PONT raiz, PONT ch, PONT *pai);
PONT maiorAEsquerda(PONT p, PONT *ant);
bool excluirAVL(PONT* raiz, PONT ch, bool* alterou);
void rotacaoL2(PONT *p);
void rotacaoR2(PONT *p);
void inserirAVL2(PONT *pp, no * ch, bool *alterou);
void destruirAux(PONT subRaiz);
void destruirArvore(PONT * raiz);
void inicializar(PONT * raiz);
void travessiaAux(PONT p, int *niv, PONT ch, bool *achou);
bool travessia(PONT p, int *niv, PONT ch);
void criaAVL(tLista * aux,PONT * arvoreAVL, bool * mudou);
int conta_AVL(PONT raiz, int i);

#endif /* AVL_H */

