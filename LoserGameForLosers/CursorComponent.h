#pragma once
#include "ECS.h"

class CursorComponent : public Component
{
	OptionsComponent * options_;
	SDL_Rect* current_link_;
	TextureComponent * texture_;
	int cursor_id_, cursor_slot_, cursor_texture_id_;
	Vector2D position_;
public:

	explicit CursorComponent(const int sprite_id)
		: cursor_id_(sprite_id)
	{}

	~CursorComponent()
	{}

	void init() override
	{
		options_ = &entity->get_component<OptionsComponent>();
		current_link_ = options_->get_current_link()->get_cursor_dimensions();

		texture_ = &entity->get_component<TextureComponent>();

		cursor_slot_ = texture_->create_image_slot(cursor_id_, current_link_->x, current_link_->y);
	}

	void update() override
	{
		current_link_ = options_->get_current_link()->get_cursor_dimensions();
		texture_->update_call(cursor_slot_, new Vector2D(current_link_->x, current_link_->y));
	}
};
