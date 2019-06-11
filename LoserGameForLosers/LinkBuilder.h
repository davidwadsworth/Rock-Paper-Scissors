#pragma once
#include "Links.h"
#include "Data.h"
#include "LinkCommandBuilder.h"

class LinkBuilder
{
public:
	LinkBuilder() {}
	~LinkBuilder() {}

	static Link * create_link(AssetManager * asset_manager, const int padding, const Vector2D alignment, LinkData * data)
	{
		auto command_gen = LinkCommandBuilder();
		const auto command = command_gen.create_command(data->command_id, data->command_value);
		Link * link;

		switch (data->link_id)
		{
		default:
			link = new CursorLeftLink(asset_manager, padding, alignment, data->text, command);
			break;
		}

		return link;
	}

};
