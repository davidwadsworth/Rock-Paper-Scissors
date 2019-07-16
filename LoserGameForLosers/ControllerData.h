#pragma once

/**
 * @author David Wadsworth
 */

struct InputData
{
	int keys = NULL;
	int command_id = NULL;
	std::string command_value;
};

struct ControllerData
{
	std::string id;
	std::vector<InputData> data{};
};

struct ControllerCollection : DataCollection
{
	std::vector<ControllerData> data{};
};