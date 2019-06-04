#pragma once
#include "ECS.h"
#include "Attack.h"
#include "character.h"

extern Manager manager;

class PlayerComponent : public Component
{
	CharacterData * data_;
	float hit_box_;
	int character_id_;
public:
	int num_wins;
	Attack* chosen_attack;
	std::string player_name;
	int attack_id = Whip;
	bool is_priority_player;
	Character player_identity;
	int direction;
	bool attack_used;

	explicit PlayerComponent(const int character_id)
		: character_id_(character_id)
	{}

	~PlayerComponent()
	{}

	void init() override
	{
		data_ = &entity->state->bank->character_data.data[character_id_];
		player_identity = Character(data_);
		chosen_attack = &player_identity.attacks[Jump_Kick];
		player_name = player_identity.id;
		num_wins = 0;
		attack_used = false;
	}

	void round_win()
	{
		num_wins++;
	}

	float get_velocity() const
	{
		auto velocity = player_identity.velocity;
		if (is_priority_player)
			velocity = player_identity.velocity + PLAYER_PRIORITY_INCREMENT;
		return velocity;
	}	

	void choose_attack(const int att_id)
	{
		attack_id = att_id;
		chosen_attack = &player_identity.attacks[att_id];
	}

	float attack_distance() const
	{
		return chosen_attack->move_distance * entity->get_component<TransformComponent>().scale * SPRITE_LENGTH;
	}

	float attack_hitbox() const
	{
		return chosen_attack->projectile_range * entity->get_component<TransformComponent>().scale * SPRITE_LENGTH;
	}

	void change_priority()
	{
		is_priority_player = !is_priority_player;
	}

	Entity* check_attack_winner(Entity *other) const
	{
		auto winner = entity;

		if (this->attack_id == Whip)
		{
			if (other->get_component<PlayerComponent>().attack_id == Jump_Kick)
				winner = other;
		}
		if (this->attack_id == Jump_Kick)
		{
			if (other->get_component<PlayerComponent>().attack_id == Grab)
				winner = other;
		}
		if (this->attack_id == Grab)
		{
			if (other->get_component<PlayerComponent>().attack_id == Whip)
				winner = other;
		}

		return winner;
	}

};
