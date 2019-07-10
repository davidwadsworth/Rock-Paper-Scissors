#pragma once
#include "ECS.h"
#include "SpriteComponent.h"
#include "Collision.h"


class ColliderComponent : public Component
{
	bool flipped_;
	TransformComponent* transform_;
public:
	SDL_Rect collider{};

	float hit_box = 1.0;

	ColliderComponent() = default;

	explicit ColliderComponent(const float hit_box)
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
		collider.x = transform_->position.x;
		if (flipped_)
			collider.x = transform_->position.x + std::round(SPRITE_LENGTH * transform_->scale * (1 - hit_box) );
		collider.y = transform_->position.y;
		collider.w = std::round(SPRITE_LENGTH * transform_->scale * hit_box);
		collider.h = std::round(SPRITE_LENGTH * transform_->scale);

	}

	void draw() override
	{
		//SDL_RenderDrawRect(Game::renderer, &collider);
	}

};
