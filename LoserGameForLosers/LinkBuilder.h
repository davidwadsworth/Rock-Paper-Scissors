#pragma once
#include "Links.h"
#include "Data.h"
#include "LinkCommandBuilder.h"

/**
 * @author David Wadsworth
 *
 * converting xml to the correct link design 
*/

class LinkBuilder
{
public:
	LinkBuilder() {}
	~LinkBuilder() {}

	static Link * create_link(BitmapFont * font, const int padding, const Vector2D alignment, LinkData * data)
	{
		auto command_gen = LinkCommandBuilder();
		const auto command = command_gen.create_command(data->command_id, data->command_value);
		Link * link;

		switch (data->link_id)
		{
		case 0:
			link = new CursorLeftLink(font, padding, alignment, data->text, command);
			break;
		default:
			link = new CursorLeftLink(font, padding, alignment, data->text, command);
			break;
		}

		return link;
	}

};
