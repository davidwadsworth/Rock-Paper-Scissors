#pragma once
#include "DrawCall.h"
#include "Vector2D.h"
#include <vector>
#include "TextureManager.h"

class Slot
{
public:
	virtual ~Slot() = default;
	virtual void set_call(AtlasData * data, int sprite_id, int rotation, SDL_RendererFlip flip) = 0;
	virtual void update_call(Vector2D* position, Vector2D* scaling) = 0;
	virtual void draw() = 0;
};

class Animated
{
public:
	virtual ~Animated() = default;
	virtual void add_animated_state(AtlasData * data, int speed, int frames, int sprite_id, int rotation, SDL_RendererFlip flip) = 0;
	virtual void update_animation(int state) = 0;
};

class ImageSlot : public Slot
{
	DrawCall call_;
	SDL_Rect rect_;

public:
	explicit ImageSlot(AtlasData * data, const int sprite_id, const int x, const int y, const int rotation, const SDL_RendererFlip flip)
		: rect_ {x,y, 0, 0}
	{
		ImageSlot::set_call(data, sprite_id, rotation, flip);
	}

	void set_call(AtlasData* data, const int sprite_id, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE) override
	{
		call_ = DrawCall(data->data[sprite_id], &rect_, rotation, flip);
	}

	void update_call(Vector2D* position, Vector2D* scaling) override
	{
		call_.update_call(position, scaling);
	}

	void draw() override
	{
		TextureManager::draw(&call_);
	}
};

struct AnimatedState
{
	std::vector<DrawCall> calls;
	int speed;
	int frames;

	DrawCall* animate()
	{
		return &calls[static_cast<int>(SDL_GetTicks() / speed) % frames];
	}
};

class AnimatedSlot : public Slot, public Animated
{
	DrawCall* call_;
	std::vector<AnimatedState> animated_states_;
	SDL_Rect rect_;

public:
	AnimatedSlot(const int x, const int y)
		: call_(nullptr), rect_{x, y, 0, 0}
	{}

	void add_animated_state(AtlasData * data, const int speed, const int frames, const int sprite_id, const int rotation, const SDL_RendererFlip flip) override
	{
		auto anim_state = AnimatedState();
		auto sprite_data = data->data;

		anim_state.frames = frames;
		anim_state.speed = speed;

		for(auto id = sprite_id; id < sprite_id + frames; id++)
		{
			anim_state.calls.push_back(DrawCall(sprite_data[id], &rect_, rotation, flip));
		}

		if (call_)
		{
			call_ = &animated_states_[0].calls[0];
		}

		animated_states_.push_back(anim_state);
	}

	void set_call(AtlasData* data, const int sprite_id, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE) override
	{
		call_ = new DrawCall(data->data[sprite_id], &rect_, rotation, flip);
	}

	void update_call(Vector2D* position, Vector2D* scaling) override
	{
		call_->update_call(position, scaling);
	}

	void update_animation(const int state) override
	{
		call_ = animated_states_[state].animate();
	}

	void draw() override
	{
		TextureManager::draw(call_);
	}

};

class NULLSlot : public Slot
{
public:
	NULLSlot() = default;
	void set_call(AtlasData* data, int sprite_id, int rotation, SDL_RendererFlip flip) override
	{}

	void update_call(Vector2D* position, Vector2D* scaling) override
	{}

	void draw() override
	{}
};