#ifndef PDS2TP___PIFE_PLAYER_TESTS_H
#define PDS2TP___PIFE_PLAYER_TESTS_H

#include "doctest.h"
#include "../player.h"

TEST_SUITE("Testando a classe player"){
    TEST_CASE("Testando a funcao iniciaMao") {
        player jogador;
        carta cards[52];

        int pos = 0;

        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= 13; ++j) {
                cards[pos].valor = j;
                cards[pos].naipe = static_cast<Naipe>(i);
                pos++;
            }
        }

        jogador.iniciaMao(cards, 0);

        for (int i = 0; i < 9; ++i) {
            CHECK((jogador.mao[i].valor == cards[i].valor));
            CHECK((jogador.mao[i].naipe == cards[i].naipe));
        }

        jogador.mao.clear();
        jogador.iniciaMao(cards, 15);

        for (int i = 15, j = 0; i < 24; ++i, j++) {
            CHECK((jogador.mao[j].valor == cards[i].valor));
            CHECK((jogador.mao[j].naipe == cards[i].naipe));
        }
    }

    TEST_CASE("Testando a funcao maoVencedora") {
        player jogador;
        carta baralho[9];

        baralho[0].valor = 10;
        baralho[0].naipe = static_cast<Naipe>(3);
        baralho[1].valor = 3;
        baralho[1].naipe = static_cast<Naipe>(2);
        baralho[2].valor = 4;
        baralho[2].naipe = static_cast<Naipe>(2);
        baralho[3].valor = 10;
        baralho[3].naipe = static_cast<Naipe>(2);
        baralho[4].valor = 5;
        baralho[4].naipe = static_cast<Naipe>(2);
        baralho[5].valor = 1;
        baralho[5].naipe = static_cast<Naipe>(3);
        baralho[6].valor = 1;
        baralho[6].naipe = static_cast<Naipe>(2);
        baralho[7].valor = 10;
        baralho[7].naipe = static_cast<Naipe>(0);
        baralho[8].valor = 1;
        baralho[8].naipe = static_cast<Naipe>(0);

        jogador.iniciaMao(baralho, 0);

        CHECK(jogador.maoVencedora());

        baralho[0].valor = 11;
        baralho[0].naipe = static_cast<Naipe>(3);
        baralho[1].valor = 3;
        baralho[1].naipe = static_cast<Naipe>(2);
        baralho[2].valor = 4;
        baralho[2].naipe = static_cast<Naipe>(2);
        baralho[3].valor = 10;
        baralho[3].naipe = static_cast<Naipe>(2);
        baralho[4].valor = 5;
        baralho[4].naipe = static_cast<Naipe>(2);
        baralho[5].valor = 1;
        baralho[5].naipe = static_cast<Naipe>(3);
        baralho[6].valor = 1;
        baralho[6].naipe = static_cast<Naipe>(2);
        baralho[7].valor = 10;
        baralho[7].naipe = static_cast<Naipe>(0);
        baralho[8].valor = 1;
        baralho[8].naipe = static_cast<Naipe>(0);

        jogador.mao.clear();
        jogador.iniciaMao(baralho, 0);

        CHECK(!jogador.maoVencedora());
    }
}

#endif //PDS2TP___PIFE_PLAYER_TESTS_H
