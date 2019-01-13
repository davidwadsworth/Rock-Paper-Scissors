#pragma once
#include "Commands.h"

class CommandBuilder
{
public:
	CommandBuilder() {}
	~CommandBuilder() {}

	Command * create_command(int command_id, const char * command_value)
	{
		Command * command;
		switch (command_id)
		{
		case 0:
			command = new MoveCommand(command_value);
			break;
		case 1:
			command = new SelectAttackCommand(command_value);
			break;
		case 2:
			command = new PauseGameCommand();
			break;
		case 3:
			command = new MoveCursorYCommand(command_value);
			break;
		case 4:
			command = new MakeSelection();
			break;
		case 5:
			command = new ChangeStateCommand(command_value);
			break;
		default:
			command = new NothingCommand();
			break;
		}
		return command;
	}
};