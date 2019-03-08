#pragma once
#include "Command.h"

class InputCommand : public Command
{
public:
	virtual void idle(Entity * entity) = 0;
};