#pragma once
#pragma once
#include "ECS.h"

class WhiteRectComponent : public Component
{
	OptionsComponent * options_;
	SDL_Rect box_rect;

public:

	WhiteRectComponent()
		: options_(nullptr), box_rect()
	{}

	void set_rect()
	{
		box_rect = options_->box;
	}

	void init() override
	{
		options_ = &entity->get_component<OptionsComponent>();
		set_rect();
	}

	void draw() override
	{
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Game::renderer, &box_rect);
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Game::renderer, &box_rect);
	}
};