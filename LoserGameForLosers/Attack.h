#pragma once
#include <string>


struct Attack
{

	float projectile_range;
	float move_distance;

	Attack(const float range, const float distance) : projectile_range(range), move_distance(distance)
	{}

	Attack()
	{
		projectile_range = WHIP_RANGE;
		move_distance = WHIP_DISTANCE;
	}
};