#include <raylib/raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

const int screenWidth = 1280;
const int screenHeight = 720;

struct gameInfo
{
    const char* cards[13] = { "cards/2.png", "cards/3.png", "cards/4.png", "cards/5.png", "cards/6.png", "cards/7.png", "cards/8.png", "cards/9.png", "cards/10.png", "cards/ace.png",
    "cards/jack.png", "cards/queen.png", "cards/king.png" };

    bool isStanding = false;
    bool wasRevealed = false;
    bool finishHand = false;

    int playerCard = 0;
    int dealerCard = 0;
    int playerHand = 0;
    int dealerHand = 0;
    int hiddenCardValue = 0;
    int playerCount = 0;
    int dealerCount = 0;

    Texture2D table = LoadTexture("table.png");
    Texture2D secret;

    Texture2D playerCardTexture;
    Texture2D playerCardTexture2;
    Texture2D playerCardTexture3;
    Texture2D playerCardTexture4;
    Texture2D playerCardTexture5;

    Texture2D* deckCards[3] = { &playerCardTexture3, &playerCardTexture4, &playerCardTexture5};

    Texture2D dealerCardTexture;
    Texture2D dealerCardTexture2 = LoadTexture("cards/back.png");
    Texture2D dealerCardTexture3;
    Texture2D dealerCardTexture4;

    Texture2D* deckCards2[2] = { &dealerCardTexture3, &dealerCardTexture4 };

    Sound dealCard = LoadSound("sounds/deal.wav");

    void setCard(Texture2D &texture, int &cardReceiver, int& hand)
    {
        UnloadTexture(texture);
        cardReceiver = GetRandomValue(0, 12);
        texture = LoadTexture(cards[cardReceiver]);

        switch (cardReceiver)
        {
        case 9: if (21 - hand < 11) hand += (21 - hand);
              else hand += 11;
            break;

        case 10: hand += 10;
            break;

        case 11: hand += 10;
            break;

        case 12: hand += 10;
            break;

        default: hand += cardReceiver + 2;
            break;
        }
    }

    void addCard()
    {
        DrawText("Press Enter to hit", 10, 650, 30, WHITE);
        DrawText("Press Spacebar to stand", 10, 687, 30, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            PlaySound(dealCard);
            setCard(*deckCards[playerCount], playerCard, playerHand);
            playerCount++;
        }
    }

    void addDealerCard()
    {
        if (dealerHand < 17)
        {
            PlaySound(dealCard);
            setCard(*deckCards2[dealerCount], dealerCard, dealerHand);
            dealerCount++;
        }
        else finishHand = false;
    }

    void checkResult()
    {
        if (playerHand > 21 && dealerHand > 21) DrawText("YOU ARE BOTH BUST", 360, 235, 50, BLACK);
        else if (playerHand > 21) DrawText("YOU ARE BUST", 440, 235, 50, BLACK);
        else if (dealerHand > 21) DrawText("DEALER IS BUST", 420, 235, 50, BLACK);
        else if (playerHand == dealerHand) DrawText("EQUAL", 560, 250, 50, BLACK);
        else if (playerHand > dealerHand) DrawText("YOU HAVE WON", 440, 235, 50, BLACK);
        else if(dealerHand > playerHand) DrawText("THE DEALER HAS WON", 340, 235, 50, BLACK);
    }
};

void mainMenu(bool &startGame)
{
    Color* startButtonColor = new Color { WHITE };
    Color* exitButtonColor = new Color { BLACK };

    Texture2D* background = new Texture2D;
    Texture2D* logo = new Texture2D;

    *background = LoadTexture("background.png");
    *logo = LoadTexture("logo.png");

    Sound* select = new Sound;
    *select = LoadSound("sounds/select.wav");

    Music* song = new Music; 
    *song = LoadMusicStream("music.mp3");

    song->looping = true;
    PlayMusicStream(*song);
    SetMusicVolume(*song, 0.2);

    while(!WindowShouldClose() && !startGame)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            startGame = true;
        }
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
        {
            PlaySound(*select);
            *startButtonColor = { BLACK };
            *exitButtonColor = { WHITE };
            SetExitKey(KEY_ENTER);
        }
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        {
            PlaySound(*select);
            *startButtonColor = { WHITE };
            *exitButtonColor = { BLACK };
            SetExitKey(KEY_ESCAPE);
        }
        BeginDrawing();
        {
            UpdateMusicStream(*song);
            DrawTexture(*background, 0, 0, WHITE);
            DrawTexture(*logo, screenWidth / 2 - logo->width / 2, 90, BLACK);
            DrawText("Start", 540, 425, 70, *startButtonColor);
            DrawText("Exit", 572, 545, 70, *exitButtonColor);
        }
        EndDrawing();
    }
    UnloadMusicStream(*song);
    UnloadSound(*select);
    UnloadTexture(*background);
    UnloadTexture(*logo);
    delete song;
    delete select;
    delete startButtonColor;
    delete exitButtonColor;
    delete background;
    delete logo;
}

void mainGame(bool &startGame, Music &ambience)
{
    SetExitKey(KEY_E);
    bool isGameGoing = true;

    gameInfo* game = new gameInfo;
    
    game->setCard(game->playerCardTexture, game->playerCard, game->playerHand);
    game->setCard(game->playerCardTexture2, game->playerCard, game->playerHand);

    game->setCard(game->dealerCardTexture2, game->dealerCard, game->dealerHand);
    game->hiddenCardValue = game->dealerHand;
    game->dealerHand -= game->hiddenCardValue;
    game->secret = game->dealerCardTexture2;
    game->dealerCardTexture2 = LoadTexture("cards/back.png");

    game->setCard(game->dealerCardTexture, game->dealerCard, game->dealerHand);

    while (!WindowShouldClose() && isGameGoing)
    {
        UpdateMusicStream(ambience);
        BeginDrawing();
        {
            DrawTexture(game->table, 0, 0, WHITE);
            DrawTexture(game->playerCardTexture, 600, 450, WHITE);
            DrawTexture(game->playerCardTexture2, 600, 490, WHITE);
            DrawTexture(game->playerCardTexture3, 600, 530, WHITE);
            DrawTexture(game->playerCardTexture4, 600, 570, WHITE);
            DrawTexture(game->playerCardTexture5, 600, 610, WHITE);

            DrawTexture(game->dealerCardTexture, 500, 100, WHITE);
            DrawTexture(game->dealerCardTexture2, 590, 100, WHITE);
            DrawTexture(game->dealerCardTexture3, 680, 100, WHITE);
            DrawTexture(game->dealerCardTexture4, 770, 100, WHITE);

            DrawText(TextFormat("Hand: %2i", game->playerHand), 1150, 687, 30, WHITE);
            DrawText(TextFormat("Dealer's Hand: %2i", game->dealerHand), 1010, 5, 30, WHITE);

            if (IsKeyPressed(KEY_SPACE) || game->finishHand)
            {
                game->isStanding = true;
                if (!game->wasRevealed)
                {
                    PlaySound(game->dealCard);
                    game->dealerCardTexture2 = game->secret;
                    game->dealerHand += game->hiddenCardValue;
                    game->wasRevealed = true;
                }
                game->addDealerCard();
            }

            if (game->playerHand < 21 && !game->isStanding)
            {
                game->addCard();
            }
            else game->finishHand = true;

            if (game->dealerHand >= 17)
            {
                game->checkResult();
                DrawText("PRESS R TO RESTART", 330, 10, 50, BLACK);
                DrawText("PRESS ESC TO QUIT", 360, 670, 50, BLACK);
                if (IsKeyPressed(KEY_R)) isGameGoing = false;
                else if (IsKeyPressed(KEY_ESCAPE))
                {
                    isGameGoing = false;
                     startGame = false;
                }
            }
        }
        EndDrawing();
    }
    delete game;
}

int main()
{
    bool startGame = false;

    InitWindow(screenWidth, screenHeight, "Blackjack");
    InitAudioDevice();
    SetTargetFPS(60);

    SetRandomSeed(NULL);
    mainMenu(startGame);

    Music ambience = LoadMusicStream("sounds/ambience.wav");
    PlayMusicStream(ambience);
    SetMusicVolume(ambience, 0.2);

    while (startGame)
    {
        mainGame(startGame, ambience);
    }

    CloseWindow();
    
    return 0;
}