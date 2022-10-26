#include <cards.h>

Cards::Cards(std::shared_ptr<Player> PLAYER, std::shared_ptr<Dealer> DEALER)
    : card(0)
    , dealCard(LoadSound("sounds/deal.wav"))
    , textureNames
    (
        { "cards/2.png", "cards/3.png", "cards/4.png", "cards/5.png", "cards/6.png"
        ,"cards/7.png", "cards/8.png", "cards/9.png", "cards/10.png"
        ,"cards/jack.png" ,"cards/queen.png", "cards/king.png", "cards/ace.png" }
    )
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
    card = GetRandomValue(0, 12);
    UnloadTexture(cardTexture);
    cardTexture = LoadTexture(textureNames[card].c_str());
    if (card == 12)
    {
        if (21 - person->getHand() < 11) person->setHand(21 - person->getHand());
        else person->setHand(11);
    }
    else if (card > 8) person->setHand(10);
    else person->setHand(card + 2);
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
