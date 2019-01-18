#pragma once
#include "Character.h"
#include "SDL.h"

class GameSettings
{
public:
	Character* player1 = new Character();
	Character* player2 = new Character();
	int background = main_background_city;

	GameSettings()
	{}
};