#include "stdafx.h"
#include "AtlasData.h"

Atlas * AtlasData::load()
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * texture_atlas_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	texture_atlas_node = data.first_node("TextureAtlas");

	const char * path(texture_atlas_node->first_attribute("imagePath")->value());
	int width(atoi(texture_atlas_node->first_attribute("width")->value()));
	int height(atoi(texture_atlas_node->first_attribute("height")->value()));

	Atlas * atlas_builder = new Atlas(path, width, height);

	for (rapidxml::xml_node<> * sprite_node = texture_atlas_node->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
	{
		const char * n(sprite_node->first_attribute("n")->value());
		int x(atoi(sprite_node->first_attribute("x")->value()));
		int y(atoi(sprite_node->first_attribute("y")->value()));
		int w(atoi(sprite_node->first_attribute("w")->value()));
		int h(atoi(sprite_node->first_attribute("h")->value()));
		
		atlas_builder->add_address(n, x, y, w, h);

		if (sprite_node->first_attribute("oX"))
		{
			int oX(atoi(sprite_node->first_attribute("oX")->value()));
			int oY(atoi(sprite_node->first_attribute("oY")->value()));
			int oW(atoi(sprite_node->first_attribute("oW")->value()));
			int oH(atoi(sprite_node->first_attribute("oH")->value()));

			atlas_builder->add_trim(oX, oY, oW, oH);
		}

		if (sprite_node->first_attribute("r"))
		{
			atlas_builder->is_rotated();
		}
	}

	return atlas_builder;
}
