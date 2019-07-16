#pragma once
#include "Command.h"

/**
 * @author David Wadsworth
 * 
 * checks idling keys
 */

class InputCommand : public Command
{
public:
	virtual void idle(Entity * entity) {}
};