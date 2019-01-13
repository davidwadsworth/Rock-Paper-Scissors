#include "stdafx.h"
#include "ControllerData.h"
#include "CommandBuilder.h"

std::vector<Controller*> ControllerData::load()
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * controllers_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	controllers_node = data.first_node("Controllers");

	auto c_builder = new CommandBuilder();
	std::vector<Controller *> controllers;

	for (rapidxml::xml_node<> * controller_node = controllers_node->first_node("Controller"); controller_node; controller_node = controller_node->next_sibling())
	{
		const char * id = controller_node->first_attribute("id")->value();
		auto controller = new Controller(id);

		for (rapidxml::xml_node<> * input_node = controller_node->first_node("Input"); input_node; input_node = input_node->next_sibling())
		{
			int key = atoi(input_node->first_attribute("key")->value());
			auto input = new Input(key);

			int command = atoi(input_node->first_attribute("command")->value());
			const char * command_value = input_node->first_attribute("command_value")->value();

			input->command = c_builder->create_command(command, command_value);
			
			controller->current_controller.push_back(input);
		}

		controllers.push_back(controller);
	}
	return controllers;
}
