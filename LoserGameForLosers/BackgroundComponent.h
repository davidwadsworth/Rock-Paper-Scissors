#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include <map>
#include "AssetManager.h"
#include "Constants.h"

class BackgroundComponent : public Component
{
private:
	TransformComponent * transform_;
	TextureComponent* texture_;
	SDL_Rect dest_rect_, left_dest_rect_, right_dest_rect_;
	int rotations_ = 0;
	int background_id_;
	SDL_RendererFlip sprite_flip_ = SDL_FLIP_NONE;
public:

	explicit BackgroundComponent(int sprite_id)
		: background_id_(sprite_id)
	{}

	~BackgroundComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		texture_ = &entity->get_component<TextureComponent>();

		auto mid_bg_id = texture_->new_tex(background_id_, &dest_rect_);
		auto left_bg_id = texture_->new_tex(background_id_, &left_dest_rect_);
		auto right_bg_id = texture_->new_tex(background_id_, &right_dest_rect_);

		texture_->create_texture_slot(mid_bg_id);
		texture_->create_texture_slot(left_bg_id);
		texture_->create_texture_slot(right_bg_id);
	}

	void update() override
	{
		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(SCREEN_HEIGHT - transform_->height * transform_->scale);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;

		left_dest_rect_.x = dest_rect_.x - dest_rect_.w;
		left_dest_rect_.y = dest_rect_.y;
		left_dest_rect_.w = dest_rect_.w;
		left_dest_rect_.h = dest_rect_.h;

		right_dest_rect_.x = dest_rect_.x + dest_rect_.w;
		right_dest_rect_.y = dest_rect_.y;
		right_dest_rect_.w = dest_rect_.w;
		right_dest_rect_.h = dest_rect_.h;
	}
};