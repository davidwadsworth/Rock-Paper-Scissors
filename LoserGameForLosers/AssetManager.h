#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS.h"
#include "SDL_ttf.h"
#include "BitMapFont.h"
#include "SDL_mixer.h"
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

	void create_option_box(Options* choices, int atlas_id, int cursor_id, float text_scaling = 1.0f, bool is_boxed = false, int box_thickness = 1, int box_corner_id = main_textbox_corner, int box_side_id = main_textbox_side, int box_center_id = main_textbox_center);

	void create_prompt(int atlas_id, int sprite_id, SDL_Rect * dest);

	//Textures
	void add_texture(const char* path);
	SDL_Texture * get_texture(const int id);

	//TTF fonts
	void add_font(std::string path, int font_size);
	TTF_Font* get_font(const int id);
	
	//BitMap fonts
	void set_bit_map_font(std::string path);
	BitmapFont* get_bitmap_font();

	//Music
	void add_music(const char* path);
	Mix_Music* get_music(const int id);

	//Sounds
	void add_sound(const char* path);
	Mix_Chunk* get_sound(const int id);

private:
	Manager * manager_;
	BitmapFont bitmap_font_;
	BitmapTexture bitmap_tex_;
	std::vector<SDL_Texture*> textures_{};
	std::vector<TTF_Font*> fonts_{};
	std::vector<Mix_Music*> music_{};
	std::vector<Mix_Chunk*> sounds_{};
	std::vector<Atlas*> atlases_{};
};
