#pragma once
#include "GameState.h"
#include "MiscAssets.h"
class Combat : public GameState
{
	Assets::PlayerLeft* player_1_;
	Assets::PlayerRight* player_2_;
	Assets::CombatBackground* background_;
	Assets::Overlay* left_overlay_, *right_overlay_;
public:
	Combat(Manager* manager);
	~Combat();
	void handle_events() override;
	void logic() override;
	void render() override;
	void close() override;
};
