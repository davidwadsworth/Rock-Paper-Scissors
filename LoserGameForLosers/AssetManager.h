#pragma once
#include "BitmapFont.h"


class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager();

	void create_option_box(Entity * option_box, int options_id, Vector2D position, int input_id) const;
	void create_menu_option_box(Entity * menu, int options_id, Vector2D position, int input_id) const;
	void create_prompt(Entity * prompt, int sprite_id, SDL_Rect* position) const;
	void create_left_player(Entity * left_player, int controller_id) const;
	void create_right_player(Entity * right_player, int controller_id) const;
	void create_combat_background(Entity * combat_bg) const;
	static void create_menu_screen(Entity * menu);
	void create_background_transition(Entity* transition, int frames) const;

	//Textures
	void add_texture(const char* path);
	SDL_Texture * get_texture(int id);
	
	//BitMap fonts
	void set_bit_map_font(std::string path);
	BitmapFont* get_bitmap_font();

private:
	BitmapFont* bitmap_font_;
	Texture* bitmap_tex_;
};
