#pragma once

#include "SDL.h"
#include "Components.h"
#include "Animation.h"


class SpriteComponent : public Component
{
	SDL_Rect dest_rect_;
	int frames_ = 1;
	int speed_ = 200;
	int animation_frames_ = 3;
	int atlas_id_;
	float angle_ = 0;
	int sprite_id_;
	TransformComponent * transform_;
	SDL_Texture * texture_;
	SpriteAddress * address_;
	Animation* current_animation;
	Atlas* atlas_;
public:

	bool animated = false;
	int anim_index = 0;

	std::vector<Animation*> animations;

	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;


	explicit SpriteComponent(int sprite_id, const bool is_animated, float angle = 0, SDL_RendererFlip flp = SDL_FLIP_NONE)
		: sprite_id_(sprite_id), animated(is_animated), angle_(angle), sprite_flip(flp)
	{}

	~SpriteComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		texture_ = entity->get_component<TextureComponent>().texture;
		atlas_ = entity->get_component<TextureComponent>().atlas;

		if (sprite_flip == SDL_FLIP_HORIZONTAL)
		{
			entity->get_component<PlayerComponent>().direction = -1;
		}
		address_ = atlas_->addresses[sprite_id_];

		auto idle = new Animation(sprite_id_, animation_frames_, speed_);
		auto walk_right = new Animation(sprite_id_ + animation_frames_, animation_frames_, speed_);
		auto walk_left = new Animation(sprite_id_ + animation_frames_ * 2, animation_frames_, speed_);

		animations.push_back(idle);
		animations.push_back(walk_right);
		animations.push_back(walk_left);
		play(Idle);
	}
	void update() override
	{
		if (animated)
		{
			address_ = atlas_->addresses[anim_index + static_cast<int>((SDL_GetTicks() / speed_) % frames_)];
		}

		dest_rect_.x = static_cast<int>(transform_->position.x);
		dest_rect_.y = static_cast<int>(transform_->position.y);
		dest_rect_.w = transform_->width * transform_->scale;
		dest_rect_.h = transform_->height * transform_->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture_, address_, &dest_rect_, angle_, sprite_flip);
	}

	void play(const int animation)
	{
		frames_ = animations[animation]->frames;
		anim_index = animations[animation]->index;
		speed_ = animations[animation]->speed;
	}
};