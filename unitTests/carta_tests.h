#ifndef PDS2TP___PIFE_CARTA_TESTS_H
#define PDS2TP___PIFE_CARTA_TESTS_H
#include "doctest.h"
#include "../carta.h"

TEST_SUITE("Testando a classe carta"){
    TEST_CASE("Testando a funcao naipe_to_string") {
        carta card;

        card.naipe = static_cast<Naipe>(0);
        CHECK((card.naipe_to_string() == "Copas"));

        card.naipe = static_cast<Naipe>(1);
        CHECK((card.naipe_to_string() == "Ouros"));

        card.naipe = static_cast<Naipe>(2);
        CHECK((card.naipe_to_string() == "Paus"));

        card.naipe = static_cast<Naipe>(3);
        CHECK((card.naipe_to_string() == "Espadas"));
    }

    TEST_CASE("Testando a funcao valorToString") {
        carta card;

        card.valor = 1;
        CHECK((card.valorToString() == "A"));

        card.valor = 11;
        CHECK((card.valorToString() == "J"));

        card.valor = 12;
        CHECK((card.valorToString() == "Q"));

        card.valor = 13;
        CHECK((card.valorToString() == "K"));

        card.valor = 8;
        CHECK((card.valorToString() == "8"));

        card.valor = 5;
        CHECK((card.valorToString() == "5"));
    }
}

#endif //PDS2TP___PIFE_CARTA_TESTS_H
