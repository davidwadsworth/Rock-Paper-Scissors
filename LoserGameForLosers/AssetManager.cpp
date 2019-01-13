#include "stdafx.h"
#include "AssetManager.h"



AssetManager::AssetManager(Manager* man) : manager_(man)
{}


AssetManager::~AssetManager()
= default;

void AssetManager::create_option_box(Options* choices, int atlas_id, int cursor_id, float text_scaling = 1.0f, bool is_boxed = false, int box_thickness = 1, int box_id = main_textbox_center)
{
	auto& option_box(manager_->add_entity());
	option_box.add_component<OptionsComponent>(choices);
	option_box.add_component<TextureComponent>(atlas_id);
	
	if (is_boxed)
		option_box.add_component<BoxComponent>(box_thickness, box_id);
	
	option_box.add_component<GlyphAtlasComponent>(text_scaling);
	option_box.add_component<CursorComponent>(cursor_id);
	option_box.add_component<ControllerComponent>("options");
	option_box.add_group(Game::group_cursors);
}

void AssetManager::create_prompt(SDL_Rect * dest, int sc, const char * texture)
{
	auto& prompt(manager_->add_entity());
	prompt.add_component<TransformComponent>(dest->x, dest->y, dest->h, dest->w, sc);
	prompt.add_component<TextureComponent>(texture);
	prompt.add_component<PromptComponent>(dest->x, dest->y, dest->w, dest->h);
	prompt.add_group(Game::group_prompts);
}

void AssetManager::create_prompt(SDL_Rect* dest, SDL_Rect* src, int sc, const char * texture)
{
	auto& prompt(manager.add_entity());
	prompt.add_component<TransformComponent>(dest->x, dest->y, dest->h, dest->w, sc);
	prompt.add_component<TextureComponent>(texture);
	prompt.add_component<PromptComponent>(src->x, src->y, src->w, src->h);
	prompt.add_group(Game::group_prompts);
}

void AssetManager::add_texture( const char * path)
{
	textures_.push_back(TextureManager::load_texture(path));
}

SDL_Texture * AssetManager::get_texture(const int id)
{
	return textures_[id];
}

void AssetManager::add_font(std::string path, int fontSize)
{
	fonts_.push_back(TTF_OpenFont(path.c_str(), fontSize));
}

void AssetManager::add_music(const char * path)
{
	music_.push_back(Mix_LoadMUS(path));
}

void AssetManager::add_sound(const char * path)
{
	sounds_.push_back(Mix_LoadWAV(path));
}

TTF_Font * AssetManager::get_font(const int id)
{
	return fonts_[id];
}

void AssetManager::set_bit_map_font(std::string path)
{
	if (bitmap_tex_.load_from_file(path))
	{
		bitmap_font_.build_font(&bitmap_tex_);
	}
	else { std::cout << "Font Failure" << std::endl; }
}

BitmapFont* AssetManager::get_bitmap_font()
{
	return &bitmap_font_;
}

Mix_Music * AssetManager::get_music(const int id)
{
	return music_[id];
}

Mix_Chunk * AssetManager::get_sound(const int id)
{
	return sounds_[id];
}
