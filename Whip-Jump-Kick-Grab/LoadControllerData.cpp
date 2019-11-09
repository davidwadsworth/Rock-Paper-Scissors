#include "stdafx.h"
#include "LoadControllerData.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>

ControllerCollection LoadControllerData::load()
{
	xml_path.open(path);

	buffer.assign((std::istreambuf_iterator<char>(xml_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	const auto controllers_node = data.first_node("Controllers");

	controller_collection_.id = controllers_node->first_attribute("id")->value();
	controller_collection_.path = controllers_node->first_attribute("path")->value();

	for (auto controller_node = controllers_node->first_node("Controller"); controller_node; controller_node = controller_node->next_sibling())
	{
		auto controller = ControllerData();
		controller.id = controller_node->first_attribute("id")->value();

		for (auto input_node = controller_node->first_node("Input"); input_node; input_node = input_node->next_sibling())
		{
			auto input = InputData();
			input.keys = atoi(input_node->first_attribute("key")->value());
			input.command_id = atoi(input_node->first_attribute("command")->value());
			if (input_node->first_attribute("command_value"))
				input.command_value = input_node->first_attribute("command_value")->value();

			controller.data.push_back(input);
		}

		controller_collection_.data.push_back(controller);
	}
	data.clear();
	return controller_collection_;
}
