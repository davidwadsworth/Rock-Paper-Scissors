#pragma once

#include "SDL.h"
#include "Animation.h"


class SpriteComponent : public Component
{
	int frames_ = 1;
	int speed_ = 200;
	int animation_frames_ = 3;
	int anim_index_;
	TransformComponent * transform_;
	TextureComponent * texture_;
	std::vector<Animation*> animations_;
	int current_animation_;
	int slot_id_;
public:

	SDL_RendererFlip sprite_flip;
	bool animated = false;
	SDL_Point rotation_point{ 0,0 };


	explicit SpriteComponent(const std::vector<Animation *> animations, const SDL_RendererFlip flp = SDL_FLIP_NONE)
		: animations_(animations), sprite_flip(flp), animated(true)
	{}

	~SpriteComponent()
	{
		animations_.clear();
		texture_ = nullptr;
		transform_ = nullptr;
	}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureComponent>();

		slot_id_ = texture_->create_texture_slot();

		for (auto anim : animations_)
		{
			for (auto i = 0; i < anim->frames; i++)
			{
				anim->call_ids.push_back(texture_->new_texture(anim->index + i, slot_id_, 0, sprite_flip));
			}
		}

		play(Idle);


		if (sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			entity->get_component<PlayerComponent>().direction = -1;
		}
	}


	void update() override
	{
		auto sprite = animations_[current_animation_]->call_ids[0];
		if (animated)
			sprite = animations_[current_animation_]->call_ids[static_cast<int>((SDL_GetTicks() / speed_) % frames_)];

		texture_->update_slot(slot_id_, sprite);
		texture_->update_call(slot_id_, &transform_->position, &transform_->scale_2d);
	}

	void play(const int animation)
	{
		frames_ = animations_[animation]->frames;
		current_animation_ = animation;
		speed_ = animations_[animation]->speed;
	}
};