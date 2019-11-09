#pragma once
#include "Targetable.h"
#include "Command.h"

/**
 * @author David Wadsworth
 *
 * Commands that are bound to OptionBoxes
 */

namespace LinkCommands
{
	class ChangeState : public Command
	{
		int state_, previous_state_;
		Entity * entity_;
	public:
		explicit ChangeState(const std::string new_state)
			: state_(std::stoi(new_state)), previous_state_(0), entity_(nullptr)
		{
		}

		void execute(Entity* entity) override;

	};

	class SelectAttack : public Command, public Targetable
	{
		int attack_id_, previous_attack_id_;
		Entity * target_, *entity_;
	public:
		explicit SelectAttack(const std::string command_val)
			: attack_id_(stoi(command_val)), previous_attack_id_(0), target_(nullptr), entity_(nullptr)
		{}

		void change_target(Entity* target) override;

		void execute(Entity * entity) override;
	};


	class ChooseCharacter : public Command
	{
		Entity * entity_;
		int character_id_, previous_id_;
	public:
		explicit ChooseCharacter(const std::string command_value)
			: character_id_(stoi(command_value)), previous_id_(0), entity_(nullptr)
		{
		}

		void execute(Entity* entity) override{}
	};

	class ChooseBackground : public Command
	{
		int background_id_, previous_id_;
	public:
		explicit ChooseBackground(const std::string command_value)
			: background_id_(stoi(command_value)), previous_id_(0)
		{}

		void execute(Entity* entity) override{}
	};

	class SetDifficulty : public Command
	{
		int difficulty_id_;
		Entity * entity_;
	public:
		explicit SetDifficulty(const std::string command_value)
			: difficulty_id_(stoi(command_value)), entity_(nullptr)
		{
		}

		void execute(Entity* entity) override;
	};

	class SetGameMode : public Command
	{
		int game_id_;
	public:
		SetGameMode(const std::string command_value)
			: game_id_(stoi(command_value))
		{}
		void execute(Entity* entity) override;
	};
}
