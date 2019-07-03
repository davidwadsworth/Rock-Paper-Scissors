#pragma once

#include "SDL.h"
#include "DrawCall.h"
#include "Texture.h"
#include "BitmapFont.h"

class TextureManager
{
	std::vector<Texture*> textures_;
	std::vector<BitmapFont*> fonts_;
public:
	void load_texture(std::string filename);
	void load_font(std::string filename);
	void free_textures();
	Texture* get_texture(int texture);
	BitmapFont* get_font(int font);
};
