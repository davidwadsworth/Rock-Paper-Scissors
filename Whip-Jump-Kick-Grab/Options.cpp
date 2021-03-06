#include "stdafx.h"

std::vector<std::vector<Link*>> Options::build_options(const int start_x, const int start_y, Vector2D alignment, const int padding)
{
	auto link_gen = LinkBuilder();
	std::vector<std::vector<LinkData>> options_data = data_->data;


	SDL_Rect *starting_rect{};

	Link * next_x_link = nullptr, *next_y_link = nullptr;

	std::vector<Link *> y_links;

	//sets the starting position to the first option
	Link* current_link = link_gen.create_link(font_, padding, alignment, &options_data[0][0]);

	current_link->set_position(start_x, start_y);
	current_link->set_link_information();

	// sets up the first rect to be used in alignment calculations
	starting_rect = current_link->get_box_dimensions();

	box.x = start_x;
	box.y = start_y;

	for (unsigned x = 0; x < options_data.size(); x++)
	{
		y_links.clear();
		for (unsigned y = 0; y < options_data[x].size(); y++)
		{
			if (next_y_link)
			{
				current_link = next_y_link;
				next_y_link = nullptr;
				current_link->set_link_information(starting_rect);
			}
			else if (next_x_link)
			{
				current_link = next_x_link;
				next_x_link = nullptr;
				current_link->set_link_information(starting_rect);
			}


			// setting up next y link position if it exists
			if (y + 1 < static_cast<unsigned>(options_data[x].size()))
			{
				next_y_link = link_gen.create_link(font_, padding, alignment, &options_data[x][y + 1]);
				next_y_link->set_position(current_link->get_box_dimensions()->x, current_link->get_box_dimensions()->y + current_link->get_box_dimensions()->h);
			}
			// setting up next x link position if it exists
			else if (x + 1 < static_cast<unsigned>(options_data.size()))
			{
				next_x_link = link_gen.create_link(font_, padding, alignment, &options_data[x + 1][y]);
				next_x_link->set_position(current_link->get_box_dimensions()->x + current_link->get_box_dimensions()->w, current_link->get_box_dimensions()->y);
			}

			// setting up option_rect 
			if (box.x + box.w < current_link->get_box_dimensions()->x + current_link->get_box_dimensions()->w)
				box.w += current_link->get_box_dimensions()->x + current_link->get_box_dimensions()->w - (box.x + box.w);
			if (box.y + box.h < current_link->get_box_dimensions()->y + current_link->get_box_dimensions()->h)
				box.h += current_link->get_box_dimensions()->y + current_link->get_box_dimensions()->h - (box.y + box.h);

			/*std::cout << "cursor dimensions = ( " << current_link->get_cursor_dimensions()->x << ", " << current_link->get_cursor_dimensions()->y << ", " << current_link->get_cursor_dimensions()->w << ", " << current_link->get_cursor_dimensions()->h << " )" << std::endl;
			std::cout << "box dimensions = ( " << current_link->get_box_dimensions()->x << ", " << current_link->get_box_dimensions()->y << ", " << current_link->get_box_dimensions()->w << ", " << current_link->get_box_dimensions()->h << " )" << std::endl;
			std::cout << "link dimensions = ( " << current_link->get_link_dimensions()->x << ", " << current_link->get_link_dimensions()->y << ", " << current_link->get_link_dimensions()->w << ", " << current_link->get_link_dimensions()->h << " )" << std::endl;
			*/
			y_links.push_back(current_link);
		}
		links.push_back(y_links);
	}
	/*std::cout << "option dimensions = ( " << box.x << ", " << box.y << ", " << box.w << ", " << box.h << " )" << std::endl;*/
	return links;
}
