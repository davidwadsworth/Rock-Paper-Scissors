#include "stdafx.h"
#include "AttackPresets.h"
#include "CombatNavigation.h"
#include "AudioNavigation.h"

AttackPresets::PlayerSlideBack::PlayerSlideBack(Entity * victim, Entity * attacker)
	: victim_(victim), attacker_(attacker), damage_(0)
{}


void AttackPresets::PlayerSlideBack::init()

{
	const auto pushed = new PathTrunk();
	const auto attacker_data = attacker_->get_component<PlayerComponent>().get_attack(attack_push);
	const auto victim_id = victim_->get_component<PlayerComponent>().get_character_id();

	auto check_for_loss = new PathBranch(pushed, nullptr, nullptr);
	check_for_loss->add_navigator(new Navigation::CheckRoundLoss(victim_id));

	auto free_player = new PathBranch(pushed, nullptr, check_for_loss);
	free_player->add_navigator(new Navigation::ResetAnimations(victim_));

	auto hit_stun = new PathBranch(pushed, nullptr, free_player);
	hit_stun->add_navigator(new Navigation::Delay(attacker_data->hit_stun));

	auto slide_back = new PathBranch(pushed, nullptr, hit_stun);
	slide_back->add_navigator(new Navigation::MovePlayer(victim_, attacker_data->op_distance * victim_->get_component<PlayerComponent>().direction, 2.0f));

	auto lock_player = new PathBranch(pushed, nullptr, slide_back);
	lock_player->add_navigator(new Navigation::SetAnimation(victim_, animation_player_hit, 1));
	lock_player->add_navigator(new Navigation::ReceiveDamage(victim_id, attacker_data->damage));
	lock_player->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_hit_1));
	lock_player->add_navigator(new Navigation::ResetVelocity(victim_));

	if (victim_->has_component<ControllerComponent>())
	{
		lock_player->add_navigator(new Navigation::DisableController(victim_));
		free_player->add_navigator(new Navigation::EnableController(victim_));
	}

	pushed->current = lock_player;
	set_trunk(pushed);
}

AttackPresets::KickHitStun::KickHitStun(Entity * victim, Entity * attacker)
	: victim_(victim), attacker_(attacker), damage_(attacker->get_component<PlayerComponent>().get_attack(attack_kick)->damage)
{}

void AttackPresets::KickHitStun::blocked()
{
	damage_ = attacker_->get_component<PlayerComponent>().get_attack()->damage / 2;
}

void AttackPresets::KickHitStun::init()
{
	const auto kicked = new PathTrunk();
	const auto attacker_data = attacker_->get_component<PlayerComponent>().get_attack(attack_kick);
	const auto victim_id = victim_->get_component<PlayerComponent>().get_character_id();

	auto check_for_loss = new PathBranch(kicked, nullptr, nullptr);
	check_for_loss->add_navigator(new Navigation::CheckRoundLoss(victim_id));

	auto free_player = new PathBranch(kicked, nullptr, check_for_loss);
	free_player->add_navigator(new Navigation::ResetAnimations(victim_));

	auto hit_stun = new PathBranch(kicked, nullptr, free_player);
	hit_stun->add_navigator(new Navigation::Delay(attacker_data->hit_stun));

	auto lock_player = new PathBranch(kicked, nullptr, hit_stun);
	lock_player->add_navigator(new Navigation::SetAnimation(victim_, animation_player_hit, 1));
	lock_player->add_navigator(new Navigation::ReceiveDamage(victim_id, damage_));
	lock_player->add_navigator(new Navigation::PlaySound(GameState::get_audio_player(), sound_hit_2));
	lock_player->add_navigator(new Navigation::ResetVelocity(victim_));

	if (victim_->has_component<ControllerComponent>())
	{
		lock_player->add_navigator(new Navigation::DisableController(victim_));
		free_player->add_navigator(new Navigation::EnableController(victim_));
	}

	kicked->current = lock_player;
	set_trunk(kicked);
}

void AttackPresets::BlockPreset::init()
{
	const auto block = new PathTrunk();
	const auto block_data = blocker_->get_component<PlayerComponent>().get_attack(attack_block);

	auto free_player = new PathBranch(block, nullptr, nullptr);
	free_player->add_navigator(new Navigation::EnableController(blocker_));

	auto move_stun = new PathBranch(block, nullptr, free_player);
	move_stun->add_navigator(new Navigation::BlockPlayer(blocker_, block_data->move_stun));

	auto lock_player = new PathBranch(block, nullptr, move_stun);
	lock_player->add_navigator(new Navigation::DisableController(blocker_));
	lock_player->add_navigator(new Navigation::ResetVelocity(blocker_));

	block->current = lock_player;
	set_trunk(block);
}

void AttackPresets::KickPreset::init()
{
	const auto kick = new PathTrunk();
	const auto kick_data = attacker_->get_component<PlayerComponent>().get_attack(attack_kick);

	auto free_player = new PathBranch(kick, nullptr, nullptr);
	free_player->add_navigator(new Navigation::ResetAnimations(attacker_));

	auto move_stun = new PathBranch(kick, nullptr, free_player);
	move_stun->add_navigator(new Navigation::KickPlayer(attacker_, victim_, kick_data->move_stun));

	auto lock_player = new PathBranch(kick, nullptr, move_stun);
	lock_player->add_navigator(new Navigation::ResetVelocity(attacker_));

	if (attacker_->has_component<ControllerComponent>())
	{
		lock_player->add_navigator(new Navigation::DisableController(attacker_));
		free_player->add_navigator(new Navigation::EnableController(attacker_));
	}

	kick->current = lock_player;
	set_trunk(kick);
}

void AttackPresets::PushPreset::init()
{
	const auto push = new PathTrunk();
	const auto push_data = attacker_->get_component<PlayerComponent>().get_attack(attack_push);

	auto free_player = new PathBranch(push, nullptr, nullptr);
	free_player->add_navigator(new Navigation::ResetAnimations(attacker_));

	auto move_stun = new PathBranch(push, nullptr, free_player);
	move_stun->add_navigator(new Navigation::PushPlayer(attacker_, victim_, push_data->move_stun));

	auto lock_player = new PathBranch(push, nullptr, move_stun);
	lock_player->add_navigator(new Navigation::ResetVelocity(attacker_));

	if (attacker_->has_component<ControllerComponent>())
	{
		lock_player->add_navigator(new Navigation::DisableController(attacker_));
		free_player->add_navigator(new Navigation::EnableController(attacker_));
	}

	push->current = lock_player;
	set_trunk(push);
}
