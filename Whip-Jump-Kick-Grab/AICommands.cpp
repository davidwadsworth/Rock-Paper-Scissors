#include "stdafx.h"
#include "AICommands.h"

void AICommands::RandomSelectAttack::execute()
{
	srand(SDL_GetTicks());
	const auto random_attack = rand() % 3;

	bot_->get_component<PlayerComponent>().choose_final_attack(random_attack);
}

void AICommands::SelectWinner::execute()
{
	const auto player_attack = player_->get_component<PlayerComponent>().get_final_attack()->encoding;

	if (player_attack == 7)
		bot_->get_component<PlayerComponent>().choose_final_attack(final_attack_Jump_Kick);
	else if (player_attack == 8)
		bot_->get_component<PlayerComponent>().choose_final_attack(final_attack_grab);
	else
		bot_->get_component<PlayerComponent>().choose_final_attack(final_attack_whip);
}


AICommands::RandRangeCombat::RandRangeCombat(Entity * bot, Entity* player, AIData * data)
	: player_(player), bot_(bot), data_(data), block_time_total_(0), move_left_time_total_(0), move_right_time_total_(0)
{
	left_ = new InputCommands::Move(-1, animation_player_walk_left);
	right_ = new InputCommands::Move(1, animation_player_walk_right);
	block_ = new Navigation::BlockAndCrawl(bot_, 0.5);
	kick_ = new AttackPresets::KickPreset(player_, bot_);
	push_ = new AttackPresets::PushPreset(player_, bot_);
	block_time_ = new Timer();
	move_left_time_ = new Timer();
	move_right_time_ = new Timer();
}



void AICommands::RandRangeCombat::execute()
{
	if (bot_->get_component<ScriptComponent>().is_empty())
	{
		srand(SDL_GetTicks());

		if (move_left_time_->is_started())
		{
			if (move_left_time_->get_ticks() > move_left_time_total_)
				move_left_time_->stop();
			left_->execute(bot_);
		}
		else if (move_right_time_->is_started())
		{
			if (move_right_time_->get_ticks() > move_right_time_total_)
				move_right_time_->stop();
			right_->execute(bot_);
		}
		else
		{
			if (rand() % 2)
			{
				move_left_time_->start();
				move_left_time_total_ = rand() % data_->move_left_range_max + data_->move_left_range_min;
			}
			else
			{
				move_right_time_->start();
				move_right_time_total_ = rand() % data_->move_right_range_max + data_->move_right_range_min;
			}
		}

		if (block_time_->is_started())
		{
			if (block_time_->get_ticks() > block_time_total_)
			{
				block_->close();
				block_time_->stop();
			}
		}
		if (bot_->get_component<TransformComponent>().get_horizontal_distance(player_) < data_->push_range)
		{
			if (static_cast<Uint32>(rand() % RAND_CONSTANT) < data_->push_rand_range)
			{
				push_->init();
				bot_->get_component<ScriptComponent>().empty_add(push_->get_trunk());
			}
		}
		if (bot_->get_component<TransformComponent>().get_horizontal_distance(player_) < data_->block_range)
		{
			if (static_cast<Uint32>(rand() % RAND_CONSTANT) < data_->block_rand_range)
			{
				block_->init();
				block_time_->start();
				block_time_total_ = rand() % data_->block_range_max + data_->block_range_min;
			}
		}
		if (bot_->get_component<TransformComponent>().get_horizontal_distance(player_) < data_->kick_range)
		{
			if (static_cast<Uint32>(rand() % RAND_CONSTANT) < data_->kick_rand_range)
			{
				kick_->init();
				bot_->get_component<ScriptComponent>().empty_add(kick_->get_trunk());
			}

		}
		
	}

}
