#pragma once
#include "Commands.h"

class InputCommandBuilder
{
public:
	InputCommandBuilder() {}
	~InputCommandBuilder() {}

	InputCommand * create_command(int command_id, std::string command_value)
	{
		InputCommand * command;
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
			command = new MoveCursorXCommand(command_value);
			break;
		case 5:
			command = new MakeSelection();
			break;
		case 6:
			command = new ChangeRotationPoint(command_value);
			break;
		case 7:
			command = new ChangeControllerCommand(command_value);
			break;
		case 8:
			command = new EndRoundCommand();
			break;
		default:
			command = new NothingCommand();
			break;
		}
		return command;
	}
};