#pragma once
#include "Pathway.h"
#include "ECS.h"
#include "Navigation.h"

class PathHack
{
	PathTrunk * combat_, * menu_;
	int round_count_ = 0;
public:
	//DELETE THIS
	PathHack() = default;

	PathTrunk* initiateCombat(Entity * player_left, Entity * player_right, Entity * background)
	{
		combat_ = new PathTrunk();
		
		auto branch_1 = new PathBranch(combat_, nullptr, nullptr);
		branch_1->add_navigator<Navigation::ClearPrompts>();
		
		auto branch_2 = new PathBranch(combat_, nullptr, branch_1);
		branch_2->add_navigator<Navigation::Delay>(3000);
		
		auto branch_3 = new PathBranch(combat_, nullptr, branch_2);
		branch_3->add_navigator<Navigation::DisplayRoundPrompt>(main_prompt_round, main_number_0, ++round_count_);
		branch_3->add_navigator<Navigation::PlaySound>(sound_cymbal_swell);

		auto branch_4 = new PathBranch(combat_, nullptr, branch_3);
		branch_4->add_navigator<Navigation::ResetPlayersAndBackground>(player_left, player_right, background);
		/*branch_4->add_navigator<Navigation::BackgroundTransition>(4);*/

		combat_->current = branch_4;
		
		const auto select_attack = new PathTrunk();

		auto branch_6 = new PathBranch(select_attack, nullptr, nullptr);
		branch_6->add_navigator<Navigation::DisplayPrompt>(main_prompt_stop);

		branch_1 = new PathBranch(select_attack, nullptr, branch_6);
		branch_1->add_navigator<Navigation::StopMusic>();
		branch_1->add_navigator<Navigation::ChangeController>(player_left, controller_no_input);
		
		branch_2 = new PathBranch(select_attack, nullptr, branch_1);
		branch_2->add_navigator<Navigation::CreateOptionBox>(options_choose_attack, input_controller_player_1,  P1_OPTIONS, player_left);
		
		branch_3 = new PathBranch(select_attack, nullptr, branch_2);
		branch_3->add_navigator<Navigation::ClearPrompts>();
		
		branch_4 = new PathBranch(select_attack, nullptr, branch_3);
		branch_4->add_navigator<Navigation::Delay>(2000);
		
		auto branch_5 = new PathBranch(select_attack, nullptr, branch_4);
		branch_5->add_navigator<Navigation::DisplayPrompt>(main_prompt_select_attack);
		branch_5->add_navigator<Navigation::PlayMusic>(music_drum_beat, -1);
		
		select_attack->current = branch_5;
		select_attack->previous = combat_;
		combat_->next = select_attack;

		return combat_;
	}

	PathTrunk * attack_selection()
	{
		
	}


	PathTrunk * create_attack()
	{
		auto attack = new PathTrunk();


	}


	PathTrunk * initiate_menu()
	{
		menu_ = new PathTrunk();

		auto path_0_branch_1 = new PathBranch(menu_, nullptr, nullptr);
		path_0_branch_1->add_navigator<Navigation::ChangeState>(STATE_COMBAT);
		auto path_0_branch_2 = new PathBranch(menu_, nullptr, path_0_branch_1);
		path_0_branch_2->add_navigator<Navigation::CreateOptionBox>(options_choose_background, input_controller_player_1, P1_OPTIONS);
		auto path_0_branch_3 = new PathBranch(menu_, nullptr, path_0_branch_2);
		path_0_branch_3->add_navigator<Navigation::CreateOptionBox>(options_choose_character, input_controller_player_1, P1_OPTIONS);
		auto path_0_branch_4 = new PathBranch(menu_, nullptr, path_0_branch_3);
		path_0_branch_4->add_navigator<Navigation::CreateOptionBox>(options_choose_difficulty, input_controller_player_1, P1_OPTIONS);

		auto path_1_branch_1 = new PathBranch(menu_, nullptr, path_0_branch_2);
		path_1_branch_1->add_navigator<Navigation::CreateOptionBox>(options_choose_character, input_controller_player_2, P2_OPTIONS);
		path_1_branch_1->add_navigator<Navigation::CreateOptionBox>(options_choose_character, input_controller_player_1, P1_OPTIONS);

		auto path_menu = new PathBranch(menu_, path_1_branch_1, path_0_branch_4);
		path_menu->add_navigator<Navigation::CreateOptionBox>(options_start_menu, input_controller_player_1, P1_OPTIONS);

		auto path_root = new PathBranch(menu_, nullptr, path_menu);
		path_root->add_navigator<Navigation::PlayMusic>(music_yamborghini_high, -1);

		menu_->current = path_root;
		return menu_;
	}

};
