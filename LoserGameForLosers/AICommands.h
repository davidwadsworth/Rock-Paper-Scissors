#pragma once
#include "AICommand.h"

/**
 * @author David Wadsworth
 * 
 * commands that are bound to robots
 */


namespace AICommands
{
	class RandomSelectAttack : public AICommand
	{
		Entity * bot_;
	public:
		RandomSelectAttack(Entity * bot)
			: bot_(bot)
		{}

		void execute() override;
	};

	class SelectWinner : public AICommand
	{
		Entity * player_,* bot_;
	public:
		SelectWinner(Entity * bot, Entity * player )
			: player_(player), bot_(bot)
		{}

		void execute() override;
	};


	class RandRangeCombat : public AICommand
	{

		Timer * block_time_, * move_left_time_,* move_right_time_;
		Entity * player_, * bot_;
		AIData * data_;
		Uint32 block_time_total_, move_left_time_total_, move_right_time_total_;
		InputCommands::Move * left_,* right_;
		Navigation::BlockAndCrawl * block_;
		AttackPresets::KickPreset * kick_;
		AttackPresets::PushPreset * push_;
	public:
		RandRangeCombat(Entity * bot, Entity * player, AIData * data);

		void execute() override;
	};
}
