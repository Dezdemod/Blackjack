#pragma once
#include <player.h>

class Dealer : public Player
{
public:
	Dealer();

	inline int getHand() const override { return hand; };
	inline int getCardCount() const override { return cardCount; };
	inline bool hasBlackjack() const override { return blackjack; }
	inline void setBlackjack(bool BLACKJACK) override { blackjack = BLACKJACK; }
	inline int getHiddenCardValue() const { return hiddenCardValue; };
	inline void setHand(int cardValue) override { hand += cardValue; }

	void setHiddenCard();
	void showHiddenCard(Sound dealCard);
	void resetHand() override;

	Texture2D& getOneCard() override;
	Texture2D& getCardTexture(int cardNumber) override;

private:

	int hand;
	int cardCount;
	int hiddenCardValue;
	bool blackjack;

	const std::unique_ptr<Texture2D[]> dealerCardTextures = std::make_unique<Texture2D[]>(6);
	Texture2D hiddenCardTexture;
};
