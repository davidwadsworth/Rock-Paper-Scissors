#pragma once
#include "ECS.h"
#include "Constants.h"
#include "SpriteComponent.h"

/**
 * @author David Wadsworth
 *
 * hub to for creating and updating the player and its attack values
*/

class PlayerComponent : public Component
{
	CharacterData * data_;
	int character_id_;
	ColliderComponent * collider_;
	SpriteComponent * sprite_;
	bool is_priority_player_;
	int final_attack_id_ = final_attack_whip;
	double velocity_offset_;

	static ANIMATIONS attack_to_animation(const int attack)
	{
		switch (attack)
		{
		case attack_block:
			return animation_player_block;
		case attack_kick:
			return animation_player_kick;
		case attack_push:
			return animation_player_push;
		default:
			return animation_player_idle;
		}
	}

	static ANIMATIONS final_attack_to_animation(const int attack)
	{
		switch (attack)
		{
		case final_attack_whip:
			return animation_player_whip;
		case final_attack_Jump_Kick:
			return animation_player_jump_kick;
		case final_attack_grab:
			return animation_player_grab;
		default:
			return animation_player_idle;
		}
	}

	static CHARACTER_ATTACK_DATA combat_attack_to_data(const int attack)
	{
		switch (attack)
		{
		case attack_block:
			return character_order_attack_block;
		case attack_kick:
			return character_order_attack_kick;
		case attack_push:
			return character_order_attack_push;
		default:
			return character_order_attack_whip;
		}
	}

	static CHARACTER_ATTACK_DATA final_attack_to_data(const int attack)
	{
		switch (attack)
		{
		case final_attack_whip:
			return character_order_attack_whip;
		case final_attack_Jump_Kick:
			return character_order_attack_jump_kick;
		case final_attack_grab:
			return character_order_attack_grab;
		default:
			return character_order_attack_push;
		}
	}

public:
	int num_wins;
	int attack_id = attack_nothing;
	int direction = 1;

	explicit PlayerComponent(const int character_id)
		: data_(nullptr), character_id_(character_id), collider_(nullptr), sprite_(nullptr), is_priority_player_(false), num_wins(0), velocity_offset_(1.0f)
	{}

	~PlayerComponent()
	{}

	void init() override
	{
		data_ = &GameState::get_character_data()->data[character_id_];
		num_wins = 0;

		sprite_ = &entity->get_component<SpriteComponent>();
		direction = sprite_->sprite_flip ? -1 : 1;

		if (!sprite_->sprite_flip)
			is_priority_player_ = true;

		collider_ = &entity->get_component<ColliderComponent>();
		collider_->hit_box = data_->hit_box;

		attack_id = attack_nothing;
	}

	void round_win()
	{
		num_wins++;
	}

	void set_velocity_offset(const double vel_o)
	{
		velocity_offset_ = vel_o;
	}

	void reset_velocity_offset()
	{
		velocity_offset_ = 1.0f;
	}

	double get_velocity() const
	{
		if (is_priority_player_)
			return (data_->velocity + PLAYER_PRIORITY_INCREMENT) * velocity_offset_;

		return data_->velocity * velocity_offset_;
	}	

	void choose_final_attack(const int att_id)
	{
		final_attack_id_ = att_id;
	}

	void execute_final_attack() const
	{
		collider_->hit_box = data_->attack_data[final_attack_id_].hit_box;
		sprite_->set_image(final_attack_to_animation(final_attack_id_), 0);
	}

	void choose_combat_attack(const int att_id)
	{
		attack_id = att_id;
	}

	void execute_combat_attack() const
	{
		collider_->hit_box = data_->attack_data[combat_attack_to_data(attack_id)].hit_box;
		sprite_->play_locked_animation(attack_to_animation(attack_id));
	}

	void reset_character_hit_box()
	{
		attack_id = attack_nothing;
		collider_->hit_box = data_->hit_box;
		sprite_->unlock_animation();
		sprite_->unset_image();
	}

	void change_priority()
	{
		is_priority_player_ = !is_priority_player_;
	}

	bool get_priority() const
	{
		return is_priority_player_;
	}

	int get_character_id() const { return character_id_; }

	AttackData* get_attack() const
	{
		return &data_->attack_data[combat_attack_to_data(attack_id)];
	}

	AttackData* get_attack(const int att_id) const
	{
		return &data_->attack_data[combat_attack_to_data(att_id)];
	}

	AttackData* get_final_attack() const
	{
		return &data_->attack_data[final_attack_id_];
	}

	AttackData* get_final_attack(const int att_id) const
	{
		return &data_->attack_data[final_attack_to_data(att_id)];
	}

	int check_attack_winner(Entity *other) const
	{
		const auto other_pc = &other->get_component<PlayerComponent>();

		if (this->final_attack_id_ == final_attack_whip)
		{
			if (other_pc->final_attack_id_ == final_attack_Jump_Kick)
				return get_character_id() + 1;
		}
		if (this->final_attack_id_ == final_attack_Jump_Kick)
		{
			if (other_pc->final_attack_id_ == final_attack_grab)
				return get_character_id() + 1;
		}
		if (this->final_attack_id_ == final_attack_grab)
		{
			if (other_pc->get_character_id() == final_attack_whip)
				return get_character_id() + 1;
		}

		return other_pc->get_character_id() + 1;
	}

};
