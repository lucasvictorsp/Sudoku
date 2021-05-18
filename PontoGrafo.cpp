/* 
 * File:   PontoGrafo.cpp
 * Author: Lucas Victo
 * 
 * Created on 7 de Junho de 2015, 10:19
 */

#include "PontoGrafo.h"

PontoGrafo::PontoGrafo(){
	this->linha = -1;
	this->coluna = -1;
	this->nCandidatos = 9;
	this->dominio[0] = -1;
	for(int i = 1; i < TAMDOMINIO; i++){
		this->dominio[i] = i;
	}
}
PontoGrafo::PontoGrafo(const PontoGrafo& p){
	this->linha = p.linha;
	this->coluna = p.coluna;
	this->nCandidatos = p.nCandidatos;
	for(int i = 0; i < TAMDOMINIO; i++){
		this->dominio[i] = p.dominio[i];
	}
}

int PontoGrafo::getLinha() const{
	return (this->linha);
}

int PontoGrafo::getColuna() const{
	return (this->coluna);
}

int PontoGrafo::getNCandidatos() const{
	return (this->nCandidatos);
}

int PontoGrafo::getPosicaoDominio(int pos)  const{
	return (this->dominio[pos]);
}

void PontoGrafo::PontoGrafo::setLinha(int nl){
	this->linha = nl;
}

void PontoGrafo::PontoGrafo::setColuna(int nc){
	this->coluna = nc;
}

void PontoGrafo::PontoGrafo::setNCandidatos(int quant){
	this->nCandidatos = quant;
}

void PontoGrafo::PontoGrafo::setPosicaoDominio(int i, int elem){
	if((i > 0) && (i <= 9) && (elem == -1) && (this->getPosicaoDominio(i) != -1) && (this->getNCandidatos() > 0)){
		this->dominio[i] = elem;
		this->setNCandidatos(this->getNCandidatos() - 1);
	}
}

void PontoGrafo::PontoGrafo::setPosicaoDominio(int elem){
	if(this->getNCandidatos() > 1){
		if(elem > 0 && elem <= 9){
			for(int i = 1; i < TAMDOMINIO; i++){
				if((i != elem) && (this->getPosicaoDominio(i) != -1)){
					this->setPosicaoDominio(i, -1);
				}
			}
			this->setNCandidatos(1);
		}
	}
}

bool PontoGrafo::verificaDominioIgual(const PontoGrafo & p){

}

int PontoGrafo::retornaValorSudoku(){
	if(this->getNCandidatos() == 1){
		for(int i = 1; i < TAMDOMINIO; i++){
			if(this->getPosicaoDominio(i) != -1){
				return (this->getPosicaoDominio(i));
			}
		}
	} else{
		cerr << "EROOOOOOOOOO não é possivel retorna valor sudoku.";
	}
}

void PontoGrafo::zeraPontoGrafo(){

}

bool PontoGrafo::operator==(const PontoGrafo & p){
	if(this->getLinha() == p.getLinha() && this->getColuna() == p.getColuna()){
		return true;
	}

	return false;
}

bool PontoGrafo::operator!=(const PontoGrafo & p){
	/*if(this->getLinha() != p.getLinha() || this->getColuna() != p.getColuna()){
		return true;
	}

	return false;//*/
	return *this==p;
}

bool PontoGrafo::operator>(const PontoGrafo & p){
	if(this->getNCandidatos() >= p.getNCandidatos()){
		return true;
	}
	return false;

}

PontoGrafo& PontoGrafo::operator=(const PontoGrafo & p){
	if(this != & p){
		this->linha = p.linha;
		this->coluna = p.coluna;
		this->nCandidatos = p.nCandidatos;
		for(int i = 1; i < TAMDOMINIO; i++){
			this->dominio[i] = p.dominio[i];
		}
	}

	return *this;
}

ostream& operator<<(ostream & os , const PontoGrafo & p){
	os << "Linha: " << p.getLinha() << ", Cluna: " << p.getColuna() << ", nCandidatos: " << p.getNCandidatos() << '\n';
	for(int i = 1; i < TAMDOMINIO; i++){
		os << p.getPosicaoDominio(i) << ' ';
	}
	os << "\n\n";
}

PontoGrafo::~PontoGrafo(){
	
}