#pragma once
#include  "Command.h"

class LinkCommand : public Command
{
public:
	virtual void undo() = 0;
};