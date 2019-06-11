#pragma once
#include "ECS.h"
#include "Attack.h"
#include "character.h"
#include "Constants.h"
#include "SpriteComponent.h"



class PlayerComponent : public Component
{
	CharacterData * data_;
	int character_id_;
	ColliderComponent * collider_;
	SpriteComponent * sprite_;
	bool is_priority_player_;
	int final_attack_id_ = final_attack_whip;

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


public:
	int num_wins;
	int attack_id;

public:
	int num_wins;
	int attack_id = attack_nothing;
	int direction = 1;

	explicit PlayerComponent(const int character_id)
		: data_(nullptr), character_id_(character_id), collider_(nullptr), sprite_(nullptr), is_priority_player_(false), num_wins(0)
	{}

	~PlayerComponent()
	{}

	void init() override
	{
		data_ = &entity->state->bank->character_data.data[character_id_];
		num_wins = 0;

		sprite_ = &entity->get_component<SpriteComponent>();
		direction = sprite_->sprite_flip ? -1 : 1;

		collider_ = &entity->get_component<ColliderComponent>();
		collider_->set_collider_hit_box(data_->hit_box);

		attack_id = attack_nothing;
	}

	void round_win()
	{
		num_wins++;
	}

	float get_velocity() const
	{
		auto velocity = data_->velocity;
		if (is_priority_player_)
			velocity = data_->velocity + PLAYER_PRIORITY_INCREMENT;
		return velocity;
	}	

	void choose_final_attack(const int att_id)
	{
		final_attack_id_ = att_id;
	}

	void execute_final_attack() const
	{
		collider_->set_collider_hit_box(data_->attack_data[final_attack_id_].hit_box);
		sprite_->set_image(final_attack_to_animation(final_attack_id_), 0);
	}

	void choose_combat_attack(const int att_id)
	{
		attack_id = att_id;
		collider_->set_collider_hit_box(data_->attack_data[attack_id].hit_box);
		sprite_->play_locked_animation(attack_to_animation(attack_id));
		sprite_->play_locked_animation(attack_to_animation(att_id));
	}

	void reset_character_hit_box()
	{
		attack_id = attack_nothing;
		collider_->set_collider_hit_box(data_->hit_box);
	}

	void change_priority()
	{
		is_priority_player_ = !is_priority_player_;
	}

	bool get_priority() const
	{
		return is_priority_player_;
	}

	AttackData* get_attack() const
	{
		return &data_->attack_data[attack_id];
	}

	AttackData* get_final_attack() const
	{
		return &data_->attack_data[final_attack_id_];
	AttackData* get_attack()
	{
		return &data_->attack_data[attack_id];
	}

	Entity* check_attack_winner(Entity *other) const
	{
		auto winner = entity;

		if (this->final_attack_id_ == final_attack_whip)
		{
			if (other->get_component<PlayerComponent>().final_attack_id_ == final_attack_Jump_Kick)
				winner = other;
		}
		if (this->final_attack_id_ == final_attack_Jump_Kick)
		{
			if (other->get_component<PlayerComponent>().final_attack_id_ == final_attack_grab)
				winner = other;
		}
		if (this->final_attack_id_ == final_attack_grab)
		{
			if (other->get_component<PlayerComponent>().final_attack_id_ == final_attack_whip)
				winner = other;
		}

		return winner;
	}

};
