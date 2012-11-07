#include "Command.h"

Command::Command(Uint16 delay, float timeout): _delay(delay), _timeout(timeout)
{

}

Command::~Command()
{

}

Uint16 Command::Delay()
{
	return _delay;
}

float Command::Timeout()
{
	return _timeout;
}
