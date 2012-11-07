#ifndef BUTTONMANAGER_H_
#define BUTTONMANAGER_H_

#include <vector>
#include "Surface.h"
#include "SDL/SDL_events.h"
#include "Button.h"

//class Screen;

class ButtonManager
{
	std::vector<Button*> buttons; // A vector of all the buttons on the screen
	short _buttonPressed; // if set to -1, no button is pressed. Any other value greater than -1 is the location in the vector of the pointer to the pressed button
public:
	ButtonManager();
	~ButtonManager();
	void Add(Button* button); // adds a button to vector<Surface*> buttons. Is called within Screen::Add(Surface*);
	void Clear();
	void CheckButtons(SDL_Event* event);
};


#endif
