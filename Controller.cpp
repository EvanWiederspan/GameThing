#include "Controller.h"

Controller::Controller(): _clicked(false), _state(0), _location({0, 0, 10, 10}), _lastX(0), _lastY(0), pressedKeys(), buttonEvents()
{
	//_location = {0, 0, 10, 10};
	/*
	_location.x = 0;
	_location.y = 0;
	_location.w = 10;
	_location.h = 10;
	*/
}

Controller::~Controller()
{
	pressedKeys.clear();
	buttonEvents.clear();
}

void Controller::SetState(Uint8 state)
{
	_state = state;
}

bool Controller::InState(Uint8 state)
{
	return (_state == state);
}

SDL_Rect* Controller::CursorLocation()
{
	return &_location;
}

void Controller::Click()
{
	_clicked = true;
}

bool Controller::Clicked()
{
	return _clicked;
}

void Controller::Release()
{
	_clicked = false;
}

void Controller::Update(SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		Click();
	else if (event->type == SDL_MOUSEBUTTONUP)
		Release();
	else if (event->type == SDL_KEYDOWN)
	{
		std::list<Uint16>::iterator pressedKey = pressedKeys.begin();
		Uint16 keyValue = (Uint16)event->key.which;
		if (!buttonEvents.empty()) // first check if any of the button events are tied to this key
		{
			for (std::list<ButtonEvent>::iterator buttonEvent = buttonEvents.begin(); (buttonEvent->Key() <= keyValue) and (buttonEvent != buttonEvents.end()); buttonEvent++)
			{
				if (buttonEvent->Key() == keyValue)
				{
					switch(buttonEvent->Type())
					{
					case ButtonEvent::kOnPress:
					{
						if (!buttonEvent->DoneOnce())
						{
							buttonEvent->GetButton()->Run();
							buttonEvent->SetDoneOnce(true);
						}
						break;
					}
					case ButtonEvent::kOnRelease:
						buttonEvent->SetDoneOnce(false);
						break;
					case ButtonEvent::kWhileHeld:
						buttonEvent->GetButton()->Initialize();
						break;
					default:
						break;
					}
				}
			}
		}
		if (pressedKeys.empty()) // if its empty, just stick it in there
		{
			pressedKeys.insert(pressedKey, keyValue);
		}
		else // else, place it so that they keys are sorted numerically from least to greatest
		{
			while (keyValue > (*pressedKey))
			{
				pressedKey++;
			}
			pressedKeys.insert(pressedKey, keyValue);
		}
	}
	else if ((event->type == SDL_KEYUP))
	{
		std::list<Uint16>::iterator iterator = pressedKeys.begin();
		Uint16 keyValue = (Uint16)event->key.which;
		if (!buttonEvents.empty())
		{
			for (std::list<ButtonEvent>::iterator buttonEvent = buttonEvents.begin(); buttonEvent != buttonEvents.end(); buttonEvent++)
			{
				if (buttonEvent->Key() == keyValue)
				{
					switch(buttonEvent->Type())
					{
					case ButtonEvent::kOnRelease:
					{
						if (!buttonEvent->DoneOnce())
						{
							buttonEvent->GetButton()->Run();
							buttonEvent->SetDoneOnce(true);
						}
						break;
					}
					case ButtonEvent::kWhileHeld:
						buttonEvent->GetButton()->Finish();
						break;
					case ButtonEvent::kOnPress:
						buttonEvent->SetDoneOnce(false);
						break;
					default:
						break;
					}
				}
				if (buttonEvent->Key() <= keyValue)
					break;
			}
		}
		if (pressedKeys.empty()) // should never happen
		{
			return;
		}
		else
		{
			while(((*iterator) != keyValue) and (iterator != pressedKeys.end()))
			{
				iterator++;
			}
			pressedKeys.erase(iterator);
		}
	}

	if ((!pressedKeys.empty()) and (!buttonEvents.empty()))
	{
		for (std::list<Uint16>::iterator keyPlace = pressedKeys.begin(); keyPlace != pressedKeys.end(); keyPlace++)
		{
			for (std::list<ButtonEvent>::iterator buttonPlace = buttonEvents.begin(); buttonPlace != buttonEvents.end(); buttonPlace++)
			{
				if (buttonPlace->Key() == (*keyPlace))
				{
					switch(buttonPlace->Type())
					{
					case ButtonEvent::kOnPress:
						break;
					case ButtonEvent::kOnRelease:
						break;
					case ButtonEvent::kWhileHeld:
						buttonPlace->GetButton()->Execute();
						break;
					default:
						break;
					}
				}
			}
		}

	}
	_lastX = GetX();
	_lastY = GetY();

	_location.x = event->button.x;
	_location.y = event->button.y;
}

bool Controller::IsPressed(SDLKey& key)
{
	if (pressedKeys.empty())
		return false;
	Uint16 keyValue = (Uint16)key;
	for (std::list<Uint16>::iterator currKey = pressedKeys.begin(); currKey != pressedKeys.end(); currKey++)
	{
		if ((*currKey) == keyValue)
			return true;
	}
	return false;
}

void Controller::AddButtonEvent(ButtonEvent* newEvent)
{
	std::list<ButtonEvent>::iterator currEvent = buttonEvents.begin();
	if (buttonEvents.empty())
		buttonEvents.insert(currEvent, *newEvent);
	else
	{
		while ((currEvent->Key() > newEvent->Key()) and (currEvent != buttonEvents.end()))
		{
			currEvent++;
		}
		buttonEvents.insert(currEvent, *newEvent);
	}
}

void Controller::DeleteEvents(Button* button)
{
	for (std::list<ButtonEvent>::iterator currEvent = buttonEvents.end(); currEvent != buttonEvents.begin(); currEvent--)
	{
		if (currEvent->GetButton() == button)
		{
			buttonEvents.erase(currEvent);
		}
	}
}

Sint16 Controller::GetX() { return _location.x; }

Sint16 Controller::GetY() { return _location.y; }

Sint16 Controller::GetLastX() { return _lastX; }

Sint16 Controller::GetLastY() { return _lastY; }
