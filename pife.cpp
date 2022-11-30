#include "pife.h"

// Função para colocar o programa em modo sleep. Apenas para desacelerar a impressão no terminal
void pife::espera(int t){
    this_thread::sleep_for( chrono::seconds (t));
}

// Função para limpar o console
void pife::limpaTela(){

    espera(2);

#ifdef WIN // Caso o Sistema operacional seja windows
    system("CLS");
#endif
#ifdef LIN // Caso o Sistema operacional seja Linux
    system("clear");
#endif

    espera(1);
}

//Função para pegar a quantidade e armazenar o nome dos jogadores
void pife::cadastraJogadores(istream& stream_in, ostream& stream_out){

    cout << "PIFE - CADASTRO DE JOGADORES" << endl;
    espera(1);
    while(numJogadores < 2 || numJogadores > 8){
        cout << endl << "Insira a quantidade de jogadores (entre 2 e 8): ";
        stream_in >> numJogadores;
        if(numJogadores < 2 || numJogadores > 8) stream_out << endl << "Quantidade invalida!" << endl;
    }

    for (int i = 0; i < numJogadores; ++i) {
        cout << endl << "Insira o nome do Jogador " << i + 1 << ": ";
        stream_in >> jogadores[i].nome;
    }

    espera(1);
    cout << endl << "Jogadores cadastrados:" << endl;

    for (int i = 0; i < numJogadores; ++i) {
        cout << i + 1 << " - " << jogadores[i].nome << endl;
    }
}

// Função para popular as 104 cartas (dois baralhos de 52 cartas) que serão utilizadas no jogo
void pife::iniciaBaralho(){
    int pos = 0;

    // Para cada naipe
    for (int i = 0; i < 4; ++i) {
        // E para cada valor de As(1) a Rei(13)
        for (int j = 1; j <= 13; ++j) {
            // Adiciona 2 cartas (pois são 2 baralhos)
            baralho[pos].valor = j;
            baralho[pos].naipe = static_cast<Naipe>(i);
            pos++;
            baralho[pos].valor = j;
            baralho[pos].naipe = static_cast<Naipe>(i);
            pos++;
        }
    }
}

// Função para reordenar o array baralho aleatoriamente
void pife::embaralhaCartas(){

    default_random_engine defEngine((unsigned) time(nullptr)); // Engine geradora de valores aleatórios.
                                                                       // "(unsigned) time(nullptr)" é a seed
    shuffle(&baralho[0], &baralho[104], defEngine); // Função do c++ 17 que reordena um vetor
}

// Função para distribuir as cartas entre os jogadores
void pife::distribuiMaos(){
    int inicio, fim;

    for (int i = 0; i < numJogadores; ++i) {
        inicio = i*9;
        jogadores[i].iniciaMao(baralho, inicio);
    }

    monte.insert(monte.end(), &baralho[inicio + 9], &baralho[104]);
}

// Função que determina o primeiro jogador. O restante será em sequência
void pife::defineOrdemDeJogo(){

    default_random_engine defEngine((unsigned) time(nullptr)); // Engine geradora de valores aleatórios.
    // "(unsigned) time(nullptr)" é a seed

    uniform_int_distribution<int> intDistro(0,(numJogadores-1)); // Distribuição de valores que vamos utilizar
    intDistro(defEngine); // Como nossa seed é fixa, precisamos descartar o primeiro valor pois ele sempre será igual

    jogadorInicial = intDistro(defEngine);
}

// Função para iniciar as configurações do jogo
void pife::configuraJogo(){
    cadastraJogadores(cin, cout);
    iniciaBaralho();
    embaralhaCartas();
    distribuiMaos();
    defineOrdemDeJogo();
}

bool pife::validaOpcao(int opcao){
    switch (opcao) {
        case 1:
            if(monte.empty()) return false;
            return true;
        case 2:
            if(descartevazia) return false;
            return true;
        default:
            return false;
    }
}

int pife::obtemOpcao(string opcao){
    try{
        return stoi(opcao);
    }
    catch (exception &e) {
        return 0;
    }
}

bool pife::validaDescarte(int opcao){
    return (opcao >= 1 && opcao <= 10);
}

// Função que remove a primeira carta do topo do monte e a retorna
carta pife::obtemCartaTopo(){
    carta cartaTopo = monte[0];
    monte.erase(monte.begin());
    return cartaTopo;
}

int pife::jogaRodada(){
    int opcao = 0;
    string leitura;

    cout << endl << "[O jogador " << jogadores[jogadorInicial].nome << " comeca o jogo]" << endl << endl;

    espera(1);

    for (int i = jogadorInicial; i <= numJogadores; ++i) {
        if(i == numJogadores) i = 0;

        limpaTela();

        jogadores[i].imprimeMao();

        if(!descartevazia){
            cout << endl << "[Carta da pilha]" << endl;
            descarte.imprimirCarta();
            cout << endl;
        }

        opcao = 0;
        while(!validaOpcao(opcao)){
            cout << endl << "Escolha sua opcao: " << endl;
            if(!monte.empty()) cout << "1 - Pegar carta do monte" << endl;
            if(!descartevazia) cout << "2 - Pegar carta do descarte" << endl;
            cin >> leitura;
            opcao = obtemOpcao(leitura);
            if(!validaOpcao(opcao)) cout << "Opcao Invalida!" << endl;
        }
        limpaTela();

        if(opcao == 1) jogadores[i].mao.push_back(obtemCartaTopo());
        else jogadores[i].mao.push_back(descarte);

        cout << endl << "[Voce obteve a carta]" << endl;
        jogadores[i].mao[9].imprimirCarta();
        limpaTela();

        jogadores[i].imprimeMao();

        opcao = 0;
        while(!validaDescarte(opcao)){
            cout << endl << "Escolha, entre 1 e 10 qual a posicao da carta que quer descartar: " << endl;
            cin >> leitura;
            opcao = obtemOpcao(leitura);
            if(!validaDescarte(opcao)) cout << "Opcao Invalida!" << endl;
        }

        descarte = jogadores[i].mao[opcao-1];
        descartevazia = false;
        jogadores[i].mao.erase(jogadores[i].mao.begin()+(opcao-1));

        limpaTela();

        cout << endl << "[Voce descartou a carta]" << endl;
        descarte.imprimirCarta();
        limpaTela();

        if(jogadores[i].maoVencedora()){
            jogadores[i].imprimeMao();

            opcao = 0;
            while(opcao != 1 && opcao != 2){
                cout << endl << "Deseja vencer com esta mao?" << endl;
                cout << "1 - Sim" << endl;
                cout << "2 - Nao" << endl;
                cin >> leitura;
                opcao = obtemOpcao(leitura);
                if(opcao != 1 && opcao != 2) cout << "Opcao Invalida!" << endl;
            }
            if(opcao == 1) return i;
        }
    }
    return 0;
}

void pife::jogarPife(){
    string lixo;

    configuraJogo();
    limpaTela();

    int vencedor = jogaRodada();

    cout << endl << "FIM DE JOGO - " << jogadores[vencedor].nome << " VENCEU!!!" << endl << endl;

    cout << "Escreva qualquer coisa para encerrar" << endl;
    cin >> lixo;
}