
#include "stdafx.h"
#include "Combat.h"

Background * bg_logic;

// probably should be somewhere else idk
std::vector<SDL_Scancode> keys = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_I, SDL_SCANCODE_O, SDL_SCANCODE_P, SDL_SCANCODE_L };

Combat::Combat(Manager * manager)
	: manager_(manager)
{
	auto& background(manager_->add_entity());
	auto& player_left(manager_->add_entity());
	auto& player_right(manager_->add_entity());

	background.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.add_component<TextureComponent>(atlas_texture_sheet_main);
	background.add_component<BackgroundComponent>(Game::game_settings->background);
	background.add_group(Game::group_background);

	//Replace this with a loaded in solution
	std::vector<Animation *> player_1_anim = { new Animation(main_player_arms_idle_1, 3, 200), new Animation(main_player_arms_walk_left_1, 3, 200), new Animation(main_player_arms_walk_right_1, 3, 200) };
	std::vector<Animation *> player_2_anim = { new Animation(main_player_fighter_idle_1, 3, 200), new Animation(main_player_fighter_walk_left_1, 3, 200), new Animation(main_player_fighter_walk_right_1, 3, 200) };

	player_left.add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left.add_component<TextureComponent>(atlas_texture_sheet_main);
	player_left.add_component<PlayerComponent>(true, Game::game_settings->player1);
	player_left.add_component<SpriteComponent>(player_1_anim);
	player_left.add_component<ControllerComponent>(controller_combat_debug);
	player_left.add_component<ColliderComponent>();
	player_left.add_group(Game::group_players);

	player_right.add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right.add_component<TextureComponent>(atlas_texture_sheet_main);
	player_right.add_component<PlayerComponent>(false, Game::game_settings->player2);
	player_right.add_component<SpriteComponent>(player_2_anim, SDL_FLIP_HORIZONTAL);
	player_right.add_component<ControllerComponent>(controller_combat_debug, keys);
	player_right.add_component<ColliderComponent>();
	player_right.add_group(Game::group_players);

	bg_logic = new Background(&player_left, &player_right, &background, Game::game_settings->max_range);

}

Combat::~Combat()
{}


void Combat::handle_events()
{
	SDL_PollEvent(&Game::event);

	switch (Game::event.type)
	{
	case SDL_QUIT:
		Game::is_running = false;
		break;
	default:
		break;
	}
}

void Combat::logic()
{
	bg_logic->screen_change();

	manager.refresh();
	manager.update();
}



void Combat::render()
{
	auto& player_group = manager.get_group(Game::group_players);
	auto& background_group = manager.get_group(Game::group_background);
	auto& prompt_group = manager.get_group(Game::group_prompts);
	auto& cursor_group = manager.get_group(Game::group_cursors);

	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& p : player_group)
	{
		p->draw();
	}
	for (auto& pr : prompt_group)
	{
		pr->draw();
	}
	for (auto& c : cursor_group)
	{
		c->draw();
	}
}

void Combat::close()
{
	for (auto& b : manager_->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& p : manager_->get_group(Game::group_players))
	{
		p->del_group(Game::group_players);
		p->destroy();
	}

	for (auto& pr : manager_->get_group(Game::group_prompts))
	{
		pr->del_group(Game::group_prompts);
		pr->destroy();
	}
}




