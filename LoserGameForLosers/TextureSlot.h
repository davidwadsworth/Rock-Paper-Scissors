#pragma once
#include "DrawCall.h"
#include "Vector2D.h"
#include <vector>
#include "TextureManager.h"

class Slot
{
public:
	Slot(AtlasData * data)
		: atlas_data(data)
	{}
	virtual ~Slot() = default;

	bool is_rotated;
	Vector2D position, data_offset;
	float scale;
	SDL_Rect dest;
	DrawCall* call;
	AtlasData * atlas_data;
	int width, height;

	void set_call(const int sprite_id, const int rotation, const SDL_RendererFlip flip)
	{
		call = new DrawCall(&atlas_data->data[sprite_id], &dest, flip, rotation);
	}

	void update_position_and_scaling(const Vector2D pos, const float sc)
	{
		position = pos;
		scale = sc;
		call->update_rotation_point(scale);
		update();

	}
	void update_position(const Vector2D pos)
	{
		position = pos;
		update();
	}
	void update_scaling(const float sc)
	{
		scale = sc;
		call->update_rotation_point(scale);
		update();
	}
	void update_dimensions(const int w, const int h)
	{
		call->update_height(h);
		call->update_width(w);
		update();
	}

	void update_width(const int w)
	{
		call->update_width(w);
		update();
	}

	void update_height(const int h)
	{
		call->update_height(h);
		update();
	}

	void update()
	{ 
		dest.x = static_cast<int>(position.x + call->position_offset().x * scale);
		dest.y = static_cast<int>(position.y + call->position_offset().y * scale);
		dest.w = static_cast<int>(call->width * scale);
		dest.h = static_cast<int>(call->height * scale);
	}

	void draw() const
	{
		TextureManager::draw(call);
	}
};

class Animated
{
public:
	virtual ~Animated() = default;
	virtual void add_animated_state(int speed, int frames, int sprite_id, int rotation, SDL_RendererFlip flip) = 0;
	virtual void update_animation(int state) = 0;
	virtual void set_animated_call(int state, int call_id) = 0;
};

class ImageSlot : public Slot
{
public:
	explicit ImageSlot(AtlasData * data, const int sprite_id, const int x, const int y, const int rotation, const SDL_RendererFlip flip)
		: Slot(data)
	{
		dest = SDL_Rect{ x,y, data->data[sprite_id].w, data->data[sprite_id].h };
		set_call(sprite_id, rotation, flip);
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

	DrawCall* get_call(const int call_id)
	{
		return &calls[call_id];
	}
};

class AnimatedSlot : public Slot, public Animated
{
	std::vector<AnimatedState> animated_states_;
	SDL_Rect rect_;
public:
	AnimatedSlot(AtlasData* data, const int x, const int y)
		: Slot(data), rect_{x, y, 0, 0}
	{}

	void add_animated_state(const int speed, const int frames, const int sprite_id, const int rotation, const SDL_RendererFlip flip) override
	{
		auto anim_state = AnimatedState();

		anim_state.frames = frames;
		anim_state.speed = speed;

		for(auto id = sprite_id; id < sprite_id + frames; id++)
			anim_state.calls.push_back(DrawCall(&atlas_data->data[sprite_id], &rect_, flip, rotation));

		call = &animated_states_[0].calls[0];
		animated_states_.push_back(anim_state);
	}

	void update_animation(const int state) override
	{
		call = animated_states_[state].animate();
	}

	void set_animated_call(const int state, const int call_id) override
	{
		call = animated_states_[state].get_call(call_id);
	}
};