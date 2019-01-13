#pragma once
#include "Links.h"

class LinkBuilder
{
public:
	LinkBuilder() {}
	~LinkBuilder() {}

	Link * create_link(int link_id, const int padding, Vector2D alignment, std::string asset, Command* command, std::string font)
	{
		Link * link;

		switch (link_id)
		{
		case 0:
			link = new CursorLeftLink(padding, alignment, asset, command, font );
			break;
		default:
			break;
		}

		return link;
	}

};