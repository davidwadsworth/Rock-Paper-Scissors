#include "stdafx.h"
#include "MenuPresets.h"
#include "AudioNavigation.h"
#include "CommonNavigation.h"
#include "TransformationNavigation.h"

void MenuPresets::CreateMenuOptions::init()
{
	const auto menu = new PathTrunk();

	auto set_state_combat = new PathBranch(menu, nullptr, nullptr);
	set_state_combat->add_navigator<Navigation::ChangeState>(STATE_COMBAT);
	auto choose_difficulty = new PathBranch(menu, nullptr, set_state_combat);
	choose_difficulty->add_navigator<Navigation::CreateMenuOptionBox>(state_->palette, options_choose_difficulty, input_controller_player_1, P1_OPTIONS);

	auto path_menu = new PathBranch(menu, set_state_combat, choose_difficulty);
	path_menu->add_navigator<Navigation::CreateMenuOptionBox>(state_->palette, options_start_menu, input_controller_player_1, P1_OPTIONS);

	auto play_menu_music = new PathBranch(menu, nullptr, path_menu);
	play_menu_music->add_navigator<Navigation::PlayMusic>(state_->audio_player, music_yamborghini_high, -1);

	auto transition = new PathBranch(menu, nullptr, play_menu_music);
	transition->add_navigator<Navigation::BackgroundTransition>(state_->palette, TRANSITION_SPEED);

	menu->current = transition;
	set_trunk(menu);
}
