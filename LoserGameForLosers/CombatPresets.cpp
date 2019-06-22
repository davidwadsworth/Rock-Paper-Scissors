#include "stdafx.h"
#include "CombatPresets.h"
#include "AudioNavigation.h"
#include "TransformationNavigation.h"
#include "CombatNavigation.h"

void CombatPresets::ResetCombat::init()
{
	const auto reset_combat = new PathTrunk();

	auto display_round = new PathBranch(reset_combat, nullptr, nullptr);
	display_round->add_navigator<Navigation::DisplayRoundPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_round, ss_main_number_0, ++round_count_);

	auto play_round_sound = new PathBranch(reset_combat, nullptr, display_round);
	play_round_sound->add_navigator<Navigation::PlaySound>(state_->audio_player, sound_cymbal_swell);

	auto reset_entities = new PathBranch(reset_combat, nullptr, play_round_sound);
	reset_entities->add_navigator<Navigation::ResetPlayersAndBackground>(player_1_, player_2_, background_);
	reset_entities->add_navigator<Navigation::DisableController>(player_1_);
	reset_entities->add_navigator<Navigation::DisableController>(player_2_);


	reset_combat->current = reset_entities;
	set_trunk(reset_combat);
}

void CombatPresets::SinglePlayerSelectAttack::init()
{
	const auto select_attack = new PathTrunk();

	auto display_stop = new PathBranch(select_attack, nullptr, nullptr);
	display_stop->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_stop);

	auto clean_up = new PathBranch(select_attack, nullptr, display_stop);
	clean_up->add_navigator<Navigation::StopMusic>(state_->audio_player);

	auto choose_attack = new PathBranch(select_attack, nullptr, clean_up);
	choose_attack->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_choose_attack, input_controller_player_1, P1_OPTIONS, player_1_);

	auto display_select_attack = new PathBranch(select_attack, nullptr, choose_attack);
	display_select_attack->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_select_attack);

	auto select_attack_music = new PathBranch(select_attack, nullptr, display_select_attack);
	select_attack_music->add_navigator<Navigation::PlayMusic>(state_->audio_player, music_drum_beat, -1);

	select_attack->current = select_attack_music;
	set_trunk(select_attack);
}

void CombatPresets::SinglePlayerCombat::init()
{
	const auto combat = new PathTrunk();

	auto display_stop = new PathBranch(combat, nullptr, nullptr);
	display_stop->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_stop);

	auto disable_controller = new PathBranch(combat, nullptr, display_stop);
	disable_controller->add_navigator<Navigation::DisableController>(player_1_);

	auto round = new PathBranch(combat, nullptr, disable_controller);
	round->add_navigator<Navigation::CombatCollision>(player_1_, player_2_);
	round->add_navigator<Navigation::Delay>(ROUND_TIME);

	auto display_fight = new PathBranch(combat, nullptr, round);
	display_fight->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_fight);

	auto enable_controller = new PathBranch(combat, nullptr, display_fight);
	enable_controller->add_navigator<Navigation::EnableController>(player_1_);

	combat->current = enable_controller;
	set_trunk(combat);
}

void CombatPresets::RoundEnding::init()
{
	const auto round_ending = new PathTrunk();

	auto player_1_attack_data = player_1_->get_component<PlayerComponent>().get_final_attack();
	auto player_2_attack_data = player_2_->get_component<PlayerComponent>().get_final_attack();

	auto clean_up = new PathBranch(round_ending, nullptr, nullptr);
	clean_up->add_navigator<Navigation::SwapPriority>(player_1_, player_2_);

	auto display_miss = new PathBranch(round_ending, nullptr, clean_up);
	display_miss->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_miss);

	auto display_player_2_wins = new PathBranch(round_ending, nullptr, clean_up);
	display_player_2_wins->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_player_2_wins);

	auto check_player_1_loss = new PathBranch(round_ending, nullptr, display_player_2_wins);
	check_player_1_loss->add_navigator<Navigation::CheckRoundLoss>(player_1_);

	auto player_1_gets_hit = new PathBranch(round_ending, nullptr, check_player_1_loss);
	player_1_gets_hit->add_navigator<Navigation::ReceiveDamage>(player_1_, player_2_attack_data->damage);
	player_1_gets_hit->add_navigator<Navigation::LockedAnimation>(player_1_, animation_player_hit);
	player_1_gets_hit->add_navigator<Navigation::PlaySound>(state_->audio_player, sound_hit_3);

	auto display_player_1_wins = new PathBranch(round_ending, nullptr, clean_up);
	display_player_1_wins->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_player_1_wins);

	auto check_player_2_loss = new PathBranch(round_ending, nullptr, display_player_1_wins);
	check_player_2_loss->add_navigator<Navigation::CheckRoundLoss>(player_2_);

	auto player_2_gets_hit = new PathBranch(round_ending, nullptr, check_player_2_loss);
	player_2_gets_hit->add_navigator<Navigation::ReceiveDamage>(player_2_, player_1_attack_data->damage);
	player_2_gets_hit->add_navigator<Navigation::LockedAnimation>(player_2_, animation_player_hit);
	player_2_gets_hit->add_navigator<Navigation::PlaySound>(player_2_->state->audio_player, sound_hit_1);

	auto player_1_att_animation = new PathBranch(round_ending, nullptr, player_2_gets_hit);
	player_1_att_animation->add_navigator<Navigation::SetAnimation>(player_1_, player_1_attack_data->encoding, 0);

	auto player_2_att_animation = new PathBranch(round_ending, nullptr, player_1_gets_hit);
	player_2_att_animation->add_navigator<Navigation::SetAnimation>(player_2_, player_2_attack_data->encoding, 0);

	auto second_check_collision_p1_att = new PathBranch(round_ending, player_2_gets_hit, display_miss);
	second_check_collision_p1_att->add_navigator<Navigation::CheckCollision>(player_1_, player_2_);

	auto second_p1_attack_delay = new PathBranch(round_ending, nullptr, second_check_collision_p1_att);
	second_p1_attack_delay->add_navigator<Navigation::Delay>(1000);

	auto second_p1_move_att = new PathBranch(round_ending, nullptr, second_p1_attack_delay);
	second_p1_move_att->add_navigator<Navigation::MovePlayerToCollision>(player_1_, player_2_, player_1_attack_data->distance);

	auto second_p1_att_animation = new PathBranch(round_ending, nullptr, second_p1_move_att);
	second_p1_att_animation->add_navigator<Navigation::SetAnimation>(player_1_, player_1_attack_data->encoding, 0);

	auto second_check_collision_p2_att = new PathBranch(round_ending,  player_1_gets_hit, display_miss );
	second_check_collision_p2_att->add_navigator<Navigation::CheckCollision>(player_1_, player_2_);

	auto second_p2_attack_delay = new PathBranch(round_ending, nullptr, second_check_collision_p2_att);
	second_p2_attack_delay->add_navigator<Navigation::Delay>(1000);

	auto second_p2_move_att = new PathBranch(round_ending, nullptr, second_p2_attack_delay);
	second_p2_move_att->add_navigator<Navigation::MovePlayerToCollision>(player_2_, player_1_, player_2_attack_data->distance);

	auto second_p2_att_animation = new PathBranch(round_ending, nullptr, second_p2_move_att);
	second_p2_att_animation->add_navigator<Navigation::SetAnimation>(player_2_, player_2_attack_data->encoding, 0);

	auto second_check_priority = new PathBranch(round_ending, second_p2_att_animation, second_p1_att_animation );
	second_check_priority->add_navigator<Navigation::CheckPriority>(player_1_);

	auto reset_animations = new PathBranch(round_ending, nullptr, second_check_priority);
	reset_animations->add_navigator<Navigation::ResetAnimations>(player_1_);
	reset_animations->add_navigator<Navigation::ResetAnimations>(player_2_);

	auto check_for_winner = new PathBranch(round_ending, player_1_att_animation, player_2_att_animation);
	check_for_winner->add_navigator<Navigation::CheckWinner>(player_1_, player_2_);

	auto check_for_collisions = new PathBranch(round_ending, check_for_winner, reset_animations);
	check_for_collisions->add_navigator<Navigation::CheckCollision>(player_1_, player_2_);

	auto p2_attack_delay = new PathBranch(round_ending, nullptr, check_for_collisions);
	p2_attack_delay->add_navigator<Navigation::Delay>(200);

	auto p2_move_att = new PathBranch(round_ending, nullptr, p2_attack_delay);
	p2_move_att->add_navigator<Navigation::MovePlayerToCollision>(player_2_, player_1_, player_2_attack_data->distance);

	auto p2_att_animation = new PathBranch(round_ending, nullptr, p2_move_att);
	p2_att_animation->add_navigator<Navigation::SetAnimation>(player_2_, player_2_attack_data->encoding, 0);

	auto p1_attack_delay = new PathBranch(round_ending, nullptr, check_for_collisions);
	p1_attack_delay->add_navigator<Navigation::Delay>(200);

	auto p1_move_att = new PathBranch(round_ending, nullptr, p1_attack_delay);
	p1_move_att->add_navigator<Navigation::MovePlayerToCollision>(player_1_, player_2_, player_1_attack_data->distance);

	auto p1_att_animation = new PathBranch(round_ending, nullptr, p1_move_att);
	p1_att_animation->add_navigator<Navigation::SetAnimation>(player_1_, player_1_attack_data->encoding, 0);

	auto check_priority = new PathBranch(round_ending, p1_att_animation, p2_att_animation );
	check_priority->add_navigator<Navigation::CheckPriority>(player_1_);

	round_ending->current = check_priority;
	set_trunk(round_ending);
}

void CombatPresets::MultiPlayerCombat::init()
{
	const auto combat = new PathTrunk();

	auto display_stop = new PathBranch(combat, nullptr, nullptr);
	display_stop->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_stop);

	auto disable_controller = new PathBranch(combat, nullptr, display_stop);
	disable_controller->add_navigator<Navigation::DisableController>(player_1_);
	disable_controller->add_navigator<Navigation::DisableController>(player_2_);
	disable_controller->add_navigator<Navigation::ResetVelocity>(player_1_);
	disable_controller->add_navigator<Navigation::ResetVelocity>(player_2_);

	auto round = new PathBranch(combat, nullptr, disable_controller);
	round->add_navigator<Navigation::CombatCollision>(player_1_, player_2_);
	round->add_navigator<Navigation::Delay>(ROUND_TIME);

	auto round_music = new PathBranch(combat, nullptr, round);
	round_music->add_navigator<Navigation::PlaySound>(state_->audio_player, sound_combat_start);

	auto display_fight = new PathBranch(combat, nullptr, round_music);
	display_fight->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_fight);

	auto enable_controller = new PathBranch(combat, nullptr, display_fight);
	enable_controller->add_navigator<Navigation::EnableController>(player_1_);
	enable_controller->add_navigator<Navigation::EnableController>(player_2_);

	combat->current = enable_controller;
	set_trunk(combat);
}

void CombatPresets::MultiPlayerSelectAttack::init()
{
	const auto select_attack = new PathTrunk();

	auto clean_up = new PathBranch(select_attack, nullptr, nullptr);
	clean_up->add_navigator<Navigation::StopMusic>(state_->audio_player);

	auto choose_attack_player_2 = new PathBranch(select_attack, nullptr, clean_up);
	choose_attack_player_2->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_choose_attack, input_controller_player_2, P2_OPTIONS, player_2_);

	auto choose_attack_player_1 = new PathBranch(select_attack, nullptr, choose_attack_player_2);
	choose_attack_player_1->add_navigator<Navigation::CreateOptionBox>(state_->palette, options_choose_attack, input_controller_player_1, P1_OPTIONS, player_1_);

	auto display_select_attack = new PathBranch(select_attack, nullptr, choose_attack_player_1);
	display_select_attack->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_select_attack);

	auto play_music = new PathBranch(select_attack, nullptr, display_select_attack);
	play_music->add_navigator<Navigation::PlayMusic>(state_->audio_player, music_drum_beat, -1);

	select_attack->current = play_music;
	set_trunk(select_attack);
}

void CombatPresets::MatchEnding::init()
{
	const auto end_match = new PathTrunk();

	auto go_to_menu = new PathBranch(end_match, nullptr, nullptr);
	go_to_menu->add_navigator<Navigation::ChangeState>(STATE_MENU);

	auto display_match_winner = new PathBranch(end_match, nullptr, go_to_menu);
	if (player_->get_component<SpriteComponent>().sprite_flip)
		display_match_winner->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_player_2_match_win);
	else
		display_match_winner->add_navigator<Navigation::DisplayPrompt>(state_->palette, PROMPT_DELAY, ss_main_prompt_player_1_match_win);

	end_match->current = display_match_winner;
	set_trunk(end_match);
}

void CombatPresets::EnableMovement::init()
{
	const auto enable_controller = new PathTrunk();
	auto reset_controllers = new PathBranch(enable_controller, nullptr, nullptr);
	reset_controllers->add_navigator<Navigation::EnableController>(player_1_);
	reset_controllers->add_navigator<Navigation::EnableController>(player_2_);

	enable_controller->current = reset_controllers;
	set_trunk(enable_controller);

}
