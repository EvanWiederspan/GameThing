#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "SDL/SDL.h"
#include <list>
#include <vector>
#include "ButtonEvent.h"

class Controller
{
private:
	bool _clicked;
	Uint8 _state; // TODO make a vector/list to have multiple states
	SDL_Rect _location;
	Sint16 _lastX, _lastY;
	std::list<Uint16> pressedKeys;
	std::list<ButtonEvent> buttonEvents;
	void Click();
	void Release();
public:
	Controller();
	~Controller();
	void Update(SDL_Event* event);
	bool Clicked();
	bool InState(Uint8 state);
	void SetState(Uint8 state);
	bool IsPressed(SDLKey& key);
	SDL_Rect* CursorLocation();
	void AddButtonEvent(ButtonEvent* newEvent);
	Sint16 GetX();
	Sint16 GetY();
	Sint16 GetLastX();
	Sint16 GetLastY();
	void DeleteEvents(Button* button); // should only be used in ~Button()
};

#endif
