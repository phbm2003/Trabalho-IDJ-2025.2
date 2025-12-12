#include "Game.h"
#include "TitleState.h"

using namespace std;

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();
    TitleState* state = new TitleState();
    game.Push(state);
    game.run();
    return 0;
}
