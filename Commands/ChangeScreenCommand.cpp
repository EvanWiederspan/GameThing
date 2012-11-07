#include "ChangeScreenCommand.h"
#include "../App.h"

ChangeScreenCommand::ChangeScreenCommand(Uint8 newScreen, bool pause): Command(0, 0.0), _newScreen(newScreen), _pause(pause)
{

}

ChangeScreenCommand::~ChangeScreenCommand()
{

}

bool ChangeScreenCommand::IsDone()
{
	return true;
}

void ChangeScreenCommand::Finish()
{
	App::GetInstance()->ChangeScreen(_newScreen, _pause);
}
