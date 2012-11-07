#ifndef BUTTONEVENT_H_
#define BUTTONEVENT_H_

#include "Button.h"

class ButtonEvent
{
private:
	Button* _button; // button to press
	Uint16 _key; // key the button is bound to
	Uint8 _type;
	bool _doneOnce;
public:
	static const Uint8 kOnPress = 0;
	static const Uint8 kOnRelease = 1;
	static const Uint8 kWhileHeld = 2;
	ButtonEvent(Button* button, Uint16 key, Uint8 type);
	~ButtonEvent();
	void Check();
	bool DoneOnce();
	void SetDoneOnce(bool doneOnce);
	void Run();
	Uint8 Type();
	Uint16 Key();
	Button* GetButton();
};

#endif
