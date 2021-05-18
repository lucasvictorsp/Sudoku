/* 
 * File:   Main.cpp
 * Author: Lucas Victor Silva Pereira
 *
 * Created on 07 de junho de 2015, 09:23
 */

#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

#include "sudoku.h"
#include "Lista.h"
#include "PontoGrafo.h"


using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;


#define MAPS "tabuleiros/"


void leArquivo(Sudoku & , string);


void enumeraCandidatos(Sudoku & , int , int , int [], int & );

void Backtracking(Sudoku & );



bool ac3(Sudoku & , int , int , PontoGrafo [][COLUNA]);
bool ac3(Sudoku & , PontoGrafo [][COLUNA]);

void Backtracking_AC3(Sudoku & , PontoGrafo [][COLUNA]);

void Backtracking_AC3Start(Sudoku & , PontoGrafo [][COLUNA]);


bool ac3ComHeuristica(Sudoku & , PontoGrafo [][COLUNA]);
bool ac3ComHeuristica(Sudoku & , int , int , PontoGrafo [][COLUNA]);

void Backtracking_AC3Heuristica(Sudoku & ,  PontoGrafo [][COLUNA]);

void Backtracking_AC3HeuristicaStart(Sudoku & ,  PontoGrafo [][COLUNA]);


bool acabou;

unsigned long long recursaoTotal = 0;
unsigned long long recursaoParacial;

 Lista<PontoGrafo> menorDominio;

int main(){
    clock_t time1, time2, time_diff;

    string nomeArquivo;
    int escolheSudoku, selecionaBactracking;
    cout << "Qual sudoku (nivel/fase) deseja verifcar a solucao (Digite o nome do arquivo sem a extensao): ";
    cin >> nomeArquivo;

    Sudoku sudo[95];
    nomeArquivo = MAPS + nomeArquivo;
    leArquivo(sudo[0], nomeArquivo);
    bool notOK;
    do{
        notOK = false;
        cout << "Deseja resolver o sudoku por qual metodo (Backtracking = 1, Backtracking_AC3 = 2 e Backtracking_AC3Heuristica = 3): ";
        cin >> selecionaBactracking;

        switch(selecionaBactracking){
            case 1:
            {
                acabou = false;
                recursaoParacial = 0;
                cout << "Backtracking:\n";
                time1 = clock() / (CLOCKS_PER_SEC / 1000); 
                Backtracking(sudo[0]);
                time2 = clock() / (CLOCKS_PER_SEC / 1000);
                time_diff = time2 - time1;
                cout << "Tempo de execução do Backtracking eh: " << time_diff << " ms";
                cout << "\nNumero de recursões do Backtracking: " << recursaoParacial << "\n" << endl;
                break;
            }
            case 2:
            {
                PontoGrafo copiaSudoku[LINHA][COLUNA];
                for(int linha = 0; linha < LINHA; linha++){
                    for(int coluna = 0; coluna < COLUNA; coluna++){
                        copiaSudoku[linha][coluna].setLinha(linha);
                        copiaSudoku[linha][coluna].setColuna(coluna);
                        if(sudo[0].getPosicao(linha, coluna) != 0){
                            copiaSudoku[linha][coluna].setPosicaoDominio(sudo[0].getPosicao(linha, coluna));
                        }
                    }
                }

                acabou = false;
                recursaoParacial = 0;
                cout << "Backtracking_AC3:\n";
                time1 = clock() / (CLOCKS_PER_SEC / 1000); 
                Backtracking_AC3Start(sudo[0], copiaSudoku);
                time2 = clock() / (CLOCKS_PER_SEC / 1000);
                time_diff = time2 - time1;
                cout << "Tempo de execução do Backtracking_AC3 eh: " << time_diff << " ms";
                cout << "\nNumero de recursões do Backtracking_AC3: " << recursaoParacial << "\n" << endl;
                break;
            }
            case 3:
            {
                PontoGrafo copiaSudoku[LINHA][COLUNA];
                for(int linha = 0; linha < LINHA; linha++){
                    for(int coluna = 0; coluna < COLUNA; coluna++){
                        copiaSudoku[linha][coluna].setLinha(linha);
                        copiaSudoku[linha][coluna].setColuna(coluna);
                        if(sudo[0].getPosicao(linha, coluna) != 0){
                            copiaSudoku[linha][coluna].setPosicaoDominio(sudo[0].getPosicao(linha, coluna));
                        }
                    }
                } 

                acabou = false;
                recursaoParacial = 0;
                cout << "Backtracking_AC3Heuristica:\n";
                time1 = clock() / (CLOCKS_PER_SEC / 1000); 
                Backtracking_AC3HeuristicaStart(sudo[0], copiaSudoku);
                time2 = clock() / (CLOCKS_PER_SEC / 1000);
                time_diff = time2 - time1;
                cout << "Tempo de execução do Backtracking_AC3Heuristica eh: " << time_diff << " ms";
                cout << "\nNumero de recursões do Backtracking_AC3Heuristica: " << recursaoParacial << "\n" << endl;
                break;
            }
            default:
            cout << "Erro. Por favor escolha uma opcao valida.\n";
            notOK = true;
        }
    } while(notOK);

    return 0;
}

void leArquivo(Sudoku &sudo, string nomeArquivo){
    //string arqEntrada;
    //cout << "Digite o nome do arquivo sudoku: ";
    //cin >> arqEntrada;
    //arqEntrada += ".txt";
    nomeArquivo += ".txt";

    ifstream arq; //cria uma variavel do tipo ifstream para recebe um arquivo de leitura
    arq.open(nomeArquivo.c_str(), ios::in); //abre o arquivo com o nome "arqMapa"
    if (arq.fail()) { //verifica se a abertura foi feita corretamente, caso contrario ele apresenta uma mensagem...
        cerr << "Falha ao abrir o arquivo.\nPrograma Abortado.\n"; //de erro na tela e returna 1 finaliando o programa.
        exit(1);
    }

    int auxInteiro, linha = 0, coluna;
    while(arq >> auxInteiro){
        if(coluna == (TAMDOMINIO) - 1){
            coluna = 0;
            linha++;
        }
        sudo.setPosicao(linha, coluna, auxInteiro);
        coluna++;
    }
    arq.close();
}

void enumeraCandidatos(Sudoku &solucao, int lin, int col, int c[], int &nCandidatos){
    int auxCandidato[10] = {0};
    auxCandidato[0] = -1; //Posição invalidada.

    for(int i = 0; i < LINHA; i++){
        auxCandidato[solucao.getPosicao(i, col)] = solucao.getPosicao(i, col);
    }

    for(int i = 0; i < COLUNA; i++){
        auxCandidato[solucao.getPosicao(lin, i)] = solucao.getPosicao(lin, i);
    }

    int auxQuadranteLinha, auxQuadranteColuna;
    auxQuadranteLinha = lin / 3;
    auxQuadranteColuna = col / 3;
    
    auxQuadranteLinha++;
    auxQuadranteColuna++;

    for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
        for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
            auxCandidato[solucao.getPosicao(linha, coluna)] = solucao.getPosicao(linha, coluna);
        }
    }

    nCandidatos = 0;
    for(int i = 1, k = 0; i < 10; i++){
        if(auxCandidato[i] == 0){
            c[k] = i;
            k++;
            nCandidatos++;
        }
    }
}

void Backtracking(Sudoku & solucao){
    recursaoParacial++;
    recursaoTotal++;
    int c[TAMDOMINIO];
    int nCandidatos; // Contador de candidatos
    Sudoku auxPossivelSolucao;
    bool andar = false;
    int lin, col;

    if (solucao.sudokuCompleto()){
        cout << solucao;
        acabou = true;
    } else {    
        for(int linha = 0; linha < LINHA; linha++){
            for(int coluna = 0; coluna < COLUNA; coluna++){
                if(solucao.getPosicao(linha, coluna) == 0){
                    andar = true;
                    lin = linha;
                    col = coluna;
                    break;
                }
            }
            if(andar){
                break;
            }
        }

        for(int linha = 0; linha < LINHA; linha++){
            for(int coluna = 0; coluna < COLUNA; coluna++){
                auxPossivelSolucao.setPosicao(linha, coluna, solucao.getPosicao(linha, coluna));
            }
        }

        enumeraCandidatos(solucao, lin, col, c, nCandidatos);

        for (int i = 0; i < nCandidatos; i++) {
            solucao.setPosicao(lin, col, c[i]);

            Backtracking(solucao);

            if (acabou){
                return;
            }

            for(int linha = 0; linha < LINHA; linha++){
                for(int coluna = 0; coluna < COLUNA; coluna++){
                    solucao.setPosicao(linha, coluna, auxPossivelSolucao.getPosicao(linha, coluna));
                }
            }
        }
    }
}


bool ac3(Sudoku & solucao, PontoGrafo copiaSudoku[][COLUNA]){ 
    int auxQuadranteLinha, auxQuadranteColuna;
    Lista<PontoGrafo> psr;

    for(int lin = 0; lin < LINHA; lin++){
        for(int col = 0; col < COLUNA; col++){
            if(solucao.getPosicao(lin, col) == 0){
                continue;
            }

            for(int i = 0; i < LINHA; i++){ //for(int coluna = 0; coluna < COLUNA; coluna++){
                if(copiaSudoku[i][col].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][col])){
                        psr.insereFinal(copiaSudoku[i][col]);
                    }
                }

                if(copiaSudoku[lin][i].getNCandidatos() > 1){
                    if(!(psr.procura_bol(copiaSudoku[lin][i]))){
                        psr.insereFinal(copiaSudoku[lin][i]);
                    }
                }
            }

            auxQuadranteLinha = lin / 3;
            auxQuadranteColuna = col / 3;
            auxQuadranteLinha++;
            auxQuadranteColuna++;
            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }
    }

    PontoGrafo aux;
    int qntNCandidatos;
    while(!psr.EstaVazia()){
        aux = psr.recupera(psr.primeiro());
        qntNCandidatos = aux.getNCandidatos();

        for(int i = 0; i < LINHA; i++){
            if(solucao.getPosicao(i, aux.getColuna()) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(i, aux.getColuna()), -1);
            }

            if(solucao.getPosicao(aux.getLinha(), i) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(aux.getLinha(), i), -1);
            }
        }

        auxQuadranteLinha = aux.getLinha() / 3;
        auxQuadranteColuna = aux.getColuna() / 3;
        auxQuadranteLinha++;
        auxQuadranteColuna++;
        for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
            for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                if(solucao.getPosicao(linha, coluna) != 0){
                    aux.setPosicaoDominio(solucao.getPosicao(linha, coluna), -1);
                }
            }
        }

        copiaSudoku[aux.getLinha()][aux.getColuna()] = aux;

        if(aux.getNCandidatos() == 1){
            solucao.setPosicao(aux.getLinha(), aux.getColuna(), aux.retornaValorSudoku());
            
            for(int i = 0; i < LINHA; i++){
                if(copiaSudoku[i][aux.getColuna()].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][aux.getColuna()])){
                        psr.insereFinal(copiaSudoku[i][aux.getColuna()]);
                    }
                }

                if(copiaSudoku[aux.getLinha()][i].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[aux.getLinha()][i])){
                        psr.insereFinal(copiaSudoku[aux.getLinha()][i]);
                    }
                }
            }

            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }

        if(aux.getNCandidatos() == 0){
            return false;
        }

        psr.remove(psr.primeiro());
    }

    return true;
}

bool ac3(Sudoku & solucao, int lin, int col, PontoGrafo copiaSudoku[][COLUNA]){ 
    int auxQuadranteLinha, auxQuadranteColuna;
    Lista<PontoGrafo> psr;

    for(int i = 0; i < LINHA; i++){ //for(int coluna = 0; coluna < COLUNA; coluna++){
        if(copiaSudoku[i][col].getNCandidatos() > 1){
            if(!psr.procura_bol(copiaSudoku[i][col])){
                psr.insereFinal(copiaSudoku[i][col]);
            }
        }

        if(copiaSudoku[lin][i].getNCandidatos() > 1){
            if(!(psr.procura_bol(copiaSudoku[lin][i]))){
                psr.insereFinal(copiaSudoku[lin][i]);
            }
        }
    }

    auxQuadranteLinha = lin / 3;
    auxQuadranteColuna = col / 3;
    auxQuadranteLinha++;
    auxQuadranteColuna++;
    for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
        for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
            if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                    psr.insereFinal(copiaSudoku[linha][coluna]);
                }
            }
        }
    }

    PontoGrafo aux;
    while(!psr.EstaVazia()){
        aux = psr.recupera(psr.primeiro());

        for(int i = 0; i < LINHA; i++){
            if(solucao.getPosicao(i, aux.getColuna()) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(i, aux.getColuna()), -1);
            }

            if(solucao.getPosicao(aux.getLinha(), i) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(aux.getLinha(), i), -1);
            }
        }

        auxQuadranteLinha = aux.getLinha() / 3;
        auxQuadranteColuna = aux.getColuna() / 3;
        auxQuadranteLinha++;
        auxQuadranteColuna++;
        for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
            for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                if(solucao.getPosicao(linha, coluna) != 0){
                    aux.setPosicaoDominio(solucao.getPosicao(linha, coluna), -1);
                }
            }
        }

        copiaSudoku[aux.getLinha()][aux.getColuna()] = aux;

        if(aux.getNCandidatos() == 1){
            solucao.setPosicao(aux.getLinha(), aux.getColuna(), aux.retornaValorSudoku());
            
            for(int i = 0; i < LINHA; i++){
                if(copiaSudoku[i][aux.getColuna()].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][aux.getColuna()])){
                        psr.insereFinal(copiaSudoku[i][aux.getColuna()]);
                    }
                }

                if(copiaSudoku[aux.getLinha()][i].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[aux.getLinha()][i])){
                        psr.insereFinal(copiaSudoku[aux.getLinha()][i]);
                    }
                }
            }

            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }

        if(aux.getNCandidatos() == 0){
            return false;
        }

        psr.remove(psr.primeiro());
    }

    return true;
}

void Backtracking_AC3(Sudoku & solucao,  PontoGrafo copiaSudoku [][COLUNA]){
    recursaoParacial++;
    recursaoTotal++;
    int c[TAMDOMINIO];
    int nCandidatos; // Contador de candidatos
    int linAux, colAux;
    Sudoku auxPossivelSolucao;
    bool andar = false;
    PontoGrafo auxCopiaGrafo[LINHA][COLUNA];
    int lin,col;

    if (solucao.sudokuCompleto()){
        cout << solucao;
        acabou = true;
    } else {
        for(int linha = 0; linha < LINHA; linha++){
            for(int coluna = 0; coluna < COLUNA; coluna++){
                if(solucao.getPosicao(linha, coluna) == 0){
                    andar = true;
                    lin = linha;
                    col = coluna;
                    break;
                }
            }
            if(andar){
                break;
            }
        }

        for(int linha = 0; linha < LINHA; linha++){
            for(int coluna = 0; coluna < COLUNA; coluna++){
                auxPossivelSolucao.setPosicao(linha, coluna, solucao.getPosicao(linha, coluna));
                auxCopiaGrafo[linha][coluna] = copiaSudoku[linha][coluna];
            }
        }

        enumeraCandidatos(solucao, lin, col, c, nCandidatos);

        linAux = lin;
        colAux = col;

        for (int i = 0; i < nCandidatos; i++) {
            solucao.setPosicao(linAux, colAux, c[i]);
            copiaSudoku[linAux][colAux].setPosicaoDominio(c[i]);
            if(ac3(solucao, lin, col, copiaSudoku)){
                Backtracking_AC3(solucao, copiaSudoku);
            }

            if (acabou){
                return;
            }

            for(int linha = 0; linha < LINHA; linha++){
                for(int coluna = 0; coluna < COLUNA; coluna++){
                    solucao.setPosicao(linha, coluna, auxPossivelSolucao.getPosicao(linha, coluna));
                    copiaSudoku[linha][coluna] = auxCopiaGrafo[linha][coluna];
                }
            }
        }
    }
}

void Backtracking_AC3Start(Sudoku & solucao,  PontoGrafo copiaSudoku [][COLUNA]){
    recursaoParacial++;
    recursaoTotal++;

    if(ac3(solucao, copiaSudoku)) {
        Backtracking_AC3(solucao, copiaSudoku);
    }

    acabou = true;
}


bool ac3ComHeuristica(Sudoku & solucao, PontoGrafo copiaSudoku[][COLUNA]){ 
    int auxQuadranteLinha, auxQuadranteColuna;
    Lista<PontoGrafo> psr;
    PontoGrafo aux;

    while(!menorDominio.EstaVazia()){
        menorDominio.remove(menorDominio.primeiro());
    }

    for(int lin = 0; lin < LINHA; lin++){
        for(int col = 0; col < COLUNA; col++){
            if(solucao.getPosicao(lin, col) == 0){
                continue;
            }

            for(int i = 0; i < LINHA; i++){ //for(int coluna = 0; coluna < COLUNA; coluna++){
                if(copiaSudoku[i][col].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][col])){
                        psr.insereFinal(copiaSudoku[i][col]);
                    }
                }

                if(copiaSudoku[lin][i].getNCandidatos() > 1){
                    if(!(psr.procura_bol(copiaSudoku[lin][i]))){
                        psr.insereFinal(copiaSudoku[lin][i]);
                    }
                }
            }

            auxQuadranteLinha = lin / 3;
            auxQuadranteColuna = col / 3;
            auxQuadranteLinha++;
            auxQuadranteColuna++;
            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }
    }

    while(!psr.EstaVazia()){
        aux = psr.recupera(psr.primeiro());

        for(int i = 0; i < LINHA; i++){
            if(solucao.getPosicao(i, aux.getColuna()) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(i, aux.getColuna()), -1);
            }

            if(solucao.getPosicao(aux.getLinha(), i) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(aux.getLinha(), i), -1);
            }
        }

        auxQuadranteLinha = aux.getLinha() / 3;
        auxQuadranteColuna = aux.getColuna() / 3;
        auxQuadranteLinha++;
        auxQuadranteColuna++;
        for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
            for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                if(solucao.getPosicao(linha, coluna) != 0){
                    aux.setPosicaoDominio(solucao.getPosicao(linha, coluna), -1);
                }
            }
        }

        copiaSudoku[aux.getLinha()][aux.getColuna()] = aux;

        if(aux.getNCandidatos() == 1){
            solucao.setPosicao(aux.getLinha(), aux.getColuna(), aux.retornaValorSudoku());
            
            for(int i = 0; i < LINHA; i++){
                if(copiaSudoku[i][aux.getColuna()].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][aux.getColuna()])){
                        psr.insereFinal(copiaSudoku[i][aux.getColuna()]);
                    }
                }

                if(copiaSudoku[aux.getLinha()][i].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[aux.getLinha()][i])){
                        psr.insereFinal(copiaSudoku[aux.getLinha()][i]);
                    }
                }
            }

            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }

        if(aux.getNCandidatos() == 0){
            return false;
        }

        psr.remove(psr.primeiro());
    }

    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                menorDominio.insereOrdenado(copiaSudoku[linha][coluna]);
            }
        }
    }

    return true;
}

bool ac3ComHeuristica(Sudoku & solucao, int lin, int col, PontoGrafo copiaSudoku[][COLUNA]){ 
    int auxQuadranteLinha, auxQuadranteColuna;
    Lista<PontoGrafo> psr;
    PontoGrafo aux;

    while(!menorDominio.EstaVazia()){
        menorDominio.remove(menorDominio.primeiro());
    }

    for(int i = 0; i < LINHA; i++){ //for(int coluna = 0; coluna < COLUNA; coluna++){
        if(copiaSudoku[i][col].getNCandidatos() > 1){
            if(!psr.procura_bol(copiaSudoku[i][col])){
                psr.insereFinal(copiaSudoku[i][col]);
            }
        }

        if(copiaSudoku[lin][i].getNCandidatos() > 1){
            if(!(psr.procura_bol(copiaSudoku[lin][i]))){
                psr.insereFinal(copiaSudoku[lin][i]);
            }
        }
    }

    auxQuadranteLinha = lin / 3;
    auxQuadranteColuna = col / 3;
    auxQuadranteLinha++;
    auxQuadranteColuna++;
    for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
        for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
            if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                    psr.insereFinal(copiaSudoku[linha][coluna]);
                }
            }
        }
    }

    while(!psr.EstaVazia()){
        aux = psr.recupera(psr.primeiro());

        for(int i = 0; i < LINHA; i++){
            if(solucao.getPosicao(i, aux.getColuna()) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(i, aux.getColuna()), -1);
            }

            if(solucao.getPosicao(aux.getLinha(), i) != 0){
                aux.setPosicaoDominio(solucao.getPosicao(aux.getLinha(), i), -1);
            }
        }

        auxQuadranteLinha = aux.getLinha() / 3;
        auxQuadranteColuna = aux.getColuna() / 3;
        auxQuadranteLinha++;
        auxQuadranteColuna++;
        for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
            for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                if(solucao.getPosicao(linha, coluna) != 0){
                    aux.setPosicaoDominio(solucao.getPosicao(linha, coluna), -1);
                }
            }
        }

        copiaSudoku[aux.getLinha()][aux.getColuna()] = aux;

        if(aux.getNCandidatos() == 1){
            solucao.setPosicao(aux.getLinha(), aux.getColuna(), aux.retornaValorSudoku());
            
            for(int i = 0; i < LINHA; i++){
                if(copiaSudoku[i][aux.getColuna()].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[i][aux.getColuna()])){
                        psr.insereFinal(copiaSudoku[i][aux.getColuna()]);
                    }
                }

                if(copiaSudoku[aux.getLinha()][i].getNCandidatos() > 1){
                    if(!psr.procura_bol(copiaSudoku[aux.getLinha()][i])){
                        psr.insereFinal(copiaSudoku[aux.getLinha()][i]);
                    }
                }
            }

            for(int linha = ((auxQuadranteLinha * SUBQUADRANTELINHA) - 1); linha > ((auxQuadranteLinha * SUBQUADRANTELINHA) - (SUBQUADRANTELINHA + 1)); linha--){
                for(int coluna = ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - 1); coluna > ((auxQuadranteColuna * SUDQUADRANTECOLUNA) - (SUDQUADRANTECOLUNA + 1)); coluna--){
                    if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                        if(!psr.procura_bol(copiaSudoku[linha][coluna])){
                            psr.insereFinal(copiaSudoku[linha][coluna]);
                        }
                    }
                }
            }
        }

        if(aux.getNCandidatos() == 0){
            return false;
        }

        psr.remove(psr.primeiro());
    }

    for(int linha = 0; linha < LINHA; linha++){
        for(int coluna = 0; coluna < COLUNA; coluna++){
            if(copiaSudoku[linha][coluna].getNCandidatos() > 1){
                menorDominio.insereOrdenado(copiaSudoku[linha][coluna]);
            }
        }
    }

    return true;
}

void Backtracking_AC3Heuristica(Sudoku & solucao,  PontoGrafo copiaSudoku [][COLUNA]){
    recursaoParacial++;
    recursaoTotal++;
    int c[TAMDOMINIO];
    int nCandidatos; // Contador de candidatos
    Sudoku auxPossivelSolucao;
    bool andar = false;
    PontoGrafo auxCopiaGrafo[LINHA][COLUNA];
    int lin,col;
    PontoGrafo aux;

    if (solucao.sudokuCompleto()){
        cout << solucao;
        acabou = true;
    } else {
        aux = menorDominio.recupera(menorDominio.primeiro());
        lin = aux.getLinha();
        col = aux.getColuna();

        for(int linha = 0; linha < LINHA; linha++){
            for(int coluna = 0; coluna < COLUNA; coluna++){
                auxPossivelSolucao.setPosicao(linha, coluna, solucao.getPosicao(linha, coluna));
                auxCopiaGrafo[linha][coluna] = copiaSudoku[linha][coluna];
            }
        }

        enumeraCandidatos(solucao, lin, col, c, nCandidatos);

        for (int i = 0; i < nCandidatos; i++) {
            solucao.setPosicao(lin, col, c[i]);
            copiaSudoku[lin][col].setPosicaoDominio(c[i]);
            if(ac3ComHeuristica(solucao, lin, col, copiaSudoku)){
                Backtracking_AC3Heuristica(solucao, copiaSudoku);
            }

            if (acabou){
                return;
            }

            for(int linha = 0; linha < LINHA; linha++){
                for(int coluna = 0; coluna < COLUNA; coluna++){
                    solucao.setPosicao(linha, coluna, auxPossivelSolucao.getPosicao(linha, coluna));
                    copiaSudoku[linha][coluna] = auxCopiaGrafo[linha][coluna];
                }
            }
        }
    }
}

void Backtracking_AC3HeuristicaStart(Sudoku & solucao,  PontoGrafo copiaSudoku [][COLUNA]){
    recursaoParacial++;
    recursaoTotal++;
    if(ac3ComHeuristica(solucao, copiaSudoku)) {
        Backtracking_AC3Heuristica(solucao, copiaSudoku);
    }

    acabou = true;
}