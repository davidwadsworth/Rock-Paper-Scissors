#pragma once
#include "ECS.h"
#include "Components.h"


class ColliderComponent : public Component
{
private:
	bool flipped_;
	Uint8 red_, green_, blue_;
public:

	SDL_Rect collider{};
	std::string tag;
	bool draw_attack;

	SDL_Rect src_r, dest_r;

	TransformComponent* transform;

	float hit_box = 1.0;
	int projectile_point;

	ColliderComponent() {}

	ColliderComponent(const std::string& t)
	{
		tag = t;
	}

	ColliderComponent(const std::string& t, const int x, const int y, const int size)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = collider.w = size;
	}

	void init() override
	{
		transform = &entity->get_component<TransformComponent>();
		flipped_ = false;
		draw_attack = false;

		red_ = 0;
		green_ = 0;
		blue_ = 0;

		if (entity->has_component<SpriteComponent>())
			if (entity->get_component<SpriteComponent>().sprite_flip == SDL_FLIP_HORIZONTAL)
				flipped_ = true;

		if (entity->has_component<PlayerComponent>())
		{
			tag = entity->get_component<PlayerComponent>().player_name;
			hit_box = entity->get_component<PlayerComponent>().player_identity->hit_box;
		}
	}

	void update() override
	{
		collider.x = transform->position.x;
		projectile_point = transform->position.x + std::round(SPRITE_LENGTH * transform->scale * (1 - hit_box));
		if (flipped_)
		{
			collider.x = transform->position.x + std::round(SPRITE_LENGTH * transform->scale * (1 - hit_box));
			projectile_point = transform->position.x + SPRITE_LENGTH * transform->scale * (1 - hit_box);
		}
		collider.y = transform->position.y;
		collider.w = std::round(SPRITE_LENGTH * transform->scale * hit_box);
		collider.h = std::round(SPRITE_LENGTH * transform->scale);

	}

	void draw() override
	{
		SDL_RenderDrawRect(Game::renderer, &collider);
	}

};