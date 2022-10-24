#include <dealer.h>

Dealer::Dealer()
	: hand(0)
	, cardCount(0)
	, hiddenCardValue(0)
	, blackjack(false)
{
}

Texture2D& Dealer::getOneCard()
{
	return dealerCardTextures[cardCount++];
}

Texture2D& Dealer::getCardTexture(int cardNumber)
{
	return dealerCardTextures[cardNumber];
}

void Dealer::setHiddenCard()
{
	if (cardCount == 1)
	{
		hiddenCardValue = hand;
	}
	else
	{
		hiddenCardTexture = dealerCardTextures[1];
		dealerCardTextures[1] = LoadTexture("cards/back.png");
		hiddenCardValue = hand - hiddenCardValue;
		hand -= hiddenCardValue;
	}
}

void Dealer::showHiddenCard(Sound dealCard)
{
	PlaySound(dealCard);

	UnloadTexture(dealerCardTextures[1]);
	dealerCardTextures[1] = hiddenCardTexture;
	hand += hiddenCardValue;
	hiddenCardValue = 0;
}

void Dealer::resetHand()
{
	hand = 0;
	blackjack = false;
	cardCount = 0;
	UnloadTexture(hiddenCardTexture);

	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(dealerCardTextures[i]);
		dealerCardTextures[i] = LoadTexture("empty.png");
	}
}
