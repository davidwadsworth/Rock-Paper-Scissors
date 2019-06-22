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
	bool animated_;
public:
	SDL_RendererFlip sprite_flip;
	bool animated = false;

	explicit SpriteComponent(const int sprite_id, const SDL_RendererFlip flp = SDL_FLIP_NONE, const int rots = 0)
		: animation_state_(0), sprite_rotation_(rots), sprite_id_(sprite_id), animated_(true), sprite_flip(flp)
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

		/* Idle       */slot_id_ = texture_->create_animated_slot(transform_->position.x, transform_->position.y, speed_, animation_frames_, sprite_id_ + animation_frames_ * 3, sprite_rotation_, sprite_flip);
		/* Walk Left  */texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_ * 6, sprite_rotation_, sprite_flip);
		/* Walk Right */texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_ * 7, sprite_rotation_, sprite_flip);
		/* Block      */texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_, sprite_rotation_, sprite_flip);
		/* Kick       */texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_ * 4, sprite_rotation_, sprite_flip);
		/* Push       */texture_->add_animation_state(slot_id_, speed_, animation_frames_, sprite_id_ + animation_frames_ * 5, sprite_rotation_, sprite_flip);
		/* Hit        */texture_->add_animation_state(slot_id_, 400, animation_frames_, sprite_id_ + animation_frames_ * 2, sprite_rotation_, sprite_flip);
		/* Whip       */texture_->add_animation_state(slot_id_, speed_, 1, sprite_id_ + 2, sprite_rotation_, sprite_flip);
		/* Jump Kick  */texture_->add_animation_state(slot_id_, speed_, 1, sprite_id_ + 1, sprite_rotation_, sprite_flip);
		/* Grab       */texture_->add_animation_state(slot_id_, speed_, 1, sprite_id_, sprite_rotation_, sprite_flip);
	}

	void play_locked_animation(const int animation) const
	{
		texture_->lock_animation(slot_id_, animation);
	}

	void unlock_animation() const
	{
		texture_->unlock_animation(slot_id_);
	}

	void set_image(const int animation, const int image_id)
	{
		animated_ = false;
		texture_->set_animated_call(slot_id_, animation, image_id);
	}

	void unset_image()
	{
		animated_ = true;
	}

	void update() override
	{
		if (animated_)
			texture_->update_animation(slot_id_, animation_state_);
		texture_->update_position_and_scaling(slot_id_, transform_->position, transform_->scale);
	}

	void play_animation(const int animation)
	{
		animation_state_ = animation;
	}
};