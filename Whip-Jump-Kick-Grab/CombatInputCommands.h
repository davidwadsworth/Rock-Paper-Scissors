#pragma once
#include "InputCommand.h"
#include "CombatNavigation.h"

/**
 * @autho David Wadsworth
 * 
 * implemented Combat Commands
 */


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
		ScriptPush()
			: was_pressed_(true)
		{}

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class ScriptKick : public InputCommand
	{
		bool was_pressed_;
	public:
		ScriptKick()
			: was_pressed_(true)
		{}

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class ScriptBlock : public InputCommand
	{
		Navigation::BlockAndCrawl * block_;
		bool was_pressed_;
	public:
		ScriptBlock()
			: block_(nullptr), was_pressed_(true)
		{}
		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class EndCombat : public InputCommand
	{
		bool was_pressed_;
	public:
		EndCombat()
			: was_pressed_(false)
		{}

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};

	class SelectAttack : public InputCommand
	{
		bool was_pressed_;
	public:
		SelectAttack()
			: was_pressed_(false)
		{}

		void idle(Entity* entity) override;
		void execute(Entity* entity) override;
	};
}

