#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"
#include "DrawCall.h"

class BoxComponent : public Component
{
	SDL_Texture * texture_; 
	std::vector<DrawCall*> draw_calls_;
	int scale_;
	int corner_id_, side_id_, center_id_;
	SpriteAddress * corner_address_, *side_address_, *center_address_;
public:
	SDL_Rect box_rect{};

	BoxComponent()
		= default;

	BoxComponent(const int scale, int corner_id, int side_id, int center_id)
		: scale_(scale), corner_id_(corner_id), side_id_(side_id), center_id_(center_id)
	{}

	BoxComponent(SDL_Rect box_rect, const int scale, int corner_id, int side_id, int center_id)
		: box_rect(box_rect), scale_(scale), corner_id_(corner_id), side_id_(side_id), center_id_(center_id)
	{}

	~BoxComponent()
	{}

	void init() override
	{
		if(entity->has_component<OptionsComponent>())
		{
			build_box(entity->get_component<OptionsComponent>().current_options->box);
		}
		else { build_box(box_rect); }

		texture_ = entity->get_component<TextureComponent>().texture;

		auto atlas = entity->get_component<TextureComponent>().atlas;

		corner_address_ = atlas->addresses[corner_id_];
		side_address_ = atlas->addresses[side_id_];
		center_address_ = atlas->addresses[center_id_];
	}

	void build_box(const SDL_Rect box)
	{
		const auto scaled_size = BOX_SIZE * scale_;
		const auto box_w = box.w;
		const auto box_h = box.h;
		const auto left_x = box.x;
		const auto top_y = box.y;
		const auto right_x = box.x + box_w;
		const auto bot_y = box.y + box_h;

		//Top Left Corner
		draw_calls_.push_back(new DrawCall(corner_address_, new SDL_Rect{ left_x, top_y, scaled_size, scaled_size }, 0, SDL_FLIP_NONE) );

		//Top Right Corner
		draw_calls_.push_back(new DrawCall(corner_address_, new SDL_Rect{ right_x, top_y, scaled_size, scaled_size }, 90, SDL_FLIP_NONE));

		//Bot Right Corner
		draw_calls_.push_back(new DrawCall(corner_address_, new SDL_Rect{ right_x, bot_y, scaled_size, scaled_size }, 180, SDL_FLIP_NONE));

		//Bot Left Corner
		draw_calls_.push_back(new DrawCall(corner_address_, new SDL_Rect{ left_x, bot_y, scaled_size, scaled_size }, 270, SDL_FLIP_NONE));

		//Top Side
		draw_calls_.push_back(new DrawCall(side_address_, new SDL_Rect{ left_x + scaled_size, top_y, box_w - scaled_size, scaled_size }, 0, SDL_FLIP_NONE));

		//Right Side
		draw_calls_.push_back(new DrawCall(side_address_, new SDL_Rect{ right_x, top_y + scaled_size, scaled_size, box_h - scaled_size }, 90, SDL_FLIP_NONE));

		//Bot Side
		draw_calls_.push_back(new DrawCall(side_address_, new SDL_Rect{ left_x + scaled_size, bot_y, box_w - scaled_size, scaled_size }, 180, SDL_FLIP_NONE));

		//Left Side
		draw_calls_.push_back(new DrawCall(side_address_, new SDL_Rect{ left_x, top_y + scaled_size, scaled_size, box_h - scaled_size }, 270, SDL_FLIP_NONE));

		//Body
		draw_calls_.push_back(new DrawCall(center_address_, new SDL_Rect{ left_x + scaled_size, top_y + scaled_size,box_w - scaled_size, box_h - scaled_size }, 0, SDL_FLIP_NONE));
	}


	void draw() override
	{
		for (auto d : draw_calls_)
		{
			TextureManager::draw(texture_, d->sprite_address, d->dest, d->rotation, d->flip);
		}
	}

};