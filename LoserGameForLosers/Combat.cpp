
#include "stdafx.h"
#include "Combat.h"

Background * bg_logic;
CombatProcessor *processor = nullptr;


Combat::Combat(Manager * manager)
	: manager_(manager)
{
	Game::stack->clear();

	auto& background(manager_->add_entity());
	auto& player_left(manager_->add_entity());
	auto& player_right(manager_->add_entity());

	background.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING);
	background.add_component<TextureComponent>();
	background.add_component<BackgroundComponent>(Game::game_settings->background);
	background.add_group(Game::group_background);

	player_left.add_component<TransformComponent>(SPRITE_LEFT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_left.add_component<TextureComponent>();
	player_left.add_component<PlayerComponent>(true, Game::game_settings->player_1_info);
	player_left.add_component<SpriteComponent>(Game::game_settings->player_1_texture);
	player_left.add_component<ControllerComponent>(controller_no_input);
	player_left.add_component<ColliderComponent>();
	player_left.add_group(Game::group_players);

	player_right.add_component<TransformComponent>(SPRITE_RIGHT_EDGE_OF_SCREEN, SPRITE_BOTTOM_OF_SCREEN, SPRITE_SCALING);
	player_right.add_component<TextureComponent>();
	player_right.add_component<PlayerComponent>(false, Game::game_settings->player_2_info);
	player_right.add_component<SpriteComponent>(Game::game_settings->player_2_texture, SDL_FLIP_HORIZONTAL);
	player_right.add_component<ControllerComponent>(controller_no_input, Game::keys);
	player_right.add_component<ColliderComponent>();
	player_right.add_group(Game::group_players);

	bg_logic = new Background(&player_left, &player_right, &background);
	processor = new CombatProcessor(&player_left, &player_right, &background);

	processor->create_combat();
}

Combat::~Combat()
{
	Combat::close();
}


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

	if (processor->tasks[processor->current_task]->do_work())
		processor->next_process();
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

	Game::player->stop_music();
}




