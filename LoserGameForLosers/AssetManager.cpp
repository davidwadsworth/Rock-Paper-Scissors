#include "stdafx.h"
#include "AssetManager.h"



AssetManager::AssetManager(Manager* man) : manager_(man)
{}


AssetManager::~AssetManager()
= default;

Entity* AssetManager::create_option_box(int options_id, Vector2D position, const int input_id) const
{
	auto& option_box(manager_->add_entity());
	option_box.add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	option_box.add_component<WhiteRectComponent>();
	option_box.add_component<TextureAtlasComponent>();
	option_box.add_component<GlyphAtlasComponent>();
	option_box.add_component<CursorComponent>(main_cursor_box);
	option_box.add_component<ControllerComponent>(controller_options_nav, input_id);
	option_box.add_group(Game::group_cursors);
	return &option_box;
}

Entity* AssetManager::create_prompt(int sprite_id, SDL_Rect * position) const
{
	auto& prompt(manager_->add_entity());
	prompt.add_component<TransformComponent>(position->x, position->y, position->h, position->w, 1);
	prompt.add_component<TextureAtlasComponent>();
	prompt.add_component<PromptComponent>(sprite_id);
	prompt.add_group(Game::group_prompts);

	return &prompt;
}

Entity * AssetManager::create_attack(Entity * player) const
{
	auto& attack(manager_->add_entity());
	attack.add_component<TransformComponent>();
	attack.add_component<TextureAtlasComponent>();
	attack.add_component<ProjectileComponent>(player);
	return &attack;
}

Entity * AssetManager::create_left_player() const 
{
	auto& player_left(manager_->add_entity());
	player_left.add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left.add_component<TextureAtlasComponent>();
	player_left.add_component<PlayerComponent>(Game::game_settings->player_1_info);
	player_left.add_component<SpriteComponent>(Game::game_settings->player_1_texture);
	player_left.add_component<ControllerComponent>(controller_combat_debug, 0);
	player_left.add_component<ColliderComponent>();
	player_left.add_group(Game::group_players);
	return &player_left;
}

Entity * AssetManager::create_right_player() const
{
	auto& player_right(manager_->add_entity());
	player_right.add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right.add_component<TextureAtlasComponent>();
	player_right.add_component<PlayerComponent>(Game::game_settings->player_2_info);
	player_right.add_component<SpriteComponent>(Game::game_settings->player_2_texture, SDL_FLIP_HORIZONTAL);

	if (Game::game_settings->game_mode)
		player_right.add_component<ControllerComponent>(controller_no_input, 0);

	player_right.add_component<ColliderComponent>();
	player_right.add_group(Game::group_players);
	return &player_right;
}

Entity * AssetManager::create_combat_background() const
{
	auto& background(manager_->add_entity());
	background.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.add_component<TextureAtlasComponent>();
	background.add_component<BackgroundComponent>(Game::game_settings->background);
	background.add_group(Game::group_background);
	return &background;
}

Entity * AssetManager::create_menu_screen() const
{
	auto& screen(manager_->add_entity());

	screen.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	screen.add_component<TextureAtlasComponent>();
	screen.add_component<MenuComponent>(main_menu_title);
	screen.add_group(Game::group_background);
	return &screen;
}

Entity * AssetManager::create_background_transition(int frames) const
{
	auto& transition(manager_->add_entity());
	transition.add_component<TransformComponent>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	transition.add_component<TextureComponent>(texture_white);
	transition.add_component<FadeComponent>(frames);
	transition.add_group(Game::group_wipes);
	return &transition;
}

void AssetManager::add_texture(const char * path)
{
	textures_.push_back(TextureManager::load_texture(path));
}

SDL_Texture * AssetManager::get_texture(const int id)
{
	return textures_[id];
}

void AssetManager::set_bit_map_font(const std::string path)
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
