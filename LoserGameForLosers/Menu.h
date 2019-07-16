#pragma once
#include "GameState.h"
/**
 * @author David Wadsworth
 * 
 * in charge of the Menu State
 */

class Menu : public GameState
{
	Assets::MenuScreen * screen_;
public:
	Menu(Manager * manager);
	~Menu()
	{}
	void logic() override;
	void handle_events() override;
	void render() override;
	void close() override;
};
