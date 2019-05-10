#pragma once

#include "SDL.h"


class SpriteComponent : public Component
{
	int speed_ = 200;
	int animation_frames_ = 3;
	TransformComponent * transform_;
	TextureAtlasComponent * texture_;
	int slot_id_;
	int animation_state_;
	int sprite_rotation_;
	int sprite_id_;
public:

	SDL_RendererFlip sprite_flip;
	bool animated = false;
	SDL_Point rotation_point{ 0,0 };


	explicit SpriteComponent(const int sprite_id, const SDL_RendererFlip flp = SDL_FLIP_NONE, const int rots = 0)
		: animation_state_(0), sprite_rotation_(rots), sprite_id_(sprite_id), sprite_flip(flp), animated(true)
	{}

	~SpriteComponent()
	{
		texture_ = nullptr;
		transform_ = nullptr;
	}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureAtlasComponent>();

		slot_id_ = texture_->create_animated_slot(transform_->position.x, transform_->position.y, speed_, animation_frames_, sprite_id_, sprite_rotation_, sprite_flip);
		texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_, sprite_rotation_, sprite_flip);
		texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_ * 2, sprite_rotation_, sprite_flip);

		if (sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			entity->get_component<PlayerComponent>().direction = -1;
		}
	}

	void update() override
	{
		if (animated)
			texture_->update_animation(slot_id_, animation_state_);
		texture_->update_position_and_scaling(slot_id_, &transform_->position, &transform_->scale);
	}

	void play(const int animation)
	{
		animation_state_ = animation;
	}
};