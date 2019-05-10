
#include "stdafx.h"
#include "Combat.h"
#include "PathHack.h"

Background * bg_logic;


Combat::Combat()
{
	const auto player_1 = Game::assets->create_left_player();
	const auto player_2 = Game::assets->create_right_player();
	const auto background = Game::assets->create_combat_background();


	bg_logic = new Background(player_1, player_2, background);
	/*processor = new CombatProcessor(&player_left, &player_right, &background);

	processor->create_combat();*/
	auto hack = PathHack();
	Game::path->add(hack.initiateCombat(player_1, player_2, background));
}

Combat::~Combat()
{
	Combat::close();
}

void Combat::logic()
{
	Game::path->navigate_path();
	bg_logic->screen_change();

	manager.refresh();
	manager.update();

	/*if (processor->tasks[processor->current_task]->do_work())
		processor->next_process();*/
}

void Combat::render()
{
	auto& background_group = manager.get_group(Game::group_background);
	auto& prompt_group = manager.get_group(Game::group_prompts);
	auto& cursor_group = manager.get_group(Game::group_cursors);

	for (auto& b : background_group)
	{
		b->draw();
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

	Game::audio_queue->stop_music();
}




