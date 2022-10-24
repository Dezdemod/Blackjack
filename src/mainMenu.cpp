#include <mainMenu.h>

mainMenu::mainMenu()
	    : beginGame(false)
		, startButtonColor({ WHITE })
		, exitButtonColor({ BLACK })
		, background(LoadTexture("background.png"))
		, logo(LoadTexture("logo.png"))
		, select(LoadSound("sounds/select.wav"))
{
}

mainMenu::~mainMenu()
{
	if (!beginGame) CloseWindow();
	UnloadTexture(background);
	UnloadTexture(logo);
	UnloadSound(select);
}

void mainMenu::draw()
{
	while (!WindowShouldClose() && !beginGame)
	{
		BeginDrawing();
		{
			DrawTexture(background, 0, 0, WHITE);
			DrawTexture(logo, screenWidth / 2 - logo.width / 2, 90, BLACK);
			DrawText("Start", 540, 425, 70, startButtonColor);
			DrawText("Exit", 572, 545, 70, exitButtonColor);
			this->controls();
		}
		EndDrawing();
	}
}

void mainMenu::controls()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		beginGame = true;
	}

	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
	{
		if (startButtonColor.r == 255)
		{
			PlaySound(select);
			startButtonColor = { BLACK };
			exitButtonColor = { WHITE };
			SetExitKey(KEY_ENTER);
		}
		else
		{
			PlaySound(select);
			startButtonColor = { WHITE };
			exitButtonColor = { BLACK };
			SetExitKey(KEY_ESCAPE);
		}
	}

	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
	{
		if (startButtonColor.r == 0)
		{
			PlaySound(select);
			startButtonColor = { WHITE };
			exitButtonColor = { BLACK };
			SetExitKey(KEY_ESCAPE);
		}
		else
		{
			PlaySound(select);
			startButtonColor = { BLACK };
			exitButtonColor = { WHITE };
			SetExitKey(KEY_ENTER);
		}
	}
}