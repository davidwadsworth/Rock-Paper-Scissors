#pragma once
#include <rapidxml.hpp>
#include "constants.h"
#include "character.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Options.h"

class OptionsData
{
	const char * path_;
public:
	OptionsData(const char * path)
		: path_(path)
	{}
	~OptionsData() {}
	std::vector<Options *> load();
};