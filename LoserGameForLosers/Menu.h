#pragma once
#include "GameState.h"

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
