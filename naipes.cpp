#include "naipes.h"

void printSuit(Naipe suitToSelect) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    switch ((int)suitToSelect) {
        case 0:
            wcout << HEART;
            break;
        case 1:
            wcout << DIAMOND;
            break;
        case 2:
            wcout << CLUB;
            break;
        case 3:
            wcout << SPADE;
            break;
    }
    _setmode(_fileno(stdout), _O_TEXT);
}