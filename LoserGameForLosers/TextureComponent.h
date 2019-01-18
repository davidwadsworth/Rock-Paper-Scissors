#pragma once
#include "ECS.h"
#include "Game.h"

class TextureComponent : public Component
{
	Uint8 alpha_, red_, green_, blue_;

public:

	Atlas* atlas;
	SDL_Texture * texture;

	TextureComponent(int sheet_id)
	{
		set_texture(sheet_id);
	}

	~TextureComponent() {}


	void set_texture(int sheet_id)
	{
		texture = Game::assets->get_texture(sheet_id);
		atlas = Game::data->get_atlas(sheet_id);
	}

	void set_alpha(Uint8 alpha)
	{
		alpha_ = alpha;
		SDL_SetTextureAlphaMod(texture, alpha_);
	}

	void increment_alpha(Uint8 increment)
	{
		alpha_ += increment;
		SDL_SetTextureAlphaMod(texture, alpha_);
	}

	void set_blend_mode(SDL_BlendMode blending)
	{
		SDL_SetTextureBlendMode(texture, blending);
	}

	void set_rgb(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod(texture, red, green, blue);
	}


};
