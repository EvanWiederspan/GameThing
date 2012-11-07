#include "GameScreen.h"
#include "../ButtonEvent.h"
#define TITLE 12

void GameScreen::Load()
{
	if ((bool)surfaces.empty() == false)
		return;

	Add(new Grid(80, 140, 15, 15, 15));
	Add(new ChangeGameStateButton(30, 30, 80, 40, GAME, "", false));
	Add(new StaticSprite("images/Title.bmp", TITLE, 200, 20, 200, 80, 0x02));
	//Button* button = new FlagButton(450, 70);
	//button->TieToButton(SDLK_a, ButtonEvent::kOnPress);
	Add(new FlagButton(450, 70));
}

