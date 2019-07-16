#pragma once
#include "Vector2D.h"
#include "Game.h"

/**
 * @author David Wadsworth
 *
 * In charge of position scaling, velocity, height, width, and scaling of the entity
*/

class TransformComponent : public Component
{
public:
	Vector2D net_velocity, player_velocity, external_velocity;
	Vector2D position;

	int height = 32;
	int width = 32;
	double scale;

	int speed = 3;

	explicit TransformComponent(const double sc)
		: scale(sc)
	{}

	TransformComponent(const double x, const double y, const double sc)
		: scale(sc)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(const double x, const double y, const int h, const int w, const double sc)
		: height(h), width(w), scale(sc)
	{
		position.x = x;
		position.y = y;
	}


	double get_horizontal_distance(Entity * compare) const
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