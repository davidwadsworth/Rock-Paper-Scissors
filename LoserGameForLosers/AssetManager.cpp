#include "stdafx.h"
#include "AssetManager.h"



AssetManager::AssetManager(Manager* man, GameState * state) : manager_(man), state_(state)
{}


AssetManager::~AssetManager()
= default;

Entity* AssetManager::create_option_box(int options_id, Vector2D position, const int input_id) const
{
	auto& option_box(manager_->add_entity(state_));
	option_box.add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	option_box.add_component<WhiteRectComponent>();
	option_box.add_component<TextureAtlasComponent>();
	option_box.add_component<GlyphAtlasComponent>();
	option_box.add_component<CursorComponent>(ss_main_cursor_box);
	option_box.add_component<ControllerComponent>(controller_options_nav, input_id);
	option_box.add_group(Game::group_cursors);
	return &option_box;
}

Entity* AssetManager::create_menu_option_box(int options_id, Vector2D position, const int input_id) const
{
	auto& option_box(manager_->add_entity(state_));
	option_box.add_component<OptionsComponent>(options_id, position.x, position.y, Vector2D(0, 0), PADDING);
	option_box.add_component<WhiteRectComponent>();
	option_box.add_component<TextureAtlasComponent>();
	option_box.add_component<GlyphAtlasComponent>();
	option_box.add_component<CursorComponent>(ss_menu_cursor);
	option_box.add_component<ControllerComponent>(controller_options_nav, input_id);
	option_box.add_group(Game::group_cursors);
	return &option_box;
}

Entity* AssetManager::create_prompt(int sprite_id, SDL_Rect * position) const
{
	auto& prompt(manager_->add_entity(state_));
	prompt.add_component<TransformComponent>(position->x, position->y, position->h, position->w, 1);
	prompt.add_component<TextureAtlasComponent>();
	prompt.add_component<PromptComponent>(sprite_id);
	prompt.add_group(Game::group_prompts);

	return &prompt;
}

Entity * AssetManager::create_attack(Entity * player) const
{
	auto& attack(manager_->add_entity(state_));
	attack.add_component<TransformComponent>(1);
	attack.add_component<TextureAtlasComponent>();
	attack.add_component<ProjectileComponent>(player);
	return &attack;
}

Entity * AssetManager::create_left_player() const 
{
	auto& player_left(manager_->add_entity(state_));
	player_left.add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left.add_component<TextureAtlasComponent>();
	player_left.add_component<PlayerComponent>(player_blue);
	player_left.add_component<SpriteComponent>(ss_main_animations_blue_grab);
	player_left.add_component<ControllerComponent>(controller_combat_debug, 0);
	player_left.add_component<ColliderComponent>();
	player_left.add_group(Game::group_players);
	return &player_left;
}

Entity * AssetManager::create_right_player() const
{
	auto& player_right(manager_->add_entity(state_));
	player_right.add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right.add_component<TextureAtlasComponent>();
	player_right.add_component<PlayerComponent>(player_red);
	player_right.add_component<SpriteComponent>(ss_main_animations_red_grab, SDL_FLIP_HORIZONTAL);
	player_right.add_component<ControllerComponent>(controller_combat_debug, 1);
	player_right.add_component<ColliderComponent>();
	player_right.add_group(Game::group_players);
	return &player_right;
}

Entity * AssetManager::create_combat_background() const
{
	auto& background(manager_->add_entity(state_));
	background.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.add_component<TextureAtlasComponent>();
	background.add_component<BackgroundComponent>(ss_main_background_city);
	background.add_group(Game::group_background);
	return &background;
}

Entity * AssetManager::create_menu_screen() const
{
	auto& screen(manager_->add_entity(state_));

	screen.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	screen.add_component<TextureAtlasComponent>();
	screen.add_component<MenuComponent>(ss_menu_title_screen);
	screen.add_group(Game::group_background);
	return &screen;
}

Entity * AssetManager::create_background_transition(int frames) const
{
	auto& transition(manager_->add_entity(state_));
	transition.add_component<TransformComponent>(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 1);
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
