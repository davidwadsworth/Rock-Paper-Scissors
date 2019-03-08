#pragma once
#include "ECS.h"


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
			hit_box = entity->get_component<PlayerComponent>().player_identity.hit_box;
		}
	}

	void draw_attack_collider()
	{
		auto player = entity->get_component<PlayerComponent>();

		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, projectile_point, collider.y + 10,
			projectile_point + player.chosen_attack->projectile_range * transform->scale_2d.x * transform->height * player.direction, collider.y + 10);
	}

	void draw_collision()
	{
		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Game::renderer, new SDL_Rect{ projectile_point, static_cast<int>(collider.y * 2 / (entity->get_component<PlayerComponent>().attack_id + 1)), static_cast<int>(entity->get_component<PlayerComponent>().chosen_attack->projectile_range * transform->scale_2d.x * SPRITE_LENGTH) * entity->get_component<PlayerComponent>().direction, static_cast<int>(transform->scale_2d.x * SPRITE_LENGTH / 3) });
	}

	void draw_movement()
	{
		SDL_SetRenderDrawColor(Game::renderer, red_, green_, blue_, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Game::renderer, new SDL_Rect{ projectile_point, collider.y, static_cast<int>(entity->get_component<PlayerComponent>().chosen_attack->move_distance * transform->scale_2d.x * SPRITE_LENGTH) * entity->get_component<PlayerComponent>().direction, static_cast<int>(transform->scale_2d.x * SPRITE_LENGTH) });
	}

	void set_color(Uint8 r, Uint8 g, Uint8 b)
	{
		red_ = r;
		green_ = g;
		blue_ = b;
	}

	void update() override
	{
		collider.x = transform->position.x;
		projectile_point = transform->position.x + std::round(SPRITE_LENGTH * transform->scale_2d.x * hit_box);
		if (flipped_)
		{
			collider.x = transform->position.x + std::round(SPRITE_LENGTH * transform->scale_2d.x * (1 - hit_box));
			projectile_point = transform->position.x + SPRITE_LENGTH * transform->scale_2d.x * (1 - hit_box);
		}
		collider.y = transform->position.y;
		collider.w = std::round(SPRITE_LENGTH * transform->scale_2d.x * hit_box);
		collider.h = std::round(SPRITE_LENGTH * transform->scale_2d.x);

	}


	void draw() override
	{
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Game::renderer, &collider);
		if (draw_attack)
		{
			draw_collision();
		}
	}

};
