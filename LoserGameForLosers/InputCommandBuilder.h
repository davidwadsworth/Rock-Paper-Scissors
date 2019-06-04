#pragma once
#include "Commands.h"

using namespace InputCommands;
class InputCommandBuilder
{
public:
	InputCommandBuilder() {}
	~InputCommandBuilder() {}

	static InputCommand * create_command(const int command_id, const std::string command_value)
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
		case 6:
			command = new CreateAttack(command_value);
			break;
		case 7:
			command = new Back();
			break;
		default:
			command = new InputCommand();
			break;
		}

		return command;
	}
};