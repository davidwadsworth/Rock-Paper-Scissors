#pragma once
#include "ECS.h"

class TextureComponent : public Component
{
	Uint8 alpha_, red_, green_, blue_;

public:

	int atlas_id;
	SDL_Texture * texture;

	TextureComponent(int tex)
		: atlas_id(tex)
	{
		set_texture(tex);
	}

	~TextureComponent() {}


	void set_texture(int tex)
	{
		texture = Game::assets->get_texture(tex);
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
