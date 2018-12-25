#pragma once

#include <utility>
#include "Attack.h"

struct Character
{
public:
	float hit_box;
	std::string id;
	const char *file_path;
	std::vector<Attack*> attacks;
	float velocity;

	Character()
	{
		attacks.push_back(new Attack(WHIP_RANGE, WHIP_DISTANCE, Whip));
		attacks.push_back(new Attack(JUMP_KICK_RANGE, JUMP_KICK_DISTANCE, Jump_Kick));
		attacks.push_back(new Attack(GRAB_RANGE, GRAB_DISTANCE, Grab));
		attacks.push_back(new Attack(0, -2, Nothing));

		hit_box = 0.5f;
		id = "fighter";
		file_path = "fighter_full.png";
		velocity = 1.0;
	}

	Character(const float hit_box, std::string name, const float vel)
		: hit_box(hit_box), id(std::move(name)), velocity(vel)
	{}

	void add_attack(const float hitbox, const float distance, ATTACKS attack)
	{
		attacks.push_back(new Attack(hitbox, distance, attack));
	}

	~Character()
	{}
};
