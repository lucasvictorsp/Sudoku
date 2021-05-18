////////         File : Lista.h             ////////
// Arquivo de interface para o TAD Lista          //
// Implementação de Lista por encadamento (lista  //
// simplesmente encadeada) incluindo o tratamento //
// de excecoes.                                   //   
// Atualizado em 15/04/14 por Marcus V. Andrade   //
////////                                    ////////

#ifndef Lista_H__
#define Lista_H__ 

#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;

#include <exception>
#include <string.h>
using std::exception;

// Classe definida para tratar exceções nas operações 

class ErroLista {
private:
    char msg[100];
public:

    ErroLista(const char *s) {
        strcpy(msg, s);
    }

    char *what() {
        return msg;
    }
};

template <class TipoItem>
class Lista {    
template <class T2>
friend ostream& operator<< (ostream &, const Lista<T2> &);
 

public:
    // Inclui a definicao da classe Nodo  
#include "Nodo.h"

    // Referencia a um componente da lista 
    // Na implementação por encadeamento, esta referencia é um apontador 
    // para a área de memória que armazena o nodo contendo um item
    typedef Nodo * RefLComp;

    Lista(); // construtor de Lista vazia
    Lista(const Lista& l); // construtor de Cópia

    Lista& operator=(const Lista &l); // sobrecarga do operador de atribuição

    RefLComp primeiro() const throw (ErroLista); // referencia para o primeiro nodo da lista
    RefLComp ultimo() const throw (ErroLista); // referencia para o ultimo nodo da lista
    RefLComp n_esimo(int n) const throw (ErroLista); // referencia para o n-esimo nodo
    int posicao(RefLComp p) const throw (ErroLista); // posicao na lista do nodo referenciado por p

    void insereOrdenado(TipoItem it);

    // retorna uma referência para o nodo tal que item == it
    RefLComp procura(TipoItem it) const throw (ErroLista);
    
    bool procura_bol(TipoItem it) const;

    // retorna uma referencia para o item armazenado no nodo referenciado por p
    TipoItem& recupera(RefLComp p) const throw (ErroLista);

    // insere o item it após o nodo referenciado por p. Caso não seja 
    // possivel inserir, lança uma exceção				
    void insere(TipoItem it, RefLComp p) throw (ErroLista);

    //insere o item it ordenado na lista
    //void insereOrdenado(TipoItem it);
    
    // insere o item it na primeira posicao.
    // Caso não seja possivel inserir, lança uma exceção
    void insere(TipoItem it) throw (ErroLista);
    void insereFinal(TipoItem it);
    // remove o nodo referenciado por p
    // Caso não seja possivel remover, lança uma exceção
    void remove(RefLComp p) throw (ErroLista);

    // retorna uma referência para o nodo posterior àquele referenciado por p
    RefLComp proximo(RefLComp p) const throw (ErroLista);

    // retorna uma referência para o nodo anterior àquele referenciado por p
    RefLComp anterior(RefLComp p) const throw (ErroLista);

    unsigned int tamanho() const; // número de nodos na lista
    void imprime() const; // imprime os itens da lista
    bool EstaVazia() const; // retorna verdadeiro se a lista esta vazia
    ~Lista(); // destrutor de Lista

private:
    RefLComp head;

    // Funcoes privadas

    void DesalocaLista();

    void CopiaLista(const Lista<TipoItem> &);
};


////////////////////////
// Funções públicas
////////////////////////

/*template<class TipoItem>
void Lista<TipoItem>::insereOrdenado(TipoItem it) {
    RefLComp q, p = head;
    if (EstaVazia() || p->item > it)
        insere(it);
    else {
        while (p && it > p->item) {
            q = p;
            p = p->prox;
        }
        if ((p && p->item != it) || !p)
            insere(it, q);
    }
}//*/

template<class TipoItem>
void Lista<TipoItem>::insereOrdenado(TipoItem it) {
    RefLComp q, p = head;
    if (EstaVazia() || p->item > it)
        insere(it);
    else {
        while (p && it > p->item) {
            q = p;
            p = p->prox;
        }
        if ((p && p->item != it) || !p)
            insere(it, q);
    }
}

template <class TipoItem>
Lista<TipoItem>::Lista() {
    head = NULL;
}

template <class TipoItem>
Lista<TipoItem>::Lista(const Lista &l) {
    CopiaLista(l);
}

template <class TipoItem>
Lista<TipoItem>& Lista<TipoItem>::operator=(const Lista<TipoItem> &l) {
    if (this != &l) {
        DesalocaLista();
        CopiaLista(l);
    }
    return *this;
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::primeiro() const throw (ErroLista) {
    if (!head)
        throw ErroLista("***EM PRIMEIRO: Lista Vazia***");
    return head;
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::ultimo() const throw (ErroLista) {
    RefLComp p = head;
    if (!p) // lista vazia
        throw ErroLista("***EM ULTIMO: Lista Vazia***");
    while (p->prox)
        p = p->prox;
    return (p);
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::n_esimo(int n) const throw (ErroLista) {
    RefLComp p = head;
    int j;
    if (p == NULL) // Lista varzia
        throw ErroLista("***EM N_ESIMO: Lista Vazia***");

    j = 1;
    while (p->prox && j < n) {
        p = p->prox;
        j++;
    }
    if (j == n)
        return p;
    else // posicao invalida
        throw ErroLista("***EM N_ESIMO: Posicao invalida***");
}

template <class TipoItem>
int Lista<TipoItem>::posicao(RefLComp p) const throw (ErroLista) {
    if (!p)
        throw ErroLista("***EM POSICAO: Referencia invalida***");

    RefLComp tmp;
    int i = 1;

    tmp = head;
    while (tmp && tmp != p) {
        tmp = tmp->prox;
        i++;
    }

    if (tmp == p)
        return i;
    else
        throw ErroLista("***EM POSICAO: Referencia invalida***");
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::procura(TipoItem it) const throw (ErroLista) {
    for (RefLComp p = head; p != NULL; p = p->prox)
        if (p->item == it)
            return (p);

    throw ErroLista("***EM PROCURA: Elemento nao existe***");
}

template <class TipoItem>
bool Lista<TipoItem>::procura_bol(TipoItem it) const {
    for (RefLComp p = head; p != NULL; p = p->prox)
        if (p->item == it)
            return true;
    return false;
}

template <class TipoItem>
TipoItem& Lista<TipoItem>::recupera(RefLComp p) const throw (ErroLista) {
    if (!p)
        throw ErroLista("***EM RECUPERA: Referencia Invalida***");

    return p->item;
}

template <class TipoItem>
void Lista<TipoItem>::insere(TipoItem it) throw (ErroLista) {
    RefLComp tmp = new Nodo(it, head);
    if (tmp)
        head = tmp;
    else
        throw ErroLista("***EM INSERE: Erro ***");
}

template <class TipoItem>
void Lista<TipoItem>::insere(TipoItem it, RefLComp p) throw (ErroLista) {
    RefLComp tmp = new Nodo(it, p->prox);
    if (tmp) {
        p->prox = tmp;
    } else
        throw ErroLista("***EM INSERE: Erro ***");
}

template <class TipoItem>
void Lista<TipoItem>::insereFinal(TipoItem it) {
    if(head == NULL)
        insere(it);
    else(insere(it,ultimo()));
}

template <class TipoItem>
void Lista<TipoItem>::remove(RefLComp p) throw (ErroLista) {
    if (!p)
        throw ErroLista("***EM REMOVE: Referencia invalida***");

    RefLComp tmp;
    if (p == head) { // remove o primeiro componente
        tmp = head;
        head = head->prox;
        delete(tmp);
    }
    else {
        tmp = head;
        while (tmp->prox != p)
            tmp = tmp->prox;
        tmp->prox = p->prox;
        delete(p);
    }
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::proximo(RefLComp p) const throw (ErroLista) {
    if (p && p->prox != NULL)
        return p->prox;
    else
        throw ErroLista("***EM PROXIMO: Referencia invalida***");
}

template <class TipoItem>
typename Lista<TipoItem>::RefLComp Lista<TipoItem>::anterior(RefLComp p) const throw (ErroLista) {
    RefLComp tmp;
    if (p && p != head) {
        tmp = head;
        while (tmp->prox != p)
            tmp = tmp->prox;
        return (tmp);
    } else
        throw ErroLista("***EM ANTERIOR: Referencia invalida***");
}

template <class TipoItem>
unsigned int Lista<TipoItem>::tamanho() const {
    int count = 0;
    for (RefLComp p = head; p; p = p->prox)
        count++;
    return (count);
}

template <class TipoItem>
ostream& operator<< (ostream &fout, const Lista<TipoItem> & l) {
    fout << "";
    typename Lista<TipoItem>::RefLComp p = l.head;
    while (p) {
        fout << l.recupera(p);
        if (p != l.ultimo()) {
            cout << "";
            p = l.proximo(p);
        }
        else 
            p = NULL; 
    }
    fout << "\n";
    return fout;
}

template <class TipoItem>
void Lista<TipoItem>::imprime() const {
    cout << (*this);
}

template <class TipoItem>
bool Lista<TipoItem>::EstaVazia() const {
    return (head == NULL);
}

template <class TipoItem>
Lista<TipoItem>::~Lista() {
    DesalocaLista();
}


////////////////////////
// Funções internas
////////////////////////

// libera o espaço reservado para os componentes da lista 

template <class TipoItem>
void Lista<TipoItem>::DesalocaLista() {
    RefLComp q, p = head;
    while (p) {
        q = p->prox;
        delete p;
        p = q;
    }
    head = NULL;
}

// copia os componentes da lista vl 

template <class TipoItem>
void Lista<TipoItem>::CopiaLista(const Lista<TipoItem>& vl) {
    if (vl.head) { // se a lista vl não está vazia
        RefLComp p, q;
        p = vl.head;
        head = new Nodo(p->item, NULL);
        p = p->prox;
        q = head;
        while (p) {
            q->prox = new Nodo(p->item, NULL);
            p = p->prox;
            q = q->prox;
        }
    } else head = NULL;
}

#endif