#pragma once
#include "ECS.h"

/**
 * @author David Wadsworth
 *
 * regular command most commonly used in context with the controller
 */

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void execute(Entity * entity){}
};

