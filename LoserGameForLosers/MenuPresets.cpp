#include "stdafx.h"
#include "MenuPresets.h"
#include "AudioNavigation.h"
#include "CommonNavigation.h"
#include "TransformationNavigation.h"
#include "MenuNavigation.h"

MenuPresets::CreateMenuOptions::CreateMenuOptions(Entity * screen)
	: screen_(screen)
{
	manager_ = GameState::get_manager();
}

void MenuPresets::CreateMenuOptions::init()
{
	const auto menu = new PathTrunk();

	auto set_state_combat = new PathBranch(menu, nullptr, nullptr);
	set_state_combat->add_navigator(new Navigation::ChangeState(STATE_COMBAT));

	auto how_to_play = new PathBranch(menu, set_state_combat, set_state_combat);
	how_to_play->add_navigator(new Navigation::ChangeScreen(screen_, ss_menu_how_to_play));

	auto choose_difficulty = new PathBranch(menu, nullptr, set_state_combat);
	choose_difficulty->add_navigator(new Navigation::CreateOptionBox(manager_, order_texture_menu_glyph_atlas, ss_menu_cursor, options_choose_difficulty, input_controller_player_1_single, controller_menu_options, P1_OPTIONS));

	auto path_menu = new PathBranch(menu, how_to_play, choose_difficulty);
	path_menu->add_navigator(new Navigation::CreateOptionBox(manager_, order_texture_menu_glyph_atlas, ss_menu_cursor, options_start_menu, input_controller_player_1_single, controller_menu_options, P1_OPTIONS));

	auto play_menu_music = new PathBranch(menu, nullptr, path_menu);
	play_menu_music->add_navigator(new Navigation::PlayMusic(GameState::get_audio_player(), music_title_theme, -1));

	auto transition = new PathBranch(menu, nullptr, play_menu_music);
	transition->add_navigator(new Navigation::BackgroundTransition(manager_, order_texture_menu_white_background, TRANSITION_SPEED));

	menu->current = transition;
	set_trunk(menu);
}
