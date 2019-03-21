#pragma once
#include "ECS.h"
#include "Game.h"
#include "TextureSlot.h"


class TextureComponent : public Component
{
	std::vector<Slot*> slots_;
	int slot_count_;
	AtlasData* data_;
public:
	
	TextureComponent()
		: slot_count_(0)
	{
		data_ = Game::data->get_atlas_data();
	}

	~TextureComponent()
	{
		slots_.clear();
		data_ = nullptr;
	}

	int create_image_slot(const int sprite_id, const int x, const int y, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE, const int slot_id = -1)
	{
		if (slot_id < 0)
		{
			slots_.push_back(new ImageSlot(data_, sprite_id, x, y, rotation, flip));
			return slot_count_++;
		}
		slots_[slot_id] = new ImageSlot(data_, sprite_id, x, y, rotation, flip);
		return slot_id;
	}

	int create_animated_slot(const int x, const int y, const int speed, const int frames, const int sprite_id, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE, const int slot_id = -1)
	{
		auto anim_slot = new AnimatedSlot(x, y);
		anim_slot->add_animated_state(data_, speed, frames, sprite_id, rotation, flip);
		if (slot_id < 0)
		{
			slots_.push_back(anim_slot);
			return slot_count_++;
		}

		slots_[slot_id] = anim_slot;
		return slot_id;
	}

	int create_NULL_slot(const int slot_id = -1)
	{
		if (slot_id < 0)
		{
			slots_.push_back(new NULLSlot());
			return slot_count_++;
		}

		slots_[slot_id] = new NULLSlot();
		return slot_id;
	}

	void update_slot(const int slot_id, const int updated_tex, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		slots_[slot_id]->set_call(data_, updated_tex, rotation, flip);
	}

	void update_call(const int slot_id, Vector2D* position, Vector2D* scale = new Vector2D(1.0f))
	{
		slots_[slot_id]->update_call(position, scale);
	}

	void add_animation_state(const int slot_id, const int speed, const int frames, const int sprite_id, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE )
	{
		auto anim_slot = dynamic_cast<Animated*>(slots_[slot_id]);

		if (anim_slot)
			anim_slot->add_animated_state(data_, speed, frames, sprite_id, rotation, flip);
	}

	void update_animation(const int slot_id, const int state)
	{
		auto anim_slot = dynamic_cast<Animated*>(slots_[slot_id]);

		if (anim_slot)
			anim_slot->update_animation(state);
	}

	void draw() override
	{
		for (auto i = 0; i < slot_count_; i++)
			slots_[i]->draw();
	}
};
