#pragma once
#include "ECS.h"

class CursorComponent : public Component
{
	OptionsComponent * options_;
	SDL_Rect *dest_;
	TextureComponent * texture_;
	float angle_;
	int cursor_id_, cursor_slot_;
	SDL_RendererFlip cursor_flip_;
public:

	CursorComponent(int sprite_id)
		: angle_(0), cursor_flip_(SDL_FLIP_NONE), cursor_id_(sprite_id)
	{}

	~CursorComponent()
	{}

	void init() override
	{
		if (entity->has_component<OptionsComponent>())
		{
			options_ = &entity->get_component<OptionsComponent>();
			dest_ = options_->get_current_link()->get_cursor_dimensions();
		}

		texture_ = &entity->get_component<TextureComponent>();

		auto current_cursor_id = texture_->new_tex(cursor_id_, dest_);
		cursor_slot_ = texture_->create_texture_slot(current_cursor_id);
	}

	void update() override
	{
		dest_ = options_->get_current_link()->get_cursor_dimensions();
	}
};
