#pragma once
#include "Commands.h"
using namespace LinkCommands;

class LinkCommandBuilder
{
public:
	LinkCommandBuilder() {}
	~LinkCommandBuilder() {}

	static Command * create_command(const int command_id, const std::string command_value)
	{
		Command * command;
		switch (command_id)
		{
		case 0:
			command = new ChangeState(command_value);
			break;
		case 1:
			command = new SelectAttack(command_value);
			break;
		case 2:
			command = new ChooseCharacter(command_value);
			break;
		case 3:
			command = new ChooseBackground(command_value);
			break;
		case 4:
			command = new SetDifficulty(command_value);
			break;
		case 5:
			command = new SetGameMode(command_value);
			break;
		default:
			command = new Command();
			break;
		}
		return command;
	}
};