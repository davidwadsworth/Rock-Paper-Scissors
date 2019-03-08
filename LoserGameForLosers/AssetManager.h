#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"
#include "BitMapFont.h"
#include "BitmapTexture.h"

class AssetManager
{
public:
	explicit AssetManager(Manager* man);
	~AssetManager();

	Entity* create_option_box(int options_id, SDL_Point position, bool player_1) const;

	Entity* create_prompt(int sprite_id, SDL_Rect* position) const;

	//Textures
	void add_texture(const char* path);
	SDL_Texture * get_texture(const int id);
	
	//BitMap fonts
	void set_bit_map_font(std::string path);
	BitmapFont* get_bitmap_font();

private:
	Manager * manager_;
	BitmapFont bitmap_font_;
	BitmapTexture bitmap_tex_;
	std::vector<SDL_Texture*> textures_{};
};
