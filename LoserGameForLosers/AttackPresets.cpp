#include "stdafx.h"
#include "AttackPresets.h"
#include "CombatNavigation.h"
#include "AudioNavigation.h"

void AttackPresets::PlayerSlideBack::init()

{
	const auto pushed = new PathTrunk();
	const auto attacker_data = attacker_->get_component<PlayerComponent>().get_attack();

	auto check_for_loss = new PathBranch(pushed, nullptr, nullptr);
	check_for_loss->add_navigator<Navigation::CheckRoundLoss>(victim_);

	auto free_player = new PathBranch(pushed, nullptr, check_for_loss);
	free_player->add_navigator<Navigation::EnableController>(victim_);
	free_player->add_navigator<Navigation::ResetAnimations>(victim_);

	auto hit_stun = new PathBranch(pushed, nullptr, free_player);
	hit_stun->add_navigator<Navigation::Delay>(attacker_data->hit_stun);

	auto slide_back = new PathBranch(pushed, nullptr, hit_stun);
	slide_back->add_navigator<Navigation::MovePlayer>(victim_, attacker_data->distance);

	auto lock_player = new PathBranch(pushed, nullptr, slide_back);
	lock_player->add_navigator<Navigation::DisableController>(victim_);
	lock_player->add_navigator<Navigation::SetAnimation>(victim_, animation_player_hit, 1);
	lock_player->add_navigator<Navigation::ReceiveDamage>(victim_, attacker_data->damage);
	lock_player->add_navigator<Navigation::PlaySound>(victim_->state->audio_player, sound_hit_1);

	pushed->current = lock_player;
	set_trunk(pushed);
}

void AttackPresets::KickHitStun::init()
{
	const auto kicked = new PathTrunk();
	const auto attacker_data = attacker_->get_component<PlayerComponent>().get_attack();

	auto check_for_loss = new PathBranch(kicked, nullptr, nullptr);
	check_for_loss->add_navigator<Navigation::CheckRoundLoss>(victim_);

	auto free_player = new PathBranch(kicked, nullptr, check_for_loss);
	free_player->add_navigator<Navigation::EnableController>(victim_);
	free_player->add_navigator<Navigation::ResetAnimations>(victim_);

	auto hit_stun = new PathBranch(kicked, nullptr, free_player);
	hit_stun->add_navigator<Navigation::Delay>(attacker_data->hit_stun);

	auto lock_player = new PathBranch(kicked, nullptr, hit_stun);
	lock_player->add_navigator<Navigation::DisableController>(victim_);
	lock_player->add_navigator<Navigation::SetAnimation>(victim_, animation_player_hit, 1);
	lock_player->add_navigator<Navigation::ReceiveDamage>(victim_, attacker_data->damage);
	lock_player->add_navigator<Navigation::PlaySound>(victim_->state->audio_player, sound_hit_2);

	kicked->current = lock_player;
	set_trunk(kicked);
}

void AttackPresets::BlockPreset::init()
{
	const auto block = new PathTrunk();
	const auto block_data = blocker_->get_component<PlayerComponent>().get_attack();

	auto free_player = new PathBranch(block, nullptr, nullptr);
	free_player->add_navigator<Navigation::EnableController>(blocker_);

	auto move_stun = new PathBranch(block, nullptr, free_player);
	move_stun->add_navigator<Navigation::BlockPlayer>(blocker_, block_data->move_stun);

	auto lock_player = new PathBranch(block, nullptr, move_stun);
	lock_player->add_navigator<Navigation::DisableController>(blocker_);

	block->current = lock_player;
	set_trunk(block);
}

void AttackPresets::KickPreset::init()
{
	const auto kick = new PathTrunk();
	const auto kick_data = attacker_->get_component<PlayerComponent>().get_attack();

	auto free_player = new PathBranch(kick, nullptr, nullptr);
	free_player->add_navigator<Navigation::EnableController>(attacker_);

	auto move_stun = new PathBranch(kick, nullptr, free_player);
	move_stun->add_navigator<Navigation::KickPlayer>(attacker_, victim_, kick_data->move_stun);

	auto lock_player = new PathBranch(kick, nullptr, move_stun);
	lock_player->add_navigator<Navigation::DisableController>(attacker_);

	kick->current = lock_player;
	set_trunk(kick);
}

void AttackPresets::PushPreset::init()
{
	const auto push = new PathTrunk();
	const auto push_data = attacker_->get_component<PlayerComponent>().get_attack();

	auto free_player = new PathBranch(push, nullptr, nullptr);
	free_player->add_navigator<Navigation::EnableController>(attacker_);

	auto move_stun = new PathBranch(push, nullptr, free_player);
	move_stun->add_navigator<Navigation::PushPlayer>(attacker_, victim_, push_data->move_stun);

	auto lock_player = new PathBranch(push, nullptr, move_stun);
	lock_player->add_navigator<Navigation::DisableController>(attacker_);

	push->current = lock_player;
	set_trunk(push);
}
