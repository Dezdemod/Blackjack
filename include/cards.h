#pragma once
#include <dealer.h>
#include <vector>
#include <string>

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

	std::vector<std::string> textureNames;
	std::shared_ptr<Player> player;
	std::shared_ptr<Dealer> dealer;
};
