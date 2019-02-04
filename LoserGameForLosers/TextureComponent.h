#pragma once
#include "ECS.h"
#include "Game.h"

class TextureComponent : public Component
{
	TransformComponent * transform_;
	Uint8 alpha_, red_, green_, blue_;
	std::vector<DrawCall *> available_calls_;
	int id_count_;
	int component_slot_;
	int atlas_id_;
	Atlas * atlas_;
public:

	std::vector<int> calls;
	
	TextureComponent(int tex_id = atlas_texture_sheet_main)
		: id_count_(0), component_slot_(0), atlas_id_(tex_id)
	{
		atlas_ = Game::data->get_atlas(tex_id);
	}

	~TextureComponent() {}

	DrawCall * get_call(int slot)
	{
		return available_calls_[calls[slot]];
	}

	SpriteAddress * get_address(int slot_id)
	{
		return atlas_->addresses[get_call(slot_id)->id];
	}

	int create_texture_slot(int starting_call)
	{
		calls.push_back(starting_call);
		component_slot_++;
		return component_slot_ - 1;
	}

	int new_tex(int data_id, SDL_Rect* dest, int rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point * rotation_point = nullptr, SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING)
	{
		auto address = atlas_->addresses[data_id];
		auto draw_call = new DrawCall();

		draw_call->id = data_id;
		draw_call->src = &address->src;
		draw_call->dest = dest;
		draw_call->tex = Game::assets->get_texture(atlas_id_);
		draw_call->rotation = rotation - address->rotation;
		draw_call->rotation_point = rotation_point;
		draw_call->flip = flip;

		if (flip == SDL_FLIP_HORIZONTAL)
		{
			draw_call->rotation = rotation + address->rotation;
		}

		available_calls_.push_back(draw_call);
		id_count_++;
		return id_count_ - 1;
	}

	void set_alpha(Uint8 alpha, int call_id)
	{
		alpha_ = alpha;
		SDL_SetTextureAlphaMod(available_calls_[call_id]->tex, alpha_);
	}

	void increment_alpha(Uint8 increment, int call_id)
	{
		alpha_ += increment;
		SDL_SetTextureAlphaMod(available_calls_[call_id]->tex, alpha_);
	}

	void set_blend_mode(SDL_BlendMode blending, int call_id)
	{
		SDL_SetTextureBlendMode(available_calls_[call_id]->tex, blending);
	}

	void set_rgb(Uint8 red, Uint8 green, Uint8 blue, int call_id)
	{
		SDL_SetTextureColorMod(available_calls_[call_id]->tex, red, green, blue);
	}

	void draw() override
	{
		for (auto call : calls)
		{
			TextureManager::draw(available_calls_[call]);
		}
	}
};