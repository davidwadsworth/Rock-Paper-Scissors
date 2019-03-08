#pragma once

#include "Attack.h"

struct Character
{
	float hit_box;
	std::string id;
	float velocity;
	std::vector<Attack> attacks;

	Character() = default;

	Character(CharacterData * data)
		: hit_box(data->hitbox), id(data->id), velocity(data->velocity)
	{
		for(auto att : data->attack_data)
		{
			attacks.push_back(Attack(att.hitbox, att.distance));
		}
	}

	~Character()
	{}
};
