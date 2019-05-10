#pragma once
#include "Links.h"
#include "Data.h"
#include "LinkCommandBuilder.h"

class LinkBuilder
{
public:
	LinkBuilder() {}
	~LinkBuilder() {}

	Link * create_link(const int padding, const Vector2D alignment, LinkData * data )
	{
		auto command_gen = LinkCommandBuilder();
		const auto command = command_gen.create_command(data->command_id, data->command_value);
		Link * link;

		switch (data->link_id)
		{
		default:
			link = new CursorLeftLink(padding, alignment, data->text, command);
			break;
		}

		return link;
	}

};
