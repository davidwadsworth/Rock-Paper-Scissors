#pragma once

#include "SDL.h"
#include "Components.h"
#include "Animation.h"


class SpriteComponent : public Component
{
	SDL_Rect dest_rect_{};
	int frames_ = 1;
	int speed_ = 200;
	int animation_frames_ = 3;
	float angle_ = 0;
	int anim_index_;
	TransformComponent * transform_;
	TextureComponent * texture_;
	std::vector<Animation*> animations_;
	SpriteAddress * current_address_;
	int current_animation_;
	int slot_id_;
	int height_diff, width_diff;
public:

	SDL_RendererFlip sprite_flip;
	bool animated = false;
	SDL_Point rotation_point{ 0,0 };


	explicit SpriteComponent(std::vector<Animation *> animations, SDL_RendererFlip flp = SDL_FLIP_NONE)
		:animated(true), animations_(animations), angle_(0), sprite_flip(flp)
	{}

	~SpriteComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();
		texture_ = &entity->get_component<TextureComponent>();

		for (auto anim : animations_)
		{
			for (int i = 0; i < anim->frames; i++)
			{
				anim->call_ids.push_back(texture_->new_tex(anim->index + i, &dest_rect_, 0, sprite_flip, &rotation_point));
			}
		}

		slot_id_ = texture_->create_texture_slot(animations_[0]->call_ids[0]);
		play(Idle);
		current_address_ = texture_->get_address(slot_id_);

		transform_->width = current_address_->src.w;
		transform_->height = current_address_->src.h;
		transform_->position_offset.x = current_address_->x_offset;
		transform_->position_offset.y = current_address_->y_offset;

		if (sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			entity->get_component<PlayerComponent>().direction = -1;
		}
	}


	void update() override
	{
		if (animated)
		{
			texture_->calls[slot_id_] = animations_[current_animation_]->call_ids[static_cast<int>((SDL_GetTicks() / speed_) % frames_)];
			current_address_ = texture_->get_address(slot_id_);
			transform_->width = current_address_->src.w;
			transform_->height = current_address_->src.h;
			transform_->position_offset.x = current_address_->x_offset;
			transform_->position_offset.y = current_address_->y_offset;

			if (sprite_flip && !current_address_->rotation)
				transform_->position_offset.x += current_address_->original_width - current_address_->src.w;
		}

		dest_rect_.x = std::round(transform_->position.x + transform_->position_offset.x * transform_->scale);
		dest_rect_.y = std::round(transform_->position.y + transform_->position_offset.y * transform_->scale);
		dest_rect_.w = std::round(transform_->width * transform_->scale);
		dest_rect_.h = std::round(transform_->height * transform_->scale);

		rotation_point = { static_cast<int>(std::round(current_address_->original_width * transform_->scale) / 2), static_cast<int>(std::round(current_address_->original_height * transform_->scale) / 2 )};
	}

	void play(const int animation)
	{
		frames_ = animations_[animation]->frames;
		current_animation_ = animation;
		speed_ = animations_[animation]->speed;
	}
};