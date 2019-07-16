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
		static int PUSH_LENGTH;
		static int KICK_LENGTH;

		Timer * block_time_, * move_left_time_,* move_right_time_;
		Entity * player_, * bot_;
		Uint32 block_rand_range_, kick_rand_range_, push_rand_range_, block_time_total_, move_left_time_total_, move_right_time_total_;
		InputCommands::Move * left_,* right_;
		Navigation::BlockAndCrawl * block_;
		AttackPresets::KickPreset * kick_;
		AttackPresets::PushPreset * push_;
	public:
		RandRangeCombat(Entity * bot, Entity * player, int block_rand, int kick_rand, int push_rand);

		void execute() override;
	};
}
