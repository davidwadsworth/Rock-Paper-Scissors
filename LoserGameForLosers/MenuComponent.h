#pragma once
#include "ECS.h"

/**
 * @author David Wadsworth
 *
 * in charge of creating and updating menu screen
*/

class MenuComponent : public Component
{
private:
	TextureAtlasComponent * texture_{};
	int menu_id_, menu_slot_;

public:

	explicit MenuComponent(const int sprite_id)
		: menu_id_(sprite_id), menu_slot_(0)
	{}

	~MenuComponent()
	{}

	void init() override
	{
		texture_ = &entity->get_component<TextureAtlasComponent>();
		menu_slot_ = texture_->create_image_slot(menu_id_, 0, 0);
	}

	void change_screen(const int screen) const
	{
		texture_->update_image_slot(menu_slot_, screen);
	}
};