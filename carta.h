#ifndef PDS2TP___PIFE_CARTA_H
#define PDS2TP___PIFE_CARTA_H

#include <string>
#include "naipes.h"

using namespace std;

class carta {
public:
    int valor = 0; // 1 a 13
    Naipe naipe = static_cast<Naipe>(0); // 0 - copas; 1 - ouros; 2 - paus; 3 - espadas
    string naipe_to_string();

    void imprimeCorpoComValorInicio();
    void imprimeCorpoComValorFinal();
    void imprimeCorpoComNaipe(int pos);
    void imprimirCarta();
    string valorToString();
};


#endif //PDS2TP___PIFE_CARTA_H
