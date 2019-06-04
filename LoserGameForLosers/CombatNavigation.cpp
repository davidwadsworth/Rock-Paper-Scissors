#include "stdafx.h"
#include "CombatNavigation.h"
namespace Navigation
{
	MovePlayerToOtherPlayer::MovePlayerToOtherPlayer(Entity * player_to_move, Entity * other_player, const float distance)
		: moving_(player_to_move), comparing_(other_player),
		move_command_(InputCommands::Move(player_to_move->get_component<PlayerComponent>().direction, player_to_move->get_component<PlayerComponent>().direction < 0 ? animation_player_walk_left : animation_player_walk_right)),
		velocity_(player_to_move->get_component<PlayerComponent>().get_velocity()), distance_(distance)
	{
		MovePlayerToOtherPlayer::init();
	}

	void MovePlayerToOtherPlayer::init()
	{
		distance_left_ = distance_;
	}

	int MovePlayerToOtherPlayer::choose_path()
	{
		const auto player_distance = moving_->get_component<TransformComponent>().get_horizontal_distance(comparing_);

		if (player_distance > -1 && player_distance < 1 || distance_left_ == 0)
			return 1;

		move_command_.execute(moving_);
		distance_left_ -= velocity_ * PLAYER_SPEED;

		return 0;
	}

	CheckAttackWinner::CheckAttackWinner(Entity * priority, Entity * other, const bool attack_used)
		: priority_(priority), other_(other), attack_used_(attack_used)
	{}

	int CheckAttackWinner::choose_path()
	{
		const auto distance = std::abs(priority_->get_component<TransformComponent>().get_horizontal_distance(other_));
		auto priority_pc = priority_->get_component<PlayerComponent>();
		auto other_pc = other_->get_component<PlayerComponent>();
		auto priority_distance = distance - priority_pc.attack_distance();

		if (!attack_used_)
			priority_distance -= other_pc.attack_hitbox();

		const auto winner = priority_pc.check_attack_winner(other_);

		if (priority_distance < 0)
		{
			if (winner == priority_ || attack_used_)
				return 2;
			return 3;
		}
		return 1;
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
	ScalingScrollingBackground::ScalingScrollingBackground(Entity * player_1, Entity * player_2, Entity * background)
		: moving_background_(nullptr), player_1_(player_1), player_2_(player_2), background_(background)
	{
	}

	void ScalingScrollingBackground::init()
	{
		moving_background_ = new Background(player_1_, player_2_, background_);
	}

	int ScalingScrollingBackground::choose_path()
	{
		moving_background_->screen_change();
		return 1;
	}

	void ScalingScrollingBackground::close()
	{
		moving_background_ = nullptr;
	}

	CreateAttack::CreateAttack(Entity * player)
		: player_(player)
	{}

	void CreateAttack::init()
	{
		attack_ = player_->state->palette->create_attack(player_);
	}

	int CreateAttack::choose_path()
	{
		return 0;
	}

	void CreateAttack::close()
	{
		attack_->del_group(Game::group_attacks);
		attack_->destroy();
	}

}


