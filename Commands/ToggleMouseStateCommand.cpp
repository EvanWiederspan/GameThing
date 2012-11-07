#include "ToggleMouseStateCommand.h"
#include "../App.h"

ToggleMouseStateCommand::ToggleMouseStateCommand(Uint8 toggleState): Command(0, 0.0), _toggleState(toggleState), _activated(false)
{

}

ToggleMouseStateCommand::~ToggleMouseStateCommand()
{

}

void ToggleMouseStateCommand::Initialize()
{
	if (_activated)
	{
		_activated = false;
		App::GetInstance()->Mouse()->SetState(NORMAL);
	}
	else
	{
		_activated = true;
		App::GetInstance()->Mouse()->SetState(_toggleState);
	}
}

void ToggleMouseStateCommand::Execute() {}

bool ToggleMouseStateCommand::IsDone()
{
	return true;
}

void ToggleMouseStateCommand::Finish() {}
