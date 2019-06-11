#pragma once
#include "GameState.h"

class Combat : public GameState
{
public:
	Combat(LoadedCollections * collections);
	~Combat();
	void handle_events() override;
	void logic() override;
	void render() override;
	void close() override;
};
