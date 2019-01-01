#pragma once

#include <utility>
#include "Attack.h"

struct Character
{
public:
	float hit_box;
	std::string id;
	std::vector<Attack*> attacks;
	float velocity;

	Character()
	{
		attacks.push_back(new Attack(WHIP_RANGE, WHIP_DISTANCE));
		attacks.push_back(new Attack(JUMP_KICK_RANGE, JUMP_KICK_DISTANCE));
		attacks.push_back(new Attack(GRAB_RANGE, GRAB_DISTANCE));
		attacks.push_back(new Attack(0, -2));

		hit_box = 0.5f;
		id = "fighter";
		velocity = 1.0;
	}

	Character( const char * name, const float vel, const float hit_box )
		: hit_box(hit_box), id(name), velocity(vel)
	{}

	void add_attack(const float hitbox, const float distance)
	{
		attacks.push_back(new Attack(hitbox, distance));
	}

	~Character()
	{}
};
