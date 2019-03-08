#pragma once
#include "Commands.h"

class LinkCommandBuilder
{
public:
	LinkCommandBuilder() {}
	~LinkCommandBuilder() {}

	LinkCommand * create_command(const int command_id, const std::string command_value)
	{
		LinkCommand * command;
		switch (command_id)
		{
		case 0:
			command = new ChangeStateLink(command_value);
			break;
		case 1:
			command = new ChangeScreenLink();
			break;
		case 2:
			command = new SelectAttackLink(command_value);
			break;
		case 3:
			command = new UndoLink();
			break;
		case 4:
			command = new ChooseCharacterLink(command_value);
			break;
		case 5:
			command = new ChooseBackgroundLink(command_value);
			break;
		case 6:
			command = new SetDifficultyLink(command_value);
			break;
		case 7:
			command = new SinglePlayerLink();
			break;
		case 8:
			command = new TwoPlayerLink();
			break;
		default:
			command = new NothingLink();
			break;
		}
		return command;
	}
};