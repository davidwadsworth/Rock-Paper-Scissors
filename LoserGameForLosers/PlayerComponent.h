#pragma once
#include "ECS.h"
#include <map>
#include "Attack.h"
#include "character.h"

extern Manager manager;

class PlayerComponent : public Component
{
	float hit_box_;
public:
	int num_wins;
	Attack* chosen_attack;
	std::string player_name;
	ATTACKS attack_id = Nothing;
	bool is_priority_player;
	Character* player_identity;
	int direction;
	bool attack_used;

	PlayerComponent() 
		: direction(1)
	{
		player_name = "NOT GOOD";
		is_priority_player = false;
		player_identity = new Character();
		num_wins = 0;

	}

	PlayerComponent(const bool has_priority, Character* character) : is_priority_player(has_priority), direction(1), player_identity(character)
	{
		player_name = character->id;

		num_wins = 0;
	}

	~PlayerComponent()
	{}

	void init() override
	{
		chosen_attack = player_identity->attacks[Nothing];
		attack_used = false;
	}

	void round_win()
	{
		num_wins++;
	}

	float get_velocity()
	{
		auto velocity = player_identity->velocity;
		if (is_priority_player)
			velocity = player_identity->velocity + PLAYER_PRIORITY_INCREMENT;
		return velocity;
	}	

	void choose_attack(ATTACKS att_id)
	{
		attack_id = att_id;
		chosen_attack = player_identity->attacks[att_id];
	}

	void change_priority()
	{
		is_priority_player = !is_priority_player;
	}

	Entity* check_attack_winner(Entity *other)
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
		if (attack_used)
			winner = other;

		return winner;
	}

};
