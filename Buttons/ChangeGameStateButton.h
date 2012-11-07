#ifndef CHANGEGAMESTATEBUTTON_H_
#define CHANGEGAMESTATEBUTTON_H_

#include "../Button.h"
#include "../SDL/SDL_events.h"

class ChangeGameStateButton: public Button
{
public:
	ChangeGameStateButton(int x, int y, int w, int h, Uint8 newScreen, std::string label, bool pause);
	~ChangeGameStateButton() {}
	void Draw();
};

#endif
