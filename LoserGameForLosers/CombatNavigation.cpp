#include "stdafx.h"
#include "CombatNavigation.h"
namespace Navigation
{
	ConvergeTowardsOtherPlayer::ConvergeTowardsOtherPlayer(Entity * player_to_move, Entity * other_player, const float distance)
		: moving_(player_to_move), comparing_(other_player),
		move_command_(InputCommands::Move(player_to_move->get_component<PlayerComponent>().direction, player_to_move->get_component<PlayerComponent>().direction < 0 ? animation_player_walk_left : animation_player_walk_right)),
		velocity_(player_to_move->get_component<PlayerComponent>().get_velocity()), distance_(distance)
	{}

	void ConvergeTowardsOtherPlayer::init()
	{
		distance_left_ = distance_;
	}

	int ConvergeTowardsOtherPlayer::choose_path()
	{
		const auto player_distance = moving_->get_component<TransformComponent>().get_horizontal_distance(comparing_);

		if (player_distance > -1 && player_distance < 1 || distance_left_ == 0)
			return 1;

		move_command_.execute(moving_);
		distance_left_ -= velocity_ * PLAYER_SPEED;

		return 0;
	}


	ResetPlayersAndBackground::ResetPlayersAndBackground(Entity * player1, Entity * player2, Entity * background)
		: player_1_(player1), player_2_(player2), background_(background)
	{}

	int ResetPlayersAndBackground::choose_path()
	{
		auto p1_transform = player_1_->get_component<TransformComponent>();
		auto p2_transform = player_2_->get_component<TransformComponent>();
		auto bg_transform = background_->get_component<TransformComponent>();

		p1_transform.position = Vector2D{ static_cast<float>(SPRITE_LEFT_EDGE_OF_SCREEN), static_cast<float>(SPRITE_BOTTOM_OF_SCREEN) };
		p2_transform.position = Vector2D{ static_cast<float>(SPRITE_RIGHT_EDGE_OF_SCREEN), static_cast<float>(SPRITE_BOTTOM_OF_SCREEN) };
		bg_transform.position = Vector2D{ static_cast<float>(BACKGROUND_X_OFFSET), static_cast<float>(BACKGROUND_Y_OFFSET) };

		return 1;
	}

	CheckCollision::CheckCollision(Entity * player_1, Entity * player_2)
		: player_1_(player_1), player_2_(player_2)
	{}

	int CheckCollision::choose_path()
	{
		if (Collision::aabb(player_1_->get_component<ColliderComponent>().collider,
			player_2_->get_component<ColliderComponent>().collider))
		{
			player_2_->get_component<TransformComponent>().position.x -= player_2_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED - 1;
			player_1_->get_component<TransformComponent>().position.x -= player_1_->get_component<TransformComponent>().player_velocity.x * PLAYER_SPEED + 1;
		}
		return 1;
	}

	PushPlayer::PushPlayer(Entity * player, Entity *other_player, AttackQueue * other_player_queue, const Uint32 attack_frames)
		: Delay(attack_frames), player_(player), other_player_(other_player), other_player_queue_(other_player_queue), used_(false)
	{}

	void PushPlayer::init()
	{
	}

	int PushPlayer::choose_path()
	{
		if(!used_ && Collision::aabb(player_->get_component<ColliderComponent>().collider,
			other_player_->get_component<ColliderComponent>().collider))
		{
			other_player_queue_->clear_add(slide_back_.get_trunk());

			used_ = true;
		}

		return Delay::choose_path();
	}

	void PushPlayer::close()
	{
		slide_back_.close();
	}

	KickPlayer::KickPlayer(Entity * player, Entity * other_player, AttackQueue * other_player_queue, const Uint32 attack_frames)
		: Delay(attack_frames), player_(player), other_player_(other_player), other_player_queue_(other_player_queue), used_(false)
	{}

}


