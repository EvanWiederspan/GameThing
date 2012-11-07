#ifndef COMMAND_H_
#define COMMAND_H_

#include "SDL/SDL.h"

class Command
{
protected:
	Uint16 _delay; // delay betwen Execute() calls in milliseconds
	float _timeout; // amount of time (in seconds) that the command will run
public:
	Command(Uint16 delay, float timeout);
	virtual ~Command();
	Uint16 Delay();
	float Timeout();
	virtual void Initialize() = 0;
	virtual void Execute() = 0;
	virtual bool IsDone() = 0;
	virtual void Finish() = 0;
};

#endif
