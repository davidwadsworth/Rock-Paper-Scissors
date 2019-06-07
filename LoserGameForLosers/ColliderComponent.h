#pragma once
#include "ECS.h"
#include "SpriteComponent.h"


class ColliderComponent : public Component
{
	bool flipped_;
public:
	SDL_Rect collider{};
	TransformComponent* transform;

	float hit_box = 1.0;

	ColliderComponent() = default;

	explicit ColliderComponent(const float hit_box)
		: flipped_(false), transform(nullptr), hit_box(hit_box)
	{}

	void init() override
	{
		transform = &entity->get_component<TransformComponent>();
		flipped_ = entity->get_component<SpriteComponent>().sprite_flip;
	}

	void set_collider_hit_box(const float new_hit_box)
	{
		hit_box = new_hit_box;
	}

	void update() override
	{
		collider.x = transform->position.x;
		if (flipped_)
		{
			collider.x = transform->position.x + std::round(SPRITE_LENGTH * transform->scale * 1-hit_box);
		}
		collider.y = transform->position.y;
		collider.w = std::round(SPRITE_LENGTH * transform->scale * hit_box);
		collider.h = std::round(SPRITE_LENGTH * transform->scale);

	}

	void draw() override
	{
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &collider);
	}

};
