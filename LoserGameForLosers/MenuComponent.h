#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Components.h"

class MenuComponent : public Component
{
private:
	TransformComponent * transform_{};
	SDL_Texture * texture_{};
	SDL_Rect dest_rect_{0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SpriteAddress * menu_address_;
	int sprite_id_;

public:

	explicit MenuComponent(int sprite_id)
		: sprite_id_(sprite_id)
	{}

	~MenuComponent()
	{}

	void init() override
	{
		transform_ = &entity->get_component<TransformComponent>();

		texture_ = entity->get_component<TextureComponent>().texture;
		auto atlas = entity->get_component<TextureComponent>().atlas;

		menu_address_ = atlas->addresses[sprite_id_];
	}

	void draw() override
	{
		TextureManager::draw(texture_, menu_address_, &dest_rect_, 0, SDL_FLIP_NONE);
	}
};