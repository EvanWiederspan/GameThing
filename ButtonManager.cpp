#include "ButtonManager.h"

ButtonManager::ButtonManager(): _buttonPressed(-1)
{

}

ButtonManager::~ButtonManager()
{
	buttons.clear(); // the actual objects will be deleted when the screen is destroyed
}

void ButtonManager::Add(Button* button)
{
	buttons.push_back(button);
}

void ButtonManager::Clear()
{
	buttons.clear();
}

void ButtonManager::CheckButtons(SDL_Event* event)
{
	if (buttons.empty()) // if there are no buttons on this screen, don't bother
		return;

	if (_buttonPressed >= 0) // if a button is still pressed, call OnPush()
		buttons[_buttonPressed]->Execute();

	if ((event->type == SDL_MOUSEBUTTONDOWN) and (_buttonPressed == -1))
	{
		int mouseX = event->button.x;
		int mouseY = event->button.y;
		for (Uint16 i = 0; i < (Uint16)buttons.size(); i++)
		{
			Button* currButton = buttons[i];
			if ((currButton->GetX() < mouseX) and ((currButton->GetX() + currButton->GetW()) > mouseX) and (currButton->GetY() < mouseY) and ((currButton->GetY() + currButton->GetH()) > mouseY)) // if the mouse clicked within the boundaries of the button
			{
				_buttonPressed = i;
				currButton->Push(); // push the button then call OnPush()
				currButton->Initialize();
				break; // no need to check any of the other buttons
			}
		}
	}
	else if ((event->type == SDL_MOUSEBUTTONUP) and (_buttonPressed >= 0))
	{
		int mouseX = event->button.x; // x coordinate of the mouse cursor
		int mouseY = event->button.y; // y coordinate of the mouse cursor
		Button* currButton = buttons[_buttonPressed];
		if ((currButton->GetX() < mouseX) and ((currButton->GetX() + currButton->GetW()) > mouseX) and (currButton->GetY() < mouseY) and ((currButton->GetY() + currButton->GetH()) > mouseY))
		{
			currButton->Finish();
		}
		currButton->Release();
		_buttonPressed = -1;
	}
}
