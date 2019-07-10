#pragma once
#include "Vector2D.h"
#include "Game.h"

class TransformComponent : public Component
{
public:
	Vector2D net_velocity, player_velocity, external_velocity;
	Vector2D position;

	int height = 32;
	int width = 32;
	float scale;

	int speed = 3;

	explicit TransformComponent(const float sc)
		: scale(sc)
	{}

	TransformComponent(const float x, const float y, const float sc)
		: scale(sc)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(const float x, const float y, const int h, const int w, const float sc)
		: height(h), width(w), scale(sc)
	{
		position.x = x;
		position.y = y;
	}


	float get_horizontal_distance(Entity * compare) const
	{
		return this->position.x - compare->get_component<TransformComponent>().position.x - this->width * this->scale;
	}

	void init() override
	{
		net_velocity.x = 0;
		net_velocity.y = 0;
		external_velocity.x = 0;
		external_velocity.y = 0;

		net_velocity = player_velocity + external_velocity;
	}

	void update() override
	{
		position.x += net_velocity.x * speed;
		position.y += net_velocity.y * speed;
	}
};