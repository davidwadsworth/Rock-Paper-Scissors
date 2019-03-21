#pragma once
#include "ECS.h"

class MenuComponent : public Component
{
private:
	TextureComponent * texture_{};
	int menu_id_, menu_slot_;

public:

	explicit MenuComponent(const int sprite_id)
		: menu_id_(sprite_id)
	{}

	~MenuComponent()
	{}

	void init() override
	{
		texture_ = &entity->get_component<TextureComponent>();
		menu_slot_ = texture_->create_image_slot(menu_id_, 0, 0);
	}
};