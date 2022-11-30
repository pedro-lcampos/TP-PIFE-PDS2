#ifndef PDS2TP___PIFE_PLAYER_H
#define PDS2TP___PIFE_PLAYER_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "carta.h"

using namespace std;

class player {
public:
    string nome;
    vector<carta> mao;
    void iniciaMao(carta *baralho, int inicio); // Função que recebe um vetor de cartas e as adiciona à mao
    bool maoVencedora(); // Função que valida se é possível vencer com esta mão
    void imprimeMao();
private:
    bool calculaSubset(vector<carta> *combinacao, bool *indisponiveis); // Função que calcula todos as combinações possíveis das cartas na mão
    bool calculaVitoria(vector<carta> *combinacao); // Função que verifica se uma determinada mao de cartas é uma mao vitoriosa
    bool setValido(vector<carta> *combinacao, int inicio); // Função que verifica se um determinado set de cartas é um set válido
};


#endif //PDS2TP___PIFE_PLAYER_H
