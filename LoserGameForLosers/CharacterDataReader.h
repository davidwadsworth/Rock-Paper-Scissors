#pragma once
#include <rapidxml.hpp>
#include "constants.h"
#include "character.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class CharacterDataReader
{
public:
	CharacterDataReader();
	~CharacterDataReader() {}

	Character * load(CHARACTER character, const char * path);
};