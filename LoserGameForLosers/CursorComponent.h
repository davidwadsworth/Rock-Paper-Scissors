#pragma once
#include "ECS.h"

class CursorComponent : public Component
{
	OptionsComponent * options_;
	SDL_Rect* dest_;
	SDL_Texture * texture_;
	float angle_;
	int sprite_id_, atlas_id_;
	SDL_RendererFlip cursor_flip_;
	SpriteAddress * cursor_address_;
public:

	CursorComponent(int sprite_id)
		: angle_(0), cursor_flip_(SDL_FLIP_NONE), sprite_id_(sprite_id)
	{}

	~CursorComponent()
	{}

	void init() override
	{
		if (entity->has_component<OptionsComponent>())
		{
			options_ = &entity->get_component<OptionsComponent>();

			dest_ = options_->get_current_link()->get_cursor_dimensions();
		}

		texture_ = entity->get_component<TextureComponent>().texture;
		atlas_id_ = entity->get_component<TextureComponent>().atlas_id;

		cursor_address_ = Game::data->get_sprite_address(atlas_id_, sprite_id_);

	}


	void update() override
	{
		dest_ = options_->get_current_link()->get_cursor_dimensions();
	}

	void draw() override
	{
		TextureManager::draw(texture_, cursor_address_, dest_, angle_, cursor_flip_);
	}
};
