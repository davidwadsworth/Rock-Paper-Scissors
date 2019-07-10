#pragma once
#include "InputCommand.h"
#include "CombatNavigation.h"

namespace Navigation
{
	class BlockPlayer;
}

namespace CombatCommands
{
	class ScriptPush : public InputCommand
	{
		bool was_pressed_;
	public:
		ScriptPush() = default;

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class ScriptKick : public InputCommand
	{
		bool was_pressed_;
	public:
		ScriptKick() = default;

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class ScriptBlock : public InputCommand
	{
		Navigation::BlockAndCrawl * block_;
		bool was_pressed_ = true;
	public:
		ScriptBlock() = default;

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class EndCombat : public InputCommand
	{
		bool was_pressed_ = false;
	public:
		EndCombat() = default;

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class SelectAttack : public InputCommand
	{
		bool was_pressed_;
	public:
		SelectAttack() = default;

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};
}

