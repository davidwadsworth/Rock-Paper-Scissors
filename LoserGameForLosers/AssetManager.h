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
	explicit AssetManager(Manager* man, GameState * state);
	~AssetManager();

	Entity* create_option_box(int options_id, Vector2D position, int input_id) const;
	Entity* create_menu_option_box(int options_id, Vector2D position, int input_id) const;
	Entity* create_prompt(int sprite_id, SDL_Rect* position) const;
	Entity* create_attack(Entity * player) const;
	Entity* create_left_player() const;
	Entity* create_right_player() const;
	Entity* create_combat_background() const;
	Entity* create_menu_screen() const;
	Entity* create_background_transition(int frames) const;

	//Textures
	void add_texture(const char* path);
	SDL_Texture * get_texture(const int id);
	
	//BitMap fonts
	void set_bit_map_font(std::string path);
	BitmapFont* get_bitmap_font();

private:
	Manager * manager_;
	GameState* state_;
	BitmapFont bitmap_font_;
	BitmapTexture bitmap_tex_;
	std::vector<SDL_Texture*> textures_{};
};
