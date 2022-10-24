#include <game.h>

int main()
{
    InitWindow(1280, 720, "Blackjack");
    InitAudioDevice();
    SetTargetFPS(60);
    Image windowIcon = LoadImage("logo.png");
    SetWindowIcon(windowIcon);

    Game game;
    game.start();
    UnloadImage(windowIcon);

    return 0;
}