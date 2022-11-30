#ifndef PDS2TP___PIFE_PIFE_H
#define PDS2TP___PIFE_PIFE_H

// Definição de sistema operacional. Utilizado pois a função para limpar console é diferente para cada um
// #define LIN // Define o sistema operacional como Linux
#define WIN // Define o sistema operacional como Windows

#include "player.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;

class pife {
public:
    player jogadores[8];
    int jogadorInicial = 0;
    int numJogadores = 0;
    carta baralho[104];
    vector<carta> monte;
    carta descarte;
    bool descartevazia = true;
    void jogarPife();
protected:
    static void espera(int t); // Função para colocar o programa em modo sleep. Apenas para desacelerar a impressão no terminal
    static void limpaTela(); // Função para limpar o console
    void cadastraJogadores(istream &stream_in, ostream &stream_out); //Função para pegar a quantidade e armazenar o nome dos jogadores
    void iniciaBaralho(); // Função para popular as 104 cartas (dois baralhos de 52 cartas) que serão utilizadas no jogo
    void embaralhaCartas(); // Função para reordenar o array baralho aleatoriamente
    void configuraJogo();
    void distribuiMaos();
    void defineOrdemDeJogo();
    int jogaRodada();
    bool validaOpcao(int opcao);
    carta obtemCartaTopo();
    bool validaDescarte(int opcao);

    int obtemOpcao(string opcao);
};


#endif //PDS2TP___PIFE_PIFE_H
