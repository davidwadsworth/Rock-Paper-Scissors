#pragma once

struct LinkData
{
	std::string text;
	int command_id = -1;
	std::string command_value = "";
	int link_id = 0;
	int path = 1;
};

struct OptionsData
{
	std::vector<std::vector<LinkData>> data;
	std::string id;
};

struct OptionsCollection
{
	std::string id;
	std::vector<OptionsData> data;
};