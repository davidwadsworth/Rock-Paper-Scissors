#pragma once
#include "InputCommandBuilder.h"

/**
 * @author David Wadsworth
 * 
 * creates a functional controller from controller data
 */

struct Input
{
	explicit Input(const int keys)
		: i_command(nullptr), keys(keys)
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


