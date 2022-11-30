#ifndef PDS2TP___PIFE_NAIPES_H
#define PDS2TP___PIFE_NAIPES_H

#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"

#include <string>
#include <fcntl.h>
#include <iostream>

using namespace std;

enum class Naipe { Copas, Ouros, Paus, Espadas };

void printSuit(Naipe suitToSelect);

#endif //PDS2TP___PIFE_NAIPES_H
