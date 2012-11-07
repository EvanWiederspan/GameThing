#include "ButtonEvent.h"

ButtonEvent::ButtonEvent(Button* button, Uint16 key, Uint8 type): _button(button), _key(key), _type(type)
{

}

ButtonEvent::~ButtonEvent()
{

}

void ButtonEvent::Check()
{

}

bool ButtonEvent::DoneOnce()
{
	return _doneOnce;
}

void ButtonEvent::SetDoneOnce(bool doneOnce)
{
	_doneOnce = doneOnce;
}

Uint8 ButtonEvent::Type()
{
	return _type;
}

Uint16 ButtonEvent::Key()
{
	return _key;
}

Button* ButtonEvent::GetButton()
{
	return _button;
}
