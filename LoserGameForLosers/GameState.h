#pragma once
#include "Data.h"
#include "Pathway.h"
#include "AssetManager.h"
#include "AudioQueue.h"


class GameState
{
public:
	explicit GameState(Manager * manager) :manager(manager), bank(new LoadedCollections())
	{}

	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void handle_events() = 0;
	virtual void close() = 0;
	virtual ~GameState() {}

	LoadedCollections * bank;
	Manager * manager;
	Path* path = nullptr;
	AudioQueue* audio_player = nullptr;
	AssetManager* palette = nullptr;
};

enum game_states
{
	STATE_NULL,
	STATE_MENU,
	STATE_VIDEO,
	STATE_OVERWORLD,
	STATE_COMBAT,
	STATE_EXIT
};
