#pragma once
#include <rapidxml.hpp>
#include "constants.h"
#include "character.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Controller.h"

class ControllerData
{
	const char * path_;
public:
	ControllerData(const char * path)
		: path_(path)
	{}
	~ControllerData() {}
	std::vector<Controller *> load();
};