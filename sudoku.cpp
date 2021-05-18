/* 
 * File:   sudoku.cpp
 * Author: Lucas Victor Silva Pereira
 * 
 * Created on 31 de Maio de 2015, 16:26
 */

#include "sudoku.h"

Sudoku::Sudoku() {
    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            sudoku[linha][coluna] = 0;
        }
    }
}

Sudoku::Sudoku(const Sudoku& orig) {
    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            sudoku[linha][coluna] = orig.sudoku[linha][coluna];
        }
    }
}

void Sudoku::ZeraSudoku(){
    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            this->setPosicao(linha, coluna, 0);
        }
    }
}

int Sudoku::getPosicao(int lin, int col) const{
    return this->sudoku[lin][col];
}

void Sudoku::setPosicao(int lin, int col, int elem){
    sudoku[lin][col] = elem;
}

bool Sudoku::sudokuCompleto(){
    for(int lin = 0; lin < LINHA; lin++){
        for(int col = 0; col < COLUNA; col++){
            if(this->getPosicao(lin, col) == 0){
                return false;
            }
        }
    }

    return true;
}

void Sudoku::imprime(){
    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            cout << this->getPosicao(linha, coluna);
            if(coluna < (COLUNA - 1)){
                cout << ' ';
            }
        }
        cout << '\n';
    }
}

bool Sudoku::operator==(const Sudoku & s){
    for(int lin = 0; lin < LINHA; lin++){
        for(int col = 0; col < COLUNA; col++){
            if(this->getPosicao(lin, col) != s.getPosicao(lin, col)){
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::operator!=(const Sudoku & s){
    for(int lin = 0; lin < LINHA; lin++){
        for(int col = 0; col < COLUNA; col++){
            if(this->getPosicao(lin, col) != s.getPosicao(lin, col)){
                return true;
            }
        }
    }

    return false;
}

Sudoku& Sudoku::operator=(const Sudoku & s){  
    if(this != & s){
        for(int lin = 0; lin < LINHA; lin++){
            for(int col = 0; col < COLUNA; col++){
                this->setPosicao(lin, col, s.getPosicao(lin, col));
            }
        }
    }
    return *this;
}

ostream& operator<<(ostream &os, const Sudoku & s){
    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            os << s.getPosicao(linha, coluna) << ' ';
        }
        os << '\n';
    }
}

Sudoku::~Sudoku() {

}