#pragma once

/**
 * @author David Wadsworth
 * 
 * controls for the difficulty bot to follow
 */

class AICommand
{
public:
	virtual ~AICommand() = default;
	virtual void execute() = 0;
};