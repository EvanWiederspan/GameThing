#ifndef CHANGESCREENCOMMAND_H_
#define CHANGESCREENCOMMAND_H_

#include "../Command.h"

class ChangeScreenCommand: public Command
{
	Uint8 _newScreen;
	bool _pause;
public:
	ChangeScreenCommand(Uint8 newScreen, bool pause);
	~ChangeScreenCommand();
	void Initialize() {}
	void Execute() {}
	bool IsDone();
	void Finish();
};

#endif
