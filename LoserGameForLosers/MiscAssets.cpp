#include "stdafx.h"
#include "MiscAssets.h"
#include "AIComponent.h"

void Assets::PlayerLeft::create(int controller_id)
{
	auto player_left = create_asset();

	player_left->add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left->add_component<TextureAtlasComponent>();
	player_left->add_component<SpriteComponent>(ss_main_animations_blue_grab);
	player_left->add_component<ColliderComponent>();
	player_left->add_component<PlayerComponent>(order_player_1);
	player_left->add_component<ControllerComponent>(controller_id, 0);
	player_left->add_component<ScriptComponent>();
	player_left->add_group(Game::group_players);
}

void Assets::PlayerLeft::destroy()
{
	get_asset()->del_group(Game::group_players);
	get_asset()->destroy();
}

void Assets::PlayerRight::create(int controller_id, int difficulty)
{
	auto player_right = create_asset();
	player_right->add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right->add_component<TextureAtlasComponent>();
	player_right->add_component<SpriteComponent>(ss_main_animations_red_grab, SDL_FLIP_HORIZONTAL);
	player_right->add_component<ColliderComponent>();
	player_right->add_component<PlayerComponent>(order_player_2);
	
	if (!Game::combat_state)
		player_right->add_component<AIComponent>(difficulty);
	else
		player_right->add_component<ControllerComponent>(controller_id, 1);

	player_right->add_component<ScriptComponent>();
	player_right->add_group(Game::group_players);
}

void Assets::PlayerRight::destroy()
{
	get_asset()->del_group(Game::group_players);
	get_asset()->destroy();
}

void Assets::CombatBackground::create()
{
	auto combat_bg = create_asset();
	combat_bg->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	combat_bg->add_component<TextureAtlasComponent>();
	combat_bg->add_component<BackgroundComponent>(ss_main_background_city);
	combat_bg->add_group(Game::group_background);
}

void Assets::CombatBackground::destroy()
{
	get_asset()->del_group(Game::group_background);
	get_asset()->destroy();
}

void Assets::OptionBox::create(int glyph_id, int cursor_id, int options_id, int controller_id, Vector2D position, int input_id)
{
	auto options = create_asset();
	options->add_component<OptionsComponent>(font_lazy_foo, options_id, static_cast<int>(position.x), static_cast<int>(position.y), Vector2D(0, 0), PADDING);
	options->add_component<WhiteRectComponent>();
	options->add_component<GlyphAtlasComponent>(glyph_id);
	options->add_component<TextureAtlasComponent>();
	options->add_component<CursorComponent>(cursor_id);
	options->add_component<ControllerComponent>(controller_id, input_id);
	options->add_group(Game::group_cursors);
}

void Assets::OptionBox::destroy()
{
	get_asset()->del_group(Game::group_cursors);
	get_asset()->destroy();
}

void Assets::Prompt::create(int sprite_id, SDL_Rect * position)
{
	auto prompt = create_asset();
	prompt->add_component<TransformComponent>(position->x, position->y, position->h, position->w, 1);
	prompt->add_component<TextureAtlasComponent>();
	prompt->add_component<PromptComponent>(sprite_id);
	prompt->add_group(Game::group_prompts);
}

void Assets::Prompt::destroy()
{
	get_asset()->del_group(Game::group_prompts);
	get_asset()->destroy();
}

void Assets::MenuScreen::create()
{
	auto menu = create_asset();
	menu->add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	menu->add_component<TextureAtlasComponent>();
	menu->add_component<MenuComponent>(ss_menu_title_screen);
	menu->add_group(Game::group_background);
}

void Assets::MenuScreen::destroy()
{
	get_asset()->del_group(Game::group_background);
	get_asset()->destroy();
}

void Assets::Transition::create(int frames, int texture_id)
{
	auto transition = create_asset();
	transition->add_component<TransformComponent>(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 1);
	transition->add_component<TextureComponent>(texture_id);
	transition->add_component<FadeComponent>(frames);
	transition->add_group(Game::group_wipes);
}

void Assets::Transition::destroy()
{
	get_asset()->del_group(Game::group_wipes);
	get_asset()->destroy();
}

void Assets::Back::create()
{
	auto back = create_asset();
	back->add_component<ControllerComponent>(controller_back, input_controller_player_1);
}

void Assets::Back::destroy()
{
	get_asset()->destroy();
}

void Assets::Overlay::create(int container_id, int bar_id, SDL_RendererFlip flip)
{
	auto overlay = create_asset();
	overlay->add_component<TextureAtlasComponent>();
	overlay->add_component<OverlayComponent>(container_id, bar_id, flip);
	overlay->add_group(Game::group_overlay);
}

void Assets::Overlay::destroy()
{
	get_asset()->del_group(Game::group_overlay);
	get_asset()->destroy();
}
