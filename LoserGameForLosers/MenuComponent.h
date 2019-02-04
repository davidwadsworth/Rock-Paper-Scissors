#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Components.h"

class MenuComponent : public Component
{
private:
	TextureComponent * texture_{};
	SDL_Rect dest_rect_;
	int menu_id_, menu_slot_;

public:

	explicit MenuComponent(int sprite_id, SDL_Rect dest = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT })
		: menu_id_(sprite_id), dest_rect_(dest)
	{}

	~MenuComponent()
	{}

	void init() override
	{
		texture_ = &entity->get_component<TextureComponent>();

		auto menu_tex_id = texture_->new_tex(menu_id_, &dest_rect_);
		menu_slot_ = texture_->create_texture_slot(menu_tex_id);
	}
};