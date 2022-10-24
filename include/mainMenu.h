#pragma once
#include <raylib/raylib.h>

class mainMenu
{
public:
	mainMenu();
	~mainMenu();

	void draw();

private:
	void controls();

	int screenWidth = 1280;

	bool beginGame;

	const Texture2D background;
	const Texture2D logo;
	const Sound select;

	Color startButtonColor;
	Color exitButtonColor;
};
