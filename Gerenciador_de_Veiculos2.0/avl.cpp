/******************************************************************************/
/* Este programa foi incialmente implemenatdo pelos estudantes da USP         */
/* Modificamos o codigo para que se encaixe no nosso proposito                */
/* O codigo original pode ser encontrado em:                                  */
/* http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c   */
/******************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include "arvore.h"
#include "avl.h"

using namespace std;

#define true 1
#define false 0


/* Cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna 
   seu endereco. */
PONT criarNovoNo(no * ch){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->car = ch->car;
    novoNo->bal = 0;
    return novoNo;
}

/* Retorna o maior valor entre dois inteiros. */
int max(int a, int b){
    if (a>b) 
        return a;
    return b;
}

/* Retorna a altura de uma (sub-)arvore. */
int altura(PONT p){
    if (!p)
        return -1;
    return 1 + max(altura(p->esq),altura(p->dir));
}

/**
 * 
 * @param n Escreve a AVL
 */
void printaAVL(PONT n){
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
    int h = altura(n);
    cout << "// Altura do nó: " << h << " " << endl;
}

/* Exibe arvore Em Ordem.         */
void exibirArvoreEmOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    exibirArvoreEmOrdem(raiz->esq);
    printaAVL(raiz);
    exibirArvoreEmOrdem(raiz->dir);
}

/* Exibe arvore Pre Ordem.         */
void exibirArvorePreOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    printaAVL(raiz);
    exibirArvorePreOrdem(raiz->esq);
    exibirArvorePreOrdem(raiz->dir);
}


* Exibe arvore Pos Ordem         */
void exibirArvorePosOrdem(PONT raiz){
    if (raiz == NULL)
        return;
    exibirArvorePreOrdem(raiz->esq);
    exibirArvorePreOrdem(raiz->dir);
    printaAVL(raiz);
}
int atualizarBalanceamentoTotal(PONT raiz){
    if (!raiz)
        return 0;
    int d = atualizarBalanceamentoTotal(raiz->dir);
    int e = atualizarBalanceamentoTotal(raiz->esq);
    raiz->bal = d-e;
    return max(d,e)+1;
}


/* Rotações à direita (LL e LR) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoL(PONT p){
    cout << "Rotacao a esquerda, problema no no: " << p->car->placa << endl;
    PONT u, v;
    u = p->esq;
    if(u->bal == -1) {   // LL
        p->esq = u->dir;
        u->dir = p;
        p->bal = 0;
        u->bal = 0;
        return u;
    }
    else 
        if (u->bal == 1) {  // LR
            v = u->dir;
            u->dir = v->esq;
            v->esq = u;
            p->esq = v->dir;
            v->dir = p;
            if(v->bal == -1)
                p->bal = 1;
            else
                p->bal = 0;
            if(v->bal == 1)
                u->bal = -1;
            else
                u->bal = 0;
            v->bal = 0;
            return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
            p->esq = u->dir;
            u->dir = p;
            u->bal = 1;
            return u;
	}
}

/* Rotações à esquerda (RR e RL) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoR(PONT p){
    cout << "Rotacao a direita, problema no no: " << p->car->placa << endl;
    PONT u, v;
    u = p->dir;
    if(u->bal == 1) {   // RR
        p->dir = u->esq;
        u->esq = p;
        p->bal = 0;
        u->bal = 0;
	return u;
    } 
    else 
        if (u->bal == -1){  // RL
            v = u->esq;
            u->esq = v->dir;
            v->dir = u;
            p->dir = v->esq;
            v->esq = p;
            if(v->bal == 1)
                p->bal = -1;
            else 
                p->bal = 0;
            if(v->bal == -1)
                u->bal = 1;
            else
                u->bal = 0;
            v->bal = 0;
            return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
            p->dir = u->esq;
            u->esq = p;
            u->bal = -1;
            return u;	
	}
}

/* Inserção AVL: p é inicializado com o endereco do nó raiz e 
   *alterou com false                                         */
void inserirAVL(PONT* pp, no * ch, bool* alterou){
    PONT p = *pp;
    if(!p){
        *pp = criarNovoNo(ch);
        *alterou = true;
    } else {
        if(ch->car->placa == p->car->placa)
            *alterou = false;
        else
            if(ch->car->placa <= p->car->placa) {
                inserirAVL(&(p->esq), ch, alterou);
                if(*alterou)
                    switch (p->bal) {
                        case 1 :
                            p->bal = 0;
                            *alterou = false;
                            break;
			case 0 : 
                            p->bal = -1;
                            break;
			case -1:
                            *pp = rotacaoL(p);
                            *alterou = false;
                            break;
			}
		} else {
                    inserirAVL(&(p->dir), ch, alterou);
                    if(*alterou)
                        switch (p->bal) {
                            case -1:
                                p->bal = 0;
				*alterou = false;
                                break;
                            case 0 :
                                p->bal = 1;
				break;
                            case 1 :
                                *pp = rotacaoR(p);
				*alterou = false;
				break;
			}
		}
	}
}

/* Retorna o endereco do NO que contem chave=ch ou NULL caso a chave nao seja
       encontrada. Utiliza busca binaria recursiva                          */
PONT buscaBinaria(PONT ch, PONT raiz){
    if (raiz == NULL)
        return NULL;
    if (raiz->car->placa == ch->car->placa)
        return raiz;
    if (raiz->car->placa < ch->car->placa) 
        return buscaBinaria(ch,raiz->dir);
    return buscaBinaria(ch,raiz->esq);
}  

// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, PONT ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if(atual->car->placa == ch->car->placa)
            return(atual);
	*pai = atual;
	if(ch->car->placa < atual->car->placa)
            atual = atual->esq;
	else
            atual = atual->dir;
    }
    return(NULL);
}

/* Auxilir da funcao excluirChave, procura a maior chave menor que a chave que 
   serah excluida.            */
PONT maiorAEsquerda(PONT p, PONT *ant){
    *ant = p;
    p = p->esq;
    while (p->dir) {
        *ant = p;
        p = p->dir;
    }
    return(p);
}

/* Exclui a chave com valor igual a ch.   */
bool excluirAVL(PONT* raiz, PONT ch, bool* alterou){
    PONT atual = *raiz;
    if (!atual) {
        *alterou = false;
        return false;
    }
    if (atual->car->placa == ch->car->placa){
        PONT substituto, pai_substituto;
        if(!atual->esq || !atual->dir) { // tem zero ou um filho
            if(atual->esq)
                substituto = atual->esq;
            else 
                substituto = atual->dir;
            *raiz = substituto;
            free(atual);
            *alterou = true;
            return true;
        }
        else {   // tem dois filhos
            substituto = maiorAEsquerda(atual,&pai_substituto);
            atual->car = substituto->car;
            ch->car = substituto->car; // continua o codigo excluindo o substituto
        }
    }
    bool res;
    if (ch->car->placa > atual->car->placa) {
        res = excluirAVL(&(atual->dir), ch, alterou);
        cout << "Excluir recursivo a direita: " << atual->car->placa << "(" << atual->bal << ")" << endl; 
        if (*alterou){
            switch (atual->bal){
                case 1:
                    atual->bal = 0;
                    return true;
                case 0:
                    atual->bal = -1;
                    *alterou = false;
                    return true;
                case -1:
                    *raiz = rotacaoL(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }else{
        res = excluirAVL(&(atual->esq), ch, alterou);
        cout << "Excluir recursivo a esquerda: " << atual->car->placa << "(" << atual->bal << ")" << endl;  
        if (*alterou){
            switch (atual->bal){
                case -1:
                    atual->bal = 0;
                    return true;
                case 0:
                    atual->bal = 1;
                    *alterou = false;
                    return true;
                case 1:
                    *raiz = rotacaoR(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    return res;
}
/* Rotações à direita (LL e LR) */
void rotacaoL2(PONT *p) {
    cout << "Rotacao a esquerda, problema no no: " << (*p)->car->placa << endl;
    PONT u, v;
    u = (*p)->esq;
    if (u->bal == -1) { // LL
        (*p)->esq = u->dir;
        u->dir = *p;
        (*p)->bal = 0;
        *p = u;
    } else { // LR
        v = u->dir;
        u->dir = v->esq;
        v->esq = u;
        (*p)->esq = v->dir;
        v->dir = *p;
        if (v->bal == -1)
            (*p)->bal = 1;
        else 
            (*p)->bal = 0;
        if (v->bal == 1)
            u->bal = -1;
        else 
            u->bal = 0;
        *p = v;
    }
    (*p)->bal = 0; // balanço final da raiz (p) da subarvore
}

/* Rotações à esquerda (RR e RL)    */
void rotacaoR2(PONT *p) {
    cout << "Rotacao a direita, problema no no: " << (*p)->car->placa << endl;
    PONT u, v;
    u = (*p)->dir;
    if (u->bal == 1) { // RR
        (*p)->dir = u->esq;
        u->esq = *p;
        (*p)->bal = 0;
        *p = u;
    } else { // RL
        v = u->esq;
        u->esq = v->dir;
        v->dir = u;
        (*p)->dir = v->esq;
        v->esq = *p;
        if (v->bal == 1)
            (*p)->bal = -1;
        else 
            (*p)->bal = 0;
        if (v->bal == -1)
            u->bal = 1;
        else 
            u->bal = 0;
        *p = v;
    }
    (*p)->bal = 0; // balanço final da raiz (p) da subarvore
}
/* Inserção AVL2: p é inicializado com raiz e *alterou com false */
void inserirAVL2(PONT *pp, no * ch, bool *alterou) {
    PONT p = *pp;
    if (!p) {
        *pp = criarNovoNo(ch);
        *alterou = true;
    } else {
        if (ch->car->placa < p->car->placa) {
            inserirAVL2(&(p->esq), ch, alterou);
            if (*alterou)
                switch (p->bal) {
                    case 1: 
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 0: 
                        p->bal = -1;
                        break;
                    case -1: 
                        rotacaoL2(pp);
                        *alterou = false;
                        break;
                }
        } else {
            inserirAVL2(&(p->dir), ch, alterou);
            if (*alterou)
                switch (p->bal) {
                    case -1: 
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 0: 
                        p->bal = 1;
                        break;
                    case 1: 
                        rotacaoR2(pp);
                        *alterou = false;
                        break;
                }
        }
    }
}

/* funcao auxiliar na destruicao (liberacao da memoria) de uma arvore */
void destruirAux(PONT subRaiz){
    if (subRaiz){
	destruirAux(subRaiz->esq);
	destruirAux(subRaiz->dir);
	free(subRaiz);
    }
}

/* libera toda memoria de uma arvore e coloca NULL no valor da raiz    */
void destruirArvore(PONT * raiz){
    destruirAux(*raiz);
    *raiz = NULL;
}

/* inicializa arvore: raiz=NULL */
void inicializar(PONT * raiz){
    *raiz = NULL;
}

void travessiaAux(PONT p, int *niv, PONT ch, bool *achou) {
    if (p) {
        (*niv)++; // *niv = *niv + 1;
        if (p->car->placa == ch->car->placa)
            *achou = true;
        else {
            travessiaAux(p->esq, niv, ch, achou);
            if (!(*achou)) 
                travessiaAux(p->dir, niv, ch, achou);
            if (!(*achou)) 
                *niv = *niv - 1;
        }
    }
}

/* Retorna true e o nivel de uma chave (caso seja encontrada) e false caso 
       contrario.                                                
*/
//bool travessia(PONT p, int *niv, PONT ch) {
    *niv = 0;
    PONT temp = buscaBinaria(ch, p);
    if (temp) {
        bool achou = false;
        travessiaAux(p, niv, ch, &achou);
        return true;
    } else 
        return false;
}
void criaAVL(tLista * aux,PONT * arvoreAVL, bool * mudou){
    no * topo = aux->lista;
    while(topo != NULL){
        if(topo->car->cambio == "Automático")
            inserirAVL(arvoreAVL, topo, mudou);
        topo=topo->prox;
    }
}

/**
 * 
 * @param raiz Arvore AVL a ser contada os nos
 * @param i Contador, numero de nós
 * @return quantidade total de nós
 */
int conta_AVL(PONT raiz, int i){
    if(raiz->esq != NULL){
        i = conta_AVL(raiz->esq,i);
    }
    if(raiz->dir != NULL){
        i = conta_AVL(raiz->dir,i);
    }
    i ++;
    return i;
}

