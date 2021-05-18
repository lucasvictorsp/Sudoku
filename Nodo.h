
class Nodo { 

friend class Lista<TipoItem>;
    
private:
    TipoItem item;
    Nodo *prox;

    Nodo() { prox = NULL; }

    Nodo (TipoItem a, Nodo *ptr=NULL)  {   // construtor 
	    item = a;
	    prox = ptr;
    }
};
