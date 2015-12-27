/*
    Rails
    ED - 2015/1
    UFSCar - S�o Carlos
*/
#include "RailsGUI.h"

/*
    A vida de um jogo utilizando o Allegro � definida por:
    1. Inicializa��o dos componentes do Allegro
    2. Loop de jogo
    3. Remo��o de todos os componentes criados
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
