#pragma once
#include <dealer.h>

class Cards
{
public:
	Cards(std::shared_ptr<Player> PLAYER, std::shared_ptr<Dealer> DEALER);

	void startingCards();
	void drawCards();
	void addCard(bool& isStanding);
	void resetCards();

private:
	void setCard(Texture2D& cardTexture, std::shared_ptr<Player> person);

	int card;
	const Sound dealCard;

	std::shared_ptr<Player> player;
	std::shared_ptr<Dealer> dealer;
};

enum cardType
{
	Two = 2,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Ace,
	Jack,
	Queen,
	King
};
