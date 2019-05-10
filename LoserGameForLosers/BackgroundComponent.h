#pragma once

#include "Constants.h"

class BackgroundComponent : public Component
{
	TransformComponent * transform_;
	TextureAtlasComponent* texture_;
	int background_id_;
	int left_bg_slot_, mid_bg_slot_, right_bg_slot_;
public:

	explicit BackgroundComponent(const int sprite_id)
		: background_id_(sprite_id)
	{}

	~BackgroundComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureAtlasComponent>();

		mid_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x, SCREEN_HEIGHT - transform_->height * transform_->scale_2d.y);
		left_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x - transform_->width * transform_->scale_2d.x, SCREEN_HEIGHT - transform_->height * transform_->scale_2d.y);
		right_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x + transform_->width * transform_->scale_2d.x, SCREEN_HEIGHT - transform_->height * transform_->scale_2d.y);
	}

	void update() override
	{
		const auto mid = new Vector2D(transform_->position.x, SCREEN_HEIGHT - transform_->height * transform_->scale_2d.y);
		const auto left = new Vector2D(mid->x - transform_->width * transform_->scale_2d.x, mid->y);
		const auto right = new Vector2D(mid->x + transform_->width * transform_->scale_2d.x, mid->y);
		texture_->update_call(mid_bg_slot_, mid, &transform_->scale_2d);
		texture_->update_call(left_bg_slot_, left, &transform_->scale_2d);
		texture_->update_call(right_bg_slot_, right, &transform_->scale_2d);
	}
};