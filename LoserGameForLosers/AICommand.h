#pragma once

class AICommand
{
public:
	virtual ~AICommand() = default;
	virtual void execute() = 0;
};