
#include "stdafx.h"
#include "Combat.h"
#include "PathHack.h"

Background * bg_logic;



Combat::Combat(LoadedCollections * collections) : GameState(collections)
{
	palette = new AssetManager(&manager, this);
	palette->add_texture(collections->atlas_data.path.c_str());
	palette->add_texture("white_background.png");
	palette->set_bit_map_font("lazyfont.png");
	audio_player = new AudioQueue(&bank->audio_data);

	const auto player_left = palette->create_left_player();
	const auto player_right = palette->create_right_player();
	const auto background = palette->create_combat_background();

	path = new Path();/*
	auto hack = PathHack(this);
	path->add(hack.initiateCombat(player_left, player_right, background));*/

	bg_logic = new Background(player_left, player_right, background);
}

Combat::~Combat()
{
	Combat::close();
}

void Combat::logic()
{
	path->navigate_path();
	bg_logic->screen_change();

	manager.refresh();
	manager.update();
}

void Combat::render()
{
	auto& background_group = manager.get_group(Game::group_background);
	auto& prompt_group = manager.get_group(Game::group_prompts);
	auto& cursor_group = manager.get_group(Game::group_cursors);
	auto& player_group = manager.get_group(Game::group_players);

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

void Combat::close()
{
	for (auto& b : manager.get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& p : manager.get_group(Game::group_players))
	{
		p->del_group(Game::group_players);
		p->destroy();
	}

	for (auto& pr : manager.get_group(Game::group_prompts))
	{
		pr->del_group(Game::group_prompts);
		pr->destroy();
	}

	audio_player->stop_music();
}




