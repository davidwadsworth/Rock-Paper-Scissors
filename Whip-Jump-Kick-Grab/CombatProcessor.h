#pragma once
#include "Processes.h"
#include "ECS.h"
#include <vector>




struct CombatProcessor
{
	int current_task;
	CombatProcessor(Entity * player_left, Entity * player_right, Entity * background)
		: current_task(0), round_count_(0), process_size_(0), player_left_(player_left), player_right_(player_right), background_(background)
	{}

	~CombatProcessor() 
	{}

	void create_combat()
	{
		round_count_++;
		current_task = 0;
		tasks.clear();
		tasks.push_back(new Skip());
		tasks.push_back(new ResetGame(player_left_, player_right_, background_));
		tasks.push_back(new AndMultiProcessor({ new DisplayRoundPrompt(main_prompt_round, main_number_0,  round_count_), new PlaySound(sound_cymbal_swell) }));
		tasks.push_back(new Delay(3000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new AndMultiProcessor({ new DisplayPrompt(main_prompt_select_attack), new PlayMusic(music_drum_beat, -1) }));
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new ChangeController(player_left_, player_right_, controller_no_input) );
		tasks.push_back(new StopMusic());
		tasks.push_back(new AndMultiProcessor({ new DisplayPrompt(main_prompt_fight), new PlaySound(sound_combat_start) }));
		tasks.push_back(new Delay(1000));
		tasks.push_back(new AndMultiProcessor({ new ClearPrompts(), new ChangeController(player_left_, player_right_, controller_combat_fight) }));
		tasks.push_back(new AndMultiProcessor({new Delay(5000), new CombatCollision(player_left_, player_right_)}));
		tasks.push_back(new AndMultiProcessor({ new StopRound(player_left_, player_right_), new DisplayPrompt(main_prompt_stop),  new ChangeController(player_left_, player_right_, controller_no_input) }));
		tasks.push_back(new Delay(500));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new EndOfRoundSequence(player_left_, player_right_, this));
		tasks.push_back(new PlaySound(sound_miss));
		tasks.push_back(new DrawAttackLines(player_left_, player_right_, 1000));
		tasks.push_back(new DisplayPrompt(main_prompt_miss) );
		tasks.push_back(new Delay(1000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new CleanUp(player_left_, player_right_, this));
	}


	void end_of_round(Entity * winner)
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		tasks.push_back(new PlaySound(sound_hit_2));
		tasks.push_back(new DrawAttackLines(player_left_, player_right_, 1000));
		if (winner->get_component<SpriteComponent>().sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			tasks.push_back(new DisplayPrompt(main_prompt_player_2_wins));
		}
		else
		{
			tasks.push_back(new DisplayPrompt(main_prompt_player_1_wins));
		}
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new CleanUp(player_left_, player_right_, this));
	}
	
	void go_to_menu()
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		tasks.push_back(new Delay(1000));
		tasks.push_back(new ChangeStateProcess(STATE_MENU));
	}

	void match_winner()
	{
		tasks.clear();
		current_task = 0;
		tasks.push_back(new Skip());
		if (player_left_->get_component<PlayerComponent>().num_wins >= ROUNDWIN)
			tasks.push_back(new DisplayPrompt(main_prompt_player_1_match_win));
		else
			tasks.push_back(new DisplayPrompt(main_prompt_player_2_match_win));
		tasks.push_back(new PlaySound(sound_round_end));
		tasks.push_back(new Delay(2000));
		tasks.push_back(new ClearPrompts());
		tasks.push_back(new Delay(500));
		tasks.push_back(new ChangeStateProcess(STATE_MENU));

	}

	void next_process()
	{
		if (current_task < tasks.size())
			current_task++;
	}

	std::vector<Process *> tasks;

private:
	int round_count_, process_size_;
	Entity * player_left_, *player_right_, *background_;
};

