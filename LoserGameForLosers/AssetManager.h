#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"
#include "BitMapFont.h"
#include "Options.h"
#include "Vector2D.h"
#include "ECS.h"
#include "Components.h"
#include "BitmapTexture.h"
#include "Atlas.h"

class AssetManager
{
public:
	explicit AssetManager(Manager* man);
	~AssetManager();

	void create_option_box(Options* choices, int atlas_id, int cursor_id, float text_scaling = 1.0f, bool is_boxed = false, int box_thickness = 1, int box_corner_id = main_textbox_default_corner, int box_side_id = main_textbox_default_side, int box_center_id = main_textbox_default_center);

	void create_prompt(int atlas_id, int sprite_id, SDL_Rect * dest);

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
	std::vector<Atlas*> atlases_{};
};
