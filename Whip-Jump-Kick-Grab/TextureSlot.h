#pragma once
#include "DrawCall.h"
#include "Vector2D.h"
#include <vector>

/**
 * @author David Wadsworth
 * 
 * Slots which keep track of single to many atlas positions
*/

class Slot
{
public:
	explicit Slot(Texture * tex)
		: is_rotated(false), dest(), call(nullptr), width(0), height(0), texture(tex)
	{}

	virtual ~Slot() = default;

	bool is_rotated;
	Vector2D position, data_offset;
	double scale = 1.0f;
	SDL_Rect dest;
	DrawCall* call;
	int width, height;
	Texture* texture;

	void set_call(AtlasData* sprite, const int rotation, const SDL_RendererFlip flip)
	{
		call = new DrawCall(sprite, &dest, flip, rotation);
	}

	void update_position_and_scaling(const Vector2D pos, const double sc)
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
	void update_scaling(const double sc)
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
		texture->render(call->src, call->dest, call->rotation, call->rotation_point, call->flip);
	}
};

class Animated
{
public:
	virtual ~Animated() = default;
	virtual void add_animated_state(int speed, std::vector<AtlasData*> frames, int rotation,  SDL_RendererFlip flip) = 0;
	virtual void update_animation(int state) = 0;
	virtual void lock_animation(int state) = 0;
	virtual void unlock_animation() = 0;
	virtual void set_animated_call(int state, int call_id) = 0;
};

class ImageSlot : public Slot
{
public:
	explicit ImageSlot(Texture * texture, AtlasData * data, const int x, const int y, const int rotation, const SDL_RendererFlip flip)
		: Slot(texture)
	{
		dest = SDL_Rect{ x,y, data->w, data->h };
		set_call(data, rotation, flip);
	}
};

struct AnimatedState
{
private:
	Uint32 start_ticks_;
public:
	AnimatedState()
		: start_ticks_(SDL_GetTicks()), speed(0), frames(0), locked(false), current_frame(0), previous_frame(0),
		  frame_count(0)
	{
	}

	std::vector<DrawCall> calls;
	int speed;
	unsigned frames;
	bool locked;
	int current_frame;
	int previous_frame;
	unsigned frame_count;

	DrawCall* animate()
	{
		current_frame = (SDL_GetTicks() - start_ticks_) / speed % frames;
		
		return &calls[current_frame];
	}

	DrawCall* locked_animation()
	{
		current_frame = frame_count;

		if (frame_count < frames - 1)
			frame_count += (SDL_GetTicks() - start_ticks_) / speed % 2;
		return &calls[current_frame];
	}

	DrawCall* get_call(const int call_id)
	{
		return &calls[call_id];
	}

	void reset_ticks()
	{
		start_ticks_ = SDL_GetTicks();
		frame_count = 0;
	}
};

class AnimatedSlot : public Slot, public Animated
{
	std::vector<AnimatedState> animated_states_;
	AnimatedState* current_state_;
public:
	AnimatedSlot(Texture * texture, const int x, const int y)
		: Slot(texture), current_state_(nullptr)
	{
		dest = {x, y, 0, 0};
	}

	void add_animated_state(const int speed, std::vector<AtlasData*> frames, const int rotation, const SDL_RendererFlip flip) override
	{
		auto anim_state = AnimatedState();

		anim_state.frames = static_cast<unsigned>(frames.size());
		anim_state.speed = speed;
		anim_state.locked = false;

		for(auto sprite : frames)
			anim_state.calls.push_back(DrawCall(sprite, &dest, flip, rotation));

		animated_states_.push_back(anim_state);
		current_state_ = &animated_states_[0];
		call = &current_state_->calls[0];
	}

	void lock_animation(const int state) override
	{
		current_state_ = &animated_states_[state];
		current_state_->locked = true;
		current_state_->reset_ticks();
	}

	void update_animation(const int state) override
	{
		if (!current_state_->locked)
		{
			current_state_ = &animated_states_[state];
			call = current_state_->animate();
		}
		else
			call = current_state_->locked_animation();
	}

	void unlock_animation() override
	{
		current_state_->locked = false;
	}

	void set_animated_call(const int state, const int call_id) override
	{
		current_state_ = &animated_states_[state];
		call = current_state_->get_call(call_id);
	}
};