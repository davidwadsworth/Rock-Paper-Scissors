#pragma once
#include "GameState.h"

class Combat : public GameState
{
	Background * bg_logic_;
public:
	Combat(Manager* manager);
	~Combat();
	void handle_events() override;
	void logic() override;
	void render() override;
	void close() override;
};
