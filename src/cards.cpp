#include <cards.h>

Cards::Cards(std::shared_ptr<Player> PLAYER, std::shared_ptr<Dealer> DEALER)
    : card(0)
    , dealCard(LoadSound("sounds/deal.wav"))
    , player(PLAYER)
    , dealer(DEALER)
{
    this->startingCards();
}

void Cards::startingCards()
{
    for (int i = 0; i < 2; i++)
    {
        this->setCard(player->getOneCard(), player);
        this->setCard(dealer->getOneCard(), dealer);
        dealer->setHiddenCard();
    }

    if (player->getHand() == 21) player->setBlackjack(true);
    if (dealer->getHand() + dealer->getHiddenCardValue() == 21) dealer->setBlackjack(true);
}

void Cards::drawCards()
{
    for (int i = 0, Ypos = 450; i < 6; i++, Ypos += 30) DrawTexture(player->getCardTexture(i), 600, Ypos, WHITE);

    for (int i = 0, Xpos = 500; i < 6; i++, Xpos += 90) DrawTexture(dealer->getCardTexture(i), Xpos, 100, WHITE);
}

void Cards::setCard(Texture2D& cardTexture, std::shared_ptr<Player> person)
{
    card = GetRandomValue(2, 14);
    UnloadTexture(cardTexture);

    switch (card)
    {
    case Two: cardTexture = LoadTexture("cards/2.png");
        person->setHand(2);
        break;

    case Three: cardTexture = LoadTexture("cards/3.png");
        person->setHand(3);
        break;

    case Four: cardTexture = LoadTexture("cards/4.png");
        person->setHand(4);
        break;

    case Five: cardTexture = LoadTexture("cards/5.png");
        person->setHand(5);
        break;

    case Six: cardTexture = LoadTexture("cards/6.png");
        person->setHand(6);
        break;

    case Seven: cardTexture = LoadTexture("cards/7.png");
        person->setHand(7);
        break;

    case Eight: cardTexture = LoadTexture("cards/8.png");
        person->setHand(8);
        break;

    case Nine: cardTexture = LoadTexture("cards/9.png");
        person->setHand(9);
        break;

    case Ten: cardTexture = LoadTexture("cards/10.png");
        person->setHand(10);
        break;

    case Jack: cardTexture = LoadTexture("cards/jack.png");
        person->setHand(10);
        break;

    case Queen: cardTexture = LoadTexture("cards/queen.png");
        person->setHand(10);
        break;

    case King: cardTexture = LoadTexture("cards/king.png");
        person->setHand(10);
        break;

    case Ace: cardTexture = LoadTexture("cards/ace.png");
        if (21 - person->getHand() < 11) person->setHand(21 - person->getHand());
        else person->setHand(11);
        break;
    }
}

void Cards::addCard(bool &isStanding)
{
    if (!isStanding)
    {
        PlaySound(dealCard);
        this->setCard(player->getOneCard(), player);
    }

    if (dealer->getHand() < 17 && isStanding)
    {
        PlaySound(dealCard);
        this->setCard(dealer->getOneCard(), dealer);
    }
}

void Cards::resetCards()
{
    player->resetHand();
    dealer->resetHand();
}
