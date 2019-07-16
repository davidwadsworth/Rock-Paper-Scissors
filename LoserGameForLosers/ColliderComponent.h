#pragma once
#include "ECS.h"
#include "SpriteComponent.h"
#include "Collision.h"

/**
 * @author David Wadsworth
 * 
 * keeps track of rectangle collision
 */

class ColliderComponent : public Component
{
	bool flipped_;
	TransformComponent* transform_;
public:
	SDL_Rect collider{};

	double hit_box = 1.0;

	ColliderComponent() = default;

	explicit ColliderComponent(const double hit_box)
		: flipped_(false), transform_(nullptr), hit_box(hit_box)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		flipped_ = entity->get_component<SpriteComponent>().sprite_flip;
	}

	bool collides(Entity * other) const
	{
		return Collision::aabb(collider, other->get_component<ColliderComponent>().collider);
	}

	bool collides(Entity * other, const int padding) const
	{
		return Collision::aabb(collider, other->get_component<ColliderComponent>().collider, padding);
	}

	void update() override
	{
		collider.x = static_cast<int>(std::round(transform_->position.x));
		if (flipped_)
			collider.x += static_cast<int>(std::round(SPRITE_LENGTH * transform_->scale * (1 - hit_box)));
		collider.y = static_cast<int>(std::round(transform_->position.y));
		collider.w = static_cast<int>(std::round(SPRITE_LENGTH * transform_->scale * hit_box));
		collider.h = static_cast<int>(std::round(SPRITE_LENGTH * transform_->scale));

	}

	void draw() override
	{
		//SDL_RenderDrawRect(Game::renderer, &collider);
	}

};
