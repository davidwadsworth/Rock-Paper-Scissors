#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"
#include "DrawCall.h"

class BoxComponent : public Component
{
	TextureComponent * texture_;
	int box_slots[9];
	int scale_;
	int corner_id_, side_id_, center_id_;
public:
	SDL_Rect box_rect{};

	BoxComponent(const int scale, int corner_id, int side_id, int center_id, SDL_Rect box_rect = {})
		: scale_(scale), corner_id_(corner_id), side_id_(side_id), center_id_(center_id), box_rect(box_rect)
	{}

	~BoxComponent()
	{}

	void init() override
	{
		texture_ = &entity->get_component<TextureComponent>();

		if(entity->has_component<OptionsComponent>())
		{
			box_rect = entity->get_component<OptionsComponent>().current_options->box;
		}

		build_box();
	}

	void build_box()
	{
		const auto scaled_size = BOX_SIZE * scale_;
		const auto box_w = box_rect.w;
		const auto box_h = box_rect.h;
		const auto left_x = box_rect.x;
		const auto top_y = box_rect.y;
		const auto right_x = box_rect.x + box_w;
		const auto bot_y = box_rect.y + box_h;

		//Top Left Corner
		auto top_left_corner_id = texture_->new_tex(corner_id_, new SDL_Rect{ left_x, top_y, scaled_size, scaled_size }, 0);

		//Top Right Corner
		auto top_right_corner_id = texture_->new_tex(corner_id_, new SDL_Rect{ right_x, top_y, scaled_size, scaled_size }, 90);

		//Bot Right Corner
		auto bot_right_corner_id = texture_->new_tex(corner_id_, new SDL_Rect{ right_x, bot_y, scaled_size, scaled_size }, 180);

		//Bot Left Corner
		auto bot_left_corner_id = texture_->new_tex(corner_id_, new SDL_Rect{ left_x, bot_y, scaled_size, scaled_size }, 270);

		//Top Side
		auto top_side_id = texture_->new_tex(side_id_, new SDL_Rect{ left_x + scaled_size, top_y, box_w - scaled_size, scaled_size }, 0 );

		//Right Side
		auto right_side_id = texture_->new_tex(side_id_, new SDL_Rect{ right_x, top_y + scaled_size, scaled_size, box_h - scaled_size }, 90 );

		//Bot Side
		auto bot_side_id = texture_->new_tex(side_id_, new SDL_Rect{ left_x + scaled_size, bot_y, box_w - scaled_size, scaled_size }, 180 );

		//Left Side
		auto left_side_id = texture_->new_tex(side_id_, new SDL_Rect{ left_x, top_y + scaled_size, scaled_size, box_h - scaled_size }, 270 );

		//Body
		auto body_id = texture_->new_tex(center_id_, new SDL_Rect{ left_x + scaled_size, top_y + scaled_size,box_w - scaled_size, box_h - scaled_size }, 0);

		texture_->create_texture_slot(top_left_corner_id);
		texture_->create_texture_slot(top_right_corner_id);
		texture_->create_texture_slot(bot_right_corner_id);
		texture_->create_texture_slot(bot_left_corner_id);
		texture_->create_texture_slot(top_side_id);
		texture_->create_texture_slot(right_side_id);
		texture_->create_texture_slot(bot_side_id);
		texture_->create_texture_slot(left_side_id);
		texture_->create_texture_slot(body_id);
	}
};