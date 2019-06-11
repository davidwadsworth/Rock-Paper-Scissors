#pragma once
#include "NavigationPreset.h"
#include "CommonNavigation.h"
#include "CombatNavigation.h"
#include "AudioNavigation.h"

namespace AttackPresets
{
	class PlayerSlideBack : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit PlayerSlideBack(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
		Entity * player_, *other_;
		AttackData * push_data_;
	public:
		explicit PlayerSlideBack(Entity * player, Entity * other)
			: player_(player), other_(other), push_data_(other->get_component<PlayerComponent>().get_attack())
		{}

		void init() override
		{
			const auto pushed = new PathTrunk();

			auto free_player = new PathBranch(pushed, nullptr, nullptr);
			free_player->add_navigator<Navigation::EnableController>(player_);
			free_player->add_navigator<Navigation::ResetAnimations>(player_);

			auto hit_stun = new PathBranch(pushed, nullptr, free_player);
			hit_stun->add_navigator<Navigation::Delay>(push_data_->hit_stun);

			auto slide_back = new PathBranch(pushed, nullptr, hit_stun);
			slide_back->add_navigator<Navigation::RepelFromOtherPlayer>(player_, other_, push_data_->distance);

			auto lock_player = new PathBranch(pushed, nullptr, slide_back);
			lock_player->add_navigator<Navigation::DisableController>(player_);
			lock_player->add_navigator<Navigation::SetAnimation>(player_, animation_player_hit, 1);
			lock_player->add_navigator<Navigation::ReceiveDamage>(player_, push_data_->damage);
			lock_player->add_navigator<Navigation::PlaySound>(player_->state->audio_player, sound_hit_1);

			pushed->current = lock_player;
			set_trunk(pushed);
		}
	};

	class KickHitStun : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit KickHitStun(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;

		Entity * player_;
		AttackData * kick_data_;
	public:
		explicit KickHitStun(Entity * player, AttackData * kick_data)
			: player_(player), kick_data_(kick_data)
		{}

		void init() override
		{
			const auto kicked = new PathTrunk();

			auto free_player = new PathBranch(kicked, nullptr, nullptr);
			free_player->add_navigator<Navigation::EnableController>(player_);
			free_player->add_navigator<Navigation::ResetAnimations>(player_);

			auto hit_stun = new PathBranch(kicked, nullptr, free_player);
			hit_stun->add_navigator<Navigation::Delay>(kick_data_->hit_stun);

			auto lock_player = new PathBranch(kicked, nullptr, hit_stun);
			lock_player->add_navigator<Navigation::DisableController>(player_);
			lock_player->add_navigator<Navigation::SetAnimation>(player_, animation_player_hit, 1);
			lock_player->add_navigator<Navigation::ReceiveDamage>(player_, kick_data_->damage);
			lock_player->add_navigator<Navigation::PlaySound>(player_->state->audio_player, sound_hit_2);

			kicked->current = lock_player;
			set_trunk(kicked);
		}
	};

	class BlockPreset : public NavigationPreset
	{
		Entity * blocker_;
	public:
		explicit BlockPreset(Entity * blocker)
			: blocker_(blocker)
		{}

		void init() override;
		Entity * player_;
		AttackData * attack_data_{};
	public:
		explicit BlockPreset(Entity * player)
			: player_(player), attack_data_(player->get_component<PlayerComponent>().get_attack())
		{}

		void init() override
		{
			const auto block = new PathTrunk();

			auto free_player = new PathBranch(block, nullptr, nullptr);
			free_player->add_navigator<Navigation::EnableController>(player_);

			auto move_stun = new PathBranch(block, nullptr, free_player);
			move_stun->add_navigator<Navigation::BlockPlayer>(player_, attack_data_->move_stun);

			auto lock_player = new PathBranch(block, nullptr, move_stun);
			lock_player->add_navigator<Navigation::DisableController>(player_);
			
			block->current = lock_player;
			set_trunk(block);
		}
	};

	class KickPreset : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit KickPreset(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
		
		Entity * player_, *other_;
		AttackQueue * other_queue_{};
		AttackData * attack_data_{};
	public:
		explicit KickPreset(Entity * player, Entity * other, AttackQueue * other_queue)
			: player_(player), other_(other), other_queue_(other_queue), attack_data_(player->get_component<PlayerComponent>().get_attack())
		{}

		void init() override
		{
			const auto kick = new PathTrunk();

			auto free_player = new PathBranch(kick, nullptr, nullptr);
			free_player->add_navigator<Navigation::EnableController>(player_);

			auto move_stun = new PathBranch(kick, nullptr, free_player);
			move_stun->add_navigator<Navigation::KickPlayer>(player_, other_, other_queue_, attack_data_->move_stun);

			auto lock_player = new PathBranch(kick, nullptr, move_stun);
			lock_player->add_navigator<Navigation::DisableController>(player_);

			kick->current = lock_player;
			set_trunk(kick);
		}
	};

	class PushPreset : public NavigationPreset
	{
		Entity * victim_, * attacker_;
	public:
		explicit PushPreset(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
		Entity * player_, *other_;
		AttackQueue * other_queue_;
		AttackData * attack_data_;
	public:
		explicit PushPreset(Entity * player, Entity * other, AttackQueue * other_queue)
			: player_(player), other_(other), other_queue_(other_queue), attack_data_(player->get_component<PlayerComponent>().get_attack())
		{}

		void init() override
		{
			const auto push = new PathTrunk();

			auto free_player = new PathBranch(push, nullptr, nullptr);
			free_player->add_navigator<Navigation::EnableController>(player_);

			auto move_stun = new PathBranch(push, nullptr, free_player);
			move_stun->add_navigator<Navigation::PushPlayer>(player_, other_, other_queue_, attack_data_->move_stun);

			auto lock_player = new PathBranch(push, nullptr, move_stun);
			lock_player->add_navigator<Navigation::DisableController>(player_);

			push->current = lock_player;
			set_trunk(push);
		}
	};

}

