#include "carta.h"

string carta::naipe_to_string(){
    string naipesString[4]{"Copas", "Ouros", "Paus", "Espadas" };

    return naipesString[(int)naipe];
}

void carta::imprimeCorpoComNaipe(int pos){
    cout << ("  |.");
    printSuit(naipe);
    cout << ("..|");
}

string carta::valorToString(){
    switch (valor) {
        case 1:
            return "A";
        case 11:
            return "J";
        case 12:
            return "Q";
        case 13:
            return "K";
        default:
            return to_string(valor);
    }
}

void carta::imprimeCorpoComValorInicio(){
    if(valor == 10) cout << ("  |") << to_string(valor) << ("..|");
    else cout << ("  |") << valorToString() << ("...|");
}

void carta::imprimeCorpoComValorFinal(){
    if(valor == 10) cout << ("  |..") + to_string(valor) + ("|");
    else cout << ("  |...") + valorToString() + ("|");
}

void carta::imprimirCarta(){
    cout << endl;
    imprimeCorpoComValorInicio();
    cout << endl;
    imprimeCorpoComNaipe(0);
    cout << endl;
    imprimeCorpoComValorFinal();
    cout << endl;
}