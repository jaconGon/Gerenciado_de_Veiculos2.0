/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 2022.1.08.040
 *
 * Created on 6 de Dezembro de 2022, 10:30
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "avl.h"

using namespace std;

tLista * lista1;
folha * raiz;
PONT arvoreAVL;

/*
 * 
 */
int main(int argc, char** argv) 
{
    bool *mudou;
    int c = -1;
    lista1 = inicia_lista(); 
    inicia_BD(lista1);
    inicializar(&arvoreAVL);
    criaAVL(lista1,&arvoreAVL,mudou);
    raiz = cria_arv(lista1,raiz);
    while(true)
    { 
        cout << "\nBem vindo ao menu:\n";
        cout << "Se deseja procurar ou remover um carro digite 1\n";
        cout << "Se deseja inserir um carro, digite 2\n" ;
        cout << "Se deseja que todos carros apareçam na tela, digite 3\n";
        cout << "Caso deseje a lista de veículos pela manuais, digite 4\n";
        cout << "Caso deseje a lista de veículos automáticos digite 5\n";
        cout << "Caso deseje um relatório da arvore binaria digite 6\n";
        cout << "Caso deseje um relatório da arvore AVL digite 7\n";
        cout << "Caso deseje sair do menu, digite 0\n";
        cin >> c;
        while(c!= 0 && c!= 1 && c!=2 && c!= 3 && c != 4 && c!= 5 && c!= 6 && c!=7)
        {
            printf("Você não informou uma opção válida tente novamente!\n ");
            cin >> c;
        }
        if(c == 1)
        {
                string pla;
                no * aux;
                PONT aux1;
                string q;
                cout << "Informe a placa a ser buscada\n";
                cin >> pla;
                aux = busca_lista(lista1, pla);
                if (aux != NULL){
                     cout << "carro encontrado, deseja remover? Digite 's' para sim e 'n' para não" << endl;
                     cin >> q;
                     if(q == "s" || q == "S"){
                         if(aux->car->cambio == "Manual"){
                            raiz = removeNo(raiz, pla);
                            remove_lista(lista1,aux);
                         }else{
                             if(aux->car->cambio == "Automático"){
                                 excluirAVL(&arvoreAVL, aux1, mudou);
                                 remove_lista(lista1,aux);
                             }
                         }
                     }
                }
        }
        if(c == 2)
        {
                cout << "Você optou por inserir um carro!" << endl;
                no* aux2 = inclui(lista1, raiz);
                if(aux2->car->cambio == "Automático"){
                    inserirAVL(&arvoreAVL, aux2, mudou);
                } 
        }
        if(c == 3)
        {
                cout << "Vocẽ optou por imprimir todos os carros na tela:\n";
                imprime_lista(lista1);
        }
        if(c == 4)
        {
                cout<< "Você optou por imprimir apenas os carros de câmbio manual:\n";
                pre_ord(raiz);
        }
        if(c == 5)
        {
                cout<< "você optou por imprimir apenas os carros automáticos: \n";
                exibirArvorePreOrdem(arvoreAVL);
        }
            
        if(c == 6)
        {
                cout<< "você optou por gerar um relatório da arvore binária \n";
                int  i = 0;
                i = conta_no(raiz,i);
                cout << "total de nós: " << i << endl;
                cout << "Altura total da árvore: " << raiz->alt-1 << endl;
        }
        if(c == 7)
        {
                cout<< "você optou por gerar um relatório da arvore AVL \n";
                int  i = 0;
                i = conta_AVL(arvoreAVL,i);
                cout << "total de nós: " << i << endl;
                i = altura(arvoreAVL);
                cout << "Altura total da árvore: " << i << endl;
        }
        if(c == 0)
        {
                cout<< "Operações encerradas e árvores desalocadas \n";
                break;
        }    
    }
  encerra_arv(raiz);
  destruirArvore(&arvoreAVL);
  desalocalista(lista1);
}
