#pragma once
#include "Character.h"
#include "SDL.h"

class GameSettings
{
public:
	Character* player1 = new Character();
	Character* player2 = new Character();
	const char * background_path = "western industrial.jpg";

	GameSettings()
	{}
};