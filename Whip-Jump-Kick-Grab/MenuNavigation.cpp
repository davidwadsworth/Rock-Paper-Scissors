#include "stdafx.h"
#include "MenuNavigation.h"

void Navigation::ChangeScreen::init()
{
	screen_->get_component<MenuComponent>().change_screen(screen_id_);
	back_ = new Assets::Back(GameState::get_manager());
	back_->create();
}

void Navigation::ChangeScreen::close()
{
	screen_->get_component<MenuComponent>().change_screen(ss_menu_title_screen);
	back_->destroy();
}

int Navigation::ChangeScreen::choose_path()
{
	return 0;
}
