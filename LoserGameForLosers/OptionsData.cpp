#include "stdafx.h"
#include "OptionsData.h"
#include "CommandBuilder.h"
#include "LinkBuilder.h"

std::vector<Options*> OptionsData::load()
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * option_maps_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	option_maps_node = data.first_node("Option_Maps");

	auto c_builder = new CommandBuilder();
	auto l_builder = new LinkBuilder();
	std::vector<Options *> option_map;

	for (rapidxml::xml_node<> * options_node = option_maps_node->first_node("Options"); options_node; options_node = options_node->next_sibling())
	{
		const char * id = options_node->first_attribute("id")->value();
		int padding = atoi(options_node->first_attribute("padding")->value());
		float alignment_x = atof(options_node->first_attribute("alignment_x")->value());
		float alignment_y = atof(options_node->first_attribute("alignment_y")->value());
		float x = atof(options_node->first_attribute("x")->value()) * SCREEN_WIDTH;
		float y = atof(options_node->first_attribute("y")->value()) * SCREEN_HEIGHT;
		const char * font = options_node->first_attribute("font")->value();

		auto options = new Options(id);

		std::vector<Link *> y_position;
		for (rapidxml::xml_node<> * x_position_node = options_node->first_node("X_Position"); x_position_node; x_position_node = x_position_node->next_sibling())
		{
			y_position.clear();
			for (rapidxml::xml_node<> * y_position_node = x_position_node->first_node("Y_Position"); y_position_node; y_position_node = y_position_node->next_sibling())
			{
				for (rapidxml::xml_node<> * option_node = y_position_node->first_node("Option"); option_node; option_node = option_node->next_sibling())
				{
					const char * text = option_node->first_attribute("text")->value();
						
					int command_id = atoi(option_node->first_attribute("command")->value());
					const char * command_value = option_node->first_attribute("command_value")->value();
					
					auto command = c_builder->create_command(command_id, command_value);

					int link_id = atoi(option_node->first_attribute("link")->value());

					auto link = l_builder->create_link(link_id, padding, Vector2D(alignment_x, alignment_y), text, command, font);

					y_position.push_back(link);
				}
			}
			options->choices.push_back(y_position);
		}

		options->choices[0][0]->set_position(Vector2D(x, y));

		for (int x = 0; x < options->choices.size(); x++)
		{
			for (int y = 0; y < options->choices[x].size(); y++)
			{
				auto starting_rect = options->choices[0][0]->get_box_dimensions();

				options->choices[x][y]->set_link_information(starting_rect);
				
				auto current_box = options->choices[x][y]->get_box_dimensions();

				// setting up next x link position if it exists
				if (x + 1 < options->choices.size())
					options->choices[x + 1][y]->set_position( Vector2D(current_box->x + current_box->w, current_box->y) );

				// setting up next y link position if it exists
				if (y + 1 < options->choices[x].size())
					options->choices[x][y + 1]->set_position( Vector2D(current_box->x, current_box->y + current_box->h) );

				// setting up option box 
				if (options->box.x > current_box->x)
					options->box.x = current_box->x;
				if (options->box.y > current_box->y)
					options->box.y = current_box->y;
				if (options->box.x + options->box.w < current_box->x + current_box->w)
					options->box.w += current_box->x + current_box->w - (options->box.x + options->box.w);
				if (options->box.y + options->box.h < current_box->y + current_box->h)
					options->box.h += current_box->y + current_box->h - (options->box.y + options->box.h);

				std::cout << "box " << y << ": ( " << current_box->x << ", " << current_box->y << ", " << current_box->w << ", " << current_box->h << ")" << std::endl;
			}
		}

		std::cout << "box: ( " << options->box.x << ", " << options->box.y << ", " << options->box.w << ", " << options->box.h << ")" << std::endl;
	

		option_map.push_back(options);
	}

	return option_map;
}
