#pragma once
#include "Commands.h"

using namespace InputCommands;
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
			command = new Move(command_value);
			break;
		case 1:
			command = new InputCommands::SelectAttack(command_value);
			break;
		case 2:
			command = new PauseGame();
			break;
		case 3:
			command = new MoveCursorY(command_value);
			break;
		case 4:
			command = new MoveCursorX(command_value);
			break;
		case 5:
			command = new MakeSelection();
			break;
		case 7:
			command = new InputCommands::ChangeController(command_value);
			break;
		default:
			command = new InputCommand();
			break;
		}
		return command;
	}
};