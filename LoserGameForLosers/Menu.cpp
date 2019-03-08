#include "stdafx.h"
#include "Menu.h"

Menu::Menu(Manager * manager)
	: manager_(manager)
{
	Game::stack->clear();

	auto& screen(manager_->add_entity());

	screen.add_component<TransformComponent>(BACKGROUND_X_OFFSET, BACKGROUND_Y_OFFSET, BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_SCALING_TARGET);
	screen.add_component<TextureComponent>();
	screen.add_component<MenuComponent>(main_menu_title);
	screen.add_group(Game::group_background);

	Game::assets->create_option_box(options_start_menu, SDL_Point{ SPRITE_LENGTH, SCREEN_HALF_HEIGHT}, true);

}


void Menu::render()
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

void Menu::logic()
{
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
	for (auto& b : manager_->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& c : manager_->get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}
}
