/* 
 * File:   PontoGrafo.h
 * Author: Lucas Victor
 *
 * Created on 7 de Junho de 2015, 10:19
 */

#ifndef PONTOGRAFO_H
#define	PONTOGRAFO_H

#define TAMDOMINIO 10

#include <iostream>

using std::ostream;
using std::cerr;

class PontoGrafo {
    friend ostream& operator<<(ostream & , const PontoGrafo & );
	public:
	    PontoGrafo();
	    PontoGrafo(const PontoGrafo& );

	    int getLinha() const;
	    int getColuna() const;
        int getNCandidatos() const;
	    int getPosicaoDominio(int )  const;

	    void setLinha(int );
	    void setColuna(int );
        void setNCandidatos(int );
	    void setPosicaoDominio(int , int );
	    void setPosicaoDominio(int );

	    bool verificaDominioIgual(const PontoGrafo & );
	    int retornaValorSudoku();
	    void zeraPontoGrafo();

	    bool operator==(const PontoGrafo & );
	    bool operator!=(const PontoGrafo & );
	    bool operator>(const PontoGrafo & );
	    PontoGrafo& operator=(const PontoGrafo & );

	    virtual ~PontoGrafo();

	private:
		int linha;
		int coluna;
		int dominio[TAMDOMINIO];
        int nCandidatos;
};

#endif	/* PONTOGRAFO_H */