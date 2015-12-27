/*
    Rails
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "RailsGUI.h"

/*
    A vida de um jogo utilizando o Allegro é definida por:
    1. Inicialização dos componentes do Allegro
    2. Loop de jogo
    3. Remoção de todos os componentes criados
*/
int main(int argc, char **argv)
{
    RailsGUI game;

    game.initAllegro();
    while (game.exitCode() == 0) {
        game.loop();
    }
    game.shutdown();

    return game.exitCode();
}
