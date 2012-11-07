#ifndef TOGGLEMOUSESTATECOMMAND_H_
#define TOGGLEMOUSESTATECOMMAND_H_

#include "../Command.h"

class ToggleMouseStateCommand: public Command
{
private:
	Uint8 _toggleState;
	bool _activated;
public:
	ToggleMouseStateCommand(Uint8 toggleState);
	~ToggleMouseStateCommand();
	void Initialize();
	void Execute();
	bool IsDone();
	void Finish();
};

#endif
