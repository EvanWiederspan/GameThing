#include "FlagButton.h"
#include "../App.h"
#include "../header.h"
#include "../ImageHolder.h"
#include "../Commands/ToggleMouseStateCommand.h"

#define UNCLICKED_FLAG 13
#define CLICKED_FLAG 14
#define FLAG_ICON 15

FlagButton::FlagButton(Sint16 x, Sint16 y): Button(x, y, 50, 50, false, 0, 0, 0, 0, "", 0x81, new ToggleMouseStateCommand(FLAG))
{
	TieToButton(SDLK_a, ButtonEvent::kOnPress);
	if(!(ImageHolder::GetInstance()->Registered(UNCLICKED_FLAG)))
	{
		Register("images/FlagUnclicked.bmp", UNCLICKED_FLAG);
		Register("images/FlagClicked.bmp", CLICKED_FLAG);
		Register("images/Flag.bmp", FLAG_ICON);
	}
}

FlagButton::~FlagButton()
{
	App::GetInstance()->Mouse()->SetState(NORMAL);
}

void FlagButton::Draw()
{
	if (_pushed)
	{
		DrawSurface(CLICKED_FLAG, NULL, Location());
		return;
	}
	DrawSurface(UNCLICKED_FLAG, NULL, Location());
}
