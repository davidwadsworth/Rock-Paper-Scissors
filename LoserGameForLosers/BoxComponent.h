#pragma once

#include "ECS.h"
#include "SDL.h"

struct Box
{
	explicit Box(const int slot_id, const int tex_id, const Vector2D position, const Vector2D scale)
		: texture_id(tex_id), slot(slot_id), scale(scale), position(position)
	{}

	int texture_id;
	int slot;
	int call;
	Vector2D scale;
	Vector2D position;
};

class BoxComponent : public Component
{
	TextureComponent * texture_;
	std::vector<Box> box_calls_;
	float scale_;
	int corner_id_, side_id_, center_id_;
public:
	SDL_Rect *box_rect{};

	BoxComponent(const float scale, const int corner_id, const int side_id, const int center_id, SDL_Rect *box_rect = nullptr)
		: scale_(200), corner_id_(corner_id), side_id_(side_id), center_id_(center_id), box_rect(box_rect)
	{}

	~BoxComponent()
	{
		box_calls_.clear();
		texture_ = nullptr;
	}

	void init() override
	{
		texture_ = &entity->get_component<TextureComponent>();

		if(entity->has_component<OptionsComponent>())
		{
			box_rect = &entity->get_component<OptionsComponent>().box;
		}

		build_box();
	}

	void build_box()
	{
		const auto scaled_size = BOX_SIZE * scale_;
		const auto box_w = box_rect->w;
		const auto box_h = box_rect->h;
		const auto left_x = box_rect->x;
		const auto top_y = box_rect->y;
		const auto right_x = box_rect->x + box_w;
		const auto bot_y = box_rect->y + box_h;

		const auto width_scale = box_w / scaled_size;
		const auto height_scale = box_h / scaled_size;


		box_calls_.push_back(Box(texture_->create_texture_slot(), corner_id_, Vector2D(right_x, top_y), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), corner_id_, Vector2D(right_x, top_y), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), corner_id_, Vector2D(right_x, bot_y), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), corner_id_, Vector2D(left_x, bot_y), Vector2D(scale_)));

		box_calls_.push_back(Box(texture_->create_texture_slot(), side_id_, Vector2D(left_x + scaled_size, top_y), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), side_id_, Vector2D(right_x, top_y + scaled_size), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), side_id_, Vector2D(left_x + scaled_size, bot_y), Vector2D(scale_)));
		box_calls_.push_back(Box(texture_->create_texture_slot(), side_id_, Vector2D(left_x, top_y + scaled_size), Vector2D(scale_)));

		box_calls_.push_back(Box(texture_->create_texture_slot(), center_id_, Vector2D(left_x + scaled_size, top_y + scaled_size), Vector2D(scale_)));

		auto rotation = 0;
		for(auto box : box_calls_)
		{
			box.call = texture_->new_texture(box.texture_id, box.slot);
			texture_->update_call(box.slot, &box.position, &box.scale);
			rotation++;
		}
	}
};