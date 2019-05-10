#include "stdafx.h"
#include "Menu.h"
#include "PathHack.h"



Menu::Menu()
{
	auto hack = PathHack();
	Game::path->add(hack.initiate_menu());
}


void Menu::render()
{
	auto& background_group = manager.get_group(Game::group_background);
	auto& cursor_group = manager.get_group(Game::group_cursors);

	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& c : cursor_group)
	{
		c->draw();
	}
}

void Menu::logic()
{
	Game::path->navigate_path();

	manager.refresh();
	manager.update();
}

void Menu::handle_events()
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

void Menu::close()
{
	for (auto& b : manager.get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}
	for (auto& c : manager.get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}

	Game::audio_queue->stop_music();
}
