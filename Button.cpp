#include "Button.h"
#include "ButtonEvent.h"
#include "App.h"

Button::Button(Sint16 x, Sint16 y, Uint16 w, Uint16 h, bool repeat, Uint16 delay, Uint16 borderWidth, Uint32 borderColor, Uint32 buttonColor, std::string label, Uint8 name, Command* command): Surface(name, x, y, w, h), _command(command), _label(label),
_pushed(false), _borderWidth(borderWidth), _repeat(repeat), _delay(delay), _borderColor(borderColor), _buttonColor(buttonColor), _doneOnce(false)
{

}

Button::~Button()
{
	delete _command;
	App::GetInstance()->Mouse()->DeleteEvents(this); // delete all events tied to this button
}

void Button::AddLabel(std::string label)
{
	_label = label;
}

bool Button::IsPressed()
{
	return _pushed;
}

void Button::Initialize()
{
	_command->Initialize();
}

void Button::Execute()
{
	_command->Execute();
}

void Button::Finish()
{
	_command->Finish();
}

void Button::Run()
{
	_command->Initialize();
	_command->Execute();
	_command->Finish();
}

void Button::TieToButton(SDLKey key, Uint8 type)
{
	App::GetInstance()->Mouse()->AddButtonEvent(new ButtonEvent(this, (Uint16)key, type));
}

void Button::Push()
{
	_pushed = true;
	_changed = true;
}

void Button::Release()
{
	_pushed = false;
	_changed = true;
}
