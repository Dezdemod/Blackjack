#pragma once
#include <raylib/raylib.h>
#include <memory>
#include <vector>

class Player
{
public:
	Player();

	virtual inline int getHand() const { return hand; };
	virtual inline int getCardCount() const { return cardCount; };
	virtual inline bool hasBlackjack() const { return blackjack; }
	virtual inline void setBlackjack(bool BLACKJACK) { blackjack = BLACKJACK; }
	virtual inline void setHand(int cardValue) { hand += cardValue; }

	virtual void resetHand();

	virtual Texture2D& getOneCard();
	virtual Texture2D& getCardTexture(int cardNumber);

private:
	int hand;
	int cardCount;
	bool blackjack;

	const std::unique_ptr<Texture2D[]> playerCardTextures = std::make_unique<Texture2D[]>(6);
};
