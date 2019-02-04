#pragma once
#include "ECS.h"
#include "Game.h"
#include "Components.h"

class PromptComponent : public Component
{
	TextureComponent * texture_;
	SDL_Rect dest_rect_;
	TransformComponent * transform_;
	int sprite_id_;
	SpriteAddress * prompt_address;
public:

	PromptComponent(int sprite_id)
		: sprite_id_(sprite_id)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureComponent>();
		
		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = static_cast<int>(transform_->width * transform_->scale);
		dest_rect_.h = static_cast<int>(transform_->height * transform_->scale);

		auto prompt_id = texture_->new_tex(sprite_id_, &dest_rect_);
		texture_->create_texture_slot(prompt_id);
	}
};