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
	const char * path_;
public:
	CharacterDataReader(const char * path) 
		: path_(path)
	{}
	~CharacterDataReader() {}
	Character * load(int character_id);
};