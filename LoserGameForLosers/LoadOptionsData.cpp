#include "stdafx.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>
#include "LoadOptionsData.h"

OptionsCollection LoadOptionsData::load() const
{	
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	const auto option_maps_node = data.first_node("Option_Maps");

	auto options_collection = OptionsCollection();

	options_collection.id = option_maps_node->first_attribute("id")->value();

	for (auto options_node = option_maps_node->first_node("Options"); options_node; options_node = options_node->next_sibling())
	{
		auto options_data = OptionsData();

		options_data.id = options_node->first_attribute("id")->value();

		std::vector<LinkData> y_data;
		for (auto x_position_node = options_node->first_node("X_Position"); x_position_node; x_position_node = x_position_node->next_sibling())
		{
			y_data.clear();
			for (auto y_position_node = x_position_node->first_node("Y_Position"); y_position_node; y_position_node = y_position_node->next_sibling())
			{
				for (auto option_node = y_position_node->first_node("Option"); option_node; option_node = option_node->next_sibling())
				{
					auto link_data = LinkData();
					link_data.text = option_node->first_attribute("text")->value();
					link_data.command_id = std::atoi(option_node->first_attribute("command")->value());
					link_data.command_value = option_node->first_attribute("command_value")->value();
					link_data.link_id = std::atoi(option_node->first_attribute("link")->value());

					y_data.push_back(link_data);
				}
			}
			options_data.data.push_back(y_data);
		}
		options_collection.data.push_back(options_data);
	}

	return options_collection;
}
