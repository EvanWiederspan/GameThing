#ifndef FLAGBUTTON_H_
#define FLAGBUTTON_H_

#include "../Button.h"

class FlagButton: public Button
{
public:
	FlagButton(Sint16 x, Sint16 y);
	~FlagButton();
	void Draw();
	void Render() {}
	void HandleEvent(SDL_Event* event) {}
};

#endif
