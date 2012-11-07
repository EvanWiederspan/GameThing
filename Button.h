#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "SDL/SDL.h"
#include "Surface.h"
#include "Command.h"

class Button: public Surface
{
protected:
	void AddLabel(std::string label);
	Command* _command;
	std::string _label;
	bool _pushed;
	Uint16 _borderWidth;
	bool _repeat; // if true, the button will repeat its action while held. If false, the action will occur once until pressed again
	Uint16  _delay;  // if _repeat is true, this will be the delay in millisecond between actions
	Uint32 _borderColor;
	Uint32 _buttonColor;
	bool _doneOnce;
public:
	Button(Sint16 x, Sint16 y, Uint16 w, Uint16 h, bool repeat, Uint16 delay, Uint16 borderWidth, Uint32 borderColor, Uint32 buttonColor, std::string label, Uint8 name, Command* command);
	virtual ~Button();
	void Push();
	void Release();
	bool IsPressed();
	bool Repeat();
	Uint16 Delay();
	void TieToButton(SDLKey key, Uint8 type);
	virtual void Initialize();
	virtual void Execute();
	virtual void Finish();
	void Run();
	virtual void Draw() {}
	virtual void Render() {}
	virtual void HandleEvent(SDL_Event* event) {}
};

#endif
