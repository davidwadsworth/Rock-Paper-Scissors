#pragma once
#include "Command.h"

class ChangeStateCommand : public Command
{
	int state_;
public:
	explicit ChangeStateCommand(const char * new_state)
		: state_(atoi(new_state))
	{}

	void execute(Entity* entity) override;

	void idle(Entity* entity) override{}

};

class ChangeScreenCommand : public Command
{
public:
	ChangeScreenCommand() {}

	void execute(Entity * entity) override
	{}

	void idle(Entity * entity) override
	{}

};

class NothingCommand : public Command
{
public:
	NothingCommand()
	{}

	void execute(Entity* entity) override
	{}

	void idle(Entity* entity) override{}

};