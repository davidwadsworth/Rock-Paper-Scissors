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

		mid_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x, SCREEN_HEIGHT - transform_->height * transform_->scale);
		left_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x - transform_->width * transform_->scale, SCREEN_HEIGHT - transform_->height * transform_->scale);
		right_bg_slot_ = texture_->create_image_slot(background_id_, transform_->position.x + transform_->width * transform_->scale, SCREEN_HEIGHT - transform_->height * transform_->scale);
	}

	void update() override
	{
		const auto mid = Vector2D(transform_->position.x, SCREEN_HEIGHT - transform_->height * transform_->scale);
		const auto left = Vector2D(mid.x - transform_->width * transform_->scale, mid.y);
		const auto right = Vector2D(mid.x + transform_->width * transform_->scale, mid.y);
		texture_->update_position_and_scaling(mid_bg_slot_, mid, transform_->scale);
		texture_->update_position_and_scaling(left_bg_slot_, left, transform_->scale);
		texture_->update_position_and_scaling(right_bg_slot_, right, transform_->scale);
	}
};