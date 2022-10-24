#include <player.h>

Player::Player()
	  : hand(0)
	  , cardCount(0)
	  , blackjack(false)
{
}

Texture2D& Player::getOneCard()
{
	return playerCardTextures[cardCount++];
}

Texture2D& Player::getCardTexture(int cardNumber)
{
	return playerCardTextures[cardNumber];
}

void Player::resetHand()
{
	hand = 0;
	cardCount = 0;
	blackjack = false;

	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(playerCardTextures[i]);
		playerCardTextures[i] = LoadTexture("empty.png");
	}
}