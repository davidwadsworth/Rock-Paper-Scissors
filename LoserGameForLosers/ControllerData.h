#pragma once

struct InputData
{
	int keys;
	int command_id;
	std::string command_value;
};

struct ControllerData
{
	std::string id;
	std::vector<InputData> data;
};

struct ControllerCollection : DataCollection
{
	std::vector<ControllerData> data;
};