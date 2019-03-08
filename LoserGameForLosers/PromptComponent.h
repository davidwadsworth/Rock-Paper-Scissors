#pragma once
#include "ECS.h"

class PromptComponent : public Component
{
	TextureComponent * texture_;
	TransformComponent * transform_;
	int sprite_id_;
public:

	explicit PromptComponent(const int sprite_id)
		: sprite_id_(sprite_id)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureComponent>();
		const auto slot_id = texture_->create_texture_slot();
		texture_->new_texture(sprite_id_, slot_id);
		texture_->update_call(slot_id, &transform_->position, &transform_->scale_2d);
	}
};