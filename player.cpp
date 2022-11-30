#include "player.h"

void player::imprimeMao(){
    cout << endl << "[Vez do Jogador: " << nome << ']' << endl << endl;
    int num = mao.size();

    cout << "    (1)";
    for (int i = 1; i < num; ++i) {
        cout << "     (" << i+1 << ")";
    }
    cout << endl;

    cout << endl;
    for (int i = 0; i < num; ++i) {
        mao[i].imprimeCorpoComValorInicio();
    }
    cout << endl;
    for (int i = 0; i < num; ++i) {
        mao[i].imprimeCorpoComNaipe(i);
    }
    cout << endl;
    for (int i = 0; i < num; ++i) {
        mao[i].imprimeCorpoComValorFinal();
    }
    cout << endl;
}

// Função que recebe um vetor de cartas e as adiciona à mao
void player::iniciaMao(carta* baralho, int inicio){
    mao.insert(mao.end(), &baralho[inicio], &baralho[inicio+9]);
}

// Função que verifica se um determinado set de cartas é um set válido
bool player::setValido(vector<carta> *combinacao, int inicio){
    int fim = inicio + 3;
    bool flag = true;
    set<Naipe> naipes;

    // Verifica sequencia
    Naipe naipeConjunto = (*combinacao)[inicio].naipe;
    for (int i = inicio, j = inicio + 1; i < (fim - 1); ++i, ++j) {
        if((*combinacao)[i].valor >= (*combinacao)[j].valor){ // Se nao for sequencial
            flag = false;
            break;
        }
        if((*combinacao)[j].naipe != naipeConjunto){ // Se nao for o mesmo naipe
            flag = false;
            break;
        }
    }

    if(flag) return true;

    // Verifica trinca
    int valor = (*combinacao)[inicio].valor;
    naipes.insert((*combinacao)[inicio].naipe);
    for (int i = inicio+1; i < fim; ++i) {
        if((*combinacao)[i].valor != valor){ // Trinca deve ser do mesmo valor
            return false;
        }
        naipes.insert((*combinacao)[i].naipe);
    }
    if(naipes.size() == 3) return true; // Trinca deve possuir naipes distintos
    return false;
}

// Função que verifica se uma determinada mao de cartas é uma mao vitoriosa
bool player::calculaVitoria(vector<carta> *combinacao){
    if(!setValido(combinacao, 0)) return false;
    if(!setValido(combinacao, 3)) return false;
    if(!setValido(combinacao, 6)) return false;
    return true;
}

// Função que calcula todos as combinações possíveis das cartas na mão
bool player::calculaSubset(vector<carta> *combinacao, bool *indisponiveis){
    if(combinacao->size() == 9){
        return calculaVitoria(combinacao);
    }

    for (int i = 0; i < 9; ++i) {
        if(!indisponiveis[i]){
            combinacao->push_back(mao[i]);
            indisponiveis[i] = true;
            if(calculaSubset(combinacao, indisponiveis)) return true;
            combinacao->pop_back();
            indisponiveis[i] = false;
        }
    }
    return false;
}

// Função que valida se é possível vencer com esta mão
bool player::maoVencedora(){
    vector<carta> combinacao;
    bool indisponiveis[9] = {};
    return calculaSubset(&combinacao, indisponiveis);
}