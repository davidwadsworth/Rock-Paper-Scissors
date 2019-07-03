#include "stdafx.h"
#include "CombatPresets.h"
#include "AudioNavigation.h"
#include "TransformationNavigation.h"
#include "CombatNavigation.h"

void CombatPresets::ResetCombat::init()
{
	const auto reset_combat = new PathTrunk();

	auto display_round = new PathBranch(reset_combat, nullptr, nullptr);
	display_round->add_navigator(new Navigation::DisplayRoundPrompt(manager_, PROMPT_DELAY, ss_main_prompt_round, ss_main_number_0, ++round_count_));

	auto play_round_sound = new PathBranch(reset_combat, nullptr, display_round);
	play_round_sound->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_cymbal_swell));

	auto transition = new PathBranch(reset_combat, nullptr, play_round_sound);
	transition->add_navigator(new Navigation::BackgroundTransition(manager_, order_texture_combat_gray_background, TRANSITION_SPEED));

	auto reset_entities = new PathBranch(reset_combat, nullptr, transition);
	reset_entities->add_navigator(new Navigation::ResetPlayersAndBackground(player_1_, player_2_, background_));
	reset_entities->add_navigator(new Navigation::DisableController(player_1_));
	reset_entities->add_navigator(new Navigation::DisableController(player_2_));

	reset_combat->current = reset_entities;
	set_trunk(reset_combat);
}

void CombatPresets::SinglePlayerSelectAttack::init()
{
	const auto select_attack = new PathTrunk();

	auto display_stop = new PathBranch(select_attack, nullptr, nullptr);
	display_stop->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_stop));

	auto clean_up = new PathBranch(select_attack, nullptr, display_stop);
	clean_up->add_navigator(new Navigation::StopMusic(GameState::get_audio_player()));

	auto choose_attack = new PathBranch(select_attack, nullptr, clean_up);
	choose_attack->add_navigator(new Navigation::CreateOptionBox(manager_, order_texture_combat_glyph_atlas, ss_main_cursor_box, options_choose_attack, input_controller_player_1, controller_combat_options, P1_OPTIONS, player_1_));

	auto display_select_attack = new PathBranch(select_attack, nullptr, choose_attack);
	display_select_attack->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_select_attack));

	auto select_attack_music = new PathBranch(select_attack, nullptr, display_select_attack);
	select_attack_music->add_navigator(new Navigation::PlayMusic(GameState::get_audio_player(), music_drum_beat, -1));

	select_attack->current = select_attack_music;
	set_trunk(select_attack);
}

void CombatPresets::SinglePlayerCombat::init()
{
	const auto combat = new PathTrunk();

	auto display_stop = new PathBranch(combat, nullptr, nullptr);
	display_stop->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_stop));

	auto disable_controller = new PathBranch(combat, nullptr, display_stop);
	disable_controller->add_navigator(new Navigation::DisableController(player_1_));
	disable_controller->add_navigator(new Navigation::ResetVelocity(player_1_));
	disable_controller->add_navigator(new Navigation::ResetVelocity(player_2_));
	disable_controller->add_navigator(new Navigation::ResetAnimations(player_1_));
	disable_controller->add_navigator(new Navigation::ResetAnimations(player_2_));
	disable_controller->add_navigator(new Navigation::StopMusic(GameState::get_audio_player()));

	auto round = new PathBranch(combat, nullptr, disable_controller);
	round->add_navigator(new Navigation::CombatCollision(player_1_, player_2_));
	round->add_navigator(new Navigation::Delay(ROUND_TIME));

	auto enable_controller = new PathBranch(combat, nullptr, round);
	enable_controller->add_navigator(new Navigation::EnableController(player_1_));
	enable_controller->add_navigator(new Navigation::PlayMusic(GameState::get_audio_player(), music_combat, -1));

	auto display_fight = new PathBranch(combat, nullptr, enable_controller);
	display_fight->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_fight));

	combat->current = display_fight;
	set_trunk(combat);
}

void CombatPresets::RoundEnding::init()
{
	const auto round_ending = new PathTrunk();

	const auto player_1_attack_data = player_1_->get_component<PlayerComponent>().get_final_attack();
	const auto player_2_attack_data = player_2_->get_component<PlayerComponent>().get_final_attack();

	auto clean_up = new PathBranch(round_ending, nullptr, nullptr);
	clean_up->add_navigator(new Navigation::SwapPriority(player_1_, player_2_));

	auto display_miss = new PathBranch(round_ending, nullptr, clean_up);
	display_miss->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_miss));

	auto display_player_2_wins = new PathBranch(round_ending, nullptr, clean_up);
	display_player_2_wins->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_player_2_wins));

	auto check_player_1_loss = new PathBranch(round_ending, nullptr, display_player_2_wins);
	check_player_1_loss->add_navigator(new Navigation::CheckRoundLoss(order_player_1));

	auto player_1_gets_hit = new PathBranch(round_ending, nullptr, check_player_1_loss);
	player_1_gets_hit->add_navigator(new Navigation::ReceiveDamage(order_player_1, player_2_attack_data->damage));
	player_1_gets_hit->add_navigator(new Navigation::LockedAnimation(player_1_, animation_player_hit));
	player_1_gets_hit->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_hit_3));

	auto display_player_1_wins = new PathBranch(round_ending, nullptr, clean_up);
	display_player_1_wins->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_player_1_wins));

	auto check_player_2_loss = new PathBranch(round_ending, nullptr, display_player_1_wins);
	check_player_2_loss->add_navigator(new Navigation::CheckRoundLoss(order_player_2));

	auto player_2_gets_hit = new PathBranch(round_ending, nullptr, check_player_2_loss);
	player_2_gets_hit->add_navigator(new Navigation::ReceiveDamage(order_player_2, player_1_attack_data->damage));
	player_2_gets_hit->add_navigator(new Navigation::LockedAnimation(player_2_, animation_player_hit));
	player_2_gets_hit->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_hit_1));

	auto player_1_att_animation = new PathBranch(round_ending, nullptr, player_2_gets_hit);
	player_1_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_1_, player_1_attack_data->encoding, 0));

	auto player_2_att_animation = new PathBranch(round_ending, nullptr, player_1_gets_hit);
	player_2_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_2_, player_2_attack_data->encoding, 0));

	auto second_check_collision_p1_att = new PathBranch(round_ending, player_2_gets_hit, display_miss);
	second_check_collision_p1_att->add_navigator(new Navigation::CheckCollision(player_1_, player_2_));

	auto second_p1_attack_delay = new PathBranch(round_ending, nullptr, second_check_collision_p1_att);
	second_p1_attack_delay->add_navigator(new Navigation::Delay(ATTACK_DELAY));

	auto second_p1_move_att = new PathBranch(round_ending, nullptr, second_p1_attack_delay);
	second_p1_move_att->add_navigator(new Navigation::MovePlayerToCollision(player_1_, player_2_, player_1_attack_data->distance));

	auto second_p1_att_animation = new PathBranch(round_ending, nullptr, second_p1_move_att);
	second_p1_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_1_, player_1_attack_data->encoding, 0));

	auto second_check_collision_p2_att = new PathBranch(round_ending,  player_1_gets_hit, display_miss );
	second_check_collision_p2_att->add_navigator(new Navigation::CheckCollision(player_1_, player_2_));

	auto second_p2_attack_delay = new PathBranch(round_ending, nullptr, second_check_collision_p2_att);
	second_p2_attack_delay->add_navigator(new Navigation::Delay(ATTACK_DELAY));

	auto second_p2_move_att = new PathBranch(round_ending, nullptr, second_p2_attack_delay);
	second_p2_move_att->add_navigator(new Navigation::MovePlayerToCollision(player_2_, player_1_, player_2_attack_data->distance));

	auto second_p2_att_animation = new PathBranch(round_ending, nullptr, second_p2_move_att);
	second_p2_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_2_, player_2_attack_data->encoding, 0));

	auto second_check_priority = new PathBranch(round_ending, second_p2_att_animation, second_p1_att_animation );
	second_check_priority->add_navigator(new Navigation::CheckPriority(player_1_));

	auto reset_animations = new PathBranch(round_ending, nullptr, second_check_priority);
	reset_animations->add_navigator(new Navigation::ResetAnimations(player_1_));
	reset_animations->add_navigator(new Navigation::ResetAnimations(player_2_));

	auto check_for_winner = new PathBranch(round_ending, player_1_att_animation, player_2_att_animation);
	check_for_winner->add_navigator(new Navigation::CheckWinner(player_1_, player_2_));

	auto check_for_collisions = new PathBranch(round_ending, check_for_winner, reset_animations);
	check_for_collisions->add_navigator(new Navigation::CheckCollision(player_1_, player_2_));

	auto p2_attack_delay = new PathBranch(round_ending, nullptr, check_for_collisions);
	p2_attack_delay->add_navigator(new Navigation::Delay(ATTACK_DELAY));

	auto p2_move_att = new PathBranch(round_ending, nullptr, p2_attack_delay);
	p2_move_att->add_navigator(new Navigation::MovePlayerToCollision(player_2_, player_1_, player_2_attack_data->distance));

	auto p2_att_animation = new PathBranch(round_ending, nullptr, p2_move_att);
	p2_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_2_, player_2_attack_data->encoding, 0));

	auto p1_attack_delay = new PathBranch(round_ending, nullptr, check_for_collisions);
	p1_attack_delay->add_navigator(new Navigation::Delay(ATTACK_DELAY));

	auto p1_move_att = new PathBranch(round_ending, nullptr, p1_attack_delay);
	p1_move_att->add_navigator(new Navigation::MovePlayerToCollision(player_1_, player_2_, player_1_attack_data->distance));

	auto p1_att_animation = new PathBranch(round_ending, nullptr, p1_move_att);
	p1_att_animation->add_navigator(new Navigation::ExecuteFinalAttack(player_1_, player_1_attack_data->encoding, 0));

	auto check_priority = new PathBranch(round_ending, p1_att_animation, p2_att_animation );
	check_priority->add_navigator(new Navigation::CheckPriority(player_1_));

	round_ending->current = check_priority;
	set_trunk(round_ending);
}

void CombatPresets::MultiPlayerCombat::init()
{
	const auto combat = new PathTrunk();

	auto display_stop = new PathBranch(combat, nullptr, nullptr);
	display_stop->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_stop));

	auto disable_controller = new PathBranch(combat, nullptr, display_stop);
	disable_controller->add_navigator(new Navigation::DisableController(player_1_));
	disable_controller->add_navigator(new Navigation::DisableController(player_2_));
	disable_controller->add_navigator(new Navigation::ResetVelocity(player_1_));
	disable_controller->add_navigator(new Navigation::ResetVelocity(player_2_));
	disable_controller->add_navigator(new Navigation::ResetAnimations(player_1_));
	disable_controller->add_navigator(new Navigation::ResetAnimations(player_2_));
	disable_controller->add_navigator(new Navigation::StopMusic(GameState::get_audio_player()));

	auto clear_scripts = new PathBranch(combat, nullptr, disable_controller);
	clear_scripts->add_navigator(new Navigation::ClearPath(player_1_));
	clear_scripts->add_navigator(new Navigation::ClearPath(player_2_));

	auto round = new PathBranch(combat, nullptr, clear_scripts);
	round->add_navigator(new Navigation::CombatCollision(player_1_, player_2_));
	round->add_navigator(new Navigation::Delay(ROUND_TIME));

	auto round_music = new PathBranch(combat, nullptr, round);
	round_music->add_navigator(new Navigation::PlayMusic(GameState::get_audio_player(), music_combat, -1));

	auto enable_controller = new PathBranch(combat, nullptr, round_music);
	enable_controller->add_navigator(new Navigation::EnableController(player_1_));
	enable_controller->add_navigator(new Navigation::EnableController(player_2_));

	auto display_fight = new PathBranch(combat, nullptr, enable_controller);
	display_fight->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_fight));

	combat->current = display_fight;
	set_trunk(combat);
}

void CombatPresets::MultiPlayerSelectAttack::init()
{
	const auto select_attack = new PathTrunk();

	auto clean_up = new PathBranch(select_attack, nullptr, nullptr);
	clean_up->add_navigator(new Navigation::StopMusic(GameState::get_audio_player()));

	auto choose_attack_player_2 = new PathBranch(select_attack, nullptr, clean_up);
	choose_attack_player_2->add_navigator(new Navigation::CreateOptionBox(manager_, order_texture_combat_glyph_atlas, ss_main_cursor_box, options_choose_attack, input_controller_player_2, controller_combat_options, P2_OPTIONS, player_2_));

	auto choose_attack_player_1 = new PathBranch(select_attack, nullptr, choose_attack_player_2);
	choose_attack_player_1->add_navigator(new Navigation::CreateOptionBox(manager_, order_texture_combat_glyph_atlas, ss_main_cursor_box, options_choose_attack, input_controller_player_1, controller_combat_options, P1_OPTIONS, player_1_));

	auto display_select_attack = new PathBranch(select_attack, nullptr, choose_attack_player_1);
	display_select_attack->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY, ss_main_prompt_select_attack));

	auto play_music = new PathBranch(select_attack, nullptr, display_select_attack);
	play_music->add_navigator(new Navigation::PlayMusic(GameState::get_audio_player(), music_drum_beat, -1));

	select_attack->current = play_music;
	set_trunk(select_attack);
}

void CombatPresets::MatchEnding::init()
{
	const auto end_match = new PathTrunk();

	auto players = GameState::get_manager()->get_group(Game::group_players);

	auto go_to_menu = new PathBranch(end_match, nullptr, nullptr);
	go_to_menu->add_navigator(new Navigation::ChangeState(STATE_MENU));

	auto display_match_winner = new PathBranch(end_match, nullptr, go_to_menu);
	if (!player_)
		display_match_winner->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY + 1000, ss_main_prompt_player_2_match_win));
	else
		display_match_winner->add_navigator(new Navigation::DisplayPrompt(manager_, PROMPT_DELAY + 1000, ss_main_prompt_player_1_match_win));
	
	auto play_music = new PathBranch(end_match, nullptr, display_match_winner);
	play_music->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_round_end));

	auto knock_out_loser = new PathBranch(end_match, nullptr, play_music);
	knock_out_loser->add_navigator(new Navigation::SetAnimation(players[player_], animation_player_hit, 2));

	auto disable_controllers = new PathBranch(end_match, nullptr, knock_out_loser);
	disable_controllers->add_navigator(new Navigation::DisableController(players[0]));
	disable_controllers->add_navigator(new Navigation::DisableController(players[1]));
	disable_controllers->add_navigator(new Navigation::ResetVelocity(players[0]));
	disable_controllers->add_navigator(new Navigation::ResetVelocity(players[1]));

	end_match->current = disable_controllers;
	set_trunk(end_match);
}

void CombatPresets::EnableMovement::init()
{
	const auto enable_controller = new PathTrunk();
	auto reset_controllers = new PathBranch(enable_controller, nullptr, nullptr);
	reset_controllers->add_navigator(new Navigation::EnableController(player_1_));
	reset_controllers->add_navigator(new Navigation::EnableController(player_2_));

	enable_controller->current = reset_controllers;
	set_trunk(enable_controller);

}
