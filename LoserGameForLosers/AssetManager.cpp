#include "stdafx.h"
#include "AssetManager.h"



AssetManager::AssetManager(Manager* man) : manager_(man)
{}


AssetManager::~AssetManager()
= default;

Entity* AssetManager::create_option_box(int options_id, SDL_Point position, const bool player_1) const
{
	auto& option_box(manager_->add_entity());
	option_box.add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	option_box.add_component<WhiteRectComponent>();
	option_box.add_component<TextureComponent>();
	//option_box.add_component<BoxComponent>(1, main_textbox_default_corner, main_textbox_default_side, main_textbox_default_center);
	option_box.add_component<GlyphAtlasComponent>();
	option_box.add_component<CursorComponent>(main_cursor_box);
	if (player_1)
		option_box.add_component<ControllerComponent>(controller_options_nav);
	else
		option_box.add_component<ControllerComponent>(controller_options_nav, Game::keys);
	option_box.add_group(Game::group_cursors);
	return &option_box;
}

Entity* AssetManager::create_prompt(int sprite_id, SDL_Rect * position) const
{
	auto& prompt(manager_->add_entity());
	prompt.add_component<TransformComponent>(position->x, position->y, position->h, position->w, 1);
	prompt.add_component<TextureComponent>();
	prompt.add_component<PromptComponent>(sprite_id);
	prompt.add_group(Game::group_prompts);

	return &prompt;
}

void AssetManager::add_texture(const char * path)
{
	textures_.push_back(TextureManager::load_texture(path));
}

SDL_Texture * AssetManager::get_texture(const int id)
{
	return textures_[id];
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
