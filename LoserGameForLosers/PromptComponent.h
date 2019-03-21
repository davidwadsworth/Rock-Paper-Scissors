#pragma once
#include "ECS.h"

class PromptComponent : public Component
{
	TextureComponent * texture_;
	TransformComponent * transform_;
	int sprite_id_, prompt_slot_;
public:

	explicit PromptComponent(const int sprite_id)
		: sprite_id_(sprite_id)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureComponent>();
		prompt_slot_ = texture_->create_image_slot(sprite_id_, transform_->position.x, transform_->position.y);
	}
};