#include "Game.h"

using namespace std;

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.run();
    //game.~Game(); destrutor é chamado automaticamente no fim da execução
    return 0;
}
