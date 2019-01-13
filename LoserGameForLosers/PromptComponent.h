#pragma once
#include "ECS.h"
#include "Game.h"
#include "Components.h"

class PromptComponent : public Component
{
	SDL_Texture * tex_;
	SDL_Rect dest_rect_;
	TransformComponent * transform_;
	int atlas_id_, sprite_id_;
	SpriteAddress * prompt_address;
public:

	PromptComponent(int sprite_id)
		: sprite_id_(sprite_id)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		tex_ = entity->get_component<TextureComponent>().texture;
		atlas_id_ = entity->get_component<TextureComponent>().atlas_id;


		prompt_address = Game::data->get_sprite_address[atlas_id_, sprite_id_];
	}

	void update() override
	{
		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::draw(tex_, prompt_address, &dest_rect_, 0, SDL_FLIP_NONE);
	}
};