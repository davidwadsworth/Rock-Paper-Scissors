#pragma once
#include <utility>
#include "ECS.h"
#include "ControllerCommands.h"

struct Input
{
	Input(const int keys)
		: keys(keys)
	{}
	Command * command;
	int keys;
};


class Controller
{
public:

	std::vector<Input *> current_controller;
	std::string controller_id;

	Controller(std::string controller)
		: controller_id(controller)
	{}
};


