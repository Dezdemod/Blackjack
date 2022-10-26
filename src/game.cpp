#include <game.h>

Game::Game()
    : screenWidth(1280)
    , screenHeight(720)
    , time(0.0f)
    , gameOver(false)
    , isStanding(false)
    , cardIsHidden(true)
    , table(LoadTexture("table.png"))
    , dealCard(LoadSound("sounds/deal.wav"))
    , shuffleDeck(LoadSound("sounds/shuffle.wav"))
    , player(std::make_shared<Player>())
    , dealer(std::make_shared<Dealer>())
    , gameCards(std::make_unique<Cards>(player, dealer))
{
    ClearBackground(WHITE);

    ambience = LoadMusicStream("sounds/music.mp3");
    ambience.looping = true;
    PlayMusicStream(ambience);
    SetMusicVolume(ambience, 0.3f);
}

void Game::drawMenu()
{
    std::unique_ptr<mainMenu> menu = std::make_unique<mainMenu>();
    menu->draw();
}

void Game::drawScore()
{
    DrawText(TextFormat("Hand: %2i", player->getHand()), 1150, 687, 30, WHITE);
    DrawText(TextFormat("Dealer's Hand: %2i", dealer->getHand()), 1010, 5, 30, WHITE);
}

void Game::start()
{
    HideCursor();
    this->drawMenu();
    while (!WindowShouldClose())
    {
        UpdateMusicStream(ambience);
        BeginDrawing();
        {
            DrawTexture(table, 0, 0, WHITE);
            this->drawScore();
            gameCards->drawCards();

            if (!gameOver)
            {
                this->controls();
                DrawText("Press Enter to hit", 10, 650, 30, WHITE);
                DrawText("Press Spacebar to stand", 10, 687, 30, WHITE);
            }
            else this->result();
        }
        EndDrawing();
    }
}

void Game::controls()
{
    if (player->hasBlackjack() || dealer->hasBlackjack()) isStanding = true;

    if (IsKeyPressed(KEY_ENTER) && !isStanding) gameCards->addCard(isStanding);

    if (IsKeyPressed(KEY_SPACE) || player->getHand() >= 21 || player->getCardCount() == 6) isStanding = true;

    if (isStanding && dealer->getCardCount() < 6)
    {
        time += GetFrameTime();
        if (cardIsHidden && time > 0.5f)
        {
            dealer->showHiddenCard(dealCard);
            cardIsHidden = false;
            time = 0.0f;

            if (player->getHand() > 21 ||player->hasBlackjack()) gameOver = true;
        }
        else if (time > 0.5f)
        {
            gameCards->addCard(isStanding);
            time = 0.0f;

            if (dealer->getHand() >= 17 || dealer->hasBlackjack()) gameOver = true;
        }
    }
}

void Game::result()
{
    if (player->getHand() == dealer->getHand()) DrawText("EQUAL", 560, 250, 50, BLACK);
    else if (player->hasBlackjack() || dealer->hasBlackjack()) DrawText("BLACKJACK", 490, 235, 50, WHITE);
    else if (player->getHand() <= 21 && player->getHand() > dealer->getHand() || dealer->getHand() > 21) DrawText("YOU HAVE WON", 440, 235, 50, WHITE);
    else DrawText("THE DEALER HAS WON", 340, 235, 50, RED);

    this->restart();
}

void Game::restart()
{
    DrawText("PRESS R TO RESTART", 330, 10, 50, WHITE);
    DrawText("PRESS ESC TO QUIT", 360, 670, 50, BLACK);
    if (IsKeyPressed(KEY_R))
    {
        PlaySound(shuffleDeck);
        gameCards->resetCards();
        gameOver = false;
        isStanding = false;
        cardIsHidden = true;
        time = 0.0f; 
        gameCards->startingCards();
    }
}