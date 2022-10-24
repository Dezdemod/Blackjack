#pragma once
#include <cards.h>
#include <mainMenu.h>
#include <dealer.h>

class Game
{
public:
	Game();

	void start();

protected:
	const int screenWidth;
	const int screenHeight;

private:

	float time;

	bool gameOver;
	bool isStanding;
	bool cardIsHidden;

	void drawMenu();
	void drawScore();
	void controls();
	void result();
	void restart();

	const Texture2D table;
	const Sound dealCard;
	const Sound shuffleDeck;
	Music ambience;

	std::shared_ptr<Player> player;
	std::shared_ptr<Dealer> dealer;
	std::unique_ptr<Cards> gameCards;
};
