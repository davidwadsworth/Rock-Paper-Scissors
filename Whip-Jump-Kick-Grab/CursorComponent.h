#pragma once
#include "ECS.h"
/**
 * @author David Wadsworth
 *
 * In charge of updating and creating option cursor
*/

class CursorComponent : public Component
{
	OptionsComponent * options_;
	SDL_Rect* current_link_;
	TextureAtlasComponent * texture_;
	int cursor_id_, cursor_slot_, cursor_texture_id_;
	Vector2D position_;
public:

	explicit CursorComponent(const int sprite_id)
		: options_(nullptr), current_link_(nullptr), texture_(nullptr), cursor_id_(sprite_id), cursor_slot_(0),
		  cursor_texture_id_(0)
	{}

	~CursorComponent()
	{}

	void init() override
	{
		options_ = &entity->get_component<OptionsComponent>();
		current_link_ = options_->get_current_link()->get_cursor_dimensions();

		texture_ = &entity->get_component<TextureAtlasComponent>();

		cursor_slot_ = texture_->create_image_slot(cursor_id_, current_link_->x, current_link_->y);
	}

	void update() override
	{
		current_link_ = options_->get_current_link()->get_cursor_dimensions();
		texture_->update_position(cursor_slot_, Vector2D(current_link_->x, current_link_->y));
	}
};
