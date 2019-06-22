#pragma once
#include "Commands.h"
#include "CombatInputCommands.h"

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
			command = new InputCommands::Move(command_value);
			break;
		case 1:
			command = new InputCommands::PauseGame();
			break;
		case 2:
			command = new InputCommands::MoveCursorY(command_value);
			break;
		case 3:
			command = new InputCommands::MoveCursorX(command_value);
			break;
		case 4:
			command = new InputCommands::MakeSelection();
			break;
		case 5:
			command = new InputCommands::Back();
			break;
		case 6:
			command = new CombatCommands::ScriptPush();
			break;
		case 7:
			command = new CombatCommands::ScriptKick();
			break;
		case 8:
			command = new CombatCommands::ScriptBlock();
			break;
		case 9:
			command = new CombatCommands::EndCombat();
			break;
		case 10:
			command = new CombatCommands::SelectAttack();
			break;
		case 11:
			command = new InputCommands::LoadData();
			break;
		case 12:
			command = new InputCommands::IChangeState();
			break;
		default:
			command = new InputCommand();
			break;
		}

		return command;
	}
};