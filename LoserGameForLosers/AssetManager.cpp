#include "stdafx.h"
#include "AssetManager.h"

AssetManager::~AssetManager()
{
}

void AssetManager::create_option_box(Entity * options, int options_id, Vector2D position, const int input_id) const
{
	options->add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	options->add_component<WhiteRectComponent>();
	options->add_component<TextureAtlasComponent>();
	options->add_component<GlyphAtlasComponent>();
	options->add_component<CursorComponent>(ss_main_cursor_box);
	options->add_component<ControllerComponent>(controller_options, input_id);
	options->add_group(Game::group_cursors);
}

void AssetManager::create_menu_option_box(Entity * options, int options_id, Vector2D position, const int input_id) const
{
	options->add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	options->add_component<WhiteRectComponent>();
	options->add_component<TextureAtlasComponent>();
	options->add_component<GlyphAtlasComponent>();
	options->add_component<CursorComponent>(ss_menu_cursor);
	options->add_component<ControllerComponent>(controller_options, input_id);
	options->add_group(Game::group_cursors);
}

void AssetManager::create_prompt(Entity * prompt, int sprite_id, SDL_Rect * position) const
{
	prompt->add_component<TransformComponent>(position->x, position->y, position->h, position->w, 1);
	prompt->add_component<TextureAtlasComponent>();
	prompt->add_component<PromptComponent>(sprite_id);
	prompt->add_group(Game::group_prompts);
}

void AssetManager::create_left_player(Entity * player_left, int controller_id) const 
{
	player_left->add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left->add_component<TextureAtlasComponent>();
	player_left->add_component<SpriteComponent>(ss_main_animations_blue_grab);
	player_left->add_component<ColliderComponent>();
	player_left->add_component<PlayerComponent>(player_blue);
	player_left->add_component<ControllerComponent>(controller_id, 0);
	player_left->add_component<ScriptComponent>();
	player_left->add_group(Game::group_players);
}

void AssetManager::create_right_player(Entity * player_right, int controller_id) const
{
	player_right->add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right->add_component<TextureAtlasComponent>();
	player_right->add_component<SpriteComponent>(ss_main_animations_red_grab, SDL_FLIP_HORIZONTAL);
	player_right->add_component<ColliderComponent>();
	player_right->add_component<PlayerComponent>(player_red);
	player_right->add_component<ControllerComponent>(controller_id, 1);
	player_right->add_component<ScriptComponent>();
	player_right->add_group(Game::group_players);
}

void AssetManager::create_combat_background(Entity * combat_bg) const
{
	combat_bg->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	combat_bg->add_component<TextureAtlasComponent>();
	combat_bg->add_component<BackgroundComponent>(ss_main_background_city);
	combat_bg->add_group(Game::group_background);
}

void AssetManager::create_menu_screen(Entity * menu)
{
	menu->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	menu->add_component<TextureAtlasComponent>();
	menu->add_component<MenuComponent>(ss_menu_title_screen);
	menu->add_group(Game::group_background);
}

void AssetManager::create_background_transition(Entity * transition, int frames) const
{
	transition->add_component<TransformComponent>(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 1);
	transition->add_component<TextureComponent>(texture_white);
	transition->add_component<FadeComponent>(frames);
	transition->add_group(Game::group_wipes);
}

void AssetManager::add_texture(const char * path)
{
}

SDL_Texture * AssetManager::get_texture(const int id)
{
	return nullptr;
}

void AssetManager::set_bit_map_font(const std::string path)
{
	if (bitmap_tex_->load_from_file(path))
	{
		bitmap_font_->build_font(bitmap_tex_);
	}
	else { std::cout << "Font Failure" << std::endl; }
}

BitmapFont* AssetManager::get_bitmap_font()
{
	return bitmap_font_;
}
