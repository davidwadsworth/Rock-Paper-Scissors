#pragma once
#include "ECS.h"
/**
 * @author David Wadsworth
 *
 * in charge of creating the prompts that flash in 
*/
class PromptComponent : public Component
{
	TextureAtlasComponent * texture_;
	TransformComponent * transform_;
	int sprite_id_, prompt_slot_;
public:

	explicit PromptComponent(const int sprite_id)
		: texture_(nullptr), transform_(nullptr), sprite_id_(sprite_id), prompt_slot_(0)
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureAtlasComponent>();
		prompt_slot_ = texture_->create_image_slot(sprite_id_, static_cast<int>(transform_->position.x), static_cast<int>(transform_->position.y));
	}
};