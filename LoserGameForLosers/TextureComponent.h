#pragma once
#include "ECS.h"
#include "Game.h"

struct Slot
{
	explicit Slot(const DrawCall call, const SDL_Rect rect)
		: call(call), slot_rect(rect)
	{}

	DrawCall call;
	SDL_Rect slot_rect;
};

class TextureComponent : public Component
{
	TransformComponent * transform_;
	Uint8 alpha_, red_, green_, blue_;
	std::vector<DrawCall> available_calls_;
	std::vector<Slot> slots_;
	int id_count_;
	int slot_count_;
	int atlas_id_;
	AtlasData* data_;
public:

	
	TextureComponent()
		: id_count_(0), slot_count_(0)
	{
		data_ = Game::data->get_atlas_data();
	}

	~TextureComponent()
	{
		available_calls_.clear();
		slots_.clear();
		data_ = nullptr;
		transform_ = nullptr;
	}

	int create_texture_slot()
	{
		slots_.push_back(Slot(DrawCall(), SDL_Rect() ));
		return slot_count_++;
	}

	void update_slot(const int slot_id, const int updated_tex)
	{
		slots_[slot_id].call = available_calls_[updated_tex];
	}

	int new_texture(const int sprite_id, const int slot_id, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		available_calls_.push_back(DrawCall(&data_->data[sprite_id], &slots_[slot_id].slot_rect, rotation, flip));
		if (!slots_[slot_id].call.tex)
			slots_[slot_id].call = available_calls_[id_count_];
		return id_count_++;
	}

	void update_call(const int slot_id, Vector2D* position, Vector2D* scale)
	{
		if (slots_[slot_id].call.tex)
			slots_[slot_id].call.update_call(position, scale);
	}

	void draw() override
	{
		for (auto slot : slots_)
		{
			if (slot.call.tex)
				TextureManager::draw(&slot.call);
		}
	}
};