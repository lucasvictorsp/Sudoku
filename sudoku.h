/* 
 * File:   sudoku.h
 * Author: DPIUFV
 *
 * Created on 31 de Maio de 2015, 16:26
 */

#ifndef SUDOKU_H
#define	SUDOKU_H

#define LINHA 9
#define COLUNA 9
#define SUBQUADRANTELINHA 3
 #define SUDQUADRANTECOLUNA 3


#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Sudoku {
    friend ostream& operator<<(ostream & , const Sudoku & );
    public:
        Sudoku();
        Sudoku(const Sudoku & );
        
        void ZeraSudoku( );
        
        int getPosicao(int , int ) const;
        
        void setPosicao(int , int , int );
        
        bool sudokuCompleto();
        void imprime();
        
        bool operator==(const Sudoku & );
        bool operator!=(const Sudoku & );
        Sudoku& operator=(const Sudoku & );
        
        virtual ~Sudoku();
    private:
        int sudoku[LINHA][COLUNA];

};

#endif	/* SUDOKU_H */