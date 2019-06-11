#pragma once
#include "Pathway.h"
#include "ECS.h"
#include "Navigation.h"

class PathHack
{
	PathTrunk * combat_ = nullptr, * menu_ = nullptr, * select_attack_ = nullptr;
	int round_count_ = 0;
	GameState * state_;
public:
	//DELETE THIS
	PathHack(GameState * state)
		: state_(state)
	{}

	~PathHack()
	{
	}
	void close() const
	{
		if (combat_)
			combat_->remove();
		if (menu_)
			menu_->remove();
		if(select_attack_)
			select_attack_->remove();
	}

	PathTrunk* initiateCombat(Entity * player_left, Entity * player_right, Entity * background)
	{
		combat_ = new PathTrunk();
		
		auto branch_1 = new PathBranch(combat_, nullptr, nullptr);
		
		auto branch_2 = new PathBranch(combat_, nullptr, nullptr);
		branch_2->add_navigator<Navigation::PlaySound>(state_->audio_player, sound_cymbal_swell);

		auto branch_3 = new PathBranch(combat_, nullptr, branch_2);
		branch_3->add_navigator<Navigation::DisplayRoundPrompt>(state_->palette, 300, ss_main_prompt_round, ss_main_number_0, ++round_count_);

		auto branch_4 = new PathBranch(combat_, nullptr, branch_3);
		branch_4->add_navigator<Navigation::ResetPlayersAndBackground>(player_left, player_right, background);
		branch_4->add_navigator<Navigation::BackgroundTransition>(state_->palette, 3);

		combat_->current = branch_4;
		
		select_attack_ = new PathTrunk();

		auto branch_6 = new PathBranch(select_attack_, nullptr, nullptr);
		branch_6->add_navigator<Navigation::DisplayPrompt>(state_->palette, 1000, ss_main_prompt_stop);

		auto branch_1 = new PathBranch(select_attack_, nullptr, branch_6);
		branch_1 = new PathBranch(select_attack_, nullptr, branch_6);
		branch_1->add_navigator<Navigation::StopMusic>(state_->audio_player);
		branch_1->add_navigator<Navigation::DisableController>(player_left);
		
		branch_2 = new PathBranch(select_attack_, nullptr, branch_1);
		branch_2->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_choose_attack, input_controller_player_1,  P1_OPTIONS, player_left);
		
		branch_4 = new PathBranch(select_attack_, nullptr, branch_2);
		branch_4->add_navigator<Navigation::DisplayPrompt>(state_->palette, 200, ss_main_prompt_select_attack);
		
		auto branch_5 = new PathBranch(select_attack_, nullptr, branch_4);
		branch_5->add_navigator<Navigation::PlayMusic>(state_->audio_player, music_drum_beat, -1);
		
		select_attack_->current = branch_5;
		combat_->next = select_attack_;

		return combat_;
	}


	PathTrunk * initiate_menu()
	{
		menu_ = new PathTrunk();

		auto path_0_branch_1 = new PathBranch(menu_, nullptr, nullptr);
		path_0_branch_1->add_navigator<Navigation::ChangeState>(STATE_COMBAT);
		auto path_0_branch_4 = new PathBranch(menu_, nullptr, path_0_branch_1);
		path_0_branch_4->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_choose_difficulty, input_controller_player_1, P1_OPTIONS);

		auto path_menu = new PathBranch(menu_, path_0_branch_1, path_0_branch_4);
		path_menu->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_start_menu, input_controller_player_1, P1_OPTIONS);

		auto path_root = new PathBranch(menu_, nullptr, path_menu);
		path_root->add_navigator<Navigation::PlayMusic>(state_->audio_player, music_yamborghini_high, -1);

		menu_->current = path_root;
		return menu_;
	}

};
