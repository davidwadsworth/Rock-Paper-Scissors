#pragma once
#include "ECS.h"
#include "CommonInputCommands.h"
#include "InputCommandBuilder.h"

struct Input
{
	Input(const int keys)
		: keys(keys)
	{}
	InputCommand * i_command;
	int keys;
};


class Controller
{
public:
	Controller() = default;

	explicit Controller(ControllerData* data)
		: controller_id(data->id)
	{
		auto build = InputCommandBuilder();

		for(auto in : data->data)
		{
			Input input(in.keys);
			input.i_command = build.create_command(in.command_id, in.command_value);
			this->inputs.push_back(input);
		}
	}
	std::vector<Input> inputs;
	std::string controller_id;
};


