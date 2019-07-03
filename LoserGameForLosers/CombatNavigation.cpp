#include "stdafx.h"
#include "CombatNavigation.h"
#include "ScriptComponent.h"
#include "AttackPresets.h"
#include "CommonInputCommands.h"

namespace Navigation
{
	ResetPlayersAndBackground::ResetPlayersAndBackground(Entity * player1, Entity * player2, Entity * background)
		: player_1_(player1), player_2_(player2), background_(background)
	{}

	int ResetPlayersAndBackground::choose_path()
	{
		auto p1_transform = &player_1_->get_component<TransformComponent>();
		auto p2_transform = &player_2_->get_component<TransformComponent>();
		auto bg_transform = &background_->get_component<TransformComponent>();

		player_1_->get_component<PlayerComponent>().reset_character_hit_box();
		player_2_->get_component<PlayerComponent>().reset_character_hit_box();

		p1_transform->scale = SPRITE_SCALING;
		p2_transform->scale = SPRITE_SCALING;
		bg_transform->scale = BACKGROUND_SCALING;

		p1_transform->position = Vector2D{ static_cast<float>(SPRITE_LEFT_EDGE_OF_SCREEN), static_cast<float>(SPRITE_BOTTOM_OF_SCREEN) };
		p2_transform->position = Vector2D{ static_cast<float>(SPRITE_RIGHT_EDGE_OF_SCREEN), static_cast<float>(SPRITE_BOTTOM_OF_SCREEN) };
		bg_transform->position = Vector2D{ static_cast<float>(BACKGROUND_X_OFFSET), static_cast<float>(BACKGROUND_Y_OFFSET) };

		return 1;
	}

	CombatCollision::CombatCollision(Entity * player_1, Entity * player_2)
		: player_1_(player_1), player_2_(player_2)
	{}

	int CombatCollision::choose_path()
	{
		if (player_1_->get_component<ColliderComponent>().collides(player_2_))
		{
			player_2_->get_component<TransformComponent>().position.x -= player_2_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED - 1;
			player_1_->get_component<TransformComponent>().position.x -= player_1_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED + 1;
		}
		return 1;
	}

	PushPlayer::PushPlayer(Entity * attacker, Entity *victim, const Uint32 attack_frames)
		: Delay(attack_frames), attacker_(attacker), victim_(victim), slide_back_(new AttackPresets::PlayerSlideBack(victim, attacker)), used_(false)
	{}

	void PushPlayer::init()
	{
		attacker_->get_component<PlayerComponent>().choose_combat_attack(attack_push);
		attacker_->get_component <PlayerComponent>().execute_combat_attack();
		slide_back_->init();
		move_ = new InputCommands::Move(0, animation_player_idle);
	}

	int PushPlayer::choose_path()
	{
		if(!used_ && attacker_->get_component<ColliderComponent>().collides(victim_))
		{
			if (victim_->get_component<PlayerComponent>().attack_id != attack_block)
				victim_->get_component<ScriptComponent>().clear_add(slide_back_->get_trunk());
			else
				GameState::get_audio_player()->play_sound(sound_blocking);

			used_ = true;
		}

		move_->execute(attacker_);

		return Delay::choose_path();
	}

	void PushPlayer::close()
	{
		attacker_->get_component<PlayerComponent>().reset_character_hit_box();
		slide_back_->close();
		move_ = new InputCommands::Move(0, animation_player_idle);
	}

	KickPlayer::KickPlayer(Entity * attacker, Entity * victim, const Uint32 attack_frames)
		: Delay(attack_frames), attacker_(attacker), victim_(victim), stun_(new AttackPresets::KickHitStun(victim, attacker)), used_(false)
	{}

	void KickPlayer::init()
	{
		attacker_->get_component<PlayerComponent>().choose_combat_attack(attack_kick);
		attacker_->get_component <PlayerComponent>().execute_combat_attack();
		stun_->init();
		move_ = new InputCommands::Move(0, animation_player_idle);
	}
	
	int KickPlayer::choose_path()
	{
		if (!used_ && attacker_->get_component<ColliderComponent>().collides(victim_))
		{
			if (victim_->get_component<PlayerComponent>().attack_id == attack_block)
			{
				stun_->blocked();
				GameState::get_audio_player()->play_sound(sound_blocking);
			}

			victim_->get_component<ScriptComponent>().clear_add(stun_->get_trunk());

			used_ = true;
		}

		move_->execute(attacker_);

		return Delay::choose_path();
	}
	
	void KickPlayer::close()
	{
		attacker_->get_component<PlayerComponent>().reset_character_hit_box();
		stun_->close();
	}
	
	BlockPlayer::BlockPlayer(Entity * blocker, const Uint32 attack_frames)
		: Delay(attack_frames), blocker_(blocker), move_(nullptr), used_(false)
	{}

	void BlockPlayer::init()
	{
		blocker_->get_component<PlayerComponent>().choose_combat_attack(attack_block);
		blocker_->get_component<PlayerComponent>().execute_combat_attack();
		move_ = new InputCommands::Move(0, animation_player_idle);
	}

	int BlockPlayer::choose_path()
	{
		move_->execute(blocker_);
		return Delay::choose_path();
	}

	void BlockPlayer::close()
	{
		blocker_->get_component<PlayerComponent>().reset_character_hit_box();
	}

	SetAnimation::SetAnimation(Entity * player, const int animation, const int animation_pos)
		: player_(player), animation_(animation), animation_pos_(animation_pos)
	{}

	int SetAnimation::choose_path()
	{
		player_->get_component<SpriteComponent>().set_image(animation_, animation_pos_);
		return 1;
	}

	ResetAnimations::ResetAnimations(Entity * player)
		: player_(player)
	{}

	int ResetAnimations::choose_path()
	{
		player_->get_component<PlayerComponent>().reset_character_hit_box();
		return 1;
	}

	ReceiveDamage::ReceiveDamage(const int player, const int damage)
		: player_(player), damage_(damage)
	{}

	void ReceiveDamage::init()
	{
		overlay_ = GameState::get_manager()->get_group(Game::group_overlay)[player_];
	}

	int ReceiveDamage::choose_path()
	{
		overlay_->get_component<OverlayComponent>().deal_damage(damage_);
		return 1;
	}

	CheckRoundLoss::CheckRoundLoss(const int player)
		: player_(player)
	{}

	void CheckRoundLoss::init()
	{
		match_end_ = new CombatPresets::MatchEnding(player_);
		overlay_ = GameState::get_manager()->get_group(Game::group_overlay)[player_];
	}

	int CheckRoundLoss::choose_path()
	{
		if (overlay_->get_component<OverlayComponent>().is_depleted())
		{
			match_end_->init();
			GameState::get_audio_player()->stop_music();
			GameState::get_path()->clear();
			GameState::set_path(new Path());
			GameState::get_path()->add(match_end_->get_trunk());
			return 0;
		}

		return 1;
	}

	void CheckRoundLoss::close()
	{
		match_end_->close();
	}

	CheckCollision::CheckCollision(Entity * player_1, Entity * player_2)
		: player_1_(player_1), player_2_(player_2)
	{}

	int CheckCollision::choose_path()
	{
		return player_1_->get_component<ColliderComponent>().collides(player_2_) + 1;
	}

	LockedAnimation::LockedAnimation(Entity * player, const int animation)
		: player_(player), animation_(animation)
	{}

	void LockedAnimation::init()
	{
		player_->get_component<SpriteComponent>().unset_image();
	}

	int LockedAnimation::choose_path()
	{
		player_->get_component<SpriteComponent>().play_locked_animation(animation_);
		return 1;
	}

	CheckWinner::CheckWinner(Entity * player_1, Entity * player_2)
		: player_1_(player_1), player_2_(player_2), priority_(nullptr), other_(nullptr)
	{}

	void CheckWinner::init()
	{
		if (player_1_->get_component<PlayerComponent>().get_priority())
		{
			priority_ = player_1_;
			other_ = player_2_;
		}
		else
		{
			priority_ = player_2_;
			other_ = player_1_;
		}
	}

	int CheckWinner::choose_path()
	{
		return priority_->get_component<PlayerComponent>().check_attack_winner(other_);
	}

	CheckPriority::CheckPriority(Entity * player)
		: player_(player)
	{}

	int CheckPriority::choose_path()
	{
		return player_->get_component<PlayerComponent>().get_priority() + 1;
	}

	MovePlayer::MovePlayer(Entity * player, const int distance_move)
		: player_(player), distance_moved_(0), total_distance_(std::abs(distance_move)), move_(new InputCommands::Move((distance_move > 0) - (distance_move < 0), distance_move > 0 ? animation_player_walk_right : animation_player_walk_left)), 
		  stop_(new InputCommands::Move(0, animation_player_idle))
	{}

	int MovePlayer::choose_path()
	{
		move_->execute(player_);
		distance_moved_ += player_->get_component<PlayerComponent>().get_velocity() * PLAYER_SPEED;

		if (distance_moved_ >= total_distance_)
			return 1;

		return 0;
	}

	void MovePlayer::close()
	{
		stop_->execute(player_);
	}

	MovePlayerToCollision::MovePlayerToCollision(Entity * player, Entity * other, const int distance_move)
		: MovePlayer(player, distance_move * player->get_component<PlayerComponent>().direction), player_(player), other_(other)
	{}

	int MovePlayerToCollision::choose_path()
	{
		if (player_->get_component<ColliderComponent>().collides(other_))
			return 1;

		return MovePlayer::choose_path();
	}

	SwapPriority::SwapPriority(Entity * player_1, Entity * player_2)
		: player_1_(player_1), player_2_(player_2)
	{}

	int SwapPriority::choose_path()
	{
		player_1_->get_component<PlayerComponent>().change_priority();
		player_2_->get_component<PlayerComponent>().change_priority();
		return 1;
	}

	ResetVelocity::ResetVelocity(Entity * player)
		: stop_(new InputCommands::Move(0, animation_player_idle)), player_(player)
	{}

	int ResetVelocity::choose_path()
	{
		stop_->execute(player_);
		player_->get_component<TransformComponent>().external_velocity = 0;
		player_->get_component<TransformComponent>().net_velocity = 0;
		player_->get_component<TransformComponent>().player_velocity = 0;
		return 1;
	}

	ClearPath::ClearPath(Entity * player)
		: player_(player)
	{}

	int ClearPath::choose_path()
	{
		player_->get_component<ScriptComponent>().clear();
		return 1;
	}

	ExecuteFinalAttack::ExecuteFinalAttack(Entity * player, int animation, int animation_pos)
		: player_(player), animation_(animation), animation_pos_(animation_pos)
	{}

	int ExecuteFinalAttack::choose_path()
	{
		player_->get_component<PlayerComponent>().execute_final_attack();
		return 1;
	}

}


