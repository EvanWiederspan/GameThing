#include "ChangeGameStateButton.h"
#include "../header.h"
#include "../App.h"
#include "../Commands/Commands.h"

ChangeGameStateButton::ChangeGameStateButton(int x, int y, int w, int h, Uint8 newScreen, std::string label, bool pause): Button(x, y, w, h, false, 0.0, 5, 0x00000000, 0x00FF0000, label, CHANGE_GAME_STATE_BUTTON, new ChangeScreenCommand(newScreen, pause))
{

}

void ChangeGameStateButton::Draw()
{

	// draw border
	if (_pushed == false)
	{
		App::GetInstance()->display->DrawRect(Location(), _borderColor);
		App::GetInstance()->display->DrawRect((Location()->x + _borderWidth), (Location()->y + _borderWidth), (Location()->w - (2 * _borderWidth)), (Location()->h - (2 * _borderWidth)), _buttonColor);
	}

	else
	{
		App::GetInstance()->display->DrawRect(Location(), 0x00FF0000); // draw border first
		App::GetInstance()->display->DrawRect((Location()->x + _borderWidth), (Location()->y + _borderWidth), (Location()->w - (2 * _borderWidth)), (Location()->h - (2 * _borderWidth)), 0x00000000);
	}

}
